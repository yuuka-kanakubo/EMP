#ifndef MINIJETSTEP
#define MINIJETSTEP
#include <iostream>
#include <memory>
#include <random>
#include "Container.h"
#include "Message.h"
#include "Settings.h"

class MiniJetStep{

private:
void Step(std::vector<Container::ParticleInfo> &part_1ev);
void PrintJets(std::vector<Container::ParticleInfo> &part_1ev);
void SetFormationTime(std::vector<Container::ParticleInfo> &part_1ev);
std::ranlux48 generator_unidist1;
std::ranlux48 generator_unidist2;
double sqrt_s;


public:

MiniJetStep(std::vector<Container::ParticleInfo> &part_1ev, Settings::Options& options);
~MiniJetStep();


};
#endif
