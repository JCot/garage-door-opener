/*
 * Controller.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: Justin Cotner, Jenny Zhen
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

#define DEBUG_

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

	if(!commands.empty()){
		#ifdef DEBUG
		cout << "Got a new command!\n";
		cout.flush();
		#endif

		// if we lock the mutex, we cannot recieve anymore 
		// signals until unlocked. Since we want to interrupt actions, 
		// we can't lock on the signals_mutex (since opening/closing 
		// the door locks it).
		//pthread_mutex_lock(&signals_mutex);
		string comm = commands.front();
		commands.pop();
		signals.lastCommand = comm;

		#ifdef DEBUG
		cout << "Processing '" << comm << "'...\n";
		cout.flush();
		#endif

		if(comm == "m"){
			pthread_kill(motorThread, SIGUSR1);
			pthread_mutex_lock(&signals_mutex);
			signals.motorOvercurrent = true;
			pthread_mutex_unlock(&signals_mutex);
			sem_post(&commands_semaphore);
		}

		else if(comm == "i" && signals.irBeamOn){
			pthread_kill(motorThread, SIGUSR1);
			pthread_mutex_lock(&signals_mutex);
			signals.irInterrupted = true;
			pthread_mutex_unlock(&signals_mutex);
			sem_post(&commands_semaphore);
		}

		else if(comm == "r"){
			if(!signals.doorClosed && !signals.doorOpen 
				&& !signals.interrupted && !signals.motorOvercurrent){
				cout << "Interrupting door operation...\n";
				cout.flush();
				pthread_kill(motorThread, SIGUSR1);
			}

			#ifdef DEBUG
			cout << "Waiting for Motor to read signal...\n";
			cout.flush();
			#endif

			// Ensure that motor gets all the commands that were
			// processed.
			sem_post(&commands_semaphore);
		}

		//pthread_cond_signal(&done); Not using anymore?
		pthread_mutex_unlock(&signals_mutex);
	}
}

void* startScanner(void *param){
	while(true){
		scanInputSignals(param);
		sleep(1);
	}
}

void* runMotor(void *param){
	Motor* motor = (Motor*)param;
	while(true){

		sem_wait(&commands_semaphore);
		pthread_mutex_lock(&signals_mutex);

		if(signals.lastCommand == "m"){
			if(signals.doorClosing){
				signals.motorDown = false;
				signals.motorUp = true;
				motor->openDoor();
			}

			else if(signals.doorOpening){
				signals.motorUp = false;
				motor->stopDoor();
			}
		}

		else if(signals.lastCommand == "i"){
			if(signals.doorClosing){
				signals.motorDown = false;
				signals.motorUp = true;
				motor->openDoor();
			}
		}

		else if(signals.lastCommand == "r"){
			sleep(1);

			#ifdef DEBUG_V
			if(signals.interrupted == true){
				cout << "Door interrupted, direction up? " << signals.doorClosing
						<< endl;
			}
			#endif

			if(signals.doorClosed || (signals.interrupted && signals.doorClosing)){
				signals.motorUp = true;
				motor->openDoor();
				signals.motorUp = false;
			}

			else if(signals.doorOpen ||
					(signals.interrupted && signals.doorOpening) ||
					(signals.motorOvercurrent && signals.doorOpening)){
				signals.motorOvercurrent = false;
				signals.motorDown = true;
				motor->closeDoor();
				signals.motorDown = false;
			}

			else{
				signals.motorDown = false;
				signals.motorUp = false;
				signals.interrupted = true;
				motor->stopDoor();
			}

			signals.buttonPressed = false;
		}
		pthread_mutex_unlock(&signals_mutex);
	}
}

int main(int argc, char *argv[]) {
	Controller control;
	Motor *motor = new Motor();
	pthread_attr_t attr;
	cout << "\nWelcome to the Garage Door Opener!\n";
	cout << "The door is closed, motor is off, and infrared beam is off.\n";
	cout << "Enter 'r' to raise/lower door, 'm' for motor overcurrent,"
			<< " 'i' for infrared beam interrupt.\n\n";

	pthread_mutex_init(&signals_mutex, NULL);
	sem_init(&commands_semaphore, 0, 0);
	pthread_cond_init(&done, NULL);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&input, NULL, startInput, (void *)1);
	pthread_create(&scanner, NULL, startScanner, (void *)motor);
	pthread_create(&motorThread, NULL, runMotor, (void*)motor);

	pthread_join(input, NULL);
	pthread_join(scanner, NULL);

	return EXIT_SUCCESS;
}
