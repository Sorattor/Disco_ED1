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
//funcoes   :
NoSetor* criar_NoSetor();//valor que indica o proximo e anterior da seqüência de dados, utulizado sentinela
void adicionar_NoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);//o campo nessa funçao insere o elemeno no inicio e no fim.
void editar_NoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim);//funçao para editar o começo e o fim.
void apagar_NoSetor(NoSetor* campos); //funçao para excluir, auxiliar é uzada para excluir anterior e o proximo


 /// PARTE 2 -  TAD ARQUIVO

typedef struct noarquivo{
    char nome[40];
    unsigned long tam;
    NoSetor* setores;
    struct noarquivo* prox;
    struct noarquivo* ant;
}NoArquivo;
//funcoes   :
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

//funcoes:
Disco* disco_cria(char* nome, unsigned long tamanho);
TipoRetorno disco_grava(Disco* d, char* nomeArquivo); ///nome arquivo deve conter o caminho absoluto ou relativo do arquivo
TipoRetorno disco_remove(Disco* d, char* nome); ///somente o nome do arquivo sem o caminho
TipoRetorno disco_recupera(Disco* d, char* nome, FILE* arquivoFisico);
unsigned long Tamanho_arquivo(char *nomeArquivo);

 ///falta essa que recebe o nome do arquivo e atraves do nome busca e grava e mostra se foi possivel


typedef enum{
    SUCESSO = 0,
    ESPACO_INSUFICIENTE,
    ARQUIVO_INEXISTENTE
}TipoRetorno;




 ///Implementação da TAD ARQUIVO

NoArquivo* NoArquivo_cria (){

	NoArquivo* A = (NoArquivo*) malloc (sizeof(NoArquivo)) ;
	A->prox = A;
	A->ant = A;
    return A ;

    }

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


NoSetor* criar_NoSetor()
   {
	NoSetor* valor=(NoSetor*)malloc(sizeof(NoSetor));
	valor->prox=valor;
	valor->ant=valor;
	return valor;
   }

void adicionar_NoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim)
   {
  NoSetor *comeco=(NoSetor*)malloc(sizeof(NoSetor));
  comeco->inicio=inicio ;
  comeco->fim=fim ;
  comeco->ant=campo->prox->ant;
  comeco->prox=campo->prox;
  campos->prox->ant =comeco;
  campos->prox=comeco;
   }

void editar_NoSetor(NoSetor* campos, unsigned long inicio, unsigned long fim)
    {
  campos->prox->inicio = inicio ;
  campos->prox->fim = fim ;
    }
void apagar_NoSetor(NoSetor* campos)
    {
  campos->prox->prox->ant = campos->prox->ant;
  campos->prox = campos->prox->prox;
  free(ant);
  free(prox);

    }

/// Implementacao do tad de DISCO E TIPO RETORNO


//funcoes implementadas

unsigned long Tamanho_axrquivo(char* nomeArquivo) {
  FILE* Arquivo = fopen(nomeArquivo, "rb") ;
  fseek(Arquivo,0,SEEK_END);
  unsigned long tamArquivo = ftell(Arquivo);
  fseek(Arquivo,0,SEEK_SET); ///nao deixa o ponteiro ficar no final do arquivo
  fclose(Arquivo) ;

  return  tamArquivo; /// recebe nome do arquivo e retorna seu tamanho
}

Disco* disco_cria(char* nome, unsigned long tamanho){

  Disco *d = (Disco*)malloc(sizeof(Disco));
   strcpy(d->nome, nome); //  cria o disco d nomeia com o nom recebido por parametro


  d->disco = (void*)malloc(tamanho) ;
  d->livres = criar_NoSetor(); //sentinela
  adiciona_NoSetor(d->livres, 0, tamanho);//Adiciona o Tamanho livre

  d->arquivos = criar_NoArquivo(); //sentinela
  strcpy(d->arquivos->nome, "Sentinela");

  d->tamDisco = d->espacoLivre = tamanho; //o disco esta completamente vazio para ser inicializado

  d->espacoOcupado = d->qtdeArquivos = 0 // disco vazio = disco sem arquivos;

  return d ;
  //retorna o disco criado
}

