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

Motor::Motor() {
	// TODO Auto-generated constructor stub

}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void Motor::openDoor(){
	pthread_mutex_lock(&signals_mutex);

	struct timespec tim;
	tim.tv_sec = 10;
	tim.tv_nsec = 0;

	//TODO: Open door stuff
	cout << "\nI am opening the door.\n";
	cout.flush();
	if(nanosleep(&tim, NULL) == -1){
		return;
	}

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
	if(nanosleep(&tim, NULL) == -1){
		return;
	}

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
