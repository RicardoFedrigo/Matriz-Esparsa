
//VERS�O SEM SENTINELA
typedef struct node{
    int linha;
    int coluna;
    int valor;
    struct node* direita;
    struct node* baixo;
}Node;

typedef struct{
    Node** linhas;    //ponteiro para o vetor cujas c�lulas s�o ponteiros de n�s
    Node** colunas;    //ponteiro para o vetor cujas c�lulas s�o ponteiros de n�s
    int numLinhas;    //Quantidade de linhas da matriz
    int numColunas;    //Quantidade de colunas da matriz
}MatrizEsparsa;

MatrizEsparsa* criarMatriz(int qtdeLinhas, int qtdeColunas);
int inserir(MatrizEsparsa* m, int linha, int coluna, int valor);

MatrizEsparsa* criarMatriz(int qtdeLinhas, int qtdeColunas){ //Cria uma matriz vazia e devolve seu endere�o de mem�ria.
  MatrizEsparsa* m = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));
  m->numLinhas = qtdeLinhas;
  m->numColunas = qtdeColunas;
  m->linhas = (Node**)malloc(qtdeLinhas*sizeof(Node*));
  m->colunas = (Node**)malloc(qtdeColunas*sizeof(Node*));
  for(int i=0;i<qtdeLinhas;i++) m->linhas[i] = NULL;
  for(int i=0;i<qtdeColunas;i++) m->colunas[i] = NULL;
  return m;
}

int inserir(MatrizEsparsa* m, int linhap, int colunap, int valorp){
  
  if( linhap<0 || linhap>=m->numLinhas || colunap<0 || colunap >=m->numColunas)
    return 0;
  Node* ant = NULL;
  Node* atual = m->linhas[linhap];
  
  while(atual != NULL && atual->coluna<colunap){
   
    ant = atual;
    atual = atual->direita;
  }
  if(atual != NULL && atual->coluna == colunap){
    if(valorp == 0){
      if(ant==NULL)
        m->linhas[linhap] = atual->direita;
      else
        ant->direita = atual->direita;
      free(atual);
    }
     else
      atual->valor = valorp;
  }
  else
  {
      Node* novo = (Node*)malloc(sizeof(Node));
      novo->coluna = colunap;
      novo->valor = valorp;
      novo->direita = atual;
      if(ant == NULL)
        m->linhas[linhap] = novo;
      else
        ant->direita = novo;
  }

  
}

//Insere o <valor> na matriz <m> na linha <linha> e coluna <coluna>. Caso a posi��o j� exista, substitua o valor da c�lula.

int remover(MatrizEsparsa* m, int linha, int coluna);
//Remove o elemento da linha <linha> e coluna <coluna> na matriz <m> . Devolva 1 caso a remo��o seja efetivada e 0 caso contr�rio.

int acessar(MatrizEsparsa* m, int linha, int coluna);
//Devolve o valor correspondente a linha e coluna solicitada. Fa�a a valida��o dos �ndices. Caso a posi��o solicitada esteja fora do intervalo, devolva zero.


void imprimir(MatrizEsparsa* m);  
//(https://repl.it/@liberato/MatrizEsparsa)
//Imprime os valores da matriz na tela. Cada linha deve ser impressa em uma linha diferente e os elementos separados por espa�o ou tabula��o. Os elementos n�o representados na matriz (valor zero), tamb�m devem ser impressos.


void desalocar(MatrizEsparsa* m);
//Libera toda mem�ria alocada dinamicamente para a matriz.
