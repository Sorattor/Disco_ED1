#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//PARTE 1- Parte do setor;

 typedef struct nosetor{
    unsigned long inicio; // O tamanho da memória é sempre positivo, entao usamos o unsigned;
    unsigned long fim;
    struct nosetor* prox;
    struct nosetor* ant;
}NoSetor;

//utilizando uma sentinela para guardar os valores.

NoSetor* valorsetor();//valor que indica o proximo e anterior da seqüência de dados, utulizado sentinela
NoSetor* valorsetor()
   {
	NoSetor* valor=(NoSetor*)malloc(sizeof(NoSetor));
	valor->prox=valor;
	valor->ant=valor;
	return valor;
   }

void inserirNoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);//o campo nessa funçao insere o elemeno no inicio e no fim.

void inserirNoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim)
   {
  NoSetor *comeco=(NoSetor*)malloc(sizeof(NoSetor));
  comeco->inicio=inicio ;
  comeco->fim=fim ;
  comeco->ant=campo->prox->ant;
  comeco->prox=campo->prox;
  campos->prox->ant =comeco;
  campos->prox=comeco;
   }
void renovarNoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);//funçao para editar o começo e o fim.

void renovarNoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim)
    {
  campos->prox->inicio = inicio ;
  campos->prox->fim = fim ;
    }
void excluirNoSetor(NoSetor* campos);//funçao para excluir, auxiliar é uzada para excluir anterior e o proximo

void excluirNoSetor(NoSetor* campos)
    {
  campos->prox->prox->ant = campos->prox->ant;
  campos->prox = campos->prox->prox;
  free(ant);
  free(prox);

    }

//PARTE 2









typedef struct noarquivo{ //uma encadeação de arquivos onde cada arquivo possui um setor que corresponde ao espaco do disco ocupado por esee arquivo.
    char nome[40];
    unsigned long tam;
    NoSetor* setores;
    struct noarquivo* prox;
    struct noarquivo* ant;
}NoArquivo;
 
typedef struct{
    char nome[40];
    void* disco;
    NoSetor* livres;
    NoArquivo* arquivos;
    unsigned long tamDisco;
    unsigned long espacoLivre;
    unsigned long espacoOcupado;
    unsigned long qtdeArquivos;   
}Disco;
 
typedef enum{
    SUCESSO = 0,
    ESPACO_INSUFICIENTE,
    ARQUIVO_INEXISTENTE
}TipoRetorno;

TipoRetorno disco_cria(char* nome, unsigned long tamanho){
       Disco* d = (Disco*) malloc(sizeof(Disco));

           memcpy(d->nome, nome, sizeof(*nome));
           int disco[tamanho] = {NULL};
           d->disco* = disco[tamanho];
           d->tamDisco = tamanho;
           d->espacoLivre = tamanho;
           d->espacoOcupado = 0;
           d->qtdeArquivos = 0;



        NoArquivo* sentinela_arq = malloc(sizeof(NoArquivo));
           sentinela_arq->ant = NULL;
           sentinela_arq->prox = NULL;
           sentinela_arq->nome = NULL;
           sentinela_arq->setores =  NULL;
           sentinela_arq->tam = NULL;

           *d->arquivos = sentinela_arq;



        NoSetor* sentinela = malloc(sizeof(NoSetor));
         sentinela->ant = NULL;
         sentinela->prox = NULL;
         sentinela->fim = NULL;
         sentinela->inicio = NULL;
          *d->livres = sentinela;



        if(d != NULL){
                if(d->disco != NULL){

            return TipoRetorno->SUCESSO;
            }

            else return TipoRetorno->ESPACO_INSUFICENTE;
}



NoSetor* novoNoSetor(int in, int fim){
         NoSetor* no = malloc(sizeof(NoSetor));
         no->inicio = in;
         no->fim = fim;
         no->ant = NULL;
         no->prox = NULL;


         return no;

}
NoArquivo* novoNoArquivo(char nome[20], int tam){
           NoArquivo* noarq = (NoArquivo*) malloc(sizeof(NoArquivo));
           memcpy(noarq->nome, nome, sizeof(nome));
           noarq->tam = tam;
           noarq->setores = novo;

           NoSetor* sentinelas = malloc(sizeof(NoSetor));
         sentinelas->ant = NULL;
         sentinelas->prox = NULL;
         sentinelas->fim = NULL;
         sentinelas->inicio = NULL;

           noarq->setores = sentinelas;

           int i;
           for(i=0;i<tam;i++){
            noarq->setores->prox  = novoNoSetor();
            noarq->setores->prox = noarq->setores->ant;

           }
      return noarq;

}

Disco * insereNoSetor(NoSetor* no, Disco* d, int posicao){


          if(posicao == 1){
            d->livres->prox = no;
            no->ant = d->livres;
            d->livres->ant = no->prox;
            no->prox = d->livres->ant;
         }

         else
         for(cont=0; cont!= posicao; cont++){
                d->livres = d->livres->prox;
         }
            d->livres->prox = no;
            no->ant = d->livres;
            d->livres->ant = no->prox;
            no->prox = d->livres->ant;

            return d;
}
Disco * insereNoArquivo(NoArquivo* noarq, Disco* d, int posicao){}


         *d->livres->prox = no;
         no->ant = *d->livres;
         *d->livres->ant = no->prox;
         no->prox = *d->livres->ant;
         }

//fazer funcao para escrever em um arquivo, usar as funcoes de abrir o arquivo e fputs(string* s, FILE* F); para escrever uma string com espaco e depois gravar ela no disco,
// ou gravar em binario no arquivo
//usar a funcao feof para final do arquivo feof();
//char * fgets(char* str, int tamanho, FILE* F);
//fwrite para escrever blocos de bites com qualquer tipo
//int fwrite(void* buffer, int bytes, int count, FILE f);

TipoRetorno disco_grava(Disco* d, char* arquivo); //nome arquivo deve contera
