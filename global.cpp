/*
 * global.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622
 */

#include "global.h"
#include <pthread.h>

bool isButtonPressed = false;
bool isDoorClosed = true;
bool isDoorOpen = false;
bool isDoorOpening = false;
bool isDoorClosing = false;
bool isIRInterrupted = false;
bool isMotorOvercurrent = false;
pthread_mutex_t mutex;
pthread_cond_t done;
