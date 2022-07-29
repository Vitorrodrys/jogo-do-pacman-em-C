#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<errno.h>
#include <time.h>
#include"mapa.c"
#include "definicoes.h"
#include "interface.c"

#define limpaBuf while(getchar()!='\n');



novoMapa mapa;

int verificaParedes(int x, int y){
    if(mapa.matriz[y][x] != VAZIO && mapa.matriz[y][x] != HEROI && mapa.matriz[y][x] != PILULA){
        return 1;
    }else{
        return 0;
    }
}



int verificaMovimento(char acao, int x, int y){
    switch(acao)
    {
    case ESQUERDA:
        if(verificaParedes(x-1, y) ){
            return 1;
        }else{
            return 0;
        }
        break;
    case DIREITA:
        if(verificaParedes(x+1, y)){
            return 1;
        }else{
            return 0;
        }
        break;
    case CIMA:
        if(verificaParedes(x, y-1)){
            return 1;
        }else{
            return 0;
        }
        break;
    case BAIXO:
        if(verificaParedes(x, y+1)){
            return 1;
        }else{
            return 0;
        }
        break;
    case ESPECIAL:
        return 0;
    default:
        return 1;

    }
}

void decideParaOndeAndar(int incremento, int qualFantasma){
    if(rand()%2 == 0){
        if(verificaParedes(mapa.fantasmas[qualFantasma].x+incremento, mapa.fantasmas[qualFantasma].y) == 0){
            mapa.fantasmas[qualFantasma].x+=incremento;
        }else
            if(verificaParedes(mapa.fantasmas[qualFantasma].x, mapa.fantasmas[qualFantasma].y+incremento) == 0){
            mapa.fantasmas[qualFantasma].y+=incremento;
            }else{
                (mapa.fantasmas[qualFantasma].incremento)*=-1;
            }
    }else{
        if(verificaParedes(mapa.fantasmas[qualFantasma].x, mapa.fantasmas[qualFantasma].y+incremento) == 0){
            mapa.fantasmas[qualFantasma].y+=incremento;
        }else
            if(verificaParedes(mapa.fantasmas[qualFantasma].x+incremento, mapa.fantasmas[qualFantasma].y) == 0){
            mapa.fantasmas[qualFantasma].x+=incremento;
            }else{
                mapa.fantasmas[qualFantasma].incremento *=-1;   
            }
    }
}
void verificaSeHeroiFoiPego(){
    
    if(mapa.matriz[mapa.y][mapa.x]!= HEROI){
        mapa.acabou = 0;
    }
}
void movimentaFantasma(int qualFantasma){

    if(mapa.fantasmas[qualFantasma].existe == 1){
        mapa.matriz[mapa.fantasmas[qualFantasma].y][mapa.fantasmas[qualFantasma].x] = VAZIO;
        decideParaOndeAndar(mapa.fantasmas[qualFantasma].incremento, qualFantasma);
        mapa.matriz[mapa.fantasmas[qualFantasma].y][mapa.fantasmas[qualFantasma].x] = FANTASMA;
        verificaSeHeroiFoiPego();
        
    }
}

