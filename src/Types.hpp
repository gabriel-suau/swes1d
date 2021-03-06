/**
 * \file Types.hpp
 * \author Gabriel Suau <gabrielsuau2@gmail.com> (2022)
 * \version 1.0.0
 * \date 2022-05-29
 *
 * \brief Definition of the main types and constants
 *
 * \copyright SWES1D : Monodimensional Shallow Water Equations Solvers
 * Copyright (C) 2022 Gabriel Suau
 *
 * \copyright This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * \copyright This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * \copyright You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SWES1D_TYPES_HPP
#define SWES1D_TYPES_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <concepts>
// #include <optional>
#include <string>
#include <tuple>
#include <vector>

namespace SWES1D
{

  /** Define basic types*/
  using Real = double;
  using Index = unsigned int;
  using Array2D = std::array<Real, 2>;
  template<typename T>
  using Vector = std::vector<T>;

  /** Define constants*/
  constexpr Real grav = 9.81;
  constexpr Real halfGrav = grav / 2;
  constexpr Real heps = 1.e-12;
  constexpr Real epsilon = 1.e-13;

  enum class NumericalFluxChoice {
    Rusanov,
    HLL,
    HLLE,
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

  enum class OutputMode: bool {
    Save = true,
    NoSave = false
  };

  enum PrintLevel {
    Low    = 1,
    Medium = 2,
    High   = 3
  };

  // Array operators

  Array2D& operator+=(Array2D& x, Array2D y) {
    x[0] += y[0];
    x[1] += y[1];
    return x;
  }

  Array2D& operator-=(Array2D& x, Array2D y) {
    x[0] -= y[0];
    x[1] -= y[1];
    return x;
  }

  Array2D& operator*=(Array2D& x, Real c) {
    x[0] *= c;
    x[1] *= c;
    return x;
  }

  Array2D operator-(Array2D x) {
    return {-x[0], -x[1]};
  };

  Array2D operator+(Array2D x, Array2D y) {
    return {x[0] + y[0], x[1] + y[1]};
  }

  Array2D operator-(Array2D x, Array2D y) {
    return {x[0] - y[0], x[1] - y[1]};
  }

  Array2D operator*(Array2D x, Real c) {
    return {x[0] * c, x[1] * c};
  }

  Array2D operator*(Real c, Array2D x) {
    return x * c;
  }

  // Vector operators
  Vector<Array2D>& operator+=(Vector<Array2D>& x, Vector<Array2D> const& y) {
    assert(x.size() == y.size());
    for (std::size_t i = 0 ; i < x.size() ; i++) {
      x[i] += y[i];
    }
    return x;
  }

  Vector<Array2D>& operator-=(Vector<Array2D>& x, Vector<Array2D> const& y) {
    assert(x.size() == y.size());
    for (std::size_t i = 0 ; i < x.size() ; i++) {
      x[i] -= y[i];
    }
    return x;
  }

  Vector<Array2D>& operator*=(Vector<Array2D>& x, Real c) {
    for (auto &e : x)
      e *= c;
    return x;
  }

  Vector<Array2D> operator-(Vector<Array2D> const& x) {
    Vector<Array2D> res(x.size());
    for (std::size_t i = 0 ; i < x.size() ; i++)
      res[i] = -x[i];
    return res;
  };

  Vector<Array2D> operator+(Vector<Array2D> const& x, Vector<Array2D> const& y) {
    assert(x.size() == y.size());
    Vector<Array2D> res = x;
    res+= y;
    return res;
  }

  Vector<Array2D> operator-(Vector<Array2D> const& x, Vector<Array2D> const & y) {
    assert(x.size() == y.size());    
    Vector<Array2D> res = x;
    res-= y;
    return res;
  }

  Vector<Array2D> operator*(Vector<Array2D> const& x, Real c) {
    Vector<Array2D> res = x;
    res *= c;
    return res;
  }

  Vector<Array2D> operator*(Real c, Vector<Array2D> const& x) {
    return x * c;
  }

}// namespace SWES1D

#endif // SWES1D_TYPES_HPP
