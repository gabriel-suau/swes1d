#include <SWES1D.hpp>
#include <cmath>

using namespace SWES1D;


/** Define your left boundary condition as a function of time
 * You have to give the water height and the discharge, even if
 * you only want to impose one of them.
 */
struct leftBCFunc {
  Array2D operator()(Real t) { return {0.1, 0.}; }
};


/** Define your right boundary condition as a function of time
 * You have to give the water height and the discharge, even if
 * you only want to impose one of them.
 */
struct rightBCFunc {
  Array2D operator()(Real t) { return {0.1, 0.}; }
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
    return {std::max(0.1, bump(x)), 0.};
  }
};


/** Exact solution and L2 error computation */
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
  using LeftBCType = BoundaryCondition::ImposedWaterHeight<leftBCFunc>;
  using RightBCType = BoundaryCondition::ImposedDischarge<rightBCFunc>;
  auto leftBCChoice = BoundaryConditionChoice::ImpWaterHeight;
  auto rightBCChoice = BoundaryConditionChoice::ImpDischarge;

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

  auto Ue = computeExactSol(params);

  auto[herr,qerr] = computeL2Error(params, U, Ue);

  return EXIT_SUCCESS;
}

/** Auxiliary function definitions */

Vector<Array2D> computeExactSol(Parameters const& params) {
  auto const nx = params.nx;
  Vector<Array2D> Ue(nx, {0.1, 0.});
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
