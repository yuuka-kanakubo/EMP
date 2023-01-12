#include "EMP.h"

//EMP::EMP(){}
EMP::EMP(Settings::Options options_in, LogSettings log_in):options(options_in), log(log_in), PrintCounter(0){

	ms = std::make_shared<Message>();

	//Storing parton list for one event.
	//=================================
	auto readin = std::make_shared<ReadIn>(this->ms, this->options);
	auto ct = std::make_shared<Container>(this->options);
	auto uf = std::make_shared<Util_func>(this->rndom);
	auto info = std::make_shared<InfoHist>(constants::x_max, constants::y_max, constants::d_x, constants::d_y, 2.0);

	//Setting for printout
	//======================
	if(constants::MODE.find("timelapse")!=std::string::npos) this->PrintCounter=constants::PrintCounterTL;
	else this->PrintCounter=constants::PrintCounter;

	//EVENT LOOP
	//===========
	for(int i=options.get_beginfile(); i<options.get_nfile(); ++i){
		if(!(i%this->PrintCounter)) ms->read(i);
		std::vector<Container::ParticleInfo> part_1ev;
		readin->read(i, part_1ev);
		readin->show_readin(part_1ev, false);

		//Converting energy and momentum into EMtensor
		//==============================================
		auto emconv = std::make_shared<EMconv>(part_1ev, ct);


		//Under construction: Getting e from Tmunu.
		//=========================================
                auto Eigen = std::make_shared<EigenSolve>(ct);


		//Write out in 2D format.
		//==============================================
		//Making output directory name
		//-----------------------------
		std::string generated_directory_name=uf->get_output_directory(options.get_out_directory_name());
		uf->make_output_directory(generated_directory_name);
		auto write = std::make_shared<Write>(ms, options, info, uf);
                write->write(generated_directory_name, ct); 

	}



}

EMP::~EMP(){}