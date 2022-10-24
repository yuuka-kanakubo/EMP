#ifndef EMtensFromPartons_H
#define EMtensFromPartons_H

#include "ReadIn.h"
#include "WriteOut.h"
#include "EMconv.h"
#include "Message.h"
#include "Settings.h"
#include "LogSettings.h"

class EMtensFromPartons{

private:
Settings::Options& options;
LogSettings& log;
std::shared_ptr<Message> ms;
int PrintCounter;

public:

EMtensFromPartons(Settings::Options options_in, LogSettings log_in);
~EMtensFromPartons();

};
#endif
