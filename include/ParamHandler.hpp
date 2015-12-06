/*
 * ParamHandler.hpp
 *
 *  Created on: Dec 5, 2015
 *      Author: xywei
 */

#ifndef PARAMHANDLER_HPP_
#define PARAMHANDLER_HPP_

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
	void display () const;
	template <typename T>
	T get (const std::string &) const;

private:
	boost::property_tree::ptree param_tree;
};

#endif /* PARAMHANDLER_HPP_ */
