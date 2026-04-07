#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "produttore.h"
#include "globals.h"

void* produttore(void*) {
    
    /*
        Domanda 3.1:
            Alla prima iterazione, mutex_prod è libero e di conseguenza non si blocca.
            Questo perché dev'essere il primo ad operare, fornendo un dato da dare al consumatore.

        Domanda 3.2: 
            Dopo pthread_mutex_unlock(&mutex_cons), il produttore non può immediatamente rientrare nel ciclo e riscrivere dato.
            Questo perché il produttore deve aspettare che mutex_prod si sblocchi, operazione che avviene solo dopo che il consumatore ha letto il dato.
    */

    for (int i = 0; i < N_ELEMENTI; i++) {
        
        pthread_mutex_lock(&mutex_prod);

        dato = i + 1;
        printf("[P] prodotto: %d\n", dato);
        fflush(stdout);

        pthread_mutex_unlock(&mutex_cons);

    }

    pthread_exit(NULL);
    
}