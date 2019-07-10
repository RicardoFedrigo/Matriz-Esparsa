#include <stdlib.h>
#include <stdio.h>
//VERS�O SEM SENTINELA
typedef struct node{
    int linha;
    int coluna;
    int valor;
    struct node* direita;
    struct node* baixo;
}Node;

typedef struct{
    Node** linhas;    
    Node** colunas;    
    int numLinhas;    
    int numColunas;    
}MatrizEsparsa;

MatrizEsparsa* criarMatriz(int qtdeLinhas, int qtdeColunas){
  MatrizEsparsa* m = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));
  m->numLinhas = qtdeLinhas;
  m->numColunas = qtdeColunas;
  m->linhas = (Node**)malloc(qtdeLinhas*sizeof(Node*));
  m->colunas = (Node**)malloc(qtdeColunas*sizeof(Node*));
  for(int i=0;i<qtdeLinhas;i++) m->linhas[i] = NULL;
  for(int i=0;i<qtdeColunas;i++) m->colunas[i] = NULL;
  return m;
}
int remover(MatrizEsparsa* m, int linha, int coluna);


int inserir(MatrizEsparsa* m, int linhap, int colunap, int valorp){
  if( linhap<0 || linhap>=m->numLinhas || colunap<0 || colunap >=m->numColunas)
    return 0;
  Node* ant = NULL;
  Node* atual = m->linhas[linhap];
  Node* aux;
  while(atual != NULL && atual->coluna<colunap){
   
    ant = atual;
    atual = atual->direita;
  }
  if(atual != NULL && atual->coluna == colunap)
  {
    if(valorp == 0)
   {
  //     if(ant==NULL)
  //     { 
  //       m->linhas[linhap] = atual->direita;
  //     }else{
  //       ant->direita = atual->direita;
  //     }free(atual);
  //    remover(m,linhap,colunap);
    }
     else
      atual->valor = valorp;
  }
  else
  {
          { 
  {
      Node* novo = (Node*)malloc(sizeof(Node));
      novo->coluna = colunap;
      novo->valor = valorp;
      novo->direita = atual;
      aux=novo;
      if(ant == NULL){
        m->linhas[linhap] = novo;
      }else{
        ant->direita = novo;
      }
  }
//IMPLEMENTACAO COLUNA 

  Node* ant_coluna = NULL;
  Node* atual_coluna = m->colunas[colunap];
  while(atual_coluna != NULL && atual_coluna->linha<linhap){
  
    ant_coluna = atual_coluna;
    atual_coluna = atual_coluna->baixo;
  }
 
  if(ant_coluna == NULL){
    m->colunas[colunap] = aux;
  }else{
    ant_coluna->baixo = atual_coluna ;
  }
  aux->baixo = atual_coluna;
}
void imprimir(MatrizEsparsa* m)
{

  for (int i = 0; i < 8; i++)
  {
    
  }
    
}