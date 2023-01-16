#include "EMconv.h"

EMconv::EMconv(std::vector<Container::ParticleInfo> part_1ev_in, std::shared_ptr<Container>& ct_in, Settings::Options& options_in):part_1ev(part_1ev_in), ct(ct_in), options(options_in){
	infohist = std::make_shared<InfoHist>(constants::x_max, constants::y_max, constants::d_x, constants::d_y, 2.0);
	xy6sigma=round(constants::transSmear*6.0/constants::dl);
	etas6sigma=round(constants::longSmear*6.0/constants::dleta);
        std::cout << ":)  xmin " << get_xcoordinate(0) << ",   xmax " << get_xcoordinate(constants::x_cell_capa) << std::endl;
        std::cout << ":)  ymin " << get_ycoordinate(0) << ",   ymax " << get_ycoordinate(constants::y_cell_capa) << std::endl;
        std::cout << ":)  zmin " << get_etacoordinate(0) << ",   zmax " << get_etacoordinate(constants::eta_cell_capa) << std::endl;
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

						double xmin = this->get_xmin(xcenter_i);
						double xmax = this->get_xmax(xcenter_i);
						double ymin = this->get_ymin(ycenter_i);
						double ymax = this->get_ymax(ycenter_i);
						//if(etamin<0 || etamax<0) continue;
						//if(xmin<0 || xmax<0) continue;
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
							//TODO: Obtain Tmunu in Milne//Here, tau should be in fm
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
									//double invV=1.0/(constants::dl*constants::dl*this->tau*constants::dleta);
									double invV=1.0/(constants::dl*constants::dl*constants::dleta);

									//Seeing only midarapidity.
									//========================
									//TODO: Obtain Tmunu in Milne
									//ct->Hist2DMultiComp[i][j].tt+=invV*(part.e*part.e/part.e)*transFactor*longFactor*constants::dl*constants::dl*this->tau*constants::dleta;
									if(!this->Skip(i,j,k)){
										int i__=i;
										int j__=j;
										if(options.get_flag_TWODMAP_zx() ){
											i__ = k;
											j__ = i;
										}
										ct->Hist2DMultiComp[i__][j__].tt+=invV*(part.e*part.e/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].tx+=invV*(part.e*part.px/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].ty+=invV*(part.e*part.py/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].tz+=invV*(part.e*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].xx+=invV*(part.px*part.px/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].xy+=invV*(part.px*part.py/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].xz+=invV*(part.px*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].yy+=invV*(part.py*part.py/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].yz+=invV*(part.py*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
										ct->Hist2DMultiComp[i__][j__].zz+=invV*(part.pz*part.pz/part.e)*transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
									}//only midy
										//TODO: Obtain Tmunu in Milne
										//GAUSS+=transFactor*longFactor*constants::dl*constants::dl*this->tau*constants::dleta;
									GAUSS+=transFactor*longFactor*constants::dl*constants::dl*constants::dleta;
								}//y
							}//x
						}//eta

if(fabs(GAUSS-1.0)>constants::SMALL){
	std::cout << "Gauss " << std::fixed << std::setprecision(8) << std::setw(16) << GAUSS << std::endl;
	//exit(1);
}



				}//End of particle loop
				//==========================
return true;
}

bool EMconv::Skip (int i, int j, int k) const{
	if(!options.get_flag_TWODMAP_zx() ){
		if(k==int(constants::eta_cell_capa/2.0)){
                  if((i>0 && i<constants::x_cell_capa) && (j>0 && j<constants::y_cell_capa)){
			  return false;
		  }else{
			  return true;
		  }
		}else{ 
			return true;
		}
	}else{
		if(j==int(constants::y_cell_capa/2.0)){
			if((i>0 && i<constants::x_cell_capa) && (k>0 && k<constants::eta_cell_capa)){
				return false;
			}else{
				return true;
			}
		}else{ 
			return true;
		}
	}
}


int EMconv::test(){
return 0;
};
