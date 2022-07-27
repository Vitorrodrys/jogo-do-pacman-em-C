#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<errno.h>
#include "definicoes.h"

void aumentaMapa(novoMapa *pt){
    pt->matriz = malloc(sizeof(char)*pt->linhas);
    for(int i = 0; i < pt->linhas; i++){
        pt->matriz[i] = malloc(sizeof(char)*pt->colunas);
    }
    
}
void preencheMapa(FILE *f, novoMapa *pt){
    for(int i = 0; i<pt->linhas; i++){
        for(int j = 0; j < pt->colunas; j++){
            pt->matriz[i][j] = fgetc(f);
        }
    }
}
void imprimeMapa(novoMapa *pt){
    for(int i = 0; i < pt->linhas; i++){
        for(int j = 0; j < pt->colunas; j++){
            printf("%c", pt->matriz[i][j]);
        }
    }
}