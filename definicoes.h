#ifndef definicoes.h
#define definicoes.h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define ESPECIAL 'b'
#define HEROI '@'
#define VAZIO '.'
#define quantFantasmas 2
#define PILULA 'P'
#define FANTASMA 'c'
#define paredeVer '|'
#define paredeHor '-'

typedef struct{
    int x;
    int y;
    int incremento;
    int existe;
    
}fantasma;

typedef struct{
    char **matriz;
    int linhas;
    int colunas;
    int x;
    int y;
    int pilulas;
    fantasma fantasmas[quantFantasmas];
    int acabou;

    
}novoMapa;




void atribuiUmAincrementoDosFantasmas();
void aumentaMapa(novoMapa *ptr);
void preencheMapa(FILE *f, novoMapa *ptr);
void imprimeMapa(novoMapa *ptr);

#endif 