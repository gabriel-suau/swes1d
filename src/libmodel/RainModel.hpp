#ifndef SWES1D_RAIN_MODEL_HPP
#define SWES1D_RAIN_MODEL_HPP

#include "libtypes/Types.hpp"

namespace SWES1D
{

  namespace Model
  {

    template<typename RainType>
    class Rain {
    public:
      void foo();
    };

    class NoRain: public Rain<NoRain> {
    public:
      void foo();      
    };

    class ConstantRain: public Rain<ConstantRain> {
    public:
      void foo();      
    };

    class MeasuredRain: public Rain<MeasuredRain> {
    public:
      void foo();      
    };

  } // namespace Model

} // namespace SWES1D

#endif // SWES1D_RAIN_MODEL_HPP
