#ifndef WRITEOUT
#define WRITEOUT
#include <iostream>
#include <memory>

class WriteOut{


public:
WriteOut(){
  std::cout << "WriteOut" << std::endl;
}; 
~WriteOut(){};

  int test();

};
#endif 
