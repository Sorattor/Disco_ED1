#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct noarquivo{
    char nome[40];
    unsigned long tam;
    NoSetor* setores;
    struct noarquivo* prox;
    struct noarquivo* ant;
}NoArquivo;

//cria adiciona e procura arquivo
NoArquivo* NoArquivo_cria();
void NoArquivo_adiciona (NoArquivo* Arquivo, char* Nome, unsigned long tam);
NoArquivo* NoArquivo_procura(NoArquivo* Arquivo, char* Nome);
void NoArquivo_apaga(NoArquivo* Arquivo);

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
      printf("LOOP");
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
}
