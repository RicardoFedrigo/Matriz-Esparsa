#include <stdio.h>
#include <stdlib.h>
#include "matrizEsparsa.h"

void main()
{
    MatrizEsparsa* m = criarMatriz(5,5);
    inserir(m,0,0,1);
    inserir(m,1,1,10);
    inserir(m,0,1,2);
    inserir(m,0,2,3);
    inserir(m,0,3,4);

    printf("%d \n",m->linhas[0]->valor);
    printf("%d \n",m->linhas[0]->direita->valor);
    printf("%d \n",m->linhas[0]->direita->direita->valor);
    printf("%d \n",m->linhas[1]->valor);

}