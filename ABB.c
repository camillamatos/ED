#include <stdio.h>
#include <stdlib.h>

typedef struct No{
  int num;
  struct No* right; 
  struct No* left; 
} No;

No* criaNo(){
	return NULL;
}

void inserirNo(No** pos, int num){ 
  if(*pos == NULL)  {
    *pos = (No*)malloc(sizeof(No)); 
    (*pos)->left = NULL; 
    (*pos)->right = NULL; 
    (*pos)->num = num; 
  }else{
    if(num <= (*pos)->num){
      inserirNo(&(*pos)->left, num);
    }else{
       inserirNo(&(*pos)->right, num);
    }
  }
}

No *MaiorEsquerda(No** arvore){
    if((*arvore)->right != NULL){
      MaiorEsquerda(&(*arvore)->right);
    }else{
    	No *aux = *arvore;
    	if((*arvore)->left != NULL){
    		*arvore = (*arvore)->left;
		}else{
			*arvore = NULL;
		}
			return aux;
    }
    
}

void remover(No **pos, int num){
    if(*pos == NULL){  
       printf("Numero nao encontrado!");    
       return;
    }
    
    if(num < (*pos)->num){
    	remover(&(*pos)->left, num);
	}else if(num > (*pos)->num){
		remover(&(*pos)->right, num);
	}else{  
        No *posAux = *pos;    
		if (((*pos)->left == NULL) && ((*pos)->right == NULL)){    
            free(posAux);
            *pos = NULL; 
        }else{   
            if((*pos)->right == NULL){
            	(*pos) = (*pos)->left;
            	posAux->left = NULL;
            	free(posAux);
			} else if ((*pos)->left == NULL){
				(*pos) = (*pos)->right;
            	posAux->right = NULL;
            	free(posAux);
			}else{
				posAux = MaiorEsquerda(&(*pos)->left);
				posAux->left = (*pos)->left;
				posAux->right = (*pos)->right;
				(*pos)->left = (*pos)->right = NULL;
				free((*pos));
				*pos = posAux;
			}
        }
    }
}

void busca(No **pos, int num){
    if(*pos == NULL){  
       printf("Numero nao encontrado!");    
       return;
    }
    
    if(num < (*pos)->num){
    	busca(&(*pos)->left, num);
	}else if(num > (*pos)->num){
		busca(&(*pos)->right, num);
	}else{  
        printf("Numero se encontra na arvore!");
    }
}

void inOrdem(No* raiz){
	if (raiz != NULL){
		inOrdem(raiz->left);
		printf("%i\t",raiz->num);
		inOrdem(raiz->right);
	}
}

void preOrdem(No* raiz){
	if (raiz != NULL){
		printf("%i\t",raiz->num);
		preOrdem(raiz->left);
		preOrdem(raiz->right);
	}
}

void posOrdem(No* raiz){
	if (raiz != NULL){
		posOrdem(raiz->left);
		posOrdem(raiz->right);
		printf("%i\t",raiz->num);
	}
}

int main(){
  No* pos = criaNo(); 
  int op, num;
  
  for(;;){
  	printf("Escolha uma opcao: (1) Inserir  (2) Excluir  (3) Imprimir  (4) Busca  (5) Sair ");
  	scanf("%i", &op);
  	
  	system("cls");

  	
  	if(op==5){
  		printf("Programa finalizado!");
  		break;
	  }else if(op==1){
	  	printf("Digite o numero que deseja inserir: ");
	  	scanf("%i", &num);
	  	inserirNo(&pos, num);
	  }else if(op==2){
	  	printf("Digite o numero que deseja remover: ");
	  	scanf("%i", &num);
	  	remover(&pos, num);
	  }else if(op==3){
	  	printf("Escolha o tipo de impressao: 1 Em ordem  2 Pre ordem  3 Pos ordem ");
	  	scanf("%i", &op);
	  	
	  	if(op==1){
	  		inOrdem(pos);
		  }else if(op==2){
		  	preOrdem(pos);
		  }else if(op==3){
		  	posOrdem(pos);
		  }else{
		  	printf("Opcao invalida!");
		  }
	  }else if(op==4){
	  	printf("Digite o numero que deseja buscar: ");
	  	scanf("%i", &num);
	  	busca(&pos, num);
	  }else{
	  	printf("Opcao invalida!");
	  }
	  
	  printf("\n\n");
  }
	
  
}

