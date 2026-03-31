#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>

#define N_ELEMENTI 10

extern int dato;

extern pthread_mutex_t mutex_cons;
extern pthread_mutex_t mutex_prod;

#endif