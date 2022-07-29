#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include "definicoes.h"




char parede[4][7] = {
    {"......."},
    {"......."},
    {"......."},
    {"......."}
};
char vazio[4][7] = {
    {"       "},
    {"       "},
    {"       "},
    {"       "}
};
char desenhaFantasma[4][7] = {
    {"  ___  "},
    {" 'o o' "},
    {" | - | "},
    {" |   | "}
};
char personagem[4][7] = {
    {" ___    "},
    {"/ \\\\   "},
    {"\\___/  "},
    {"        "}
};

char pilula[4][7] = {
    {"   _   "},
    {" |TNT| "},
    {" |TNT| "},
    {"       "}
};



void imprimeParte(char vetor[], int tamanho){
    for(int i = 0; i<tamanho; i++){
        printf("%c", vetor[i]);
    }
}







void imprimeMapa(novoMapa *pt){
    if(pt->pilulas > 0)
        printf("pilulas: %d\n", pt->pilulas);
    else
        printf("\n");
    for(int i = 0; i < pt->linhas; i++){
        for(int parte = 0; parte<4; parte++){
            for(int j = 0; j < pt->colunas; j++){
                  switch (pt->matriz[i][j])
                {
                    case VAZIO:
                        imprimeParte(vazio[parte], 7);
                        break;
                    case HEROI:
                        imprimeParte(personagem[parte], 7);
                        break;
                    case paredeHor:
                    case paredeVer:
                        imprimeParte(parede[parte], 7);
                        break;
                    case FANTASMA:
                        imprimeParte(desenhaFantasma[parte], 7);
                        break;
                    case PILULA:
                        imprimeParte(pilula[parte], 7);
                        break;
                    default:
                        printf("\n");
                        break;
                        
                }
            }
        }
    }
}