/*
 * Input.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622
 */

#include "Input.h"
#include "global.h"
#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;

Input::Input() {
	// TODO Auto-generated constructor stub

}

Input::~Input() {
	// TODO Auto-generated destructor stub
}

void* Input::processInput(){
	while(true){
		string input;
		cout << "Please enter a command: ";
		getline(cin, input);

//		if(input == "m"){
//			pthread_mutex_lock(&mutex);
//			motorOvercurrent = true;
//			pthread_cond_wait(&done, &mutex);
//			pthread_mutex_unlock(&mutex);
//		}
//
//		else if(input == "i"){
//			pthread_mutex_lock(&mutex);
//			irInterrupted = true;
//			pthread_cond_wait(&done, &mutex);
//			pthread_mutex_unlock(&mutex);
//		}
//
//		else if(input == "r"){
//			pthread_mutex_lock(&mutex);
//			buttonPressed = true;
//			pthread_cond_wait(&done, &mutex);
//			pthread_mutex_unlock(&mutex);
//		}

		if(input == "m" || input == "i" || input == "r"){
			commands.push(input);
		}

		else{
			cout << "Incorrect input.\n";
		}
	}
}
