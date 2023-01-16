#ifndef WRITE
#define WRITE
#include "InfoHist.h" 
#include "Util_func.h" 
#include "Message.h" 
#include <memory>

class Write{

private:

		std::shared_ptr<Message>& ms;  
		Settings::Options& options;
		std::shared_ptr<InfoHist>& infohist;
		std::shared_ptr<Util_func>& uf;
		std::shared_ptr<Container>& ct;

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

public:

Write(std::shared_ptr<Message> ms_in, Settings::Options options_in, std::shared_ptr<InfoHist> info, std::shared_ptr<Util_func> uf, std::shared_ptr<Container> ct);
~Write();
		int getMapEdgeX(const double maxval);
		int getMapEdgeY(const double maxval);
		bool write(const std::string& fname);
		bool write_RtYield(const std::string& fname);
		bool write_zxmap(const std::string& fname);
		bool write_xymap(const std::string& fname);
};
#endif
