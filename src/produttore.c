#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "produttore.h"
#include "globals.h"

void* produttore(void*) {
    
    for (int i = 0; i < N_ELEMENTI; i++) {
        
        pthread_mutex_lock(&mutex_prod);

        dato = i + 1;
        printf("[P] prodotto: %d\n", dato);
        fflush(stdout);

        pthread_mutex_unlock(&mutex_cons);

    }

    pthread_exit(NULL);
    
}