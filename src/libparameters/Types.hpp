#ifndef SWES1D_NUMERIC_TYPES_H
#define SWES1D_NUMERIC_TYPES_H

#include <cstdlib>
#include <cmath>

namespace SWES1D
{

  using Real = double;
  using Index = unsigned int;

  constexpr Real grav = 9.81;

  enum class NumericalFlux {
    Rusanov,
    HLL,
    Kinetic,
    VFRoe
  };

  enum class SpaceOrder {
    One = 1,
    Two = 2
  };

  enum class TimeScheme {
    Euler,
    Heun,
  };

  enum class Limiter {
    MinMod,
    VanLeer
  };

  enum class BoundaryCondition {
    ImpWaterHeight,
    ImpDischarge,
    Wall,
    Periodic
  };

} // namespace SWES1D

#endif // SWES1D_NUMERIC_TYPES_H
