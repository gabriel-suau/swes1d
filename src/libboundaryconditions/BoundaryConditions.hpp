#ifndef SWES1D_BOUNDARY_CONDITIONS_HPP
#define SWES1D_BOUNDARY_CONDITIONS_HPP

#include "Types.hpp"

namespace SWES1D
{

  namespace BoundaryCondition
  {

    // struct BCFuncType {
    //   Real operator()(Real t);
    // };

    // template<typename T>
    // concept BoundaryConditionConcept = requires(T BC) {
    //   { BC.foo() };
    // };

    template<typename BCType>
    struct BoundaryCondition {
      void foo();
    };

    template<typename BCFuncType>
    struct ImposedWaterHeight: public BoundaryCondition<ImposedWaterHeight<BCFuncType>> {
      BCFuncType BCFunc;
      void foo();
    };

    template<typename BCFuncType>
    struct ImposedDischarge: public BoundaryCondition<ImposedDischarge<BCFuncType>> {
      BCFuncType BCFunc;
      void foo();
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
