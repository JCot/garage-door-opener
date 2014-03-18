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

static void sigintHandler(int sig){
	cout << "I did something";
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
	pthread_mutex_lock(&signals_mutex);
	pthread_cond_wait(&done, &signals_mutex);

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

		if(signals.doorClosed){
			signals.motorUp = true;
			pthread_mutex_unlock(&signals_mutex);
			openDoor();
			pthread_mutex_lock(&signals_mutex);
			signals.motorUp = false;
			pthread_mutex_unlock(&signals_mutex);
		}

		else if(signals.doorOpen){
			signals.motorDown = true;
			pthread_mutex_unlock(&signals_mutex);
			closeDoor();
			pthread_mutex_lock(&signals_mutex);
			signals.motorDown = false;
			pthread_mutex_unlock(&signals_mutex);
		}

		else{
			signals.motorDown = false;
			signals.motorUp = false;
			signals.interrupted = true;
			pthread_mutex_unlock(&signals_mutex);
			stopDoor();
		}

		signals.buttonPressed = false;
	}
}

void Motor::openDoor(){
	pthread_mutex_lock(&signals_mutex);

	struct timespec tim;
	tim.tv_sec = 10;
	tim.tv_nsec = 0;

	//TODO: Open door stuff
	cout << "\nI am opening the door.\n";
	cout.flush();
//	for(int i = 1; i <= 10; i++){
//		pthread_mutex_unlock(&signals_mutex);
//		nanosleep(&tim, NULL);
//		pthread_mutex_lock(&signals_mutex);
//		cout << i << " seconds passed\n";
//		cout.flush();
//		if(signals.interrupted){
//			cout << "Hi";
//			cout.flush();
//			stopDoor();
//			signals.interrupted = false;
//			pthread_mutex_unlock(&signals_mutex);
//			return;
//		}
//	}
	if(nanosleep(&tim, NULL) == -1){
		cout << "I am returning\n";
		return;
	}
	
	//pthread_mutex_lock(&signals_mutex); already locked at top of function
	signals.doorClosed = false;
	cout << "\nDoor opened\n";
	cout.flush();
	signals.doorOpen = true;
	pthread_mutex_unlock(&signals_mutex);
}

void Motor::closeDoor(){
	pthread_mutex_lock(&signals_mutex);

	struct timespec tim;
	tim.tv_sec = 10;
	tim.tv_nsec = 0;

	//TODO: Close door stuff
	cout << "\nI am closing the door.\n";
	cout.flush();
	pthread_mutex_unlock(&signals_mutex);
	if(nanosleep(&tim, NULL) == -1){
		return;
	}

	pthread_mutex_lock(&signals_mutex);
	signals.doorOpen = false;
	cout << "\nDoor closed\n";
	cout.flush();
	signals.doorClosed = true;
	pthread_mutex_unlock(&signals_mutex);
}

void Motor::stopDoor(){
	pthread_mutex_lock(&signals_mutex);

	//TODO: Stop door stuff
	cout << "\nI am stopping the door.\n";
	cout.flush();

	cout << "\nDoor stopped\n";
	cout.flush();
	pthread_mutex_unlock(&signals_mutex);
}
