#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <time.h>
#include"mapa.c"
#include "definicoes.h"
#include "interface.c"

#define limpaBuf while(getchar()!='\n');


extern int quantFantasmas = 1;
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
            for(int j = 0; j < quantFantasmas; j++){
                if(mapa.fantasmas[j].x == mapa.x + i*incremento && 
                    mapa.fantasmas[j].y == mapa.y){
                        mapa.matriz[mapa.y][mapa.x + i*incremento] = VAZIO;
                        mapa.fantasmas[j].existe = 0;
                        

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
    if(rand()%mapa.chancePilula== 0){
        int x, y;
        do{
            x = rand()%(mapa.colunas-3);
            y = rand()%(mapa.linhas-2);
        }while (mapa.matriz[y][x] != VAZIO);

        mapa.matriz[y][x] = PILULA;

        
    }
}
int verificaGanhou(){
    for(int i = 0; i<quantFantasmas; i++){
        if(mapa.fantasmas[i].existe == 1){
            return 0;
        }
    }
    printf("voce ganhou!");
    return 1;
}
FILE* abriArq(char *nome, char *modo){
    FILE *f = fopen(nome, modo);
    if(f == NULL){
        printf("erro na abertura do arquivo");
        exit(1);
    }
    return f;
}
void selecionaDificuldade(){
    char dificuldade[10];
    printf("digite a dificuldade desejada\n");
    printf("dificil\nmedio\nfacil\n");
    scanf("%s", dificuldade);
    limpaBuf;
    if(strcmp(dificuldade, "dificil") == 0){
        mapa.dificuldade = 'd';
    }else
        if(strcmp(dificuldade, "medio") == 0){
            mapa.dificuldade = 'm';
        }else
            if(strcmp(dificuldade, "facil") == 0){
                mapa.dificuldade = 'f';
            }else{
                printf("digite uma opcao valida\n");
                selecionaDificuldade();
            }
}
void aumentaCapacidadeFantasmas(int tamanho){
    mapa.fantasmas = malloc(sizeof(fantasma)*tamanho);
}
void abriArqDaDificuldade(){
    FILE *f;
    if(mapa.dificuldade == 'm'){
        f = abriArq("quantidade.txt", "r");
        fscanf(f, "%d %d %d %d %d", &(mapa.linhas), &(mapa.colunas), &(mapa.y), &(mapa.x), &quantFantasmas);
        aumentaCapacidadeFantasmas(quantFantasmas);
        fscanf(f, "%d %d %d %d %d", &(mapa.fantasmas[0].y), &(mapa.fantasmas[0].x), &(mapa.fantasmas[1].y), &(mapa.fantasmas[1].x), &(mapa.chancePilula));
        f = abriArq("mapa.txt", "r");
    }else
        if(mapa.dificuldade == 'd'){
            f = abriArq("quantidadeDificil.txt", "r");
            fscanf(f, "%d %d %d %d %d", &(mapa.linhas), &(mapa.colunas), &(mapa.y), &(mapa.x), &quantFantasmas);
            aumentaCapacidadeFantasmas(quantFantasmas);
            fscanf(f, "%d %d %d %d %d %d %d", &(mapa.fantasmas[0].y), &(mapa.fantasmas[0].x), &(mapa.fantasmas[1].y), &(mapa.fantasmas[1].x), &(mapa.fantasmas[2].y), &(mapa.fantasmas[2].x), &(mapa.chancePilula));
            f = abriArq("mapaDificil.txt", "r"); 
        }else
            if(mapa.dificuldade == 'f'){
                f = abriArq("quantidadeFacil.txt", "r");
                fscanf(f, "%d %d %d %d %d", &(mapa.linhas), &(mapa.colunas), &(mapa.y), &(mapa.x), &quantFantasmas);
                aumentaCapacidadeFantasmas(quantFantasmas);
                fscanf(f, "%d %d %d", &(mapa.fantasmas[0].y), &(mapa.fantasmas[0].x), &(mapa.chancePilula));
                f = abriArq("mapaFacil.txt", "r");
            }
    atribuiUmAincrementoDosFantasmas();
    aumentaMapa(&mapa);
    preencheMapa(f, &mapa);
    fclose(f);
    system("cls");
}
void controlaFantasma(){
    for(int i = 0; i<quantFantasmas; i++){
        movimentaFantasma(i);
    }
}
int jogarNovamente(){
    char querOuNao[3];
    scanf("%s", querOuNao);
    if(strcmp(querOuNao, "sim") == 0){
        return 1;
    }else
        if(strcmp(querOuNao, "nao") == 0){
            return 0;
        }else{
            printf("digite uma opcao valida\n");
            return jogarNovamente();
            
        }
}
void liberaMapaEfantasma(){
    free(mapa.fantasmas);
  
    for(int i = 0; i<mapa.linhas; i++){
        free(mapa.matriz[i]);
    }
    free(mapa.matriz);
   
}
int main(){
    
    do{
        selecionaDificuldade();

        mapa.pilulas = 0;
        mapa.acabou = 1;
        srand(time(NULL)); 
        char acao;

        
        abriArqDaDificuldade();
        
    
        imprimeMapa(&mapa);
        do{
            acao = getchar();
            movimentaPlayer(acao);
            controlaFantasma();
            sorteiaPilulas();
            limpaBuf;
            system("cls");
            imprimeMapa(&mapa);
            if(verificaGanhou())
                break;

        }while(mapa.acabou);
        (mapa.acabou)?printf(""):printf("voce perdeu!\n");
        printf("deseja jogar Novamente?\n");
        liberaMapaEfantasma();
    }while(jogarNovamente());
}