#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define m 1000
#define n 1000
#define thread_count 100

double A[m][n];
double x[n];
double y[m];

void *Pth_mat_vect(void* rank) {
    long my_rank = (long) rank;
    int i, j;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;

    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
            // Imprimir a linha de multiplicação com os valores de A e x
            printf("Thread %ld: y[%d] += %lf * %lf\n", my_rank, i, A[i][j], x[j]);
        }
    }

    return NULL;
}

int main() {
    pthread_t threads[thread_count];
    long i;

    // Preencher com valores de exemplo a matriz A
    for (i = 0; i < m; i++) {
        for (long j = 0; j < n; j++) {
            A[i][j] = i + j + 1; 
        }
    }
    
    for (int i = 0; i < n; i++) {  // Preencher vetor x
        x[i] = i + 1;
    }
    

    // Criar as threads e executar a função Pth_mat_vect.
    for (i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], NULL, Pth_mat_vect, (void*)i);
    }

    // Aguardar até que todas as threads terminem.
    for (i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    // Agora, o vetor y contém o resultado da multiplicação da matriz A pelo vetor x.
    printf("\n");
    for (i = 0; i < m; i++) {
        printf("y[%ld] = %lf\n", i, y[i]);
    }

    return 0;
}
