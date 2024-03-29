// -*- mode:c++ -*-
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <complex>
#include <math.h>
#include "Constants.h"
#include "Util_func.h"
#include "Container.h"
#include "Message.h"
#include "LogSettings.h"
#include "Settings.h"
#include "InfoHist.h"
#include "Write.h"

using namespace std;


Write::Write(shared_ptr<Message> ms_in, Settings::Options options_in, shared_ptr<InfoHist> infohist_in, shared_ptr<Util_func> uf_in, shared_ptr<Container> ct_in):ms(ms_in), options(options_in), infohist(infohist_in), uf(uf_in), ct(ct_in){};
Write::~Write(){};


		int Write::getMapEdgeX(const double maxval){
			int n=(int)((maxval/this->infohist->d_x)+(std::fabs(constants::x_min)/this->infohist->d_x));
			return n;
		}
		int Write::getMapEdgeY(const double maxval){
			int n=(int)((maxval/this->infohist->d_y)+(std::fabs(constants::y_min)/this->infohist->d_y));
			return n;
		}


bool Write::write(const std::string& fname){
	ct->max_nx+=constants::margin;
	if(!options.get_flag_TWODMAP_zx()){
		cout <<"write xy" << endl;
		return this->write_xymap(fname);
	}else{
		cout <<"write zx" << endl;
		return this->write_zxmap(fname);
	}

}



bool Write::write_xymap(const std::string& fname){
	ofstream ofs;
	ofs.open((fname+"/"+constants::default_out_fname).c_str());
	if(!ofs){ms->open(fname+"/"+constants::default_out_fname); return false;}

ofs << "# x, y,  tt, tx, ty, tz, xx, xy, xz, yy, yz, zz,  eLOCAL, Px, Py, Pz, pixy, P_L, P_T" << std::endl;
ofs << "#       <======================================>  <=================================>" << std::endl;
ofs << "#             Tmunu components before boost,        at LOCAL " << std::endl;
for(int i=0; i<constants::x_cell_capa; ++i){
	for(int j=0; j<constants::y_cell_capa; ++j){

		double xaxis=0.;
		double yaxis=0.;
		if (constants::MODE.find("2dmap")!=string::npos) {
			xaxis=this->get_xcoordinate(i);
			yaxis=this->get_ycoordinate(j);
		}
		//ct->Hist2D_x[i][j];
		//ct->Hist2D_y[i][j];
		ofs << setw(16) << fixed << setprecision(8) << xaxis << "  "
			<< setw(16) << yaxis << "     "
			<< setw(16) << ct->Hist2DMultiComp[i][j].tt << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].tx << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].ty << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].tz << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xx << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xy << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xz << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].yy << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].yz << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].zz << "    " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].pixx << "    " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].piyy << "    " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].pizz << "    " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].ttLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xxLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].yyLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].zzLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xyLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].e << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].P << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].Peq << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].P_L << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].P_T << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].pixxLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].piyyLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].pizzLOCAL << "  " 
			<< endl;
	}
	ofs << endl;
}
ofs << endl;
return true;
}


bool Write::write_zxmap(const std::string& fname){
		std::cout << "Writing_zxmap==>" << std::endl;
	ofstream ofs;
	ofs.open((fname+"/"+constants::default_out_fname).c_str());
	if(!ofs){ms->open(fname+"/"+constants::default_out_fname); return false;}


ofs << "# z, x,  tt, tx, ty, tz, xx, xy, xz, yy, yz, zz, pizz,   ttLOCAL, xxLOCAL, yyLOCAL, zzLOCAL, xyLOCAL, e, P, P_L, P_T" << std::endl;
ofs << "#       <=============================================>  <================================>" << std::endl;
ofs << "#             Tmunu components before boost,        at LOCAL " << std::endl;
for(int i=0; i<constants::eta_cell_capa; ++i){
	for(int j=0; j<constants::x_cell_capa; ++j){

		double xaxis=0.;
		double yaxis=0.;
		if (constants::MODE.find("2dmap")!=string::npos) {
			xaxis=this->get_etacoordinate(i);
			yaxis=this->get_xcoordinate(j);
		}
		//ct->Hist2D_x[i][j];
		//ct->Hist2D_y[i][j];
		ofs << setw(16) << fixed << setprecision(8) << xaxis << "  "
			<< setw(16) << yaxis << "     "
			<< setw(16) << ct->Hist2DMultiComp[i][j].tt << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].tx << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].ty << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].tz << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xx << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xy << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xz << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].yy << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].yz << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].zz << "    " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].pixx << "    " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].piyy << "    " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].pizz << "    " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].ttLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xxLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].yyLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].zzLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].xyLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].e << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].P << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].Peq << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].P_L << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].P_T << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].pixxLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].piyyLOCAL << "  " 
			<< setw(16) << ct->Hist2DMultiComp[i][j].pizzLOCAL << "  " 
			<< endl;
	}
	ofs << endl;
}
ofs << endl;


		std::cout << "<==Writing_zxmap" << std::endl;
return true;
}





			bool Write::write_RtYield(const std::string& fname){
				cout <<"writeRt" << endl;
				Container::yield spname;
				for(int sp=0; sp<constants::num_of_Species_Rt; sp++){
					//Make output file
					//-------------------
					ofstream ofsTrans;
					ofsTrans.open((fname+"/"+"Trans_"+spname.get_particleName(sp)+constants::default_out_fname).c_str());
					if(!ofsTrans){ms->open(fname+"/"+"Trans_"+spname.yield::get_particleName(sp)+constants::default_out_fname); return false;}

					ct->max_nx+=constants::margin;

					for(int i=0; i<ct->max_nx+1; ++i){
						if(ct->HistHit_Rt[sp][i]==0) continue;
						double x_axis =ct->Hist_x[i];
						ofsTrans << setw(16) << fixed << setprecision(8) << x_axis << "  "
							<< setw(16) << ct->RtHist_RtTrans_yield[sp][i] << "  "
							<< setw(16) << ct->HistErrTrans_Rt[sp][i] << "  "
							<< setw(16) << ct->HistHit_Rt[sp][i] << endl;
					}
					ofsTrans << "%Mean Nt:" << ct->meanNt << endl;
					ofsTrans.close();

					ofstream ofsToward;
					ofsToward.open((fname+"/"+"Toward_"+spname.get_particleName(sp)+constants::default_out_fname).c_str());
					if(!ofsToward){ms->open(fname+"/"+"Toward_"+spname.yield::get_particleName(sp)+constants::default_out_fname); return false;}

					ct->max_nx+=constants::margin;

					for(int i=0; i<ct->max_nx+1; ++i){
						if(ct->HistHit_Rt[sp][i]==0) continue;
						double x_axis =ct->Hist_x[i];
						ofsToward << setw(16) << fixed << setprecision(8) << x_axis << "  "
							<< setw(16) << ct->RtHist_RtToward_yield[sp][i] << "  "
							<< setw(16) << ct->HistErrToward_Rt[sp][i] << "  "
							<< setw(16) << ct->HistHit_Rt[sp][i] << endl;
					}
					ofsToward << "%Mean Nt:" << ct->meanNt << endl;
					ofsToward.close();
					
				}
				return true;
			}
