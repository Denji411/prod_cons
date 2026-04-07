#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "consumatore.h"
#include "globals.h"

void* consumatore(void*) {

    /*
        Domanda 4.1:
            Alla prima iterazione, mutex_cons è acquisito e di conseguenza si blocca.
            Questo perché deve leggere il dato fornito dal produttore, e deve quindi aspettare che glielo fornisca.

        Domanda 4.2:
            mutex_cons -> acquisito dal main immediatamente.
            prima iterazione:
                mutex_prod -> acquisito dal produttore.
                il produttore inserisce il dato.
                mutex_cons -> rilasciato dal produttore - da il permesso al consumatore di fare lock.
                inizia la seconda iterazione del produttore, ma dato che cerca di fare lock su un mutex già occupato, va in attesa.

                mutex_cons -> acquisito dal consumatore.
                il consumatore legge il dato.
                mutex_prod -> rilasciato dal consumatore - da il permesso al produttore di fare lock.
                inizia la seconda iterazione del consumatore, ma dato che cerca di fare lock su un mutex già occupato, va in attesa.
            seconda iterazione: 
                il produttore termina l'attesa e esegue la stessa cosa della prima iterazione.
                il consumatore termina l'attesa e esegue la stessa cosa della prima iterazione.
    */
    
    for (int i = 0; i < N_ELEMENTI; i++) {
        
        pthread_mutex_lock(&mutex_cons);

        printf("[C] consumato: %d\n", dato);
        fflush(stdout);

        pthread_mutex_unlock(&mutex_prod);
        
    }

    pthread_exit(NULL);
    
}