#include "EigenSolve.h"

EigenSolve::EigenSolve(std::shared_ptr<Container>& ct_in):ct(ct_in){
 
  this->Solve();

};
EigenSolve::~EigenSolve(){};


void EigenSolve::Solve(){

//Loop over the entire space in x, y.
//========================================
				for(int i=0; i<constants::x_cell_capa; ++i){
							for(int j=0; j<constants::y_cell_capa; ++j){

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
										});
								const FourVector u = T.landau_frame_4velocity();

								EnergyMomentumTensor TL = T.boosted(u);
								//std::cout << "Eigen vec u " << u << std::endl; 
								//Archiving solutions (e, umu...) in Container.
								//==========================================
								this->ct->Hist2DMultiComp[i][j].eLOCAL = TL[0];
								this->ct->Hist2DMultiComp[i][j].PxLOCAL = TL[4];
								this->ct->Hist2DMultiComp[i][j].pixyLOCAL = TL[5];
								this->ct->Hist2DMultiComp[i][j].PyLOCAL = TL[7];
								this->ct->Hist2DMultiComp[i][j].PzLOCAL = TL[9];

							}
				}
			



return ;
}
