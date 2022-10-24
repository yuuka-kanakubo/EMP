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

bool read(std::vector<Container::ParticleInfo> &part_1ev);
  int test();
};
#endif
