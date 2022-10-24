#include "EMP.h"

EMP::EMP(Settings::Options options_in, LogSettings log_in):options(options_in), log(log_in){

	ms = std::make_shared<Message>();

	//Storing parton list for one event.
	//=================================
	std::vector<Container::ParticleInfo> part_1ev;
	auto readin = std::make_shared<ReadIn>(this->ms, this->options, part_1ev);
	readin.read();

	auto emconv = std::make_shared<EMconv>();

	auto writeout = std::make_shared<WriteOut>();

}

EMP::~EMP(){}
