#ifndef SWES1D_MODEL_HPP
#define SWES1D_MODEL_HPP

#include "libtypes/Types.hpp"
#include "libmodel/InfiltrationModel.hpp"
#include "libmodel/FrictionModel.hpp"
#include "libmodel/RainModel.hpp"

namespace SWES1D
{

  namespace Model
  {

    template<typename M>
    concept ModelConcept = requires(M a) {
      { a.foo() };
    };

    template<typename Infiltration, typename Friction, typename Rain>
    class FullModel {
    public:
      void foo();
    };

  } // namespace Model

} // namespace SWES1D

#endif // SWES1D_MODEL_HPP
