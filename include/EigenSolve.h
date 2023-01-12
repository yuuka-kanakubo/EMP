#ifndef EigenSolve_H
#define EigenSolve_H

#include "Container.h"
#include "energymomentumtensor.h"
#include <memory>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_poly.h>

class EigenSolve{

  public:

  EigenSolve(std::shared_ptr<Container>& ct_in);
  ~EigenSolve();


  private:
  std::shared_ptr<Container>& ct;
  void Solve();


};
#endif
