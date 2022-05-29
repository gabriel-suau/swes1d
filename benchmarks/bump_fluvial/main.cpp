#include <SWES1D.hpp>
#include <cmath>
#include <tuple>
#include <complex>

using namespace SWES1D;


/** Define your left boundary condition as a function of time
 * You have to give the water height and the discharge, even if
 * you only want to impose one of them.
 */
struct leftBCFunc {
  Array2D operator()(Real t) { return {2., 4.42}; }
};


/** Define your right boundary condition as a function of time
 * You have to give the water height and the discharge, even if
 * you only want to impose one of them.
 */
struct rightBCFunc {
  Array2D operator()(Real t) { return {2., 4.42}; }
};


/** Define your topography as a function of the space */
struct BumpFunc {
  Real operator()(Real x) {
    if (8. < x && x < 12.)
      return (0.2 - 0.05 * std::pow(x - 10, 2));
    else
      return 0;
  }
};


/** Define your initial condition as a function of the space
 * NOTE : the initial condition is on {(h+z), q}
 */
struct InitFunc {
  BumpFunc bump;
  Array2D operator()(Real x) {
    return {std::max(2., bump(x)), 0.};
  }
};

/** Auxiliary function declarations */
template<typename BumpFunc>
Vector<Array2D> computeExactSol(Parameters const& params);
Array2D computeL2Error(Parameters const& params, Vector<Array2D> const& U, Vector<Array2D> const& Ue);


/** There we go */
int main(int argc, char** argv)
{

  /** Declare the model Type (Infiltration, Friction and Rain laws) */
  using ModelType = Model::FullModel<Model::NoInfiltration,
                                     Model::NoFriction,
                                     Model::NoRain>;

  /** Declare the initial condition type */
  using InitialConditionType = InitialCondition::Generated<InitFunc>;

  /** Declare the topography type */
  using TopographyType = Topography::Generated<BumpFunc>;

  /** Declare the numerical flux type (Rusanov, HLL, HLLE, Kinetic)*/
  using FluxType = Flux::Rusanov;

  /** Declare the time integrator */
  using TimeSchemeType = TimeScheme::Euler;

  /** Declare the left and right boundary conditions */
  using LeftBCType = BoundaryCondition::ImposedDischarge<leftBCFunc>;
  using RightBCType = BoundaryCondition::ImposedWaterHeight<rightBCFunc>;
  auto leftBCChoice = BoundaryConditionChoice::ImpDischarge;
  auto rightBCChoice = BoundaryConditionChoice::ImpWaterHeight;

  /** Declare the solver type. The templates arguments are all of the above. */
  using SolverType = Solver<ModelType,
                            InitialConditionType,
                            TopographyType,
                            FluxType,
                            TimeSchemeType,
                            LeftBCType,
                            RightBCType>;

  Parameters params;
  params.setSpaceVariables(0., 25., 500)
    .setTimeVariables(15., 0.005, 0.5)
    .setBoundaryConditions(leftBCChoice, rightBCChoice)
    .setOutputParameters(OutputMode::NoSave, "output", 0)
    .setPrintLevel(PrintLevel::Low);

  SolverType solver(&params);

  auto [U,tf] = solver.solve();

  auto Ue = computeExactSol<BumpFunc>(params);

  auto[herr,qerr] = computeL2Error(params, U, Ue);

  return EXIT_SUCCESS;
}

/** Auxiliary function definitions */

auto computeCardanPQ(Real a, Real b, Real c, Real d) {
  auto const p = -b * b / (3.0 * a * a) + c / a;
  auto const q = b / (27.0 * a) * (2.0 * b * b / (a * a) - 9.0 * c / a) + d / a;
  return std::tuple(p,q);
}

auto computeCardanDet(Real p, Real q) {
  return q * q + 4.0 / 27.0 * p * p * p;
}

auto computeABCD(Real qin, Real hout, Real z, Real zend) {
  auto const a = 1.;
  auto const b = - (qin * qin / (2 * grav * hout * hout) + hout * (z - zend));
  auto const c = 0.;
  auto const d = qin * qin / (2. * grav);
  return std::tuple(a,b,c,d);
}

auto computeHeight(Real p, Real q, Real a, Real b, Real hnear, Real hmax) {
  auto const det = computeCardanDet(p, q);
  Real h;
  Real eps = 1.e-13;

  if (det > eps) {
    auto const h1 = 0.5 * (-q + std::sqrt(det));
    auto const h2 = 0.5 * (-q - std::sqrt(det));
    h = h1 / std::abs(h1) * std::pow(std::abs(h1), 1./3)
      + h2 / std::abs(h2) * std::pow(std::abs(h2), 1./3)
      - b / (3 * a);
  }
  else if (std::abs(det) < eps) {
    auto const l1 = 3 * q / p;
    auto const l2 = -3 * q / (2 * p);
    h = (l1 > 0) ? (l1 - b / (3 * a)) : (l2 - b / (3 * a));
  }
  else {
    std::complex<Real> const u3 = {- 0.5 * q, 0.5 * std::sqrt(std::abs(det))};
    std::complex<Real> const u = std::pow(u3, 1./3);
    std::complex<Real> const j = {- 0.5, 0.5 * std::sqrt(3.)};
    auto const l1 = 2 * std::real(u) - b / (3 * a);
    auto const l2 = 2 * std::real(j*u) - b / (3 * a);
    auto const l3 = 2 * std::real(j*j*u) - b / (3 * a);
    auto const a1 = std::abs(l1 - hnear);
    auto const a2 = std::abs(l2 - hnear);
    auto const a3 = std::abs(l3 - hnear);
    auto const m = std::min(std::min(a1, a2), a3);
    if (m == a1) h = l1;
    else if (m == a2) h = l2;
    else h = l3;
  }
  return h;
}

template<typename BumpFunc>
Vector<Array2D> computeExactSol(Parameters const& params) {
  auto const nx = params.nx;
  auto const qin = 4.42;
  auto const hout = 2.;
  auto const hmax = 3.;

  Vector<Array2D> Ue(nx, {hout, qin});

  // (Re-)build the topography
  auto const xmin = params.xmin;
  auto const dx = params.dx;
  BumpFunc f;
  Vector<Real> topo(nx, 0.);
  for (int i = 0 ; i < nx ; i++) {
    Real x = xmin + (i + 0.5) * dx;
    topo[i] = f(x);
  }

  // Compute the exact solution
  auto const zend = topo[nx - 1];
  for (int i = nx - 1 ; i >= 0 ; i--) {
    auto const z = topo[i];
    auto const [a,b,c,d] = computeABCD(qin, hout, z, zend);
    auto const [p,q] = computeCardanPQ(a, b, c, d);
    auto const hnear = (i == nx - 1) ? hout : Ue[i+1][0];
    Ue[i][0] = computeHeight(p, q, a, b, hnear, hmax);
  }
  return Ue;
}

Array2D computeL2Error(Parameters const& params, Vector<Array2D> const& U, Vector<Array2D> const& Ue) {
  Real herr = 0.;
  Real qerr = 0.;
  auto dx = params.dx;
  assert( U.size() == Ue.size() );
  for (int i = 0 ; i < U.size() ; i++) {
    herr += std::pow(U[i][0] - Ue[i][0], 2);
    qerr += std::pow(U[i][1] - Ue[i][1], 2);
  }
  herr = std::sqrt(dx * herr);
  qerr = std::sqrt(dx * qerr);
  return {herr, qerr};
}
