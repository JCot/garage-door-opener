/*
 * Motor.h
 *
 *  Created on: Mar 11, 2014
 *      Author: jdc9622
 */

#ifndef MOTOR_H_
#define MOTOR_H_

class Motor {
public:
	Motor();
	virtual ~Motor();
	void openDoor();
	void closeDoor();
	void stopDoor();
};

#endif /* MOTOR_H_ */