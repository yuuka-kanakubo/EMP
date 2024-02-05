#include <vector>
#include <math.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "ReadIn.h"

int ReadIn::test(){

return 0;
};


ReadIn::ReadIn(shared_ptr<Message> ms_in, Settings::Options options_in):ms(ms_in), options(options_in){
  std::cout << "ReadIn" << std::endl;
}



bool ReadIn::readEKRT(const int i, std::vector<Container::ParticleInfo> &part_1ev){

	std::stringstream ss;
	ss << options.get_dir_name() << "/" 
		<< options.get_f_name() 
		<< setw(9) << setfill('0') << i << "/" 
		<< options.get_ext_name();
	std::string inputpath = ss.str();

	ifstream in;
	in.open(inputpath.c_str(),ios::in);
	if(!in){ ms->open(inputpath); return false;}

	{
		std::string templine;
		while(getline(in,templine)) {
			if(templine.find('#')!=std::string::npos) {
			} else if(templine.find('%')!=std::string::npos){
			}else{
				double x, y, pt, rap, phi, t;
				double tata;
				int ID;
				int momID1;
				int momID2;
				int imomNucleon1;
				int imomNucleon2;
				double xmomNucleon1;
				double xmomNucleon2;
				double ymomNucleon1;
				double ymomNucleon2;
				double zmomNucleon1;
				double zmomNucleon2;
				bool is_mom1Neutron;
				bool is_mom2Neutron;
				istringstream is(templine);
				is >> t 
					>> x 
					>> y 
					>> pt 
					>> rap 
					>> phi 
					>> tata 
					>> ID 
					>> momID1 
					>> momID2 
					>> imomNucleon1 
					>> imomNucleon2 
					>> xmomNucleon1 
					>> xmomNucleon2 
					>> ymomNucleon1 
					>> ymomNucleon2 
					>> zmomNucleon1 
					>> zmomNucleon2 
					>> is_mom1Neutron 
					>> is_mom2Neutron;

				Container::ParticleInfo part_in;

				part_in.x=x;//[fm]
				part_in.y=y;//[fm]
				double rr = pow(x,2)+pow(y,2);
				part_in.r=(rr<constants::SMALL)? 0.0:sqrt(rr);//[fm]
				part_in.t=t;//[fm]
				part_in.phi=phi;
				part_in.rap=rap;
				part_in.pt=pt;//[GeV]
				part_in.tata=tata;
				part_in.ID=ID;
				part_in.momID1=momID1;
				part_in.momID2=momID2;
				part_in.imomNucleon1=imomNucleon1;
				part_in.imomNucleon2=imomNucleon2;
				part_in.xmomNucleon1=xmomNucleon1;
				part_in.xmomNucleon2=xmomNucleon2;
				part_in.ymomNucleon1=ymomNucleon1;
				part_in.ymomNucleon2=ymomNucleon2;
				part_in.zmomNucleon1=zmomNucleon1;
				part_in.zmomNucleon2=zmomNucleon2;
				part_in.is_mom1Neutron=is_mom1Neutron;
				part_in.is_mom2Neutron=is_mom2Neutron;

				double mtsq=pow(part_in.pt,2)+pow(part_in.m,2);
				double mt=(mtsq>0.0) ? sqrt(mtsq):0.0;
				part_in.mt=mt;
				part_in.px=part_in.pt*cos(part_in.phi);
				part_in.py=part_in.pt*sin(part_in.phi);
				part_in.pz=part_in.mt*sinh(part_in.rap);
				part_in.e=part_in.mt*cosh(part_in.rap);
				//part_in.tau=part_in.t/cosh(part_in.rap);
				//part_in.z=part_in.tau*sinh(part_in.rap);
				part_in.tau=0.0;
				part_in.z=0.0;
				part_in.t=0.0;
				double msq=pow(part_in.e,2)
					-pow(part_in.px,2)
					-pow(part_in.py,2)
					-pow(part_in.pz,2);
				double m=(msq>0.)? sqrt(msq):0.;
				part_in.m=m;

				//Pushing back particles
				//=======================
				//if(std::fabs(part_in.eta)<constants::delta_eta){ 
				part_1ev.push_back(part_in);
				//}

			}//particle loop if no # %
		}//particle loop
		in.close();
	}//namespace 

	return true;
}






bool ReadIn::read(const int i, std::vector<Container::ParticleInfo> &part_1ev){

//File name
//===========
	std::stringstream ss;
	ss << options.get_dir_name() << "/" << options.get_f_name() << setw(9) << setfill('0') << i << "/" << options.get_ext_name();
	std::string inputpath = ss.str();




			std::ifstream in;
			in.open(inputpath.c_str(),std::ios::in);
			if(!in){ 
				ms->open(inputpath); 
				return false;
			}


			{
				std::string templine;
				while(getline(in,templine)) {
					if(templine.find('#')!=std::string::npos) {
					}else if(templine.find("JC")!=std::string::npos) {
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
						int data1, data2,data3,data4, ID, col, acol;
						double m,e,px,py,pz,x,y,z,t,ft, rap;
						std::string TAG;
						//is >> data1 >> data2 >> data3 >> data4 >> col >> acol >> ID >> m >> e >> px >> py >> pz >> rap >> x >> y >> z >> t;

//FOR EKRT, parton_manager output
//=======================
//std::cout << __FILE__ << "  " << __LINE__ << std::endl;
is >> data1 >> data2 >> col >> acol >> ID >> m >> e >> px >> py >> pz >> x >> y >> z >> t >> ft  >> rap;
						//ID=21;
//============================

						//std::cout << e << "   " << px << std::endl;
						//is >> data1 >> data2 >> col >> acol >> ID >> m >> e >> px >> py >> pz >> rap >> x >> y >> z >> t >> ft >> TAG;


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



						if(isParton(ID)) { 
						//if(fabs(eta)<0.5){
							Container::ParticleInfo part_in;
							part_in.eta=eta;
							part_in.phi=phi;
							part_in.mt=mt;
							part_in.id=ID;
							part_in.e=e;
							part_in.px=px;
							part_in.py=py;
							part_in.pz=pz;
							part_in.x=x;
							part_in.y=y;
							part_in.z=z;
							part_in.t=t;
							part_1ev.push_back(part_in);
						}
				//}



					}
				}//getline
				in.close();
			}


			return true;
}



