#include "EMconv.h"

EMconv::EMconv(std::vector<Container::ParticleInfo> part_1ev_in, std::shared_ptr<Container>& ct_in):part_1ev(part_1ev_in), ct(ct_in){

infohist = std::make_shared<InfoHist>(constants::x_max, constants::y_max, constants::d_x, constants::d_y, 2.0);

};
EMconv::~EMconv(){};

bool EMconv::Convert(){

		//Initialize arrays
		//=============
				double **Hit1ev;
				Hit1ev = new double *[constants::x_cell_capa];
				for(int i_cell=0; i_cell<constants::x_cell_capa; i_cell++){
					Hit1ev[i_cell] = new double [constants::y_cell_capa];
				}
				for(int i=0; i<constants::x_cell_capa; i++){
					for(int j=0; j<constants::y_cell_capa; j++){
						Hit1ev[i][j]=0.0;
					}
				}
				int max_nx = 0, max_ny = 0;
				int NumPair=0;
				int NumTrig=0;

		//Particle loop
		//=============
	for(const auto& part: part_1ev){

		std::cout << part.id << "  "
			<< part.e << "  "
			<< part.px << "  "
			<< part.py << "  "
			<< part.pz << "  "
			<< std::endl;

						double x_val=part.x;
						if(x_val<constants::x_min || x_val>this->infohist->x_max) continue;
						int nx=(int)((x_val/this->infohist->d_x)+(std::fabs(constants::x_min)/this->infohist->d_x));

						double y_val=part.y;
						if(y_val<constants::y_min || y_val>this->infohist->y_max) continue;
						int ny=(int)((y_val/this->infohist->d_y)+(std::fabs(constants::y_min)/this->infohist->d_y));

						if(max_nx<nx) max_nx = nx;
						if(max_ny<ny) max_ny = ny;

						//Tmunu
						//=====
						Hit1ev[nx][ny]+=1.0;

						ct->Hist2D_x[nx][ny]+=x_val;
						ct->Hist2D_y[nx][ny]+=y_val;
						if(ct->max_nx<nx) ct->max_nx=nx;
						if(ct->max_ny<ny) ct->max_ny=ny;

				}//End of particle loop
				//==========================
				
				//Normalization if needed 
				//====================
				//for(int nx = 0; nx<max_nx+1; nx++){
				//	for(int ny = 0; ny<max_ny+1; ny++){
				//		ct->Hist2D[nx][ny]+=Hit1ev[nx][ny]*EVENT.weight()/((double)NumTrig);
				//		ct->Hist2DPartHit[nx][ny]+=Hit1ev[nx][ny]*EVENT.weight();
				//	}
				//}

				//ct->SumWeight+=EVENT.weight();


				for(int i = 0; i < constants::x_cell_capa; i++) {
					delete[] Hit1ev[i];
				}
				delete[] Hit1ev;

return true;
}


//double f_parton(){
//
//
//}


int EMconv::test(){

return 0;
};
