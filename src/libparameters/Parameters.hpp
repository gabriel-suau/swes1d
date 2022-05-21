#ifndef SWES1D_PARAMETERS_H
#define SWES1D_PARAMETERS_H

#include "Types.hpp"
#include <string>

namespace SWES1D
{

  struct Parameters {

    Parameters(std::string const& filename);

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
    BoundaryCondition leftBC;
    BoundaryCondition rightBC;
    Real impLeftH;
    Real impLeftQ;
    Real impRightH;
    Real impRightQ;

    /** Numerical flux */
    NumericalFlux flux;

    /** Spatial order */
    SpaceOrder ord;

    /** Flux/Slope limiter */
    Limiter lim;

    /** Time scheme */
    TimeScheme tscheme;

    /** Outputs */
    std::string outputDir;
    int saveFreq;

  }; // struct Parameters

} // namespace SWES1D

#endif // SWES1D_PARAMETERS_H
