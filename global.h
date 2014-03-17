/*
 * global.h
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <pthread.h>
#include <queue>

using namespace std;

typedef struct{
	bool buttonPressed;
	bool doorClosed;
	bool doorOpen;
	bool motorUp;
	bool motorDown;
	bool irInterrupted;
	bool irBeamOn;
	bool motorOvercurrent;
}SIGNALS;

extern SIGNALS signals;
extern pthread_mutex_t signals_mutex;
extern pthread_cond_t done;
extern pthread_t input;
extern pthread_t scanner;
extern queue <string> commands;

#endif /* GLOBAL_H_ */
