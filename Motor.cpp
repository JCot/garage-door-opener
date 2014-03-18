/*
 * Motor.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: jdc9622, Jenny Zhen
 */

#include "Motor.h"
#include "global.h"
#include <iostream>
#include <unistd.h>
#include <time.h>

using namespace std;

#define DEBUG

static void sigintHandler(int sig){
	#ifdef DEBUG_V
	cout << "Received signal: " << sig << endl;
	#endif
	
	
	// If we get this interrupt while not sleeping, we need another way to 
	// indicate that we should stop.
	signals.interruptMovement = true;
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
		if(signals.doorClosing){
			signals.motorDown = false;
			signals.motorUp = true;
			openDoor();
		}

		else if(signals.doorOpening){
			signals.motorUp = false;
			stopDoor();
		}
	}

	else if(signals.lastCommand == "i"){
		if(signals.doorClosing){
			signals.motorDown = false;
			signals.motorUp = true;
			openDoor();
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
			openDoor();
			signals.motorUp = false;
		}

		else if(signals.doorOpen || 
			(signals.interrupted && signals.doorOpening) ||
			(signals.motorOvercurrent && signals.doorOpening)){
			signals.motorOvercurrent = false;
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
	signals.doorClosing = false;

	struct timespec tim;
	tim.tv_sec = 1;
	tim.tv_nsec = 0;

	//TODO: Open door stuff
	cout << "I am opening the door.\n";
	cout << "\tOpening for: " << (10 - signals.secondsPassed) << " seconds.\n";
	cout.flush();

	int i = 1;
	while(signals.secondsPassed < 10){
		if(nanosleep(&tim, NULL) == -1 || signals.interruptMovement){
			#ifdef DEBUG_V
			cout << "I was interrupted; returning!\n";
			#endif
			signals.interruptMovement = false;
			return;
		}
		signals.secondsPassed++;
		cout << "\t\tOpening for " << i++ << " seconds...\n";
		cout.flush();
	}
	
	cout << "Door opened.\n";
	cout.flush();
	signals.doorOpen = true;
	signals.doorOpening = false;
}

void Motor::closeDoor(){
	signals.doorOpen = false;
	signals.interrupted = false;
	signals.doorClosing = true;
	signals.doorOpening = false;
	signals.irBeamOn = true;
	
	struct timespec tim;
	tim.tv_sec = 1;
	tim.tv_nsec = 0;

	//TODO: Close door stuff
	cout << "I am closing the door.\n\tI am turning on the infrared beam.\n";
	cout << "\tClosing for: " << signals.secondsPassed << " seconds.\n";
	cout.flush();
	
	int i = 1;
	while(signals.secondsPassed > 0){
		if(nanosleep(&tim, NULL) == -1 || signals.interruptMovement){
			#ifdef DEBUG_V
			cout << "I was interrupted; returning!\n";
			#endif
			signals.interruptMovement = false;
			signals.irBeamOn = false;
			return;
		}
		cout << "\t\tClosing for " << i++ << " seconds...\n";
		cout.flush();
		signals.secondsPassed--;
	}

	cout << "Door closed.\n";
	cout.flush();
	signals.doorClosed = true;
	signals.irBeamOn = false;
	signals.doorClosing = false;
}

void Motor::stopDoor(){

	//TODO: Stop door stuff
	cout << "I am stopping the door.\n";
	cout.flush();

	cout << "Door stopped.\n";
	cout.flush();
}
