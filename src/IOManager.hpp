#ifndef SWES1D_IOMANAGER_HPP
#define SWES1D_IOMANAGER_HPP

#include "Types.hpp"
#include "Parameters.hpp"
#include "Topography.hpp"

#include <fstream>

namespace SWES1D
{

  struct IOManager {
    void saveParameters(Parameters const& params,
                        std::string const& filename) {
      std::ofstream file(filename);
    }

    template<typename TopographyType>
    void saveTopography(Parameters const& params,
                        TopographyType const& topo,
                        std::string const& filename) {
      std::ofstream file(filename);
      auto const xmin = params.xmin;
      auto const dx = params.dx;

      file << "#  x     z" << std::endl;
      for (int i = 0 ; i < params.nx ; i++) {
        auto const x = xmin + (i + 0.5) * dx;
        file << x << " " << topo.z[i] << std::endl;
      }

    }

    template<typename TopographyType>
    void saveSol(Parameters const& params,
                 TopographyType const& topo,
                 Vector<Array2D> const& U,
                 std::string const& filename) {
      std::ofstream file(filename);
      auto const xmin = params.xmin;
      auto const dx = params.dx;

      file << "#  x     h     h+z     q     u" << std::endl;
      for (int i = 0 ; i < params.nx ; i++) {
        auto const x = xmin + (i + 0.5) * dx;
        auto const [h,q] = U[i];
        file << x << " " << h << " " << h+topo.z[i] << " " << q << " " << ((h == 0) ? 0. : q / h) << std::endl;
      }

    }
  };

} // namespace SWES1D

#endif // SWES1D_IOMANAGER_HPP
