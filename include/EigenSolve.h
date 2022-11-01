#ifndef EigenSolve_H
#define EigenSolve_H

#include "Container.h"
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

enum error_codes { decomp_ok=0, decomp_failed=2};
  void get_energy_flow_from_Tmunu(double Tmunu_raised[4][4], double tau_in_GeV, double * energy_density, double flow[], enum error_codes * error_code);
  bool parse_eigensystem(double tau_in_GeV, double im_tolerance, gsl_matrix * matrix_orig, gsl_vector_complex * eigenvalues, gsl_matrix_complex * eigenvectors, double * energy, double flow[]);

};
#endif
