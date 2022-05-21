#ifndef SWES1D_PARAMETERS_HPP
#define SWES1D_PARAMETERS_HPP

#include "libtypes/Types.hpp"
#include <string>

namespace SWES1D
{

  struct Parameters {

    explicit Parameters(std::string const& filename);

    void readParameters();

    void printParameters();

    /** Name of the parameters file */
    std::string filename;

    /** Space variables */
    Real xmin;
    Real xmax;
    Real length;
    int nx;
    Real dx;

    /** Time variables */
    Real tf;
    Real dt;
    Real cfl;

    /** Boundary conditions */
    BoundaryConditionChoice leftBC;
    BoundaryConditionChoice rightBC;
    Real impLeftH;
    Real impLeftQ;
    Real impRightH;
    Real impRightQ;

    /** Numerical flux */
    NumericalFluxChoice flux;

    /** Spatial order */
    SpaceOrderChoice ord;

    /** Flux/Slope limiter */
    LimiterChoice lim;

    /** Time scheme */
    TimeSchemeChoice tscheme;

    /** Outputs */
    std::string outputDir;
    int saveFreq;

  }; // struct Parameters

} // namespace SWES1D

#endif // SWES1D_PARAMETERS_HPP
