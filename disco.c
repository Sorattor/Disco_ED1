#include<stdio.h>
#include<stdlib.h>
#include<string.h>



///PARTE 1- TAD setor;

 typedef struct nosetor {
    unsigned long inicio; // O tamanho da memória é sempre positivo, entao usamos o unsigned;
    unsigned long fim;
     struct nosetor* prox;
     struct nosetor* ant;
}NoSetor;

NoSetor* valorsetor();//valor que indica o proximo e anterior da seqüência de dados, utulizado sentinela
void inserirNoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);//o campo nessa funçao insere o elemeno no inicio e no fim.
void editarNoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);//funçao para editar o começo e o fim.
void excluirNoSetor(NoSetor* campos); //funçao para excluir, auxiliar é uzada para excluir anterior e o proximo


 /// PARTE 2 -  TAD ARQUIVO
typedef struct noarquivo{
    char nome[40];
    unsigned long tam;
    NoSetor* setores;
    struct noarquivo* prox;
    struct noarquivo* ant;
}NoArquivo;

//cria adiciona e procura arquivo, alem de apagar
NoArquivo* NoArquivo_cria();
void NoArquivo_adiciona (NoArquivo* Arquivo, char* Nome, unsigned long tam);
NoArquivo* NoArquivo_procura(NoArquivo* Arquivo, char* Nome);
void NoArquivo_apaga(NoArquivo* Arquivo);

 ///Parte 3 - TAD disco e TIPO RETORNO
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

 //FUNCOES TAD





 ///Implementação da TAD ARQUIVO
NoArquivo* NoArquivo_cria (){

	NoArquivo* A = (NoArquivo*) malloc (sizeof(NoArquivo)) ;
	A->prox = A;
	A->ant = A;
    return A;}

void NoArquivo_adiciona(NoArquivo* Arquivo, char* Nome, unsigned long tam){

  NoArquivo *Novo = (NoArquivo*)malloc(sizeof(NoArquivo));
  strcpy(Novo->nome, Nome);
  Novo->tam = tam ;

  Novo->setores = criar_NoSetor(); // cria um setor sentinela no arquivo

  Novo->ant = Arquivo->prox->ant;
  Novo->prox = Arquivo->prox;
  Arquivo->prox->ant = Novo;
  Arquivo->prox = Novo;

}

NoArquivo*  NoArquivo_procura(NoArquivo* Arquivo, char* Nome){
  NoArquivo* auxiliar = Arquivo->prox;

  while( (strcmp (aux->nome,Nome)) != 0 ){
      printf("Procurando");
      auxiliar = auxiliar->prox;

      if(aux == Arquivo) return NULL;
  }

  return auxiliar;

}

void NoArquivo_apaga(NoArquivo* Arquivo){
  NoArquivo *auxiliar = Arquivo->prox;
  Arquivo->prox->prox->ant = Arquivo->prox->ant;
  Arquivo->prox = Arquivo->prox->prox;
  free(auxiliar);
 }


///Implementação do TAD SETORES COM FUNCOES INSERIR EDITAR E EXCLUIR E CONSULTAR CONTEUDO DO SETOR


NoSetor* valorsetor()
   {
	NoSetor* valor=(NoSetor*)malloc(sizeof(NoSetor));
	valor->prox=valor;
	valor->ant=valor;
	return valor;
   }

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

void editarNoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim)
    {
  campos->prox->inicio = inicio ;
  campos->prox->fim = fim ;
    }
void excluirNoSetor(NoSetor* campos)
    {
  campos->prox->prox->ant = campos->prox->ant;
  campos->prox = campos->prox->prox;
  free(ant);
  free(prox);

    }

/// Implementacao do tad de DISCO E TIPO RETORNO


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



        NoSetor* sentinela_setor = malloc(sizeof(NoSetor));
         sentinela_setor->ant = NULL;
         sentinela_setor->prox = NULL;
         sentinela_setor->fim = NULL;
         sentinela_setor->inicio = NULL;
          *d->livres = sentinela_setor;



        if(d != NULL )
         {
                if(d->disco != NULL)
                    {

 return TipoRetorno->SUCESSO;

                    }
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
