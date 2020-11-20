#pragma once
#include <iostream>
#include <string>

void error(std::string msg) {
	std::cout << "ERROR: " << msg << std::endl;
	std::cin.get();
	exit(EXIT_FAILURE);
}