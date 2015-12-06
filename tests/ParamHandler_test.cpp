/*
 * ParamHandler_test.cpp
 *
 *  Created on: Dec 5, 2015
 *      Author: xywei
 */

#include "../include/ParamHandler.hpp"

int ParamHandler_test (int argc, char** argv)
{
	assert (argc==1);
	std::string param_filename = argv[1];
	ParamHandler parameters;

	parameters.read_file (param_filename);
	parameters.display ();
	return 0;
}
