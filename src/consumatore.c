#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "consumatore.h"
#include "globals.h"

void* consumatore(void*) {
    
    for (int i = 0; i < N_ELEMENTI; i++) {
        
        pthread_mutex_lock(&mutex_cons);

        printf("Dato consumato: %d", dato);
        fflush(stdout);

        pthread_mutex_unlock(&mutex_prod);
        
    }

    pthread_exit(NULL);
    
}