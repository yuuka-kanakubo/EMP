#ifndef EBYEINSETTINGS_H
#define EBYEINSETTINGS_H
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include "Settings.h" 
#include "Rndom.h" 

class eByeInSettings{


	private:

				ofstream ofs_eBye;

	public:

				//Functions for eBye info
				//----------------------------
				class eByeMulti{
					public:
						EbyeInfo ebye;
						eByeMulti(Settings::Options option_in, const std::string inputpath, shared_ptr<Rndom>& rndom_in):rndom(rndom_in){
							EbyeInfo ebye_;
							this->get_EbyeInfo(option_in, inputpath, ebye_);
							ebye=ebye_;
						}
					private:
						shared_ptr<Rndom>& rndom;
						void get_EbyeInfo(Settings::Options options, const std::string inputpath, EbyeInfo& ebye){
							auto utl_ = make_shared<Util_func>(this->rndom);
							double rap_shift=0.0;
							if(options.get_hist_rapidity_shift() || options.get_flag_pPb_cm_calculation()){
								rap_shift=(options.get_flag_pPb_cm_calculation())? constants::pPb_rap_shift_from_lab_to_cm:options.dlty;
							}
							utl_->get_EbyeInfo_(inputpath, ebye, rap_shift, options.get_flag_VZEROAND_trigger(), options.get_hist_parton_level(), options.get_collision_type());
						}

				};
				void open_eBye_output(const std::string output){
					std::string output_eBye=output+"/"+constants::fname_eByeInfo;
					ofs_eBye.open(output_eBye.c_str());  
				}
				void print_eByeInfo(const int i, const eByeMulti Multi){
					ofs_eBye << i << "  " << Multi.ebye.multiplicity << "  " << Multi.ebye.multiplicity_V0M << "  " << Multi.ebye.weight << endl;
				}


				eByeInSettings(){};
				~eByeInSettings(){};


};
#endif
