#include "EMtensFromPartons.h"

//EMtensFromPartons::EMtensFromPartons(){}
EMtensFromPartons::EMtensFromPartons(Settings::Options options_in, LogSettings log_in):options(options_in), log(log_in), PrintCounter(0){

	ms = std::make_shared<Message>();

	//Storing parton list for one event.
	//=================================
	auto readin = std::make_shared<ReadIn>(this->ms, this->options);


	//Setting for printout
	//===================
	if(constants::MODE.find("timelapse")!=std::string::npos) this->PrintCounter=constants::PrintCounterTL;
	else this->PrintCounter=constants::PrintCounter;


	//EVENT LOOP
	//===========
	for(int i=options.get_beginfile(); i<options.get_nfile(); ++i){
		if(!(i%this->PrintCounter)) ms->read(i);
		std::vector<Container::ParticleInfo> part_1ev;
		readin->read(i, part_1ev);
		readin->show_readin(part_1ev);
	}

	auto emconv = std::make_shared<EMconv>();

	auto writeout = std::make_shared<WriteOut>();

}

EMtensFromPartons::~EMtensFromPartons(){}
