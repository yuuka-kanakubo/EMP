#ifndef READIN
#define READIN
#include <iostream>
#include <memory>
#include "Container.h"
#include "Message.h"
#include "Settings.h"

class ReadIn{

private:
std::shared_ptr<Message> ms;
Settings::Options options;


public:
ReadIn(shared_ptr<Message> ms_in, Settings::Options options_in);
~ReadIn(){};

bool read(const int i, std::vector<Container::ParticleInfo> &part_1ev);
bool show_readin(std::vector<Container::ParticleInfo> part_1ev){

std::cout << "Showing readin data " << std::endl;
for(const auto& elem: part_1ev)
std::cout << elem.id << "  "
	<< elem.e << "  "
	<< elem.px << "  "
	<< elem.py << "  "
	<< elem.pz << "  "
	<< std::endl;

std::cout << "-->Showing readin data " << std::endl;
return true;
};

int test();
};
#endif
