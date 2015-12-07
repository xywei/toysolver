/*******************************************************************************
 * Copyright (c) 2015 Xiaoyu Wei.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 * 	Xiaoyu Wei
 *******************************************************************************/

#include <iostream>
#include <boost/range/irange.hpp>

#include <ParamHandler.hpp>

int main (int argc, char** argv)
{
	std::cout << "Hello, this is ToySolver!" << std::endl;
	std::cout << "You gave me "<< argc << " arguments:" << std::endl;
	for (auto i : boost::irange<int> (0,argc))
		std::cout << "# " << i << "-th: " << argv[i] << std::endl;

	assert (argc==2);
	std::string param_filename = argv[1];
	ParamHandler parameters;

	parameters.read_file (param_filename);
	parameters.display ();
	return 0;
}
