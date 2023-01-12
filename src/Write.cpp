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


Write::Write(shared_ptr<Message> ms_in, Settings::Options options_in, shared_ptr<InfoHist> infohist_in, shared_ptr<Util_func> uf_in):ms(ms_in), options(options_in), infohist(infohist_in), uf(uf_in), detas(0.5){};
Write::~Write(){};


		int Write::getMapEdgeX(const double maxval){
			int n=(int)((maxval/this->infohist->d_x)+(std::fabs(constants::x_min)/this->infohist->d_x));
			return n;
		}
		int Write::getMapEdgeY(const double maxval){
			int n=(int)((maxval/this->infohist->d_y)+(std::fabs(constants::y_min)/this->infohist->d_y));
			return n;
		}


bool Write::write(const std::string& fname, const shared_ptr<Container>& ct){
	ofstream ofs;
	ofs.open((fname+"/"+constants::default_out_fname).c_str());
	cout <<"write" << endl;
	if(!ofs){ms->open(fname+"/"+constants::default_out_fname); return false;}

	ct->max_nx+=constants::margin;

	ofs << "# x, y,  tt, tx, ty, tz, xx, xy, xz, yy, yz, zz,  eLOCAL, Px, Py, Pz, pixy" << std::endl;
	ofs << "#       <======================================>  <=======================>" << std::endl;
	ofs << "#             Tmunu components before boost,        at LOCAL " << std::endl;
	for(int i=0; i<constants::x_cell_capa; ++i){
		for(int j=0; j<constants::y_cell_capa; ++j){

			double xaxis=((constants::x_min+(this->infohist->d_x*i))+(constants::x_min+(this->infohist->d_x*(i+1))))/2.0;
			double yaxis=((constants::y_min+(this->infohist->d_y*j))+(constants::y_min+(this->infohist->d_y*(j+1))))/2.0;
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
				<< setw(16) << ct->Hist2DMultiComp[i][j].eLOCAL << "  " 
				<< setw(16) << ct->Hist2DMultiComp[i][j].PxLOCAL << "  " 
				<< setw(16) << ct->Hist2DMultiComp[i][j].PyLOCAL << "  " 
				<< setw(16) << ct->Hist2DMultiComp[i][j].PzLOCAL << "  " 
				<< setw(16) << ct->Hist2DMultiComp[i][j].pixyLOCAL << "  " 
				<< endl;
		}
		ofs << endl;
	}
	ofs << endl;
	return true;
}





			bool Write::write_RtYield(const std::string& fname, const shared_ptr<Container>& ct){
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