void pegouPilula(int x, int y){
    if(mapa.matriz[y][x] == PILULA){
        mapa.pilulas++;
    }
}
void atacaY(int incremento){
    
    for(int i = 1; i<=3 && mapa.y + i*incremento>0 && mapa.y + i*incremento < mapa.linhas-1; i++){
        if(mapa.matriz[mapa.y + incremento*i][mapa.x] == paredeHor || mapa.matriz[mapa.y + incremento*i][mapa.x] == paredeVer){
            return;
        }
        if(mapa.matriz[mapa.y + incremento*i][mapa.x] == FANTASMA){
            
            
            
            for(int j = 0; j<quantFantasmas; j++){
                if(mapa.fantasmas[j].x == mapa.x && 
                    mapa.fantasmas[j].y == mapa.y + i*incremento){
                        
                        mapa.matriz[mapa.y + incremento*i][mapa.x] = VAZIO;
                        mapa.fantasmas[j].existe = 0;
                        return;
                }
            }
        }
    }
}
void atacaX(int incremento){
    for(int i = 0; i<=3 && mapa.x + i*incremento > 0 && mapa.x + i*incremento < mapa.colunas - 2; i++){
        if(mapa.matriz[mapa.y][mapa.x + i*incremento] == paredeHor || mapa.matriz[mapa.y][mapa.x + i*incremento] == paredeVer){
            return;
        }
        if(mapa.matriz[mapa.y][mapa.x + i*incremento] == FANTASMA){
            for(int j = 0; quantFantasmas; j++){
                if(mapa.fantasmas[j].x == mapa.x + i*incremento && 
                    mapa.fantasmas[j].y == mapa.y){
                        mapa.matriz[mapa.y][mapa.x + i*incremento] = VAZIO;
                        mapa.fantasmas[j].existe = 0;
                        return;

                    }
            }
        }
    }
}
void movimentaPlayer(char acao){

    if(verificaMovimento(acao, mapa.x, mapa.y)==0){
       
        mapa.matriz[mapa.y][mapa.x] = VAZIO;
        switch (acao)
        {
        case ESQUERDA:
            --mapa.x;
            pegouPilula(mapa.x, mapa.y);
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;
        case DIREITA:
            ++mapa.x;
            pegouPilula(mapa.x, mapa.y);
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;
        case CIMA:
        
            --mapa.y;
            pegouPilula(mapa.x, mapa.y);
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;
        case BAIXO:
            ++mapa.y;
            pegouPilula(mapa.x, mapa.y);
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;
        
        case ESPECIAL:
            if(mapa.pilulas>0){
                atacaY(-1);
                atacaY(1);
                atacaX(-1);
                atacaX(1);
                mapa.pilulas--;
            }
            mapa.matriz[mapa.y][mapa.x] = HEROI;
            break;

        }
    }
}
void atribuiUmAincrementoDosFantasmas(){
    for(int i = 0; i < quantFantasmas; i++){
        mapa.fantasmas[i].incremento = 1;
        mapa.fantasmas[i].existe = 1;
    }
}
void sorteiaPilulas(){
    if(rand()%10== 0){
        int x, y;
        do{
            x = rand()%(mapa.colunas-3);
            y = rand()%(mapa.linhas-2);
        }while (mapa.matriz[y][x] != VAZIO);

        mapa.matriz[y][x] = PILULA;

        
    }
}
void verificaGanhou(){
    for(int i = 0; i<quantFantasmas; i++){
        if(mapa.fantasmas[i].existe == 1){
            return;
        }
    }
    printf("voce ganhou!");
    exit(1);
}
FILE* abriArq(char *nome, char *modo){
    FILE *f = fopen(nome, modo);
    if(f == NULL){
        printf("erro na abertura do arquivo");
        exit(1);
    }
    return f;
}
int main(){
    
    mapa.pilulas = 0;
    mapa.acabou = 1;
    srand(time(NULL));
    atribuiUmAincrementoDosFantasmas();
    char acao;

    FILE *f, *z;
    f = abriArq("quantidade.txt", "r");
    fscanf(f, "%d %d %d %d %d %d %d %d", &(mapa.linhas), &(mapa.colunas), &(mapa.y), &(mapa.x), &(mapa.fantasmas[0].y), &(mapa.fantasmas[0].x), &(mapa.fantasmas[1].y), &(mapa.fantasmas[1].x));
    fclose(f);
    z = abriArq("mapa.txt", "r");
    aumentaMapa(&mapa);
    preencheMapa(f, &mapa);
    imprimeMapa(&mapa);
    do{
        acao = getchar();
        movimentaPlayer(acao);
        movimentaFantasma(0);

        movimentaFantasma(1);
        sorteiaPilulas();
        limpaBuf;
        system("cls");
        imprimeMapa(&mapa);
        verificaGanhou();

    }while(mapa.acabou);
    printf("\nvoce perdeu!");
}