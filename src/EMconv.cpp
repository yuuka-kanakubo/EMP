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

//		std::cout << part.id << "  "
//			<< part.e << "  "
//			<< part.px << "  "
//			<< part.py << "  "
//			<< part.pz << "  "
//			<< part.x << "  "
//			<< part.y << "  "
//			<< part.z << "  "
//			<< std::endl;


						//Get cell index of the position of each particle.
						//=============================================
						int xcenter_i=get_xcell(part.x);
						int ycenter_i=get_ycell(part.y);
						//TODO: Obtain Tmunu in Milne
						//int etacenter_i=get_etacell(part.eta);
						int etacenter_i=get_etacell(part.z);


						//If the particle is outside of the cells, then neglect them.
						//=============================================================
						double etamin = this->get_etamin(etacenter_i);
						double etamax = this->get_etamax(etacenter_i);
//std::cout << "etamin  " << etamin << std::endl;
//std::cout << "etamax  " << etamax << std::endl;

						//if(etamin<0 || etamax<0) continue;
						double xmin = this->get_xmin(xcenter_i);
						double xmax = this->get_xmax(xcenter_i);
						//if(xmin<0 || xmax<0) continue;
						double ymin = this->get_ymin(ycenter_i);
						double ymax = this->get_ymax(ycenter_i);
						//if(ymin<0 || ymax<0) continue;
//std::cout << "xmin  " << xmin << std::endl;
//std::cout << "xmax  " << xmax << std::endl;
//std::cout << "ymin  " << ymin << std::endl;
//std::cout << "ymax  " << ymax << std::endl;

						//Get nx and ny.
						//Loop over the distribution.
						//============================
						double GAUSS=0.0;
						int k = 0;
						for(int k = etamin; k < etamax; k++ ){
							//TODO: Obtain Tmunu in Milne
							//double etat = part.eta - this->get_etacoordinate(k);
							double etat = part.z - this->get_etacoordinate(k);
							//TODO: Obtain Tmunu in Milne
							//double longFactor = (1.0/(sqrt(2*M_PI)*constants::longSmear*this->tau))*exp(-0.5*etat*etat/(constants::longSmear*constants::longSmear));
							double longFactor = (1.0/(sqrt(2*M_PI)*constants::longSmear))*exp(-0.5*etat*etat/(constants::longSmear*constants::longSmear));
//std::cout << "  Smearing  in z: " << this->get_etacoordinate(k) << std::endl;

								//Get how much pmu should be deposited: Tmunu
							//==========================================
								for( int i = xmin; i < xmax; i++ ){
									for( int j = ymin; j < ymax; j++ ){
									double xt = this->get_xcoordinate(i) - part.x;
									double yt = this->get_ycoordinate(j) - part.y; 
									double transFactor = (1.0/(2*M_PI*constants::transSmear*constants::transSmear))*exp(-0.5*(xt*xt+yt*yt)/(constants::transSmear*constants::transSmear) );
									//TODO: Obtain Tmunu in Milne
									//double invV=1.0/(constants::dl*constants::dl*this->tau*this->detas);
									double invV=1.0/(constants::dl*constants::dl*this->detas);

									//Seeing only midarapidity.
									//========================
									//TODO: Obtain Tmunu in Milne
									//ct->Hist2DMultiComp[i][j].tt+=invV*(part.e*part.e/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
							if(k==int(constants::eta_cell_capa/2.0)){
										ct->Hist2DMultiComp[i][j].tt+=invV*(part.e*part.e/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].tx+=invV*(part.e*part.px/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].ty+=invV*(part.e*part.py/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].tz+=invV*(part.e*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].xx+=invV*(part.px*part.px/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].xy+=invV*(part.px*part.py/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].xz+=invV*(part.px*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].yy+=invV*(part.py*part.py/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].yz+=invV*(part.py*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
										ct->Hist2DMultiComp[i][j].zz+=invV*(part.pz*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->detas;
									}//only midy
										//TODO: Obtain Tmunu in Milne
										//GAUSS+=transFactor*longFactor*constants::dl*constants::dl*this->tau*this->detas;
									GAUSS+=transFactor*longFactor*constants::dl*constants::dl*this->detas;
								}//y
							}//x
						}//eta

if(fabs(GAUSS-1.0)>constants::SMALL){
	std::cout << "Gauss " << std::fixed << std::setprecision(8) << std::setw(16) << GAUSS << std::endl;
	exit(1);
}



				}//End of particle loop
				//==========================
return true;
}



int EMconv::test(){
return 0;
};
