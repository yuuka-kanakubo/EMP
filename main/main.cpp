#include "EMtensFromPartons.h"

int main(int argc, char* argv[]){

	std::cout << "Hello:)" << std::endl; 
	auto ms = make_shared<Message>();
	ms->TestMode();

	auto setting = std::make_shared<Settings>(argc, argv);
	auto emp = std::make_shared<EMtensFromPartons>(setting->options, setting->log);

	std::cout << "DONE:)" << std::endl; 

return 0;
}
