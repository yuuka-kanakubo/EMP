#include "EMconv.h"

EMconv::EMconv(std::vector<Container::ParticleInfo> part_1ev_in, std::shared_ptr<Container>& ct_in):part_1ev(part_1ev_in), ct(ct_in), tau(0.30), detas(0.5){//Here, tau is in fm
	infohist = std::make_shared<InfoHist>(constants::x_max, constants::y_max, constants::d_x, constants::d_y, 2.0);
	xy6sigma=round(constants::transSmear*6.0/constants::dl);
	etas6sigma=round(constants::longSmear*6.0/this->detas);
	this->Convert();
};

EMconv::~EMconv(){};



bool EMconv::Convert(){

		//Particle loop
		//=============
	for(const auto& part: part_1ev){

	//	std::cout << part.id << "  "
	//		<< part.e << "  "
	//		<< part.px << "  "
	//		<< part.py << "  "
	//		<< part.pz << "  "
	//		<< std::endl;


						//Get cell index of the position of each particle.
						//=============================================
						int xcenter_i=get_xcell(part.x);
						int ycenter_i=get_ycell(part.y);
						int etacenter_i=get_etacell(part.eta);

						//Get nx and ny.
						//Loop over the distribution.
						//============================
						double GAUSS=0.0;
						int k = 0;
						for(int k = this->get_etamin(etacenter_i); k < this->get_etamax(etacenter_i); k++ ){
std::cout << "k " << k << "    in eta " << part.eta<< std::endl;
							double etat = part.eta - this->get_etacoordinate(k);
							double longFactor = (1.0/(sqrt(2*M_PI)*constants::longSmear*this->tau))*exp(-0.5*etat*etat/(constants::longSmear*constants::longSmear));

							//Get how much pmu should be deposited: Tmunu
							//==========================================
							for( int i = this->get_xmin(xcenter_i); i < this->get_xmax(xcenter_i); i++ ){
								for( int j = this->get_ymin(ycenter_i); j < this->get_ymax(ycenter_i); j++ ){
									double xt = this->get_xcoordinate(i) - part.x;
									double yt = this->get_ycoordinate(j) - part.y; 
									double transFactor = (1.0/(2*M_PI*constants::transSmear*constants::transSmear))*exp(-0.5*(xt*xt+yt*yt)/(constants::transSmear*constants::transSmear) );
									double invV=1.0/(constants::dl*constants::dl*this->tau*this->detas);
									if(k==84){
										ct->Hist2DMultiComp[i][j].tt+=invV*(part.e*part.e/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
										ct->Hist2DMultiComp[i][j].xx+=invV*(part.px*part.px/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
										ct->Hist2DMultiComp[i][j].yy+=invV*(part.py*part.py/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
										ct->Hist2DMultiComp[i][j].zz+=invV*(part.pz*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
										ct->Hist2DMultiComp[i][j].xy+=invV*(part.pz*part.py/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
										ct->Hist2DMultiComp[i][j].xz+=invV*(part.px*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
									}
									GAUSS+=transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
								}//y
							}//x
						}//eta

	std::cout << "Gauss " << std::fixed << std::setprecision(8) << std::setw(16) << GAUSS << std::endl;



				}//End of particle loop
				//==========================
return true;
}



int EMconv::test(){
return 0;
};
