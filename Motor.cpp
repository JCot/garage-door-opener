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

#define DEBUG

static void sigintHandler(int sig){
	#ifdef DEBUG_V
	cout << "Received signal: " << sig << endl;
	signals.interruptMovement = true;
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
		if(signals.doorClosing){
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

		#ifdef DEBUG
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
			(signals.interrupted && signals.doorOpening)){
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
	cout.flush();

	#ifdef DEBUG
	cout << "Opening for: " << (10 - signals.secondsPassed) << " seconds.\n";
	#endif

	int i = 1;
	while(signals.secondsPassed < 10){
		if(nanosleep(&tim, NULL) == -1){
			#ifdef DEBUG_V
			cout << "I was interrupted; returning!\n";
			#endif
			return;
		}
		signals.secondsPassed++;
		#ifdef DEBUG
		cout << "Opening for " << i++ << " seconds...\n";
		#endif
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

	struct timespec tim;
	tim.tv_sec = 1;
	tim.tv_nsec = 0;

	//TODO: Close door stuff
	cout << "I am closing the door.\n";
	cout.flush();
	
	#ifdef DEBUG
	cout << "Closing for: " << signals.secondsPassed << " seconds.\n";
	#endif
	
	int i = 1;
	while(signals.secondsPassed > 0){
		if(nanosleep(&tim, NULL) == -1){
			#ifdef DEBUG_V
			cout << "I was interrupted; returning!\n";
			#endif
			return;
		}
		#ifdef DEBUG
		cout << "Closing for " << i++ << " seconds...\n";
		#endif
		signals.secondsPassed--;
	}

	cout << "Door closed.\n";
	cout.flush();
	signals.doorClosed = true;
	signals.doorClosing = false;
}

void Motor::stopDoor(){

	//TODO: Stop door stuff
	cout << "I am stopping the door.\n";
	cout.flush();

	cout << "Door stopped.\n";
	cout.flush();
}
