/*
 * global.h
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622, jxz6853
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <pthread.h>
#include <queue>
#include <string>

using namespace std;

extern struct signals;

extern pthread_mutex_t mutex;
extern pthread_cond_t done;
extern queue <string> commands;

#endif /* GLOBAL_H_ */
