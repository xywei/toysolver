/*
 * ParamHandler.h
 *
 *  Created on: Dec 5, 2015
 *      Author: xywei
 */

#ifndef SOURCE_PARAMHANDLER_H_
#define SOURCE_PARAMHANDLER_H_

#include <iostream>
#include <string>

#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

class ParamHandler {
public:
	ParamHandler();
	virtual ~ParamHandler();

	int read_file (const std::string &);
	void display_param () const;
	template <typename T>
	boost::optional<T> look_for (const std::string &) const;

private:
	boost::property_tree::ptree param_tree;
};

#endif /* SOURCE_PARAMHANDLER_H_ */
