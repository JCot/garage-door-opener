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
#include <string>

using namespace std;

//extern pthread_mutex_t signals_mutex;
//extern pthread_cond_t done;

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

	if(!commands.empty()){
		pthread_mutex_lock(&signals_mutex);
		string comm = commands.front();
		commands.pop();
		signals.lastCommand = comm;

		if(comm == "m"){
			signals.motorOvercurrent = true;
			pthread_cond_signal(&done);
			pthread_mutex_unlock(&signals_mutex);
		}

		else if(comm == "i"){
			signals.irInterrupted = true;
			pthread_cond_signal(&done);
			pthread_mutex_unlock(&signals_mutex);
		}

		else if(comm == "r"){
//			signals.buttonPressed = true;
//			sleep(1);
//
//			if(signals.doorClosed){
//				signals.motorUp = true;
//				pthread_mutex_unlock(&signals_mutex);
//				motor->openDoor();
//				pthread_mutex_lock(&signals_mutex);
//				signals.motorUp = false;
//			}
//
//			else if(signals.doorOpen){
//				signals.motorDown = true;
//				pthread_mutex_unlock(&signals_mutex);
//				motor->closeDoor();
//				pthread_mutex_lock(&signals_mutex);
//				signals.motorDown = false;
//			}
//
//			else{
//				signals.motorDown = false;
//				signals.motorUp = false;
//				signals.interrupted = true;
//				pthread_mutex_unlock(&signals_mutex);
//				motor->stopDoor();
//			}
//
//			signals.buttonPressed = false;

			if(!signals.doorClosed && !signals.doorOpen){
				cout << "This is broken";
				cout.flush();
				pthread_kill(motorThread, SIGUSR1);
			}

			else{
				pthread_cond_signal(&done);
				pthread_mutex_unlock(&signals_mutex);
			}
		}

		pthread_cond_signal(&done);
		pthread_mutex_unlock(&signals_mutex);
	}
}

void* startScanner(void *param){
	while(true){
		scanInputSignals(param);
		sleep(1);
	}
}

void* startMotor(void *param){
	Motor* motor = (Motor*)param;
	while(true){
		motor->waitForInput();
	}
}

int main(int argc, char *argv[]) {
	Controller control;
	Motor *motor = new Motor();
	pthread_attr_t attr;

	pthread_mutex_init(&signals_mutex, NULL);
	pthread_cond_init(&done, NULL);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&input, NULL, startInput, (void *)1);
	pthread_create(&scanner, NULL, startScanner, (void *)motor);
	pthread_create(&motorThread, NULL, startMotor, (void*)motor);

	pthread_join(input, NULL);
	pthread_join(scanner, NULL);

	return EXIT_SUCCESS;
}
