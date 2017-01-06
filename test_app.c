#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "hash.h"

HashTable *ht1; // space allocated inside library

typedef struct PARAMETER {
    int start, end;
    int val;
} Parameter;

void * insertThread(void * ptr) {

    Parameter * parameter = (Parameter *) ptr;

    int i = 0;

    for (i = parameter->start; i < parameter->end; i++) {
        hash_insert(ht1, i, parameter->val);
    }

    pthread_exit(NULL);
}

void * deleteThread(void * ptr) {

    Parameter * parameter = (Parameter *) ptr;

    int i = 0;

    for (i = parameter->start; i < parameter->end; i++) {
        while (hash_delete(ht1, i) < 0);
    }

    pthread_exit(NULL);
}

int main(int argc, char ** args) {
    int i, j;

    int N = atoi(args[1]), M = atoi(args[2]);

    ht1 = hash_init(N, M);

    int nthreads = 5;
    int iret;

    int C = 500;

    Parameter parameter[nthreads];
    pthread_t threads[nthreads];

    //thread parameters
    for (int i = 0; i < 4; i++) {
        parameter[i].val = i;
        parameter[i].start = i * C + 1;
        parameter[i].end = (i + 1) * C + 1;
    }

    for (int i = 4; i < 5; i++) {
        parameter[i].start = (i - 1) * C + 1;
        parameter[i].end = (i) * C + 1;
    }

    for (i = 0; i < 4; i++) {
        iret = pthread_create(&threads[i], NULL, insertThread, &parameter[i]);
        if (iret) {
            fprintf(stderr, "Error - pthread_create() return code: %d\n", iret);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 4; i < 5; i++) {
        iret = pthread_create(&threads[i], NULL, deleteThread, &parameter[i]);
        if (iret) {
            fprintf(stderr, "Error - pthread_create() return code: %d\n", iret);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
    }

    int error = 0;

    //Check results
    for (i = 0; i < 3; i++) {
        for (j = i * C + 1; j < (i + 1) * C + 1; j++) {
            int val;
            if (hash_get(ht1, j, &val) == 0) {
                if (val != i)
                    error = 1;
            } else
                error = 1;
        }
    }

    for (i = 3 * C + 1; i < 4 * C; i ++) {
        int val;
        if (hash_get(ht1, i, &val) == 0) {
            error = 1;
        }
    }

    hash_destroy(ht1);

    switch (error) {
        case 0:printf("OK!\n");
            break;
        case 1:printf("NOT OK!\n");
    }

}



