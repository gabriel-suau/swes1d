#ifndef SWES1D_MODEL_HPP
#define SWES1D_MODEL_HPP

#include "Types.hpp"
#include "libmodel/InfiltrationModel.hpp"
#include "libmodel/FrictionModel.hpp"
#include "libmodel/RainModel.hpp"

namespace SWES1D
{

  namespace Model
  {

    template<typename Infiltration, typename Friction, typename Rain>
    class FullModel {
    private:
      Infiltration inf;
      Friction fric;
      Rain rain;
    public:
      void foo();
    };

  } // namespace Model

} // namespace SWES1D

#endif // SWES1D_MODEL_HPP
