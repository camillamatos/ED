#include<stdio.h> 
#include<stdlib.h> 

struct Node { 
    int num; 
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 
  
int max(int a, int b); 
  
int height(struct Node *tree) { 
    if (tree == NULL){
        return 0;
    } 
    return tree->height; 
} 
 
int max(int a, int b) { 
    if(a>b){
        return a;
    }else{
        return b;
    }
} 
  
struct Node* new(int num) { 
    struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
    node->num  = num; 
    node->left  = NULL; 
    node->right = NULL; 
    node->height = 1;  
    return(node); 
} 
  
struct Node *rotateR(struct Node *tree) { 
    struct Node *aux = tree->left; 
    struct Node *aux2 = aux->right; 
  
    aux->right = tree; 
    tree->left = aux2; 
  
    tree->height = max(height(tree->left), height(tree->right))+1; 
    aux->height = max(height(aux->left), height(aux->right))+1; 
 
    return aux; 
} 
  
struct Node *rotateL(struct Node *tree) { 
    struct Node *aux = tree->right; 
    struct Node *aux2 = aux->left; 
   
    aux->left = tree; 
    tree->right = aux2; 
  
    tree->height = max(height(tree->left), height(tree->right))+1; 
    aux->height = max(height(aux->left), height(aux->right))+1; 
  
    return aux; 
} 
  
int getBalance(struct Node *tree) { 
    if (tree == NULL){
        return 0; 
    } 
        
    return height(tree->left) - height(tree->right); 
} 
  
struct Node* insert(struct Node* node, int num) { 
    if (node == NULL){
        return(new(num));
    } 
         
    if (num <= node->num){
         node->left  = insert(node->left, num); 
    }else if (num > node->num){
        node->right = insert(node->right, num);
    }
  
    node->height = 1 + max(height(node->left), height(node->right)); 
  
    int balance = getBalance(node); 
  
    if (balance > 1 && num < node->left->num){
        return rotateR(node); 
    }else if (balance < -1 && num > node->right->num){
        return rotateL(node);
    } else if (balance > 1 && num > node->left->num) { 
        node->left =  rotateL(node->left); 
        return rotateR(node); 
    } else if (balance < -1 && num < node->right->num) { 
        node->right = rotateR(node->right); 
        return rotateL(node); 
    } 
  
    return node; 
} 

struct Node * maiorEsquerda(struct Node* node) {
    
    if(node->right != NULL){
        maiorEsquerda(node->left);
    }else{
        struct Node* aux = node; 
        if(node->left != NULL){
            node = node->left;
        }else{
            node = NULL;
        }
        return aux;
    }
} 
  
struct Node* deleteNode(struct Node* node, int num) { 
  
    if (node == NULL){
        return node;
    } 
         
    if ( num < node->num ){
        node->left = deleteNode(node->left, num);
    } else if( num > node->num ){
        node->right = deleteNode(node->right, num); 
    }else{ 
        struct Node *aux = node;
        if((node->left == NULL) && (node->right == NULL)){
            node = NULL;
        }else{
            
            if(node->right == NULL){
                node = node->left;
            }else if(node->left == NULL){
                node = node->right;
            }else{
                aux = maiorEsquerda(node->left);
                aux->left = node->left;
                aux->right = node->right;
                node->left = NULL;
                node->right = NULL;
                free(node);
                *node = *aux;
            }
        }
    }
 
    if (node == NULL){
        return node; 
    } 
      
    node->height = 1 + max(height(node->left), height(node->right)); 
    
    int balance = getBalance(node); 
  
    if (balance > 1 && getBalance(node->left) >= 0){
        return rotateR(node); 
    } 
        
    if (balance > 1 && getBalance(node->left) < 0) { 
        node->left =  rotateL(node->left); 
        return rotateR(node); 
    } 
  
    if (balance < -1 && getBalance(node->right) <= 0){
        return rotateL(node);
    } 
          
    if (balance < -1 && getBalance(node->right) > 0) { 
        node->right = rotateR(node->right); 
        return rotateL(node); 
    } 
  
    return node; 
} 
  
void preOrder(struct Node *node) { 
    if(node != NULL) { 
        printf("%d ", node->num); 
        preOrder(node->left); 
        preOrder(node->right); 
    } 
} 

void inOrder(struct Node *node){
	if(node != NULL) { 
        inOrder(node->left); 
        printf("%d ", node->num); 
        inOrder(node->right); 
    } 
}

void posOrder(struct Node *node){
	if(node != NULL) { 
        posOrder(node->left); 
        posOrder(node->right); 
        printf("%d ", node->num);
    } 
}
  

int main() { 
  struct Node *node = NULL; 
  int op, num;
  
  for(;;){
        printf("Escolha uma opcao: (1) Inserir  (2) Excluir  (3) Imprimir  (4) Sair ");
	  	scanf("%i", &op);
	  	
	  	system("cls");
	
	  	if(op==4){
	  		printf("Programa finalizado!");
	  		break;
		  }else if(op==1){
		  	printf("Digite o numero que deseja inserir: ");
		  	scanf("%i", &num);
		  	node = insert(node, num);
		  }else if(op==2){
		  	printf("Digite o numero que deseja remover: ");
		  	scanf("%i", &num);
		  	node = deleteNode(node, num); 
		  }else if(op==3){
		  	printf("Escolha o tipo de impressao: 1 Em ordem  2 Pre ordem  3 Pos ordem ");
		  	scanf("%i", &op);
		  	
		  	if(op==1){
		  		inOrder(node);
			  }else if(op==2){
			  	preOrder(node);
			  }else if(op==3){
			  	posOrder(node);
			  }else{
			  	printf("Opcao invalida!");
			  }
		  }else{
		  	printf("Opcao invalida!");
		  }
		  
		  printf("\n\n");
  }
  
  
} 
