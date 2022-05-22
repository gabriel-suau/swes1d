#ifndef SWES1D_INFILTRATION_MODEL_HPP
#define SWES1D_INFILTRATION_MODEL_HPP

#include "libtypes/Types.hpp"

namespace SWES1D
{

  namespace Model
  {

    template<typename Infiltrationtype>
    class Infiltration {
    public:
      void foo() {};
    };

    class NoInfiltration: public Infiltration<NoInfiltration> {
    public:
      void foo() {};
    };

    class GreenAmpt: public Infiltration<GreenAmpt> {
    public:
      void foo() {};
    };

  } // namespace Model

} // namespace SWES1D

#endif // SWES1D_INFILTRATION_MODEL_HPP
