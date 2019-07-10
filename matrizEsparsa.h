#include <stdlib.h>
#include <stdio.h>

#define TAMANAHO_INICIAL 5

//VERSÃO COM SENTINELA
typedef struct node{
	int linha;
	int coluna;
	int valor;
	struct node* direita;
	struct node* baixo;
	struct node* esquerda;
	struct node* cima;	
}Node;

typedef struct{
	Node** linhas;	//ponteiro para o vetor cujas células são ponteiros de nós
	Node** colunas;	//ponteiro para o vetor cujas células são ponteiros de nós
	int numLinhas;	//Quantidade de linhas da matriz
	int numColunas;	//Quantidade de colunas da matriz
}MatrizEsparsa;

int matriz_verifica_IO(MatrizEsparsa* m, int linha, int coluna, int valor)
{
    if(m==NULL) return 1;
    if(valor == 0)
    {
      printf("O valor nao pode ser zero (0)");
      return 1;
    } 
    if (linha < 0) return 1;
    if (coluna < 0) return 1;
    if(m->numColunas<linha) return 1;
    if(m->numLinhas<coluna) return 1;

    return 0;
}


// Cria uma matriz vazia e devolve seu endereço de memória.
MatrizEsparsa* criarMatriz(int qtdeLinhas, int qtdeColunas)
{


    MatrizEsparsa* m =(MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));
    m->numColunas=qtdeColunas;
    m->numLinhas =qtdeLinhas;


    m->colunas=(Node**)malloc((qtdeColunas)*sizeof(Node*));
    m->linhas=(Node**)malloc((qtdeLinhas)*sizeof(Node*));
    return m;
    
}

int matriz_existe();
Node* acessar(MatrizEsparsa* m, int linha, int coluna)
{
  for( Node* i = m->colunas[coluna]; i != NULL ; i= i->baixo)
  {
    for (Node* j = m->linhas[linha] ; j != NULL ; j = j->direita)
    {
       
      if (j == i)
      {
         printf("HERE\n");
          return j;
      }
    }
  }

  return NULL;
}

//Parametro maior ou menor so retorna 

// Insere o <valor> na matriz <m> na linha <linha> e coluna <coluna>. Caso a posição já exista, substitua o valor da célula.
int inserir(MatrizEsparsa* m, int linha, int coluna, int valor)
{

  if(matriz_verifica_IO(m,linha,coluna,valor)) return 0;
  Node* elemento = acessar(m,linha,coluna);
  if (elemento != NULL)
  {
    elemento->valor=valor;
  }
  int atras = coluna-1;
  int frente= coluna+1;
  int baixo = linha-1;
  int cima  = linha+1;
  elemento=0;
  elemento=(Node*)malloc(sizeof(Node));

 

// Coloca a linha e a coluna, poderia fazer sem esses itens, maaaaaaas ia ser um trampo um pouco mais chato
  elemento->coluna = coluna;
  elemento->linha  = linha;
  elemento->valor =valor;
  Node* aux;

  
  if (atras<= 0)
  {
    elemento->esquerda=m->linhas[linha];
  }else
  {
    int finalColuna = m->numColunas -1;
    for (int i= finalColuna; i > 1; i--)
    {
        aux = acessar(m,linha,i);
        if (aux != NULL)
        {
          if(aux->coluna < coluna)
          {
            elemento->esquerda = aux;
            break;
          }
        }
    }
  }
  if (frente > m->numColunas)
  {
    elemento->direita=NULL;

  }else
  {
    for (int i=0 ; i < m->numColunas ; i++)
    {
        aux = acessar(m,linha,i);
        if (aux != NULL)
        {
          if(aux->coluna > coluna)
          { 
            elemento->direita=aux;
            break;
          }
        }
    }
  }
  if (cima<=0)
  {
    
    elemento->cima=m->colunas[coluna];

  }else
  {
    int finallinha = (m->numLinhas) -1;
    for (int i = finallinha; i > 1; i--)
    {
        aux= acessar(m,i,coluna);
        if (aux != NULL)
        {
          if(aux->linha < linha)
          {
            elemento->cima = aux;
            break;
          }
        }  
    }
  }
  if (baixo > m->numLinhas)
  {
    elemento->baixo = NULL;

  }else
  {
    for (int i = 0; i < m->numLinhas; i++)
    {
      aux = acessar(m,i,coluna);
      if (aux != NULL)
      {
        if (aux->linha > linha)
        {
          elemento->baixo=aux;
          break;
        }
      }
    }  
  }
// PARTE DA INSERCAO
    
  if(elemento->baixo != NULL)
  {
    elemento->baixo->cima=elemento;
  }
  if (elemento->direita != NULL)
  {
    elemento->direita->esquerda=elemento;
  }
  if (elemento->cima==m->colunas[coluna])
  {
    m->colunas[coluna]=elemento;
  }else
  {
    elemento->cima->baixo=elemento;
  }
  
  if (elemento->esquerda == m->linhas[linha])
  {
    m->linhas[linha]=elemento;    
  }else
  {
    elemento->esquerda->direita = elemento;
  }

  return 1;

}


// Remove o elemento da linha <linha> e coluna <coluna> na matriz <m> . Devolva 1 caso a remoção seja efetivada e 0 caso contrário.
int remover(MatrizEsparsa* m, int linha, int coluna);

// Devolve o valor correspondente a linha e coluna solicitada. Faça a validação dos índices. Caso a posição solicitada esteja fora do intervalo, devolva zero.


// Imprime os valores da matriz na tela. Cada linha deve ser impressa em uma linha diferente e os elementos separados por espaço ou tabulação. Os elementos não representados na matriz (valor zero), também devem ser impressos.
void imprimir(MatrizEsparsa* m)
{
  Node* aux;

  for (int i = 0; i < m->numLinhas; i++)
  {
    for (int j = 0; j < m->numColunas; j++)
    {
        aux =  acessar(m,i,j);
        if(aux != NULL){
          printf("%d \t", aux->valor);
        }
        if(aux == NULL){
          printf(" 0 \t");
        }
        
    }
    printf("\n");
  }
}

// Libera toda memória alocada dinamicamente para a matriz.
void desalocar(MatrizEsparsa* m){

  Node* aux;
  for (int i = 0; i < m->numLinhas; i++)
    for (int j = 0; j < m->numColunas; j++){
      aux =  acessar(m,i,j);
      if(aux != NULL)
        free(aux);
    }
}



// IMPLEMENTAÇÃO


// COM SENTINELA
// void imprimir(MatrizEsparsa* m){
//   int l,c;
  
//   Node* aux;

//   for(l = 0; l < m->numLinhas; l++) {    
//     aux = m->linhas[l]->direita; 
//     for(c = 0; c < m->numColunas; c++){
//       if(aux->coluna == c){
//         printf("%3d ", aux->valor);
//         aux = aux->direita;
//       }else{
//         printf("%3d ", 0);
//       }
//     }
//     printf("\n");
//   }   
//   printf("\n");
// }
