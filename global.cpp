/*
 * global.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: jdc9622, Jenny Zhen
 */

#include "global.h"
#include <pthread.h>
#include <queue>

using namespace std;

SIGNALS signals{false, true, false, false, false, false, false, 
false, false, false, false, false, "", 0};

pthread_mutex_t signals_mutex;
sem_t commands_semaphore;
pthread_cond_t done;
pthread_t input;
pthread_t scanner;
pthread_t motorThread;
queue <string> commands;
