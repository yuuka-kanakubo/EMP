#include "eostableclasses.h"

//functions in eosmatrix
//=====================
eosmatrix::eosmatrix(int NX, int NY)
{
			int i;

			nx = NX;
			ny = NY;

			value = new double [nx*ny];

			for(i = 0; i < nx*ny; ++i)
				value[i] = 0.0;
}


eosmatrix::~eosmatrix()
{
	delete [] value;
}

double eosmatrix::interpolate_linear(double *xtable, double xvalue, int npoints_x, double *ytable, double yvalue, int npoints_y)
{
	int iminus, jminus;
	int iplus, jplus;
	double ifrac, jfrac, iQ, jQ;
	double interpolatedvalue, Mld, Mrd, Mru, Mlu;
	double deltax, deltay;

	if(npoints_x > 0)
	{
		iminus = gsl_interp_bsearch(xtable, xvalue, 0, npoints_x);
		iplus = iminus + 1;
		deltax = xtable[iplus] - xtable[iminus];
		ifrac = xvalue - xtable[iminus];
		iQ = ifrac/deltax;
	}
	else 
	{
		iminus = 0;
		iplus = 0;
		iQ = 0;
	}

	jminus = gsl_interp_bsearch(ytable, yvalue, 0, npoints_y);
	jplus = jminus + 1;
	deltay = ytable[jplus] - ytable[jminus];
	jfrac = yvalue - ytable[jminus];
	jQ = jfrac/deltay;

	if(npoints_x == 0)
	{
		Mld = gv(iminus, jminus);
		Mlu = gv(iminus, jplus);
		interpolatedvalue = (1.0 - jQ)*Mld + jQ*Mlu;
	
		return interpolatedvalue;
	}

	Mld = gv(iminus, jminus);
	Mrd = gv(iplus, jminus);
	Mru = gv(iplus, jplus);
	Mlu = gv(iminus, jplus);

	interpolatedvalue = (1.0 - iQ)*(1.0 - jQ)*Mld + iQ*(1.0 - jQ)*Mrd + (1.0 - iQ)*jQ*Mlu + iQ*jQ*Mru;

	return interpolatedvalue;
}

double eosmatrix::interpolate_polynomial(double *xtable, double xvalue, int npoints_x, double *ytable, double yvalue, int npoints_y)
{
	int iminus, jminus;
	int iplus, jplus;
	double ifrac, iQ;
	double interpolatedvalue, Mld, Mrd, Mru, Mlu, Mruu, Mluu;
	double deltax;

	if(npoints_x > 0)
	{
		iminus = gsl_interp_bsearch(xtable, xvalue, 0, npoints_x);
		iplus = iminus + 1;
		deltax = xtable[iplus] - xtable[iminus];
		ifrac = xvalue - xtable[iminus];
		iQ = ifrac/deltax;
	}
	else 
	{
		iminus = 0;
		iplus = 0;
		iQ = 0.0;
	}

	jminus = gsl_interp_bsearch(ytable, yvalue, 0, npoints_y);
	jplus = jminus + 1;

	double valuel;

	if(npoints_x == 0)
	{
		Mld = gv(iminus, jminus);
		Mlu = gv(iminus, jplus);
		Mluu = gv(iminus, jplus+1);

// 		valuel = 0.0;
		double tmp1 = (yvalue - ytable[jminus+1])/(ytable[jminus] - ytable[jminus+2]);
		double tmp2 = (yvalue - ytable[jminus+2])/(ytable[jminus] - ytable[jminus+1]);
		double tmp3 = (yvalue - ytable[jminus])/(ytable[jminus+1] - ytable[jminus+2]);

		valuel = (Mld*tmp1 - Mlu*tmp3)*tmp2 + Mluu*tmp3*tmp1;

		return valuel;
	}

	double valuer, tmp;

	Mld = gv(iminus, jminus);
	Mrd = gv(iplus, jminus);
	Mru = gv(iplus, jplus);
	Mlu = gv(iminus, jplus);
	Mruu = gv(iplus, jplus+1);
	Mluu = gv(iminus, jplus+1);

	valuel = 0.0;
	tmp = (ytable[jminus] - ytable[jminus+1])*(ytable[jminus] - ytable[jminus+2]);
	if(fabs(tmp) > 0.0)
		valuel += Mld*(yvalue - ytable[jminus+1])*(yvalue - ytable[jminus+2])/tmp;
	tmp = (ytable[jminus+1] - ytable[jminus])*(ytable[jminus+1] - ytable[jminus+2]);
	if(fabs(tmp) > 0.0)
		valuel += Mlu*(yvalue - ytable[jminus])*(yvalue - ytable[jminus+2])/tmp;
	tmp = (ytable[jminus+2] - ytable[jminus])*(ytable[jminus+2] - ytable[jminus+1]);
	if(fabs(tmp) > 0.0)
		valuel += Mluu*(yvalue - ytable[jminus])*(yvalue - ytable[jminus+1])/tmp;

	valuer = 0.0;
	tmp = (ytable[jminus] - ytable[jminus+1])*(ytable[jminus] - ytable[jminus+2]);
	if(fabs(tmp) > 0.0)
		valuer += Mrd*(yvalue - ytable[jminus+1])*(yvalue - ytable[jminus+2])/tmp;
	tmp = (ytable[jminus+1] - ytable[jminus])*(ytable[jminus+1] - ytable[jminus+2]);
	if(fabs(tmp) > 0.0)
		valuer += Mru*(yvalue - ytable[jminus])*(yvalue - ytable[jminus+2])/tmp;
	tmp = (ytable[jminus+2] - ytable[jminus])*(ytable[jminus+2] - ytable[jminus+1]);
	if(fabs(tmp) > 0.0)
		valuer += Mruu*(yvalue - ytable[jminus])*(yvalue - ytable[jminus+1])/tmp;

	interpolatedvalue = (1.0 - iQ)*valuel + iQ*valuer;

	return interpolatedvalue;
}



