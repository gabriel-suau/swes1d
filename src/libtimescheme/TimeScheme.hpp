#ifndef SWES1D_TIMESCHEME_HPP
#define SWES1D_TIMESCHEME_HPP

#include "libtypes/Types.hpp"

namespace SWES1D
{

  namespace TimeScheme {

    struct RHSType {
      Vector<Array2D> operator()(Real time, Vector<Array2D>& U);
    };

    template<typename T>
    concept TimeSchemeConcept = requires (T scheme, Real time, Vector<Array2D>& U, RHSType rhs) {
      { scheme.computeOneTimeStep(U, time, rhs) } -> std::same_as<Vector<Array2D>&>;
    };

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
                                          RHSType rhs);
    }; // class Euler

    class Heun: public TimeScheme<Heun> {
    public:
      explicit Heun(Real dt): TimeScheme<Heun>(dt) {}
      template<typename RHSType>
      Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                          Real time,
                                          RHSType rhs);
    }; // class Heun

  } // namespace TimeScheme

} // namespace SWES1D

#endif // SWES1D_TIMESCHEME_HPP
