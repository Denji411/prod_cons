#ifndef GLOBALS_H
#define GLOBALS_H

#include <pthread.h>

/*
    Domanda 1.1:
        La variabile "dato" è globale e non esclusiva del main perché dev'essere aggiornabile e accessibile dai thread.
        Entrambi non devono restituire valori al main ma lavorare sullo stesso valore comune.
    
    Domanda 1.2:
        In totale verranno scambiati N_ELEMENTI (in questo caso 10) valori.
*/

#define N_ELEMENTI 10

extern int dato;

extern pthread_mutex_t mutex_cons;
extern pthread_mutex_t mutex_prod;

#endif