/*
 * Controller.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: Justin Cotner
 * 				Jenny Zhen
 */

#include "Controller.h"
#include "global.h"
#include "Input.h"
#include "Motor.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <signal.h>


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
	Motor* motor = (Motor*)param;

	if(!commands.empty()){
		pthread_mutex_lock(&signals_mutex);
		string comm = commands.front();
		commands.pop();

		if(comm == "m"){
			signals.motorOvercurrent = true;
		}

		else if(comm == "i"){
			if(signals.irBeamOn){
				signals.irInterrupted = true;
				motor->stopDoor();
				signals.irBeamOn = false;
				motor->openDoor();
			}
		}

		else if(comm == "r"){
			signals.buttonPressed = true;
			sleep(1);

			if(signals.doorClosed){
				signals.motorUp = true;
				pthread_mutex_unlock(&signals_mutex);
				motor->openDoor();
				sleep(2);
				pthread_kill(scanner, SIGUSR1);
				pthread_mutex_lock(&signals_mutex);
				signals.motorUp = false;
			}

			else if(signals.doorOpen){
				signals.motorDown = true;
				signals.irBeamOn = true;
				pthread_mutex_unlock(&signals_mutex);
				motor->closeDoor();
				pthread_mutex_lock(&signals_mutex);
				signals.motorDown = false;
				signals.irBeamOn = false;
			}

			else{
				signals.motorDown = false;
				signals.motorUp = false;
				pthread_kill(scanner, SIGUSR1);
				motor->stopDoor();
			}

			signals.buttonPressed = false;
			pthread_mutex_unlock(&signals_mutex);
		}
	}
}

void* startScanner(void *param){
	while(true){
		scanInputSignals(param);
		sleep(1);
	}
}

void Controller::run(){
	Motor *motor = new Motor();

	pthread_t input;
	pthread_t scanner;
	pthread_t motorThread;

	// To explicitly create a thread as joinable or detached, the attr argument 
	// in the pthread_create() routine is used.
	pthread_attr_t attr;

	// Initialize mutex and condition variable objects.
	pthread_mutex_init(&signals_mutex, NULL);
	pthread_cond_init(&done, NULL);

	// Initialize and set thread detached attribute.
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	/* The first thread just takes the input from the keyboard and throws it on 
		a queue of commands if it is valid input.
		The second thread goes through the queue executing commands. */
	pthread_create(&input, NULL, startInput, (void *)1);
	pthread_create(&scanner, NULL, startScanner, (void *)motor);
//	pthread_create(&motorThread, NULL, NULL, NULL);

	pthread_join(input, NULL);
	pthread_join(scanner, NULL);
//	pthread_join(motorThread, NULL);

	//input.processInput();
}

int main(int argc, char *argv[]) {
	Controller control;

//	control.run();
	Motor *motor = new Motor();

	pthread_t input;
	pthread_t scanner;
	pthread_t motorThread;

	// To explicitly create a thread as joinable or detached, the attr argument
	// in the pthread_create() routine is used.
	pthread_attr_t attr;

	// Initialize mutex and condition variable objects.
	pthread_mutex_init(&signals_mutex, NULL);
	pthread_cond_init(&done, NULL);

	// Initialize and set thread detached attribute.
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	/* The first thread just takes the input from the keyboard and throws it on
	a queue of commands if it is valid input.
	The second thread goes through the queue executing commands. */
	pthread_create(&input, NULL, startInput, (void *)1);
	pthread_create(&scanner, NULL, startScanner, (void *)motor);
	pthread_create(&motorThread, NULL, NULL, NULL);

	pthread_join(input, NULL);
	pthread_join(scanner, NULL);
	pthread_join(motorThread, NULL);

	//input.processInput();

	return EXIT_SUCCESS;
}
