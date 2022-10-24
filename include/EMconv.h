#ifndef EMCONV_H
#define EMCONV_H
#include <iostream>
#include <memory>
#include <vector>
#include "Container.h" 
#include "InfoHist.h" 

class EMconv{


public:
EMconv(std::vector<Container::ParticleInfo> part_1ev_in, std::shared_ptr<Container>& ct_in);
~EMconv();

private:
std::vector<Container::ParticleInfo> part_1ev;
std::shared_ptr<Container>& ct;
std::shared_ptr<InfoHist> infohist;

bool Convert();
int test();

};
#endif 
