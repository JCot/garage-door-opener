/*
 * Input.h
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622, Jenny Zhen
 */

#ifndef INPUT_H_
#define INPUT_H_

/**
* Class Input receives user input through key presses.
* Simulates a remote control.
**/
class Input {
public:
	Input();
	virtual ~Input();
	void* processInput();
};

#endif /* INPUT_H_ */
