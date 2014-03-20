/*
 * Controller.h
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622, Jenny Zhen
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

/**
* Class Controller takes user input from Input class and translate it for 
* the Motor class to use to perform garage door opener operations.
**/
class Controller {
public:
	Controller();
	virtual ~Controller();
};

#endif /* CONTROLLER_H_ */
