#ifndef SWES1D_TIMESCHEME_HPP
#define SWES1D_TIMESCHEME_HPP

#include "Types.hpp"

namespace SWES1D
{

  namespace TimeScheme {

    template<typename TimeSchemeType>
    class TimeScheme {
    public:
      template<typename RHSType>
      static Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                                 Real time,
                                                 Real dt,
                                                 RHSType rhs) {
        return TimeSchemeType::computeOneTimeStep(U, time, dt, rhs);
      }
    }; // template class TimeScheme

    class Euler: public TimeScheme<Euler> {
    public:
      template<typename RHSType>
      static Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                                 Real time,
                                                 Real dt,
                                                 RHSType rhs) {
        U += dt * rhs(time, U);
        return U;
      }
    }; // class Euler

    class Heun: public TimeScheme<Heun> {
    public:
      template<typename RHSType>
      static Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                                 Real time,
                                                 Real dt,
                                                 RHSType rhs) {
        auto k1 = rhs(time, U);
        auto k2 = rhs(time + dt, U + dt * k1);
        U += dt * 0.5 * (k1 + k2);
        return U;
      }
    }; // class Heun

    class MidPoint: public TimeScheme<MidPoint> {
    public:
      template<typename RHSType>
      static Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                                 Real time,
                                                 Real dt,
                                                 RHSType rhs) {
        auto k1 = rhs(time, U);
        auto k2 = rhs(time + 0.5 * dt, U + 0.5 * dt * k1);
        U += dt * k2;
        return U;
      }
    }; // class MidPoint

  } // namespace TimeScheme

} // namespace SWES1D

#endif // SWES1D_TIMESCHEME_HPP
