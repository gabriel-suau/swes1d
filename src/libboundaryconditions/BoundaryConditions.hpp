#ifndef SWES1D_BOUNDARY_CONDITIONS_HPP
#define SWES1D_BOUNDARY_CONDITIONS_HPP

#include "libtypes/Types.hpp"

namespace SWES1D
{

  namespace BC
  {

    struct BCFuncType {
      Real operator()(Real t);
    };

    template<typename T>
    concept BoundaryConditionConcept = requires(T BC) {
      { BC.foo() };
    };

    template<typename BCType>
    struct BoundaryCondition {
      BCType BC;
      void foo();
    };

    template<typename BCFuncType>
    struct ImposedWaterHeight {
      BCFuncType BCFunc;
      void foo();
    };

    template<typename BCFuncType>
    struct ImposedDischarge {
      BCFuncType BCFunc;
      void foo();
    };

  } // namespace BoundaryConditions

} // namespace SWES1D

#endif // SWES1D_BOUNDARY_CONDITIONS_HPP
