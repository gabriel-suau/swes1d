#ifndef SWES1D_TIMESCHEME_HPP
#define SWES1D_TIMESCHEME_HPP

#include "Types.hpp"

namespace SWES1D
{

  namespace TimeScheme {

    template<typename TimeSchemeType>
    class TimeScheme {

    protected:
      Real dt_;

    public:
      explicit TimeScheme(Real dt):
        dt_(dt) {}

      template<typename RHSType>
      Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                          Real time,
                                          RHSType rhs) {
        return static_cast<TimeSchemeType*>
          (this)->computeOneTimeStep(U, time, rhs);
      }
    }; // template class TimeScheme

    class Euler: public TimeScheme<Euler> {
    public:
      explicit Euler(Real dt): TimeScheme<Euler>(dt) {}
      template<typename RHSType>
      Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                          Real time,
                                          RHSType rhs) {
        U += dt_ * rhs(time, U);
        return U;
      }
    }; // class Euler

    class Heun: public TimeScheme<Heun> {
    public:
      explicit Heun(Real dt): TimeScheme<Heun>(dt) {}
      template<typename RHSType>
      Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                          Real time,
                                          RHSType rhs) {
        auto k1 = rhs(time, U);
        auto k2 = rhs(time + dt_, U + dt_ * k1);
        U += dt_ * 0.5 * (k1 + k2);
        return U;
      }
    }; // class Heun

    class MidPoint: public TimeScheme<MidPoint> {
    public:
      explicit MidPoint(Real dt): TimeScheme<MidPoint>(dt) {}
      template<typename RHSType>
      Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                          Real time,
                                          RHSType rhs) {
        auto k1 = rhs(time, U);
        auto k2 = rhs(time + 0.5 * dt_, U + 0.5 * dt_ * k1);
        U += dt_ * k2;
        return U;
      }
    }; // class MidPoint

  } // namespace TimeScheme

} // namespace SWES1D

#endif // SWES1D_TIMESCHEME_HPP
