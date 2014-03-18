/*
 * Motor.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: jdc9622
 */

#include "Motor.h"
#include "global.h"
#include <iostream>
#include <unistd.h>
#include <time.h>

using namespace std;

#define DEBUG_

static void sigintHandler(int sig){
	#ifdef DEBUG
	cout << "Received signal: " << sig << endl;
	#endif
	cout.flush();
	return;
}

Motor::Motor() {
	// TODO Auto-generated constructor stub
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigintHandler;
	signal(SIGUSR1, sigintHandler);
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void Motor::waitForInput(){
	sem_wait(&commands_semaphore);
	pthread_mutex_lock(&signals_mutex);

	if(signals.lastCommand == "m"){
		if(signals.motorDown){
			signals.motorDown = false;
			signals.motorUp = true;
			openDoor();
		}

		else{
			signals.motorUp = false;
			stopDoor();
		}
	}

	else if(signals.lastCommand == "i"){
		if(signals.motorDown){
			signals.motorDown = false;
			signals.motorUp = true;
			openDoor();
		}
	}

	else if(signals.lastCommand == "r"){
		sleep(1);

		if(signals.doorClosed || (signals.interrupted && signals.doorClosing)){
			signals.motorUp = true;
			openDoor();
			signals.motorUp = false;
		}

		else if(signals.doorOpen || (signals.interrupted && signals.doorOpening)){
			signals.motorDown = true;
			closeDoor();
			signals.motorDown = false;
		}

		else{
			signals.motorDown = false;
			signals.motorUp = false;
			signals.interrupted = true;
			stopDoor();
		}

		signals.buttonPressed = false;
	}
	pthread_mutex_unlock(&signals_mutex);
}

void Motor::openDoor(){
	signals.doorClosed = false;
	signals.interrupted = false;
	signals.doorOpening = true;

	struct timespec tim;
	tim.tv_sec = 10;
	tim.tv_nsec = 0;

	//TODO: Open door stuff
	cout << "\nI am opening the door.\n";
	cout.flush();
//	for(int i = 1; i <= 10; i++){
//		nanosleep(&tim, NULL);
//		cout << i << " seconds passed\n";
//		cout.flush();
//		if(signals.interrupted){
//			cout << "Hi";
//			cout.flush();
//			stopDoor();
//			signals.interrupted = false;
//			return;
//		}
//	}
	if(nanosleep(&tim, NULL) == -1){
		#ifdef DEBUG
		cout << "I was interrupted; returning!\n";
		#endif
		return;
	}
	
	cout << "\nDoor opened\n";
	cout.flush();
	signals.doorOpen = true;
	signals.doorOpening = false;
}

void Motor::closeDoor(){
	signals.doorOpen = false;
	signals.interrupted = false;
	signals.doorClosing = true;

	struct timespec tim;
	tim.tv_sec = 10;
	tim.tv_nsec = 0;

	//TODO: Close door stuff
	cout << "\nI am closing the door.\n";
	cout.flush();
	pthread_mutex_unlock(&signals_mutex);
	if(nanosleep(&tim, NULL) == -1){
		#ifdef DEBUG
		cout << "I was interrupted; returning!\n";
		#endif
		return;
	}

	cout << "\nDoor closed\n";
	cout.flush();
	signals.doorClosed = true;
	signals.doorClosing = false;
}

void Motor::stopDoor(){

	//TODO: Stop door stuff
	cout << "\nI am stopping the door.\n";
	cout.flush();

	cout << "\nDoor stopped\n";
	cout.flush();
}
