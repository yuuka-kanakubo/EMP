#include "ReadIn.h"
#include <vector>
#include <math.h>
#include <sstream>
#include <fstream>

int ReadIn::test(){

return 0;
};


ReadIn::ReadIn(shared_ptr<Message> ms_in, Settings::Options options_in):ms(ms_in), options(options_in){
  std::cout << "ReadIn" << std::endl;
}

bool ReadIn::read(std::vector<Container::ParticleInfo> &part_1ev){

			std::ifstream in;
			in.open(options.get_f_name().c_str(),std::ios::in);
			if(!in){ ms->open(options.get_f_name().c_str()); return false;}


			{
				std::string templine;
				while(getline(in,templine)) {
					if(templine.find('#')!=std::string::npos) {
					} else if(templine.find('%')!=std::string::npos){
						std::istringstream iss(templine);
						std::string pct;
						int iev, nv;
						std::string com;
						double weight_in, tau;
						iss >> com >> iev >> nv >> tau >> weight_in;
						//weight=weight_in;
					}else{
						std::istringstream is(templine);
						int data1, data2, ID, col, acol;
						double m,e,px,py,pz,x,y,z,t,ft, rap;
						std::string TAG;
						is >> data1 >> data2 >> col >> acol >> ID >> m >> e >> px >> py >> pz >> rap >> x >> y >> z >> t >> ft >> TAG;


						double P_squared=px*px+py*py+pz*pz;
						double P=(P_squared)>0.0 ? sqrt(P_squared):0.0;
						double pt_squared=px*px+py*py;
						double pt=(pt_squared)>0.0 ? sqrt(pt_squared):0.0;
						double mt_squared=pt*pt+m*m;
						double mt=(mt_squared)>0.0 ? sqrt(mt_squared):0.0;
						double phi = atan2(py, px);

						////
						double eta;
						{
							const double LARGE = 10.0;
							if(P==0.0 && pz==0.0) eta=0.0;
							else if(P==-pz) eta=-LARGE;
							else if(P==pz) eta=LARGE;
							else eta=std::log((P + pz)/(P - pz)) / 2.0;
						}
						///



						if(constants::MODE.find("dndeta_proton")!=string::npos){
							if(ID==constants::id_proton) { 

								Container::ParticleInfo part_in;
								part_in.eta=eta;
								part_1ev.push_back(part_in);

							}
						}



						}
					}//getline
					in.close();
				}


				return true;
}

