#include "MiniJetStep.h"

MiniJetStep::MiniJetStep(std::vector<Container::ParticleInfo> &part_1ev, Settings::Options& options){
	generator_unidist1.seed(options.get_seed());
	generator_unidist2.seed(options.get_seed());
	sqrt_s = options.get_sqrt_s();
 	  cout << "(:3 = )3 ? " << __FILE__ << " (" << __LINE__ << ") sqrt_s :" << sqrt_s << endl;
	if(options.get_minijet_freestream()==1)
		this->Step(part_1ev);
	else if(options.get_minijet_freestream()==2){
		this->SetFormationTime(part_1ev);
		this->Step_wDeltaz(part_1ev);
	}else{
		cout << ":3 ? Error " << __FILE__ << " (" << __LINE__ << ") :options.get_minijet_freestream() " << options.get_minijet_freestream() << endl;
		exit(EXIT_FAILURE);
        }
	this->PrintJets(part_1ev);

}

MiniJetStep::~MiniJetStep(){
}


void MiniJetStep::Step_wDeltaz(std::vector<Container::ParticleInfo> &part_1ev){

std::cout << ":) Minijet::Step_wDeltaz is called." << std::endl;  

	for(auto& part: part_1ev){
		double vx = part.px/part.e;
		double vy = part.py/part.e;
		double vz = part.pz/part.e;
		part.x = part.x + constants::tau0*cosh(part.rap)*vx;
		part.y = part.y + constants::tau0*cosh(part.rap)*vy;
		double sq = (1.0+pow(sinh(part.rap),2))*part.z*part.z + constants::tau0*constants::tau0;
		part.t = (sq>0.)? part.z*cosh(part.rap)*sinh(part.rap)+cosh(part.rap)*sqrt(sq) :  constants::TINY;
		//part.t = (sq>0.)? part.z*cosh(part.rap)*sinh(part.rap)+sqrt(sq) :  part.z*cosh(part.rap)*sinh(part.rap)+sqrt(constants::TINY);
		part.z = part.z + vz * part.t;
		//part.z = sqrt(part.t * part.t - constants::tau0*constants::tau0);
	}

	return;
}
void MiniJetStep::Step(std::vector<Container::ParticleInfo> &part_1ev){

std::cout << ":) Minijet::Step is called." << std::endl;  

	for(auto& part: part_1ev){
		double vx = part.px/part.e;
		double vy = part.py/part.e;
		double vz = part.pz/part.e;
		part.x = part.x + constants::tau0*cosh(part.rap)*vx;
		part.y = part.y + constants::tau0*cosh(part.rap)*vy;
		part.z = part.z + constants::tau0*cosh(part.rap)*vz;
		part.t = part.t + constants::tau0*cosh(part.rap);
	}

	return;
}


void MiniJetStep::SetFormationTime(std::vector<Container::ParticleInfo> &part_1ev){

std::cout << ":) Minijet::SetFormationTime is called." << std::endl;  

for(int i=0; i<(int)part_1ev.size(); i++){
	if(fabs(i%2)<constants::SMALL){
		Container::ParticleInfo &part3 = part_1ev[i];
		Container::ParticleInfo &part4 = part_1ev[i+1];
		double pt3 = part3.pt;//can be jet2
		double pt4 = part4.pt;//can be jet2
		double rap3 = part3.rap;
		double rap4 = part4.rap;
		double x1 = (pt3/sqrt_s)*(exp(rap3)+exp(rap4));
		double x2 = (pt4/sqrt_s)*(exp(-rap3)+exp(-rap4));
		part3.Bjx1 = x1;
		part4.Bjx2 = x2;
		part3.Bjx1 = x1;
		part4.Bjx2 = x2;

		double sqrttt = sqrt_s*x1*pt3*exp(-part3.rap);
		double sqrtuu = sqrt_s*x1*pt3*exp(-part4.rap);
		double sqrt_t = (sqrttt>0.)? sqrt(sqrttt)/constants::hbarc:  constants::TINY;
		double sqrt_u = (sqrtuu>0.)? sqrt(sqrtuu)/constants::hbarc:  constants::TINY;

		//min(sqrt u, sqrt t)^-1 
		//==========
		part3.deltaz = 1.0/min(sqrt_t, sqrt_u);
		part4.deltaz = 1.0/min(sqrt_t, sqrt_u);

		//Eskola, Wang
		//==========
		//part3.deltaz =2.0/((sqrt_s/constants::hbarc)*part1.Bjx1); 
		//part4.deltaz =2.0/((sqrt_s/constants::hbarc)*part1.Bjx2); 

		//Sample formation vertices
		std::uniform_real_distribution<> uni_dist1(-part3.deltaz/2.0, part3.deltaz/2.0);
		part3.z = uni_dist1(generator_unidist1);
		std::uniform_real_distribution<> uni_dist2(-part4.deltaz/2.0, part4.deltaz/2.0);
		part4.z = uni_dist2(generator_unidist2);

		//Now tform is set to 0.
		//======================
		part3.t = 0.;
		part4.t = 0.;

		if(fabs(pt3-pt4)>constants::SMALL){
			cout << "ERROR " << __FILE__ << " (" << __LINE__ << ") different pt3, pt4 :" << pt3 << "  pt4 " << pt4 << endl;
			exit(EXIT_FAILURE);
		}
	}
		if(i==(int)part_1ev.size()-2) break;
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
