#ifndef SWES1D_TIMESCHEME_HPP
#define SWES1D_TIMESCHEME_HPP

#include "libtypes/Types.hpp"

namespace SWES1D
{

  template<typename T>
  concept RHSConcept = requires(T rhs, Real t, Vector<Array2D> const& U) {
    { rhs(t,U) } -> std::same_as<Vector<Array2D>>;
  };

  template<typename TimeSchemeType>
  class TimeScheme {

  protected:
    Real dt_;

  public:
    explicit TimeScheme(Real dt):
      dt_(dt) {}

    template<RHSConcept RHSFunc>
    Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                        Real time,
                                        RHSFunc rhs) {
      return static_cast<TimeSchemeType*>
        (this)->computeOneTimeStep(U, time, rhs);
    }

  }; // template class TimeScheme

  class Euler: public TimeScheme<Euler> {
    explicit Euler(Real t): TimeScheme<Euler>(t) {}

    template<RHSConcept RHSFunc>
    Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                        Real time,
                                        RHSFunc rhs);

  }; // class Euler

  class Heun: public TimeScheme<Heun> {
    explicit Heun(Real t): TimeScheme<Heun>(t) {}

    template<RHSConcept RHSFunc>
    Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                        Real time,
                                        RHSFunc rhs);

  }; // class Heun

} // namespace SWES1D

#endif // SWES1D_TIMESCHEME_HPP
