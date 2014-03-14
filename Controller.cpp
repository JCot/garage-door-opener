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

extern pthread_mutex_t mutex;
extern pthread_cond_t done;

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

	pthread_t input;
	pthread_t scanner;
	pthread_attr_t attr;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&done, NULL);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	int rc = pthread_create(&input, NULL, startInput, (void *)1);
	//pthread_create(&scanner, NULL, scanInputSignals, (void *)motor);

	if(rc){
		cout << "Something's wrong";
	}

	pthread_join(input, NULL);
	//pthread_join(scanner, NULL);

	//input.processInput();

	return EXIT_SUCCESS;
}
