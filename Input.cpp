/*
 * Input.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622
 */

#include "Input.hpp"
#include <iostream>
#include "global.hpp"

using namespace std;

Input::Input() {
	// TODO Auto-generated constructor stub

}

Input::~Input() {
	// TODO Auto-generated destructor stub
}

void Input::processInput(){
	while(true){
		char input;
		cout << "Please enter a command: ";
		cin >> input;

		if(input == 'm'){
			isMotorOvercurrent = true;
		}

		else if(input == 'i'){
			isIRInterrupted = true;
		}

		else if(input == 'r'){
			isButtonPressed = true;
		}

		else{
			cout << "Incorrect input.\n";
		}
	}
}