//functions in EOS
//=====================
EOS::EOS(int NX, int NY)
:
ed(NX, NY),
rhoB(NX, NY),
pr(NX, NY),
T(NX, NY),
muB(NX, NY),
cs2(NX, NY),
muS(NX, NY),
x_Q(NX, NY),
x_H(NX, NY),
sd(NX, NY),
ed_s(NX, NY)
{
	int looped, looprhoB;
	FILE *buffer;

	e = new double[NY];
	b = new double[NX];
	s = new double[NY];

	//eosflag = config.geos();
	eosflag = 2;
	printf("EOS: %s\n", "eos/s95p-Tchem150.dat");
	buffer = fopen("eos/s95p-Tchem150.dat", "r");
	
	npoints_rhoB = cread.commentintread(buffer);
	npoints_ed = cread.commentintread(buffer);
 	printf("npoints_rhoB = %d\t npoints_ed = %d\n", npoints_rhoB, npoints_ed);

// 	My EoS
	if(eosflag == 1)
	{
		for(looprhoB = 0; looprhoB<npoints_rhoB; looprhoB++)
		{
			for(looped = 0; looped < npoints_ed; looped++)
			{
				rhoB.sv(looprhoB, looped, cread.commentfloatread(buffer));
				ed.sv(looprhoB, looped, cread.commentfloatread(buffer));

				pr.sv(looprhoB, looped, cread.commentfloatread(buffer));
				T.sv(looprhoB, looped, cread.commentfloatread(buffer));
				muB.sv(looprhoB, looped, cread.commentfloatread(buffer));
				muS.sv(looprhoB, looped, cread.commentfloatread(buffer));
				x_Q.sv(looprhoB, looped, cread.commentfloatread(buffer));
				x_H.sv(looprhoB, looped, cread.commentfloatread(buffer));
				sd.sv(looprhoB, looped, cread.commentfloatread(buffer));
			}
		}
	}

	// Pasi's EoS
	if(eosflag == 2)
	{
		looprhoB = 0;
		double tmp;
		for(looped = 0; looped < npoints_ed; looped++)
		{
			ed.sv(looprhoB, looped, cread.commentfloatread(buffer));
			pr.sv(looprhoB, looped, cread.commentfloatread(buffer));
			sd.sv(looprhoB, looped, cread.commentfloatread(buffer));
			rhoB.sv(looprhoB, looped, cread.commentfloatread(buffer));
			x_Q.sv(looprhoB, looped, cread.commentfloatread(buffer));
			T.sv(looprhoB, looped, cread.commentfloatread(buffer));
			muB.sv(looprhoB, looped, cread.commentfloatread(buffer));
			muS.sv(looprhoB, looped, cread.commentfloatread(buffer));
			x_H.sv(looprhoB, looped, 1.0 - x_Q.gv(looprhoB, looped));
			cs2.sv(looprhoB, looped, cread.commentfloatread(buffer));
			tmp = cread.commentfloatread(buffer);

// 		printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", ed[looprhoB][looped], pr[looprhoB][looped], sd[looprhoB][looped],
// 						rhoB[looprhoB][looped], x_Q[looprhoB][looped], T[looprhoB][looped],
// 						muB[looprhoB][looped], muS[looprhoB][looped], cs2[looprhoB][looped]);
		}
	}

	for(looprhoB = 0; looprhoB<npoints_rhoB; looprhoB++)
		b[looprhoB] = rhoB.gv(looprhoB, 0);

	for(looped = 0; looped < npoints_ed; looped++)
		e[looped] = ed.gv(0, looped);

	for(looped = 0; looped < npoints_ed; looped++)
		s[looped] = sd.gv(0, looped);

	fclose(buffer);
}


EOS::~EOS()
{
	delete [] e;
	delete [] b;
	delete [] s;
}
