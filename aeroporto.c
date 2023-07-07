/*
 * Problema do aeroporto.
 */ 
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_AVIOES 10
#define N_PISTAS 5
#define N_PORTOES 5

// A struct do aviao armazena seu id (para facilitar prints) e o seu status de voo, que será usado para definir qual procedimento o avião vai realizar
typedef struct aviao {
    int em_voo, id;
} aviao;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t aviao_cond = PTHREAD_COND_INITIALIZER; // variavel de condicao que bloqueia os avioes durante o acesso as pistas

int pistas_livres = N_PISTAS, portoes_livres = N_PORTOES;

aviao avioes[N_AVIOES]; // o vetor dos aviões serve para indicar quais aviões querem usar a pista e a quanto tempo

void* f_aviao(void* v) {
    int id = *(int*) v;
    aviao av = avioes[id];
    while(1) {
        sleep(1);
        pthread_mutex_lock(&mutex);
            // Verifica se existe alguma pista livre
            // Ainda que exista alguma pista livre, caso o aviao deseje pousar, ele precisa verificar se existe algum portao disponivel
            while (pistas_livres == 0 || (av.em_voo && portoes_livres == 0)) {
                printf("piloto %d: desejo acessar a pista!\n", av.id);
                pthread_cond_wait(&aviao_cond,&mutex);
            }
            
            // Acessa a pista
            if (av.em_voo) {
                // Caso o aviao esteja em voo, ele reserva um portao disponivel
                printf("piloto %d: iniciando procedimento de pouso e reservando um portão!\n", av.id);
                portoes_livres--;
            }
            else {
                printf("piloto %d: iniciando decolagem!\n", av.id);
            }
            pistas_livres--;

            printf("pistas: %d; portoes: %d\n", pistas_livres, portoes_livres);
        pthread_mutex_unlock(&mutex);

        sleep(5); // Sleep para simular tempo de acesso a pista
        
        pthread_mutex_lock(&mutex);
            // Apos utilizar a pista, os avioes liberam ela
            pistas_livres++;
            if (!av.em_voo) {
                // Se o avião tiver decolado ele acorda todos os pilotos esperando por uma pista para avisar que um portão está livre
                portoes_livres++;
                printf("piloto %d: acabo de decolar! Portões disponíveis %d\n", av.id, portoes_livres);
            }
            else {
                printf("piloto %d: pouso bem sucedido!\n", av.id);
            }
            av.em_voo = !av.em_voo;

            // Acorda todos os pilotos que esperam por uma pista
            pthread_cond_broadcast(&aviao_cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

int main() {
    pthread_t thr_avioes[N_AVIOES], thr_aeroporto;
    int i, id[N_AVIOES];

    // Inicializar aviões com todos em voo
    for (i = 0; i < N_AVIOES; i++) {
        avioes[i].id = i;
        avioes[i].em_voo = 1;
    }
    for (i = 0; i < N_AVIOES; i++) {
        id[i] = i;
        pthread_create(&thr_avioes[i], NULL, f_aviao, (void*) &id[i]);
    }

    for (i = 0; i < N_AVIOES; i++) 
        pthread_join(thr_avioes[i], NULL);
    return 0;
}
