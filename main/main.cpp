#include "EMP.h"

int main(int argc, char* argv[]){

	std::cout << "Hello:)" << std::endl; 
	auto ms = make_shared<Message>();
	ms->TestMode();

	auto setting = std::make_shared<Settings>();
	auto emp = std::make_shared<EMP>(setting->options, setting->log);

	std::cout << "DONE:)" << std::endl; 

return 0;
}
