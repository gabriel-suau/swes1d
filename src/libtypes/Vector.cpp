#include "libtypes/Types.hpp"

namespace SWES1D
{

  template<typename T>
  Vector<T>& operator+=(Vector<T>& x, Vector<T> const& y) {
    assert(x.size() == y.size());
    for (std::size_t i = 0 ; i < x.size() ; i++) {
      x[i] += y[i];
    }
    return x;
  }

  template<typename T>
  Vector<T>& operator-=(Vector<T>& x, Vector<T> const& y) {
    assert(x.size() == y.size());
    for (std::size_t i = 0 ; i < x.size() ; i++) {
      x[i] -= y[i];
    }
    return x;
  }

  template<typename T>
  Vector<T>& operator*=(Vector<T>& x, Real c) {
    for (auto &e : x)
      e *= c;
    return x;
  }

  template<typename T>
  Vector<T> operator+(Vector<T> const& x, Vector<T> const& y) {
    assert(x.size() == y.size());
    Vector<T> res = x;
    res+= y;
    return res;
  }

  template<typename T>
  Vector<T> operator-(Vector<T> const& x, Vector<T> const & y) {
    assert(x.size() == y.size());    
    Vector<T> res = x;
    res-= y;
    return res;
  }

  template<typename T>
  Vector<T> operator*(Vector<T> const& x, Real c) {
    Vector<T> res = x;
    res *= c;
    return res;
  }

  template<typename T>
  Vector<T> operator*(Real c, Vector<T> const& x) {
    return x * c;
  }


} // namespace SWES1D
