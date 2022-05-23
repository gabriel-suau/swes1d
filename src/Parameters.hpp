#ifndef SWES1D_PARAMETERS_HPP
#define SWES1D_PARAMETERS_HPP

#include "Types.hpp"

namespace SWES1D
{

  struct Parameters {

    void setSpaceVariables(Real xmin, Real xmax, int nx);

    void setTimeVariables(Real tf, Real dt, Real cfl = -1.);

    void setBoundaryConditions(BoundaryConditionChoice leftBC,
                               Real impLeftH,
                               Real impLeftQ,
                               BoundaryConditionChoice rightBC,
                               Real impRightH,
                               Real impRightQ);

    void setOutputParameters(std::string const& outputDir,
                             int saveFreq);
    void printParameters();

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

    /** Outputs */
    std::string outputDir;
    int saveFreq;

  }; // struct Parameters

} // namespace SWES1D

#endif // SWES1D_PARAMETERS_HPP
