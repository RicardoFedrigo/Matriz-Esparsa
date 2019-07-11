#include <stdio.h>
#include <stdlib.h>
#include "matrizEsparsa.h"

int main() {
  MatrizEsparsa* m = criarMatriz(10,10);
  inserir(m, 2, 7, 70);
  inserir(m, 2, 8, 80);
  inserir(m, 2, 9, 90);
  inserir(m, 2, 0, 1);
  inserir(m, 2, 1, 10);
  inserir(m, 2, 2, 20);
  inserir(m, 2, 3, 30);
  inserir(m, 2, 3, 300);
  inserir(m, 9, 0, 15);
  inserir(m, 9, 9, 20);
  inserir(m, 0, 0, 20);
  remover(m,0,0); 


  printf("acessar %d\n",acessar(m,2,1));

  imprimir(m);

}
