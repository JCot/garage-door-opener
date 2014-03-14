/*
 * Motor.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: jdc9622
 */

#include "Motor.h"
#include "global.h"
#include <iostream>

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
	cout << "I am opening the door.";

	pthread_cond_signal(&done);
	cout << "Door opened";
	pthread_mutex_unlock(&mutex);
}

void Motor::closeDoor(){
	pthread_mutex_lock(&mutex);

	//TODO: Close door stuff
	cout << "I am closing the door.";

	pthread_cond_signal(&done);
	cout << "Door closed";
	pthread_mutex_unlock(&mutex);
}

void Motor::stopDoor(){
	pthread_mutex_lock(&mutex);

	//TODO: Stop door stuff
	cout << "I am stopping the door.";

	pthread_cond_signal(&done);
	cout << "Door stopped";
	pthread_mutex_unlock(&mutex);
}
