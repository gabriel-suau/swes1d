#ifndef SWES1D_PARAMETERS_HPP
#define SWES1D_PARAMETERS_HPP

#include "Types.hpp"

namespace SWES1D
{

  struct Parameters {

    Parameters():
      xmin(0.), xmax(1.), length(xmax-xmin), nx(100), dx(length/nx),
      tf(5.), dt(0.005), cfl(0.5),
      leftBC(BoundaryConditionChoice::ImpDischarge),
      rightBC(BoundaryConditionChoice::ImpWaterHeight),
      outputDir("output"), saveFreq(50)
    {}

    Parameters& setSpaceVariables(Real xmin, Real xmax, int nx) {
      this->xmin = xmin;
      this->xmax = xmax;
      this->nx = nx;
      return *this;
    }

    Parameters& setTimeVariables(Real tf, Real dt, Real cfl) {
      this->tf = tf;
      this->dt = dt;
      this->cfl = cfl;
      return *this;
    }

    Parameters& setBoundaryConditions(BoundaryConditionChoice leftBC,
                               BoundaryConditionChoice rightBC) {
      this->leftBC = leftBC;
      this->rightBC = rightBC;
      return *this;
    }

    Parameters& setOutputParameters(std::string const& outputDir,
                             int saveFreq) {
      this->outputDir = outputDir;
      this->saveFreq = saveFreq;
      return *this;
    }

    void printParameters() {}

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

    /** Boundary condition choices */
    BoundaryConditionChoice leftBC;
    BoundaryConditionChoice rightBC;

    /** Outputs */
    std::string outputDir;
    int saveFreq;

  }; // struct Parameters

} // namespace SWES1D

#endif // SWES1D_PARAMETERS_HPP
