#ifndef EMCONV_H
#define EMCONV_H
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "Container.h" 
#include "InfoHist.h" 

class EMconv{


public:
EMconv(std::vector<Container::ParticleInfo> part_1ev_in, std::shared_ptr<Container>& ct_in);
~EMconv();

private:
std::vector<Container::ParticleInfo> part_1ev;
std::shared_ptr<Container>& ct;
std::shared_ptr<InfoHist> infohist;
double 	xy6sigma;
double 	etas6sigma;

//TEMP
//=====
double tau;
double detas;

bool Convert();
int test();



		double get_xcoordinate(int i){
			double x_coord = (i-(constants::x_cell_capa-1)/2)*constants::dl;//[fm]
			return x_coord;
		}

		double get_ycoordinate(int j){
			double y_coord = (j-(constants::y_cell_capa-1)/2)*constants::dl;//[fm]
			return y_coord;
		}

		double get_etacoordinate(int k){
			double eta_coord = (k-(constants::eta_cell_capa-1)/2)*this->detas;
			return eta_coord;
		}

		int get_xcell(double xProd){
			int xcell = int ((xProd/(constants::dl))+(constants::x_cell_capa/2.0));
			return xcell;
		}

		int get_ycell(double yProd){
			int ycell = int ((yProd/(constants::dl))+(constants::y_cell_capa/2.0));
			return ycell;
		}

		int get_etacell(double eta){
			int etacell = int ((eta/this->detas)+(constants::eta_cell_capa/2.0));
			return etacell;
		}

//==========================

int get_etamin(const int etacenter_i){
	int SmearRangeNetas= etas6sigma; 
	int etamin = etacenter_i - SmearRangeNetas;
	if(etacenter_i<SmearRangeNetas){
		etamin=0;
	}
return etamin;
}

int get_etamax(const int etacenter_i){
					int SmearRangeNetas= etas6sigma; 
					int etamax = etacenter_i + SmearRangeNetas;
					if(etacenter_i>(constants::eta_cell_capa-SmearRangeNetas)){
						etamax=constants::eta_cell_capa;
					}
return etamax;
}


int get_xmin(const int xcenter_i){
						int SmearRangeNxy= xy6sigma;
						int xmin = xcenter_i - SmearRangeNxy;
						if(xcenter_i<SmearRangeNxy){
							xmin=0;
						}
return xmin;
}

int get_xmax(const int xcenter_i){
						int SmearRangeNxy= xy6sigma;
						int xmax = xcenter_i + SmearRangeNxy;
						if(xcenter_i>(constants::x_cell_capa-SmearRangeNxy)){
							xmax=constants::x_cell_capa;
						}
return xmax;
}

int get_ymin(const int ycenter_i){
						int SmearRangeNxy= xy6sigma;
						int ymin = ycenter_i - SmearRangeNxy;
						if(ycenter_i<SmearRangeNxy){
							ymin=0;
						}
return ymin;
}

int get_ymax(const int ycenter_i){
						int SmearRangeNxy= xy6sigma;
						int ymax = ycenter_i + SmearRangeNxy;
						if(ycenter_i>(constants::y_cell_capa-SmearRangeNxy)){
							ymax=constants::y_cell_capa;
						}
return ymax;
}



};
#endif 
