/*
 * global.h
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <pthread.h>

extern bool isButtonPressed;
extern bool isDoorClosed;
extern bool isDoorOpen;
extern bool isDoorOpening;
extern bool isDoorClosing;
extern bool isIRInterrupted;
extern bool isMotorOvercurrent;
extern pthread_mutex_t mutex;
extern pthread_cond_t done;

#endif /* GLOBAL_H_ */
