/*
 * Controller.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: Justin Cotner
 */

#include "Controller.h"
#include "global.h"
#include "Input.h"
#include "Motor.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char *argv[]) {
	Controller control;
	Input input;
	Motor motor;

	pthread_t threads[4];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	int rc = pthread_create(&threads[0], NULL, input.processInput(), NULL);

	input.processInput();

	return EXIT_SUCCESS;
}
