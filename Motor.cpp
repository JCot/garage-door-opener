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

using namespace std;

Motor::Motor() {
	// TODO Auto-generated constructor stub

}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void Motor::openDoor(){
	pthread_mutex_lock(&mutex);

	//TODO: Open door stuff
	cout << "\nI am opening the door.\n";
	cout.flush();
	sleep(10);

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
	cout << "I am closing the door.\n";
	sleep(10);

	pthread_cond_signal(&done);
	doorOpen = false;
	cout << "Door closed\n";
	doorClosed = true;
	pthread_mutex_unlock(&mutex);
}

void Motor::stopDoor(){
	pthread_mutex_lock(&mutex);

	//TODO: Stop door stuff
	cout << "I am stopping the door.\n";

	pthread_cond_signal(&done);
	cout << "Door stopped\n";
	pthread_mutex_unlock(&mutex);
}
