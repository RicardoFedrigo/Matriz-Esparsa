#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int linha;
  int coluna;
  int valor;
  struct Node* direita;
  struct Node* esquerda;
  struct Node* cima;
  struct Node* baixo;
}Node;

typedef struct{
  Node** linhas;	//ponteiro para o vetor cujas células são ponteiros de nós
  Node** colunas;	//ponteiro para o vetor cujas células são ponteiros de nós
  int numLinhas;	//Quantidade de linhas da matriz
  int numColunas;	//Quantidade de colunas da matriz
}MatrizEsparsa;

    // FUNÇÕES PRINCIPAIS:

// Cria uma matriz vazia e devolve seu endereço de memória.
MatrizEsparsa* criarMatriz(int qtdeLinhas, int qtdeColunas);

// Insere o <valor> na matriz <m> na linha <linha> e coluna <coluna>. Caso a posição já exista, substitua o valor da célula.
int inserir(MatrizEsparsa* m, int linha, int coluna, int valor);

// Devolve o valor correspondente a linha e coluna solicitada. Faça a validação dos índices. Caso a posição solicitada esteja fora do intervalo, devolva zero.
int acessar(MatrizEsparsa* m, int linha, int coluna);

//Remove o elemento da linha <linha> e coluna <coluna> na matriz <m> . Devolva 1 caso a remoção seja efetivada e 0 caso contrário.
int remover(MatrizEsparsa* m, int linha, int coluna);

// Libera toda memória alocada dinamicamente para a matriz.
void desalocar(MatrizEsparsa* m);

// Imprime os valores da matriz na tela. Cada linha deve ser impressa em uma linha diferente e os elementos separados por espaço ou tabulação. Os elementos não representados na matriz (valor zero), também devem ser impressos.
void imprimir(MatrizEsparsa* m);

Node* no_criar(int linha, int coluna, int valor){
  Node* no = (Node*) malloc(sizeof(Node));
  no->linha = linha;
  no->coluna = coluna;
  no->valor = valor;
  no->direita = no;
  no->esquerda = no;
  no->cima = no;
  no->baixo = no;
  return no;
}
MatrizEsparsa* criarMatriz(int qtdeLinhas, int qtdeColunas){
  MatrizEsparsa* m = (MatrizEsparsa*) malloc(sizeof(MatrizEsparsa));
  m->colunas = (Node**) malloc(qtdeColunas * sizeof(Node*));
  m->linhas = (Node**) malloc(qtdeLinhas * sizeof(Node*));
  m->numLinhas = qtdeLinhas;
  m->numColunas = qtdeColunas;
  for (int i = 0 ; i < m->numColunas ; i++ )
    m->colunas[i] = no_criar(0,i,0);
  for (int i = 0 ; i < m->numLinhas ; i ++)
    m->linhas[i] = no_criar(i,0,0);
  return m;
}
// aqui retorna endereço da linha
Node* endLinha(Node* sentinela, int pos){
  Node* aux = sentinela;
  while(aux->direita != sentinela && pos > aux->direita->coluna){
    aux = aux->direita;
  }
  return aux;
}
// aqui retorna endereço da coluna
Node* endColuna(Node* sentinela, int pos){
  Node* aux = sentinela;
  while(aux->baixo != sentinela && pos > aux->baixo->linha){
    aux = aux->baixo;
  }
  return aux;
}
// Recebe o a linha em que o possivel elemento pode estar retorna verdadeiro se tiver lincada em algum lugar
int verifica(MatrizEsparsa* m, int linha, int coluna, int valor){
  Node* sentinela = m->linhas[linha];
  Node* aux = sentinela->direita;
  while (aux != sentinela ){
    if(coluna == aux->coluna){
      aux->valor = valor;
      return 1;
    }
    aux=aux->direita;
  }
  return 0;
}
// parte da inserção pelo endereço da linha
void inserir_linha(Node* sentinela, Node* no){
  Node* aux = endLinha (sentinela, no->coluna);
  no->direita = aux->direita;
  no->esquerda = aux;
  aux->direita->esquerda = no;
  aux->direita = no;
}
// parte da remoção pelo endereço de linha
void remover_linha(Node* sentinela, Node* no){
  no->esquerda->direita = no->direita;
  no->direita->esquerda = no->esquerda;
}
//parte da remoção pelo endereço de coluna
void remover_coluna(Node* sentinela, Node* no){
  no->baixo->cima = no->cima;
  no->cima->baixo = no->baixo;

}
// Utiliza do sentinela procurando a coluna a ser colocada
void inserir_coluna(Node* sentinela, Node* no){
  Node* aux = endColuna (sentinela, no->linha);
  no->baixo = aux->baixo;
  no->cima = aux;
  aux->baixo->cima = no;
  aux->baixo = no;
}
//Faz a 
int inserir(MatrizEsparsa* m, int linha, int coluna, int valor){
  if(linha < 0 || linha > m->numLinhas ) return 0;
  if(coluna < 0 || coluna > m->numColunas ) return 0;
  if(verifica(m,linha, coluna, valor) ) return 1;

  Node* novo = no_criar(linha, coluna, valor);
  inserir_linha(m->linhas[linha], novo);
  inserir_coluna(m->colunas[coluna], novo);
  return 1;
}

//Desvincula as linhas e colunas de cada no
void desalocar(MatrizEsparsa* m){
  for (int i = 0 ; i<m->numLinhas ; i++)
    free(m->linhas[i]);
  for (int i = 0 ; i<m->numColunas ; i++)
    free(m->colunas[i]);
  free(m);
}
//Funcao do professor =D
void imprimir(MatrizEsparsa *m) {
  Node* aux;
  int l,c;
  printf(" ");
  for (l = 0 ; l < m->numLinhas ; l++) {
    aux = m->linhas[l]->direita;
    for (c = 0 ; c < m->numColunas ; c++) {
        if (aux != m->linhas[l] && c == aux->coluna) {
          printf("%3d ", aux->valor);
          aux = aux->direita;
        } else
            printf("%3d ", 0);
    }
    printf("\n ", 0);
  }
}
// acessa a matriz e retorna o valor do nó na linha e coluna
int acessar(MatrizEsparsa* m, int linha, int coluna) {
  if (linha < 0 || linha > m->numLinhas ) return 0;
  if (coluna < 0 || coluna > m->numColunas ) return 0;
  Node* sentinela = m->linhas[linha];
  Node* aux = endLinha(sentinela, coluna+1);
  return aux->valor;
}
// acessa a matriz e retorna o nó na linha  e coluna solicitada
Node* acessaraux(MatrizEsparsa* m, int linha, int coluna) {
  if (linha < 0 || linha > m->numLinhas ) return 0;
  if (coluna < 0 || coluna > m->numColunas ) return 0;
  Node* sentinela = m->linhas[linha];
  Node* aux = endLinha(sentinela, coluna+1);
  return aux;
}
//Substitui os ponteiros dos de tras, fazendo apontar para frente e baixo
int remover(MatrizEsparsa* m, int linha, int coluna){
  if (linha < 0 || linha > m->numLinhas ) return 0;
  if (coluna < 0 || coluna > m->numColunas ) return 0;

  Node* novo = acessaraux(m, linha, coluna);
  remover_linha(m->linhas[linha], novo);
  remover_coluna(m->colunas[coluna], novo);
  free(novo);
  return 1;
}
