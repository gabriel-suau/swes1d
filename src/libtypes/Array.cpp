#include "libtypes/Types.hpp"

namespace SWES1D
{

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

} // namespace SWES1D
