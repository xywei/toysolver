/*
 * ParamHandler.cpp
 *
 *  Created on: Dec 5, 2015
 *      Author: xywei
 */

#include "ParamHandler.h"

ParamHandler::ParamHandler() {
	// TODO Auto-generated constructor stub

}

ParamHandler::~ParamHandler() {
	// TODO Auto-generated destructor stub
}

int ParamHandler::read_file (const std::string & param_file) {
	assert (param_file.size>0);
	boost::property_tree::ini_parser::read_ini (param_file, param_tree);
	return 0;
}

void ParamHandler::display_param () const {
	for (auto& section : param_tree)
	{
		std::cout << '[' << section.first << "]" << std::endl;
		for (auto& key : section.second)
			std::cout << key.first << "=" << key.second.get_value<std::string>() << std::endl;
	}
}

template <typename T>
boost::optional<T> ParamHandler::look_for (const std::string & key_name) const {

}