TipoRetorno disco_grava(Disco* d, char* nomeArquivo){

  int t = 1 ;
  unsigned long tamRestante = 0;


	unsigned long SizeFile = Tamanho_arquivo(nomeArquivo); // pega o tamanho do arquivo e coloca na variavel size file

  FILE* Arquivo = fopen(nomeArquivo, "rb") ; //abre o arquivo


	if( SizeFile > ( d->espacoLivre )) return ESPACO_INSUFICIENTE; //Verifica se o tamanho do arquivo é maior que o disco

  adicionar_NoArquivo(d->arquivos, nomeArquivo, SizeFile); //Cria uma struct Arquivo e Aloca dentro de Arquivos

  tamRestante = SizeFile; // quanto falta para colocar no disco

  while(t){
    adiciona_NoSetor(d->arquivos->prox->setores, 0, 0); // cria um nó em setores no Arquivos
    editar_NoSetor(d->arquivos->prox->setores, d->livres->prox->inicio, 0); // editar o nó de acordo com o diagrama

    if( ((d->livres->prox->fim) - (d->livres->prox->inicio)) >= tamRes ){ // Verifica se o nó que esta no livres tem espaço suficiente para alocar os bits

      editar_NoSetor(d->arquivos->prox->setores, d->arquivos->prox->setores->prox->inicio, (d->arquivos->prox->setores->prox->inicio)+tamRes);

      if(d->livres->prox->inicio == d->arquivos->prox->setores->prox->inicio ){ // Verificar se é um Nó no Livre que ainda esta 'virgem'

        d->livres->prox->inicio = d->arquivos->prox->setores->prox->fim;

        if(d->livres->prox->inicio == d->livres->prox->fim){// veririca se a capacidade do nó nao esta cheia
            /* Apagar Nó no Livre, fazer essa função*/


          apagar_NoSetor(d->livres);
        }

      }

      fread(d->disco+(d->arquivos->prox->setores->prox->inicio), (d->arquivos->prox->setores->prox->fim)-(d->arquivos->prox->setores->prox->inicio), 1, Arquivo);
      d->espacoLivre = d->espacoLivre - SizeFile;
      d->qtdeArquivos = d->qtdeArquivos + 1 ;
      tmp = 0;

    }else{

      d->arquivos->prox->setores->prox->fim = d->livres->prox->fim;
      apagar_NoSetor(d->livres);
      tamRes = tamRes - ( d->arquivos->prox->setores->prox->fim - d->arquivos->prox->setores->prox->inicio );
      fread(d->disco+(d->arquivos->prox->setores->prox->inicio), (d->arquivos->prox->setores->prox->fim)-(d->arquivos->prox->setores->prox->inicio), 1, Arquivo);


    }

  }
  fclose(Arquivo);
  return SUCESSO;
}

TipoRetorno disco_recupera(Disco* d, char* nome, FILE* arquivoFisico){

  NoArquivo* auxArq = procurar_NoArquivo(d->arquivos, nome);
  if(auxArq == NULL) return ARQUIVO_INEXISTENTE;

  NoSetor *AuxNo = auxArq->setores->ant;

  while(!(AuxNo == auxArq->setores)){
    fwrite(d->disco+(AuxNo->inicio), (AuxNo->fim)-(AuxNo->inicio), 1, arquivoFisico);
    AuxNo = AuxNo->ant;
  }
  fclose(arquivoFisico);

  return SUCESSO;
}

TipoRetorno disco_remove(Disco* d, char* nome){

  NoArquivo* auxArq = procurar_NoArquivo(d->arquivos, nome);
  if(auxArq == NULL) return ARQUIVO_INEXISTENTE;

  NoSetor *AuxNo = auxArq->setores->ant;
  while(!(AuxNo == auxArq->setores)){

    AuxNo = setorTolivre(d->livres, AuxNo);
  }

  d->espacoLivre = d->espacoLivre + (auxArq->tam);
  apagar_NoArquivo(auxArq->ant);
  d->qtdeArquivos = d->qtdeArquivos - 1;

  return SUCESSO;

}

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
         sentine zla_setor->ant = NULL;
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
Disco * insereNoArquivo(NoArquivo* noarq, Disco* d, int posicao){


         *d->livres->prox = no;
         no->ant = *d->livres;
         *d->livres->ant = no->prox;
         no->prox = *d->livres->ant;
}
