#ifndef SWES1D_BOUNDARY_CONDITIONS_HPP
#define SWES1D_BOUNDARY_CONDITIONS_HPP

#include "Types.hpp"

namespace SWES1D
{

  namespace BoundaryCondition
  {

    template<typename BCType>
    struct BoundaryCondition {
      void foo();
    };

    template<typename BCFuncType>
    struct ImposedWaterHeight: public BoundaryCondition<ImposedWaterHeight<BCFuncType>> {
      static Array2D computeBC(Real t, Array2D const& sol);
    private:
      static BCFuncType func;
    };

    template<typename BCFuncType>
    struct ImposedDischarge: public BoundaryCondition<ImposedDischarge<BCFuncType>> {
      Array2D computeBC(Real t, Array2D const& sol);
    private:
      static BCFuncType func;
    };

    struct Wall: public BoundaryCondition<Wall> {
      void foo();
    };

    struct Periodic: public BoundaryCondition<Periodic> {
      void foo();
    };

  } // namespace BoundaryCondition

} // namespace SWES1D

#endif // SWES1D_BOUNDARY_CONDITIONS_HPP
