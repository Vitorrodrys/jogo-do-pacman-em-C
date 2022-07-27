#ifndef BIBLIOTECA_VITOR_h
#define BIBLIOTECA_VITOR_h
#include <stdio.h>/*bibliotecas necessarias para o funcionamente das funcoes desta biblioteca*/
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define HEROI '@'
#define VAZIO '.'
#define quantFantasmas 2

typedef struct{
    int x;
    int y;
    int incremento;
    
}fantasma;

typedef struct{
    char **matriz;
    int linhas;
    int colunas;
    int x;
    int y;
    fantasma fantasmas[quantFantasmas];

    
}novoMapa;




void atribuiUmAincrementoDosFantasmas();
void aumentaMapa(novoMapa *ptr);
void preencheMapa(FILE *f, novoMapa *ptr);
void imprimeMapa(novoMapa *ptr);

#endif /*minhas funcoes*/