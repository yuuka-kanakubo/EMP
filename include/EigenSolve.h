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

  EigenSolve(std::shared_ptr<Container>& ct_in, Settings::Options& options);
  ~EigenSolve();


  private:
  std::shared_ptr<Container>& ct;
  Settings::Options& options;
  void Solve();
  double Tmunu_lmulnu(FourVector u, EnergyMomentumTensor T){
    double l0=1./(1-pow(u[3]/u[0], 2));//0th component of l^mu(contravariant vector) 
    double l3=-1.*l0*u[3]/u[0];//0th component of l^mu (contravariant vector)
    return T[0]*l0*l0 - 2.*T[3]*l0*l3 + T[9]*l3*l3; 
  }
  double Tmunu_Deltamunu(double e, EnergyMomentumTensor T){
    return T[0]-T[4]-T[7]-T[9] - e;
  }

  double PiMunu(int comp, FourVector u, EnergyMomentumTensor T, double e){
	  int mu=0;
	  int nu=0;
	  for(int i =0; i<5; i++){if(i!=0) u[i]*=-1.0;}
	  if (comp<4){
		  nu=comp;
	  }else if(comp<7){
		  mu=1;
		  nu=comp-3;
	  }else if(comp<9){
		  mu=2;
		  nu=comp-5;
	  }else{
		  mu=3; nu=3;
	  }
	  double gmunu=0.0;
	  if(mu==nu) gmunu = (comp==0)? 1.0:-1.0;
	  return T[comp] - (e-this->Tmunu_Deltamunu(e, T)/3.0)*u[mu]*u[nu] - this->Tmunu_Deltamunu(e, T) * gmunu/3.0;
  }

};
#endif
