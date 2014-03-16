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
#include <iostream>;

using namespace std;

extern pthread_mutex_t mutex; // mutex variable
extern pthread_cond_t done; // condition variable

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void* startInput(void *param){
	Input input;
	input.processInput();
}

void* scanInputSignals(void *param){
	Motor* motor = (Motor *)param;
	if(isButtonPressed){
		if(isDoorClosed){
			motor->openDoor();
		}

		if(isDoorOpen){
			motor->closeDoor();
		}

		else{
			motor->stopDoor();
		}
	}
}

int main(int argc, char *argv[]) {
	Controller control;
	Motor motor;
	int rc;

	pthread_t input;
	pthread_t scanner;
	
	// To explicitly create a thread as joinable or detached, the attr argument 
	// in the pthread_create() routine is used.
	pthread_attr_t attr;

	// Initialize mutex and condition variable objects.
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&done, NULL);

	// Initialize and set thread detached attribute.
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	rc = pthread_create(&input, NULL, startInput, (void *)1);
	//pthread_create(&scanner, NULL, scanInputSignals, (void *)motor);

	if(rc){
		cout << "Something's wrong";
	}

	pthread_join(input, NULL);
	//pthread_join(scanner, NULL);

	//input.processInput();

	return EXIT_SUCCESS;
}
