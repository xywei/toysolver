/*
 * ParamHandler.cpp
 *
 *  Created on: Dec 5, 2015
 *      Author: xywei
 */

#include "ParamHandler.hpp"

ParamHandler::ParamHandler() {
	// TODO Auto-generated constructor stub

}

ParamHandler::~ParamHandler() {
	// TODO Auto-generated destructor stub
}

int ParamHandler::read_file (const std::string & param_file) {
	assert (param_file.size ()>0);
	boost::property_tree::ini_parser::read_ini (param_file, param_tree);
	return 0;
}

void ParamHandler::display () const {
	for (auto& section : param_tree)
	{
		std::cout << '[' << section.first << "]" << std::endl;
		for (auto& key : section.second)
			std::cout << key.first << "=" << key.second.get_value<std::string>() << std::endl;
	}
}

template <typename T>
T ParamHandler::get (const std::string & key_name) const {
	// If get fails, exception is thrown:
	//  - If path does not exist, it will be ptree_bad_path exception.
	//  - If value could not be translated, it will be ptree_bad_data.
	return param_tree.get<T>(key_name);
}
