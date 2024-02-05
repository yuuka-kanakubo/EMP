#ifndef READIN
#define READIN
#include <iostream>
#include <memory>
#include "Container.h"
#include "Message.h"
#include "Settings.h"

class ReadIn{

private:
std::shared_ptr<Message> ms;
Settings::Options options;
std::string path;

bool isGluon(const int pid){
 if(pid==constants::id_gluon){return true;}
else return false;

}

 bool isParton(const int pid){
 if(isQuark(pid) || isGluon(pid)){return true;}
else return false;
}


    bool isQuark(const int pid) {
      if(abs(pid)<9||this->is_diquark(pid)) return true;
      else return false;
    }


    bool is_diquark(const int pid){
      bool is_diquark=false;
      if(abs(pid)!=2212 && abs(pid)!=2112 && abs(pid)<10000 && 999<abs(pid)) {
	int PID= pid/10;
	if(PID%10==0) is_diquark=true;
      }
      return is_diquark;
    }








public:
ReadIn(shared_ptr<Message> ms_in, Settings::Options options_in);
~ReadIn(){};

void setoutputpath(const std::string path){this->path=path;}
bool read(const int i, std::vector<Container::ParticleInfo> &part_1ev);
bool readEKRT(const int i, std::vector<Container::ParticleInfo> &part_1ev);

bool show_readin(std::vector<Container::ParticleInfo> part_1ev, const bool ALL){

	ofstream ofs;
	if(ALL){
		ofs.open((path+"/"+constants::default_out_fnamejet).c_str());
		if(!ofs) {
			std::cout << ":( Could not open the output file." << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	std::cout << "Showing readin data " << std::endl;
	int count = 0;
	for(const auto& elem: part_1ev){
		count++;
		std::cout << elem.id << "  "
			<< elem.e << "  "
			<< elem.rap << "  "
			<< elem.pt << "  "
			<< elem.px << "  "
			<< elem.py << "  "
			<< elem.pz << "  "
			<< elem.x << "  "
			<< elem.y << "  "
			<< elem.z << "  "
			<< elem.t << "  "
			<< elem.Bjx1 << "  "
			<< elem.Bjx2 << "  "
			<< elem.deltaz << "  "
			<< std::endl;

		if(ALL){
			ofs << elem.id << "  "
				<< elem.e << "  "
				<< elem.rap << "  "
				<< elem.pt << "  "
				<< elem.px << "  "
				<< elem.py << "  "
				<< elem.pz << "  "
				<< elem.x << "  "
				<< elem.y << "  "
				<< elem.z << "  "
				<< elem.t << "  "
				<< elem.Bjx1 << "  "
				<< elem.Bjx2 << "  "
				<< elem.deltaz << "  "
				<< std::endl;
		}
		if(!ALL && count>10) break;
	}
	std::cout << "-->Showing readin data " << std::endl;
	if(ALL) ofs.close();
	return true;
};




int test();
};
#endif
