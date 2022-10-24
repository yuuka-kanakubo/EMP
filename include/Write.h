#ifndef WRITE
#define WRITE
#include "InfoHist.h" 
#include "Util_func.h" 
#include "Message.h" 
#include <memory>

class Write{

private:

		std::shared_ptr<Message> ms;  
		Settings::Options options;
		std::shared_ptr<InfoHist> infohist;
		std::shared_ptr<Util_func> uf;

public:

Write(std::shared_ptr<Message> ms_in, Settings::Options options_in, std::shared_ptr<InfoHist> info, std::shared_ptr<Util_func> uf);
~Write();
		int getMapEdgeX(const double maxval);
		int getMapEdgeY(const double maxval);
		bool write(const std::string& fname, const std::shared_ptr<Container>& ct);
		bool write_RtYield(const std::string& fname, const std::shared_ptr<Container>& ct);

};
#endif
