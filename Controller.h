/*
 * Controller.h
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <pthread.h>

class Controller {

public:
	Controller();
	virtual ~Controller();
	void run();
};

#endif /* CONTROLLER_H_ */
