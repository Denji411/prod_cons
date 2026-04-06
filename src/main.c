#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "globals.h"
#include "consumatore.h"
#include "produttore.h"

int main() {

    /*
        Domanda 2.1: Nel caso i due mutex fossero stati inizializzati entrambi liberi, il primo produttore avrebbe rischiato di leggere il dato ancora non aggiornato dal produttore.
        
        Domanda 2.2: Se i due mutex fossero invece stati inizializzati acquisiti il processo sarebbe finito in stallo.
            Questo perchè nessuno dei due thread avrebbe potuto sbloccare l'altro e avrebbero cercato entrambi di lockarsi con un mutex già occupato.
    */

    pthread_mutex_init(&mutex_cons, NULL);
    pthread_mutex_init(&mutex_prod, NULL);
    pthread_mutex_lock(&mutex_cons);

    pthread_t prod, cons;
    
    if(pthread_create(&prod, NULL, produttore, NULL) != 0) {
        perror("Errore creazione produttore");
        return EXIT_FAILURE;
    }

    if(pthread_create(&cons, NULL, consumatore, NULL) != 0) {
        perror("Errore creazione consumatore");
        return EXIT_FAILURE;
    }

    /*
        Domanda 5.1: È importante chiamare pthread_join() prima di pthread_mutex_destroy() perchè, nel caso si invertissero, si distruggerebbero i mutex prima che i thread finiscano di utilizzarli, provocando errori.
    */

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex_prod);
    pthread_mutex_destroy(&mutex_cons);
    return EXIT_SUCCESS;

    /*
        Domanda 7.1: Non sarebbe possibile utilizzare questo metodo con due o più produttori perchè si presenterebbe una race condition sulla scrittura del dato.
            Non si potrebbe inoltre determinare quale produttore viene lockato o unlockato.

        Domanda 7.2: 
    */

}