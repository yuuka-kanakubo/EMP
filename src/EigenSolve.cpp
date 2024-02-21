#include "EigenSolve.h"

EigenSolve::EigenSolve(std::shared_ptr<Container>& ct_in, Settings::Options& options_in):ct(ct_in), options(options_in){
 
	eos = std::make_shared<EOS>(30, 3600);
	this->Solve();

};
EigenSolve::~EigenSolve(){};


void EigenSolve::Solve(){

	//Loop over the entire space in x, y.
	//========================================
	int COUNTER=0;

	int max_i=constants::x_cell_capa;
	int max_j=constants::y_cell_capa;
	if(options.get_flag_TWODMAP_zx()){
		max_i=constants::eta_cell_capa;
		max_j=constants::x_cell_capa;
	}
	for(int i=0; i<max_i; ++i){
							for(int j=0; j<max_j; ++j){

								//Solve the eigenvalue problem for each Tmunu at each cell.
								//======================================================
								//EnergyMomentumTensor T(
								//		{100., 1.0, 10., 3.3, 30.0, 4.3, 5.5, 29.9, 11.0, 40.0});
								EnergyMomentumTensor T({
										this->ct->Hist2DMultiComp[i][j].tt,
										this->ct->Hist2DMultiComp[i][j].tx,
										this->ct->Hist2DMultiComp[i][j].ty,
										this->ct->Hist2DMultiComp[i][j].tz,
										this->ct->Hist2DMultiComp[i][j].xx,
										this->ct->Hist2DMultiComp[i][j].xy,
										this->ct->Hist2DMultiComp[i][j].xz,
										this->ct->Hist2DMultiComp[i][j].yy,
										this->ct->Hist2DMultiComp[i][j].yz,
										this->ct->Hist2DMultiComp[i][j].zz
										});//T^munu
								const FourVector u = T.landau_frame_4velocity();
								double e_COLLIDER = T.GetEigenVal();

								//Get PL = T_mu nu l^nu l^mu
								//=======================
								double P_L = this->Tmunu_lmulnu(u, T);
								double P = -(1.0/3.)*this->Tmunu_Deltamunu(e_COLLIDER, T); 
								double P_T = 0.50*(3.*P-P_L); 
								double Pizz = PiMunu(9, u, T, e_COLLIDER);

								EnergyMomentumTensor TL = T.boosted(u);


								//Sanity check
								//===============
								const FourVector u__DUMMY = TL.landau_frame_4velocity();
								double e_LOCALRST = TL.GetEigenVal();
								double PizzLOCAL = PiMunu(9, u__DUMMY, TL, e_LOCALRST);
								if(COUNTER < 5 && this->ct->Hist2DMultiComp[i][j].tt>constants::DECENT){

									double P_LOCALRST = -(1.0/3.)*this->Tmunu_Deltamunu(e_LOCALRST, TL); 

									//Here I am checking if u given by energymomentumtensor.cc 
									//is actually covariant  vector, i.e. u_mu, or u^mu.
									//===========================================================================================================
									double uTu_ =uTu(T,u); 

									std::cout << "e_COLLIDER: " << e_COLLIDER << ",  umu : " << u << std::endl;
									std::cout << "e_LOCALRST: " << e_LOCALRST << ",  umu : " << u__DUMMY << std::endl;
									std::cout << "uTu       : " << uTu_ << std::endl;//it is u_mu
									std::cout << "P_COLLIDER    : " << P << std::endl;
									std::cout << "P_LOCALRST    : " << P_LOCALRST << std::endl;
									if(fabs(P-P_LOCALRST)>constants::SMALL){
										std::cout << "Lorentz invariant valuable is not invariant under the rotation. Something is weired." << std::endl;
										exit(EXIT_FAILURE);
									}
									std::cout << "P_L, P_T: " << P_L << ",  " << P_T << std::endl;
									std::cout << std::endl;
									COUNTER++;
								}

								//std::cout << "Eigen vec u " << u << std::endl; 
								//eos->s_en(val, 0.0)
								//Archiving solutions (e, umu...) in Container.
								//==========================================
								this->ct->Hist2DMultiComp[i][j].ttLOCAL = TL[0];
								this->ct->Hist2DMultiComp[i][j].xxLOCAL = TL[4];
								this->ct->Hist2DMultiComp[i][j].xyLOCAL = TL[5];
								this->ct->Hist2DMultiComp[i][j].yyLOCAL = TL[7];
								this->ct->Hist2DMultiComp[i][j].zzLOCAL = TL[9];
								this->ct->Hist2DMultiComp[i][j].P = P;
								this->ct->Hist2DMultiComp[i][j].e = e_COLLIDER;
								this->ct->Hist2DMultiComp[i][j].zzLOCAL=TL[9];
								this->ct->Hist2DMultiComp[i][j].P_T = P_T;
								this->ct->Hist2DMultiComp[i][j].P_L = P_L;
								this->ct->Hist2DMultiComp[i][j].pizzLOCAL = PizzLOCAL;
								this->ct->Hist2DMultiComp[i][j].pizz = Pizz;

							}
				}
			



return ;
}
