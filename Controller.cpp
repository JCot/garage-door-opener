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
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <time.h>
#include <signal.h>
#include <string>

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

	while(true){
		if(!commands.empty()){
			pthread_mutex_lock(&mutex);
			string comm = commands.front();
			commands.pop();

			if(comm == "m"){
				motorOvercurrent = true;
				pthread_mutex_unlock(&mutex);
			}

			else if(comm == "i"){
				if(irBeamOn){
					irInterrupted = true;
					pthread_mutex_unlock(&mutex);
				}
			}

			else if(comm == "r"){
				buttonPressed = true;
				sleep(1);

				if(doorClosed){
					motorUp = true;
					pthread_mutex_unlock(&mutex);
					motor->openDoor();
					pthread_mutex_lock(&mutex);
					motorUp = false;
					pthread_mutex_unlock(&mutex);
				}

				else if(doorOpen){
					motorDown = true;
					irBeamOn = true;
					pthread_mutex_unlock(&mutex);
					motor->closeDoor();
					pthread_mutex_lock(&mutex);
					motorDown = false;
					irBeamOn = false;
					pthread_mutex_unlock(&mutex);
				}

				else{
					pthread_mutex_unlock(&mutex);
					pthread_kill(motor, 7);
					motor->stopDoor();
				}

				buttonPressed = false;
			}
		}
	}

//	pthread_mutex_lock(&mutex);

//	if(buttonPressed){
//		if(doorClosed){
//			motorUp = true;
//			pthread_mutex_unlock(&mutex);
//			motor->openDoor();
//			pthread_mutex_lock(&mutex);
//			motorUp = false;
//			pthread_mutex_unlock(&mutex);
//		}
//
//		if(doorOpen){
//			motorDown = true;
//			pthread_mutex_unlock(&mutex);
//			motor->closeDoor();
//			pthread_mutex_lock(&mutex);
//			motorDown = false;
//			pthread_mutex_unlock(&mutex);
//		}
//
//		else{
//			pthread_mutex_unlock(&mutex);
//			motor->stopDoor();
//		}
//
//		buttonPressed = false;
//	}
}

void * startScanner(void *param){
	while(true){
		scanInputSignals(param);
		sleep(1);
	}
}

int main(int argc, char *argv[]) {
	Controller control;
	Motor *motor = new Motor();

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

	pthread_create(&input, NULL, startInput, (void *)1);
	pthread_create(&scanner, NULL, startScanner, (void *)motor);

	pthread_join(input, NULL);
	pthread_join(scanner, NULL);

	//input.processInput();

	return EXIT_SUCCESS;
}
