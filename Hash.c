#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sElemento{
	char dado[30];
	struct sElemento *next;
	struct sElemento *prev;
}Elemento;

typedef struct sLista{
	struct sElemento *head;
	struct sElemento *tail;
	struct sLista *next;
	struct sLista *prev;
	int dado;
	int size;
}Lista;

typedef struct sHash{
	struct sLista *head;
	struct sLista *tail;
	int size;
}Hash;

Hash* criarHash(){
	Hash *hash = (Hash*) malloc (sizeof(Hash));
	hash->head = NULL;
	hash->tail = NULL;
	hash->size = 0;
	return hash;
}

Elemento* criarElemento(){
	Elemento* elemento = (Elemento*) malloc (sizeof(Elemento));
	elemento->next = NULL;
	elemento->prev=NULL;
	return elemento;
}

Lista* criarListaPrincipal(int dado){
	Lista *lista = (Lista*) malloc (sizeof(Lista));
	lista->head = NULL;
	lista->tail = NULL;
	lista->next = NULL;
	lista->prev = NULL;
	lista->dado = dado;
	lista->size = 0;
	
	return lista;
}

int pegarChave(char *dado){
	char palavra = dado[0];
	int chave = (int) palavra;
	return chave % 10;
}

Lista* inserirHash(Hash *hash, int dado){
	Lista *pivo = hash->tail;
	Lista *nova = criarListaPrincipal(dado);
	
	if(pivo==NULL && hash->size!=0){
		printf("Nao e possivel inserir um valor na posicao NULL quando a lista nao esta vazia.");
		return;
	}
	
	if(hash->size == 0){
		hash->head = nova;
		hash->tail =nova;
	}else{
		nova->next = pivo->next;
		nova->prev = pivo;
		if(pivo->next == NULL){
			hash->tail = nova;
		}else{
			pivo->next->prev = nova;
		}
		pivo->next = nova;
	}
	hash->size++;
	
	return nova;
}

void inserirNomeLista(Lista *lista, Elemento *pivo, char *nome){
	Elemento *elemento = criarElemento();
	strcpy(elemento->dado, nome);
	
	if(pivo==NULL && lista->size!=0){
		elemento->next = lista->head;
		elemento->prev = pivo;
		lista->head->prev = elemento;
		lista->head = elemento;
		
	}else if(lista->size == 0){
		lista->head = elemento;
		lista->tail = elemento;		
	}else{
		elemento->next = pivo->next;
		elemento->prev = pivo;
		if(pivo->next == NULL){
			lista->tail = elemento;
		}else{
			pivo->next->prev = elemento;
		}
		pivo->next = elemento;
	}
	lista->size++;	
}

Elemento* ordenaNome(Lista *lista, char *nome){
	Elemento *elemento = lista->head;
	
	while(elemento != NULL){
		int tam1 = strlen(nome);
		int tam2 = strlen(elemento->dado);
		int tam = tam1;
		
		if(tam1>tam2){
			tam = tam2;
		}
		
		if(strncmp(nome, elemento->dado, tam)<0 && strncmp(elemento->dado, lista->head->dado, tam)==0){
			return NULL;
		}else if(strncmp(nome, elemento->dado, tam)==0){
			return elemento;
		}else if (strncmp(nome, elemento->dado, tam) <0){
			return elemento->prev;
		}
		
		elemento = elemento->next;	
	}
	return lista->tail;
}

Elemento* encontraNome(Lista *lista, char *nome){
	Elemento *elemento = lista->head;
	strcat(nome, "\n");
	
	while(elemento != NULL){
		int tam1 = strlen(nome);
		int tam2 = strlen(elemento->dado);
		int tam = tam1;
		
		if(tam1<tam2){
			tam = tam2;
		}
		
		if(strncmp(nome, elemento->dado, tam)==0){
			return elemento;
		}
		
		elemento = elemento->next;	
	}
	return NULL;
}
		
void atribuirHash(Hash *hash){
	Lista* nova;
	int i = 0;
	for(i=0;i<10;i++){
		nova = inserirHash(hash, i);
	}
}

void imprimirHash(Hash *hash){
	int total=0;
	Lista *aux = hash->head;
	Elemento *auxNomes;
	
	while(aux!=NULL){
		printf("Chave: %d  Qnt de nomes (%i) = ", aux->dado, aux->size);
		auxNomes = aux->head;
		while(auxNomes!=NULL){
			printf("%s", auxNomes->dado);
			auxNomes = auxNomes->next;
		}
		printf("\n");	
		total += aux->size;
		aux = aux->next;
	}
	
	printf("Total de nomes: %i \n\n", total);
}

