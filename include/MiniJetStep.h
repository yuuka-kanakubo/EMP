#ifndef MINIJETSTEP
#define MINIJETSTEP
#include <iostream>
#include <memory>
#include "Container.h"
#include "Message.h"
#include "Settings.h"

class MiniJetStep{

private:
void Step(std::vector<Container::ParticleInfo> &part_1ev);
void PrintJets(std::vector<Container::ParticleInfo> &part_1ev);

public:

MiniJetStep(std::vector<Container::ParticleInfo> &part_1ev);
~MiniJetStep();




};
#endif
