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
#include <signal.h>

using namespace std;

static void sigintHandler(int sig){
	return;
}

Motor::Motor() {
	// TODO Auto-generated constructor stub
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigintHandler;

}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void Motor::openDoor(){
	pthread_mutex_lock(&mutex);

	struct timespec tim;
	tim.tv_sec = 10;
	tim.tv_nsec = 0;

	//TODO: Open door stuff
	cout << "\nI am opening the door.\n";
	cout.flush();
//	sleep(10);
	nanosleep(&tim, NULL);

	pthread_cond_signal(&done);
	doorClosed = false;
	cout << "\nDoor opened\n";
	cout.flush();
	doorOpen = true;
	pthread_mutex_unlock(&mutex);
}

void Motor::closeDoor(){
	pthread_mutex_lock(&mutex);

	//TODO: Close door stuff
	cout << "\nI am closing the door.\n";
	sleep(10);

	pthread_cond_signal(&done);
	doorOpen = false;
	cout << "\nDoor closed\n";
	doorClosed = true;
	pthread_mutex_unlock(&mutex);
}

void Motor::stopDoor(){
	pthread_mutex_lock(&mutex);

	//TODO: Stop door stuff
	cout << "\nI am stopping the door.\n";

	pthread_cond_signal(&done);
	cout << "\nDoor stopped\n";
	pthread_mutex_unlock(&mutex);
}
