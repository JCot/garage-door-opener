/*
 * Input.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622, Jenny Zhen
 */

#include "Input.h"
#include "global.h"
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define SUPPRESS

Input::Input() {
	// TODO Auto-generated constructor stub

}

Input::~Input() {
	// TODO Auto-generated destructor stub
}

void* Input::processInput(){
	while(true){
		string input;
		#ifndef SUPPRESS
		cout << "Please enter a command: ";
		#endif
		getline(cin, input);

		if(input == "m" || input == "i" || input == "r"){
			commands.push(input);
		}

		else{
			cout << "Incorrect input.\n";
		}

		sleep(1);
	}
}
