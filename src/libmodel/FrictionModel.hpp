#ifndef SWES1D_FRICTION_MODEL_HPP
#define SWES1D_FRICTION_MODEL_HPP

#include "Types.hpp"

namespace SWES1D
{

  namespace Model
  {

    template<typename FrictionType>
    class Friction {
    protected:
      /** Constant friction coeff */
      Real c_;
    public:
      explicit Friction(Real c): c_(c) {}
      void foo();
    };

    class NoFriction: public Friction<NoFriction> {
      NoFriction(): Friction(0.) {}
      void foo();
    };

    class Laminar: public Friction<Laminar> {
      explicit Laminar(Real c): Friction(c) {}
      void foo();
    };

    class Manning: public Friction<Manning> {
      explicit Manning(Real c): Friction(c) {}
      void foo();
    };

    class DarcyWeisbach: public Friction<DarcyWeisbach> {
      explicit DarcyWeisbach(Real c): Friction(c) {}
      void foo();
    };

  } // namespace Model

} // namespace SWES1D

#endif // SWES1D_FRICTION_MODEL_HPP
