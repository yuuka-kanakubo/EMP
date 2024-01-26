#include "MiniJetStep.h"

MiniJetStep::MiniJetStep(std::vector<Container::ParticleInfo> &part_1ev){
this->Step(part_1ev);
this->PrintJets(part_1ev);
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



void MiniJetStep::PrintJets(std::vector<Container::ParticleInfo> &part_1ev){


	ofstream ofs;
	ofs.open("data/JetsEMP.dat",ios::out);
	if(!ofs) {
		cout << "ERROR:( unable to open file " << endl;
		return;
	}
	ofs << "#t(1), x(2), y(3), pt(4), rap(5), phi(6), tata(7), ID(8), mom1ID(9), mom2ID(10), mom1i(11), mom2i(12), mom1x(13), mom2x(14), mom1y(15), mom2y(16), mom1z(17), mom2z(18), ismom1N(19), ismom2N(20)" << endl;
	for(int iout=0; iout<(int)part_1ev.size(); iout++){
			ofs << std::scientific
				<< part_1ev[iout].t << "  "
				<< part_1ev[iout].x << "  "
				<< part_1ev[iout].y << "  "
				<< part_1ev[iout].pt << "  "
				<< part_1ev[iout].rap << "  "
				<< part_1ev[iout].phi << "  "
				<< part_1ev[iout].tata << "  "
				<< part_1ev[iout].ID << "  "
				<< part_1ev[iout].momID1 << "  "
				<< part_1ev[iout].momID2 << "  "
				<< part_1ev[iout].imomNucleon1 << "  "
				<< part_1ev[iout].imomNucleon2 << "  "
				<< part_1ev[iout].xmomNucleon1 << "  "
				<< part_1ev[iout].xmomNucleon2 << "  "
				<< part_1ev[iout].ymomNucleon1 << "  "
				<< part_1ev[iout].ymomNucleon2 << "  "
				<< part_1ev[iout].zmomNucleon1 << "  "
				<< part_1ev[iout].zmomNucleon2 << "  "
				<< part_1ev[iout].is_mom1Neutron << "  "
				<< part_1ev[iout].is_mom2Neutron << endl;
	}

	ofs.close();

	return;
}
