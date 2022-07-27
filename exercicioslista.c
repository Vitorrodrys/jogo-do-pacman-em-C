#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<errno.h>
#include"mapa.c"
#include "definicoes.h"
#define limpaBuf while(getchar()!='\n');



novoMapa mapa;

int verificaParedes(int x, int y){
    if(mapa.matriz[y][x] != VAZIO){
        return 1;
    }else{
        return 0;
    }
}



int verificaMovimento(char acao, int x, int y){
    switch(acao)
    {
    case 'a':
        if(verificaParedes(x-1, y) ){
            return 1;
        }else{
            return 0;
        }
        break;
    case 'd':
        if(verificaParedes(x+1, y)){
            return 1;
        }else{
            return 0;
        }
        break;
    case 'w':
        if(verificaParedes(x, y-1)){
            return 1;
        }else{
            return 0;
        }
        break;
    case 's':
        if(verificaParedes(x, y+1)){
            return 1;
        }else{
            return 0;
        }
        break;
    default:
        return 1;

    }
}
void verificaSeMudaMovimento( int qualFantasma){
    if((mapa.colunas)-4 == mapa.fantasmas[qualFantasma].x || 
    1 == mapa.fantasmas[qualFantasma].x){
        (mapa.fantasmas[qualFantasma].incremento)*= -1;
    }
}

void movimentaFantasma(int qualFantasma){

    verificaSeMudaMovimento( qualFantasma);
    mapa.matriz[mapa.fantasmas[qualFantasma].y][mapa.fantasmas[qualFantasma].x] = '.';
    mapa.fantasmas[qualFantasma].x += mapa.fantasmas[qualFantasma].incremento;
    mapa.matriz[mapa.fantasmas[qualFantasma].y][mapa.fantasmas[qualFantasma].x] = 'c';
    
}
void movimentaPlayer(char acao){

    if(verificaMovimento(acao, mapa.x, mapa.y)==0){
        mapa.matriz[mapa.y][mapa.x] = VAZIO;
        switch (acao)
        {
        case ESQUERDA:
            --mapa.x;
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;
        case DIREITA:
            ++mapa.x;
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;
        case CIMA:
            --mapa.y;
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;
        case BAIXO:
            ++mapa.y;
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;
        }
    }
}
void atribuiUmAincrementoDosFantasmas(){
    for(int i = 0; i < quantFantasmas; i++){
        mapa.fantasmas[i].incremento = 1;
    }
}
int main(){
   
 
    atribuiUmAincrementoDosFantasmas();
    char acao;

    FILE *f, *z;
    f = fopen("quantidade.txt", "r");
    fscanf(f, "%d %d %d %d %d %d %d %d", &(mapa.linhas), &(mapa.colunas), &(mapa.y), &(mapa.x), &(mapa.fantasmas[0].y), &(mapa.fantasmas[0].x), &(mapa.fantasmas[1].y), &(mapa.fantasmas[1].x));
    fclose(f);
    z = fopen("mapa.txt", "r");
    aumentaMapa(&mapa);
    preencheMapa(f, &mapa);
    imprimeMapa(&mapa);
    do{
        acao = getchar();
        movimentaFantasma(0);
        movimentaFantasma(1);
        movimentaPlayer(acao);
        limpaBuf;
        system("cls");
        imprimeMapa(&mapa);

    }while(1);
}