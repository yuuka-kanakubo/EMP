// written by h. niemi
#include<gsl/gsl_sf.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
#include "commentread.h"

#ifndef EOSTABLE_H 
#define EOSTABLE_H 
class eosmatrix
{
	public:
		eosmatrix(int NX, int NY);
		eosmatrix & operator = (const eosmatrix & other)
		{
			if (this != &other) // protect against invalid self-assignment
			{
				// allocate new memory and copy the elements
				int i;
				int nx = other.nx;
				int ny = other.ny;

				delete [] value;

				// assign the new memory to the object
				value = new double [nx*ny];

				for(i = 0; i < nx*ny; ++i)
					value[i] = other.value[i];

			}
			// by convention, always return *this
			return *this;
		}

		~eosmatrix();

		void sv(int i, int j, double v) { value[i*ny + j] = v;	}
		double gv(int i, int j) { return value[i*ny + j]; }
		double interpolate_linear(double *xtable, double xvalue, int npoints_x, double *ytable, double yvalue, int npoints_y);
		double interpolate_polynomial(double *xtable, double xvalue, int npoints_x, double *ytable, double yvalue, int npoints_y);

		int gNX()	{ return nx;	}
		int gNY()	{ return ny;	}

	private:
		double *value;
		int nx;
		int ny;
};
#endif




#ifndef EOS_H 
#define EOS_H 
class EOS
{
	public:
		EOS(int NX, int NY);
		~EOS();

// 		double p_en(double ed, double nd)	{	return pr.interpolate_polynomial(b, nd, npoints_rhoB, e, ed, npoints_ed);}
		double p_en(double ed, double nd)	{	return pr.interpolate_linear(b, nd, npoints_rhoB, e, ed, npoints_ed);	}
		double T_en(double ed, double nd)	{	return T.interpolate_linear(b, nd, npoints_rhoB, e, ed, npoints_ed);	}	
		double muB_en(double ed, double nd)	{	return muB.interpolate_linear(b, nd, npoints_rhoB, e, ed, npoints_ed);	}
		double muS_en(double ed, double nd)	{	return muS.interpolate_linear(b, nd, npoints_rhoB, e, ed, npoints_ed);	}
		double s_en(double ed, double nd)	{	return sd.interpolate_linear(b, nd, npoints_rhoB, e, ed, npoints_ed);	}
		double cs2_en(double ed, double nd)	{	return cs2.interpolate_linear(b, nd, npoints_rhoB, e, ed, npoints_ed);	}
		double e_sn(double sd, double nd)	{	return ed.interpolate_linear(b, nd, npoints_rhoB, s, sd, npoints_ed);	}

	private:
		eosmatrix ed;
		eosmatrix rhoB;
		eosmatrix pr;
		eosmatrix T;
		eosmatrix muB;
		eosmatrix cs2;
		eosmatrix muS;
		eosmatrix x_Q;
		eosmatrix x_H;
		eosmatrix sd;
		eosmatrix ed_s;

                commentread cread;
	
		double *e;
		double *b;
		double *s;
	
		int npoints_rhoB;
		int npoints_ed;
		int eosflag;
};

#endif
