#ifndef EMP
#define EMP
#include "ReadIn.h"
#include "WriteOut.h"
#include "EMconv.h"
#include "Message.h"
#include "Settings.h"
#include "LogSettings.h"

class EMP{

private:
Settings::Options& options;
LogSettings& log;
std::shared_ptr<Message> ms;

public:
EMP(Settings::Options options_in, LogSettings log_in);
~EMP();


};
#endif
