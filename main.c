#include <stdio.h>
#include <stdlib.h>
#include "matrizEsparsa.h"

void main()
{
    MatrizEsparsa* m = criarMatriz(5,5);
    inserir(m,1,0,1);
    inserir(m,1,1,2);
    inserir(m,1,2,3);
    inserir(m,1,3,4);
    inserir(m,1,4,5);


    inserir(m,2,0,6);
    inserir(m,2,1,7);
    inserir(m,2,2,8);
    inserir(m,2,3,9);
    inserir(m,2,4,10);

    printf("%d \n ",m->colunas[1]->valor);
    printf("%d \n ",m->linhas[2]->direita->valor);
}