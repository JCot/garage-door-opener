/*
 * Controller.h
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <pthread>

class Controller {

public:
	Controller();
	virtual ~Controller();

private:
	pthread_t input;
	pthread_t scanner;
	pthread_t motorThread;
};

#endif /* CONTROLLER_H_ */
