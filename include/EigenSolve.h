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

    //u given here is u_mu, thus, v_z = (-u[3]/u[0])
    double one_vzvz=1-pow(-u[3]/u[0], 2);
     if(one_vzvz<0){
	     std::cout << "Something is wrong with vz." << std::endl;
	     exit(EXIT_FAILURE);
     }else if(one_vzvz==0.0){
	     one_vzvz += constants::SMALL;
    }
    double l3=1./sqrt(one_vzvz);//l3 is the third component of l^mu = gamma_z (v_z, 0, 0, 1)
    double l0=l3*(-u[3]/u[0]);//0th component of l^mu
	    return T[0]*l0*l0 - 2.*T[3]*l0*l3 + T[9]*l3*l3; 
  }
  double Tmunu_Deltamunu(double e, EnergyMomentumTensor T){
    return T[0]-T[4]-T[7]-T[9] - e;
  }

  double uTu(EnergyMomentumTensor T, FourVector u){
	  double uTu = T[0]*u[0]*u[0] 
		  + 2.*T[1]*u[0]*u[1] + 2.*T[2]*u[0]*u[2] + 2.*T[3]*u[0]*u[3]
		  + 2.*T[5]*u[1]*u[2] + 2.*T[6]*u[1]*u[3] + 2.*T[8]*u[2]*u[3] 
		  + T[4]*u[1]*u[1] 
		  + T[7]*u[2]*u[2] 
		  + T[9]*u[3]*u[3];
          return uTu;
  }

  double PiMunu(int comp, FourVector u, EnergyMomentumTensor T, double e){
	  int mu=0;
	  int nu=0;
	  for(int i =0; i<5; i++){if(i!=0) u[i]*=-1.0;}//u_mu is given, so I want to make it u^mu
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
	  if(mu==nu) gmunu = (comp==0)? 1.0:-1.0;//g^munu = diag(+,-,-,-)
	  return T[comp] - (e-this->Tmunu_Deltamunu(e, T)/3.0)*u[mu]*u[nu] - this->Tmunu_Deltamunu(e, T) * gmunu/3.0;
  }

};
#endif
