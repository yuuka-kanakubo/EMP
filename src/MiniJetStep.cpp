#include "MiniJetStep.h"

MiniJetStep::MiniJetStep(std::vector<Container::ParticleInfo> &part_1ev){
this->Step(part_1ev);
}

MiniJetStep::~MiniJetStep(){
}


void MiniJetStep::Step(std::vector<Container::ParticleInfo> &part_1ev){

std::cout << ":) Minijet::Step is called." << std::endl;  

	for(auto& part: part_1ev){
		double vx = part.px/part.e;
		double vy = part.py/part.e;
		double vz = part.pz/part.e;
		part.x = constants::tau0*cosh(part.rap)*vx;
		part.y = constants::tau0*cosh(part.rap)*vy;
		part.z = constants::tau0*cosh(part.rap)*vz;
		part.t = constants::tau0*cosh(part.rap);

	}

	return;
}