void imprimirHashEspec(Hash *hash, int key){
	Lista *aux = hash->head;
	Elemento *auxNomes;
	
	while(aux!=NULL){
		if(aux->dado==key){
			printf("Chave: %d  Qnt de nomes (%i) = ", aux->dado, aux->size);
			auxNomes = aux->head;
			while(auxNomes!=NULL){
				printf("%s", auxNomes->dado);
				auxNomes = auxNomes->next;
			}
			printf("\n");
			break;			
		}
		aux = aux->next;	
	}		
}

Lista* encontraChave(Hash *hash, int key){
	Lista *aux = hash->head;	
	while(aux!=NULL){
		if (aux->dado == key){
			return aux;
		}
		aux = aux->next;	
	}	
	return NULL;
}

void removerNome(Lista *lista, Elemento *antigo){
	if(lista->size!=0 && antigo!=NULL){
		if(antigo == lista->head){
			lista->head = antigo->next;
			if(lista->head == NULL){
				lista->tail=NULL;
			}else{
				antigo->next->prev = NULL;
			}
		}else{
			antigo->prev->next = antigo->next;
			if(antigo->next == NULL){
				lista->tail = antigo->prev;
			}else{
				antigo->next->prev = antigo->prev;
			}
		}
		
		free(antigo);
		lista->size--;
	}
}

void abrirTxt(hash){
	int key;
	FILE *arquivo = fopen("nomes.txt", "r");

	char linha[30];
	while(!feof(arquivo)){
		fgets(linha, 30, arquivo);
		key = pegarChave(linha);
		Lista *lista = encontraChave(hash, key);
		Elemento *pivo = ordenaNome(lista, linha);
		inserirNomeLista(lista, pivo, linha);
		
	}
}

int main(){
	Hash *hash = criarHash();
	atribuirHash(hash);
	Elemento *elemento = criarElemento();
	int key, op=0;
	char nome[30];
	
	printf("Carregando o arquivo de nomes ...\n");
	abrirTxt(hash);
	
	system("cls");
	for(;;){
		printf("Escolha uma opcao: 1 Inserir   2 Remover   3 Imprimir   4 Buscar   5 Sair: ");
		scanf("%i", &op);
		
		if(op ==1){
			printf("Qual nome deseja inserir?");
			scanf("%s", &nome);
			strcpy(elemento->dado, nome);
			key = pegarChave(elemento->dado);
			Lista *lista = encontraChave(hash, key);
			Elemento *existe = encontraNome(lista, elemento->dado);
			if(existe!=NULL){
				system("cls");
				printf("%s ja esta inserido!\n", nome);
			}else{
				Elemento *pivo = ordenaNome(lista, elemento->dado);
				inserirNomeLista(lista, pivo, elemento->dado);
				system("cls");
				printf("%s inserido com sucesso! \n", nome);
			}
			
		}else if(op==2){
			printf("Qual nome deseja remover?");
			scanf("%s", &nome);
			strcpy(elemento->dado, nome);
			key = pegarChave(elemento->dado);
			Lista *lista = encontraChave(hash, key);
			Elemento *pivo = encontraNome(lista, elemento->dado);
			system("cls");
			if(pivo==NULL){
				printf("%s nao encontrado!\n", nome);
			}else{
				removerNome(lista, pivo);
				printf("%s removido com sucesso! \n", nome);
			}
			
			
		}else if(op==3){
			printf("Deseja imprimir uma chave especifica (digite o valor da chave [0 - 9]) ou todas (digite qualquer outro numero)? ");
			scanf("%i", &key);
			system("cls");
			
			if ((key>=0) && (key<10)){
				imprimirHashEspec(hash, key);
			}else{
				imprimirHash(hash);
			}
				
		}else if(op==4){
			printf("Qual nome deseja buscar?");
			scanf("%s", &nome);
			strcpy(elemento->dado, nome);
			key = pegarChave(elemento->dado);
			Lista *lista = encontraChave(hash, key);
			Elemento *pivo = encontraNome(lista, elemento->dado);
			system("cls");
			if(pivo==NULL){
				printf("%s nao se encontra na base de dados!\n", nome);
			}else{
				printf("%s foi encontrado na chave %i!\n", nome, key);
			}
			
		}else if(op==5){
			system("cls");
			printf("Programa finalizado!");
			break;
		}else{
			printf("Opcao invalida!");
		}
	}
	
}




