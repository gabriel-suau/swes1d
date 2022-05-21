#ifndef SWES1D_TYPES_HPP
#define SWES1D_TYPES_HPP

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cmath>
#include <concepts>
// #include <optional>
#include <string>
#include <vector>

namespace SWES1D
{

  /** Define basic types*/
  using Real = double;
  using Index = unsigned int;
  using Array2D = std::array<Real, 2>;
  using Vector = std::vector<Array2D>;

  /** Define constants*/
  constexpr Real grav = 9.81;
  constexpr Real halfGrav = grav / 2;
  constexpr Real heps = 1.e-12;
  constexpr Real epsilon = 1.e-13;

  enum class NumericalFluxChoice {
    Rusanov,
    HLL,
    Kinetic,
    VFRoe
  };

  enum class SpaceOrderChoice {
    One = 1,
    Two = 2
  };

  enum class TimeSchemeChoice {
    Euler,
    Heun,
  };

  enum class LimiterChoice {
    MinMod,
    VanLeer
  };

  enum class BoundaryConditionChoice {
    ImpWaterHeight,
    ImpDischarge,
    Wall,
    Periodic
  };

  // Array operators
  Array2D& operator+=(Array2D& x, Array2D y);
  Array2D& operator-=(Array2D& x, Array2D y);
  Array2D& operator*=(Array2D& x, Real c);
  Array2D operator+(Array2D x, Array2D y);
  Array2D operator-(Array2D x, Array2D y);
  Array2D operator*(Array2D x, Real c);
  Array2D operator*(Real c, Array2D x);

}// namespace SWES1D

#endif // SWES1D_TYPES_HPP
