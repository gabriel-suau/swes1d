#include <SWES1D.hpp>
#include <cmath>

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
  Array2D operator()(Real x) {
    return {2., 0.};
  }
};


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
    .setOutputParameters("output", -1);

  SolverType solver(&params);

  solver.solve();

  return EXIT_SUCCESS;
}
