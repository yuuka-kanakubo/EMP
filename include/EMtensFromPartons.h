#ifndef EMtensFromPartons_H
#define EMtensFromPartons_H

#include "ReadIn.h"
#include "Write.h"
#include "EMconv.h"
#include "Message.h"
#include "Settings.h"
#include "LogSettings.h"
#include "InfoHist.h"
#include "EigenSolve.h"
#include "energymomentumtensor.h"

class EMtensFromPartons{

private:
Settings::Options& options;
LogSettings& log;
std::shared_ptr<Message> ms;
int PrintCounter;
std::shared_ptr<Rndom> rndom;


public:

EMtensFromPartons(Settings::Options options_in, LogSettings log_in);
~EMtensFromPartons();

};
#endif
