#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "globals.h"
#include "consumatore.h"
#include "produttore.h"

int main() {

    pthread_mutex_init(&mutex_cons, NULL);
    pthread_mutex_init(&mutex_prod, NULL);
    pthread_mutex_lock(&mutex_cons);

    pthread_t prod, cons;
    
    if(!pthread_create(&prod, NULL, produttore, NULL)) {
        perror("Errore creazione produttore");
        return EXIT_FAILURE;
    }

    if(!pthread_create(&cons, NULL, consumatore, NULL)) {
        perror("Errore creazione consumatore");
        return EXIT_FAILURE;
    }

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex_prod);
    pthread_mutex_destroy(&mutex_cons);
    pthread_exit(NULL);

}