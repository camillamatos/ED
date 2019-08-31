#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento{
	int dado;
	struct sElemento *next;
	struct sElemento *prev;
}Elemento;

typedef struct sLista{
	struct sElemento *head;
	struct sElemento *tail;
	int size;
}Lista;


void imprimir(Lista *valores){
	Elemento* aux;
	aux = valores->head;
	int i = 0;
	for(i=0;i<valores->size;i++){
		printf("%i  ", aux->dado);
		aux = aux->next;
	}
	printf("\n");
}

void inserir(Lista* valores, Elemento* pivo, int valor){
	Elemento* novo = (Elemento*) malloc (sizeof(Elemento));
	
	novo->dado=valor;
	novo->next = NULL;
	novo->prev=NULL;

	if(pivo==NULL && valores->size!=0){
		printf("Nao e possivel inserir um valor na posicao NULL quando a lista nao esta vazia.");
		return;
	}
	
	if(valores->size==0){
		valores->head = novo;
		valores->tail=novo;
	}else{
		novo->next=pivo->next;
		novo->prev=pivo;
		
		if(pivo->next==NULL){
			valores->tail=novo;
		} else{
			pivo->next->prev = novo;
		}	
			
		pivo->next=novo;			
	}
		valores->size++;
}
					
void remover(Lista *valores, Elemento *antigo){
	if(valores->size!=0 && antigo!=NULL){
		if(antigo == valores->head){
			valores->head = antigo->next;
			if(valores->head == NULL){
				valores->tail=NULL;
			}else{
				antigo->next->prev = NULL;
			}
		}else{
			antigo->prev->next = antigo->next;
			if(antigo->next == NULL){
				valores->tail = antigo->prev;
			}else{
				antigo->next->prev = antigo->prev;
			}
		}
		
		free(antigo);
		valores->size--;
	}
}

int main(){
	Lista* valores = (Lista*) malloc(sizeof(Lista));
	valores->head=NULL;
	valores->tail=NULL;
	valores->size=0;
	inserir(valores, NULL, 1);
	inserir(valores, valores->head, 4);
	inserir(valores, valores->tail, 7);
	inserir(valores, NULL, 8);
	inserir(valores, valores->head->next, 2);
	printf("\nInsercao de 1, 4, 7, 8 e 2: ");
	imprimir(valores);
	remover(valores,NULL);
	printf("\nRemocao na posicao null: ");
	imprimir(valores);
	remover(valores,valores->tail);
	printf("\nRemocao na posicao tail: ");
	imprimir(valores);
	remover(valores,valores->head);
	printf("\nRemocao na posicao head: ");
	imprimir(valores);
	remover(valores,NULL);
	printf("\nRemocao na posicao null: ");
	imprimir(valores);

	free(valores);
	}




