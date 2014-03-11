/*
 * Controller.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: Justin Cotner
 */

#include "Controller.hpp"
#include "global.hpp"
#include "Input.hpp"
#include <stdlib.h>
#include <stdio.h>

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char *argv[]) {
	Controller control;
	Input input;

	input.processInput();

	return EXIT_SUCCESS;
}
