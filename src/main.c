#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "globals.h"
#include "consumatore.h"
#include "produttore.h"

#define NS_PER_SECONDS 1000000000

void sub_clocktime(struct timespec t1, struct timespec t2, struct timespec *td) {
    td -> tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td -> tv_sec = t2.tv_sec - t1.tv_sec;

    if (td -> tv_sec > 0 && td -> tv_nsec < 0) {
        td -> tv_nsec += NS_PER_SECONDS;
        td -> tv_sec--;
    }

    if (td -> tv_sec < 0 && td -> tv_nsec > 0) {
        td -> tv_nsec -= NS_PER_SECONDS;
        td -> tv_sec++;
    }
}

int main() {

    /*
        Domanda 2.1: Nel caso i due mutex fossero stati inizializzati entrambi liberi, il primo produttore avrebbe rischiato di leggere il dato ancora non aggiornato dal produttore.
        
        Domanda 2.2: Se i due mutex fossero invece stati inizializzati acquisiti il processo sarebbe finito in stallo.
            Questo perchè nessuno dei due thread avrebbe potuto sbloccare l'altro e avrebbero cercato entrambi di lockarsi con un mutex già occupato.
    */

    pthread_mutex_init(&mutex_cons, NULL);
    pthread_mutex_init(&mutex_prod, NULL);
    pthread_mutex_lock(&mutex_cons);

    struct timespec start, finish, delta;
    pthread_t prod, cons;
    
    clock_gettime(CLOCK_REALTIME, &start);

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

    clock_gettime(CLOCK_REALTIME, &finish);
    sub_clocktime(start, finish, &delta);

    printf("Durata scambio prod/cons: %ld.%.9ld\n", delta.tv_sec, delta.tv_nsec);

    pthread_mutex_destroy(&mutex_prod);
    pthread_mutex_destroy(&mutex_cons);
    return EXIT_SUCCESS;

    /*
        Domanda 7.1:
            Non sarebbe possibile utilizzare questo metodo con due o più produttori perchè si presenterebbe una race condition sulla scrittura del dato.
            Non si potrebbe inoltre determinare quale produttore viene lockato o unlockato.

        Domanda 7.2: 
            1. Il produttore non aspetterebbe mai il consumatore e sfornerebbe prodotti non curante di se stanno venendo consumati;
            2. Il conumatore non unlockerebbe mai, provocandogli uno stato di stallo perpetuo.

        Domanda 7.3:
            Il throughput massimo di questo sistema è di circa 1052 scambi al secondo.
            Questo dipende dalla velocità di entrambi, si il produttore che il consumatore, di eseguire le loro operazioni.

        Domanda 7.4:
            Questa pratica si chiama rendez-vous e permette a due thread di aspettarsi a vicenda quando devono operare insieme.
            Vantaggi: Evita problemi di condivisione dati tra threads, permette di evitare la gestione dei buffer.
            Svantaggi: I threads non lavorano mai veramente in parallelo, ma uno aspetta sempre l'altro.
    */

}