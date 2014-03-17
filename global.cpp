/*
 * global.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622
 */

#include "global.h"
#include <pthread.h>
#include <queue>

using namespace std;

typedef struct{
	bool buttonPressed = false;
	bool doorClosed = true;
	bool doorOpen = false;
	bool motorUp = false;
	bool motorDown = false;
	bool irInterruped = false;
	bool irBeamOn = false;
	bool motorOvercurrent = false;
}signals;

pthread_mutex_t signals_mutex;
pthread_cond_t done;
queue <string> commands;
