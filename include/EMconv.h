#ifndef EMCONV_H
#define EMCONV_H
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "Container.h" 
#include "InfoHist.h" 
#include "Settings.h" 

class EMconv{


public:
EMconv(std::vector<Container::ParticleInfo> part_1ev_in, std::shared_ptr<Container>& ct_in, Settings::Options& options_in);
~EMconv();

private:
std::vector<Container::ParticleInfo> part_1ev;
std::shared_ptr<Container>& ct;
std::shared_ptr<InfoHist> infohist;
Settings::Options& options;
double 	xy6sigma;
double 	etas6sigma;
bool Skip (int i, int j, int k) const;


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
			double eta_coord = (k-(constants::eta_cell_capa-1)/2)*constants::dleta;
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
			int etacell = int ((eta/constants::dleta)+(constants::eta_cell_capa/2.0));
			return etacell;
		}

//==========================

int get_etamin(const int etacenter_i){
	int SmearRangeNetas= etas6sigma; 
	int etamin = etacenter_i - SmearRangeNetas;
	if(etacenter_i<SmearRangeNetas){
                if(options.get_flag_TWODMAP_zx()) std::cout << ":( Energy is leaking out from the prepared space... etamin " << etamin << "  " << __FILE__ << " " << __LINE__ << std::endl;
                return etamin;
	}
return etamin;
}

int get_etamax(const int etacenter_i){
					int SmearRangeNetas= etas6sigma; 
					int etamax = etacenter_i + SmearRangeNetas;
					if(etacenter_i>(constants::eta_cell_capa-SmearRangeNetas)){
						if(options.get_flag_TWODMAP_zx()) std::cout << ":( Energy is leaking out from the prepared space... etamax " << etamax << "  " << __FILE__ << " " << __LINE__ << std::endl;
						return etamax;
					}
return etamax;
}


int get_xmin(const int xcenter_i){
						int SmearRangeNxy= xy6sigma;
						int xmin = xcenter_i - SmearRangeNxy;
						if(xcenter_i<SmearRangeNxy){
							std::cout << ":( Energy is leaking out from the prepared space... " << __FILE__ << " " << __LINE__ << std::endl;
							return xmin;
						}
return xmin;
}

int get_xmax(const int xcenter_i){
						int SmearRangeNxy= xy6sigma;
						int xmax = xcenter_i + SmearRangeNxy;
						if(xcenter_i>(constants::x_cell_capa-SmearRangeNxy)){
							std::cout << ":( Energy is leaking out from the prepared space... " << __FILE__ << " " << __LINE__ << std::endl;
							return xmax;
						}
return xmax;
}

int get_ymin(const int ycenter_i){
						int SmearRangeNxy= xy6sigma;
						int ymin = ycenter_i - SmearRangeNxy;
						if(ycenter_i<SmearRangeNxy){
							std::cout << ":( Energy is leaking out from the prepared space... " << __FILE__ << " " << __LINE__ << std::endl;
							return ymin;
						}
return ymin;
}

int get_ymax(const int ycenter_i){
						int SmearRangeNxy= xy6sigma;
						int ymax = ycenter_i + SmearRangeNxy;
						if(ycenter_i>(constants::y_cell_capa-SmearRangeNxy)){
							std::cout << ":( Energy is leaking out from the prepared space... " << __FILE__ << " " << __LINE__ << std::endl;
							return ymax;
						}
return ymax;
}



};
#endif 
