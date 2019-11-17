#include <stdio.h> 
#include <stdlib.h> 
  
#define MAX_TREE_HT 100 
   
struct Node { 
    char dado; 
    unsigned freq;  
    struct Node *esquerdo, *direito; 
}; 
   
struct Arvore { 
    unsigned tamanho; 
    unsigned capacidade; 
    struct Node** array; 
}; 
  
struct Node* new(char dado, unsigned freq) { 
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); 
  
    temp->esquerdo = temp->direito = NULL; 
    temp->dado = dado; 
    temp->freq = freq; 
  
    return temp; 
} 
  
struct Arvore* criaArvore(unsigned capacidade) { 
  
    struct Arvore* arvore = (struct Arvore*)malloc(sizeof(struct Arvore)); 
  
    arvore->tamanho = 0; 
  
    arvore->capacidade = capacidade; 
  
    arvore->array = (struct Node**)malloc(arvore->capacidade * sizeof(struct Node*)); 
    return arvore; 
} 
  
void trocaNode(struct Node** a, struct Node** b) { 
    struct Node* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
void minHeapify(struct Arvore* arvore, int idx) { 
  
    int menor = idx; 
    int esquerdo = 2 * idx + 1; 
    int direito = 2 * idx + 2; 
  
    if (esquerdo < arvore->tamanho && arvore->array[esquerdo]-> freq < arvore->array[menor]->freq){
    	menor = esquerdo; 	
	}
  
    if (direito < arvore->tamanho && arvore->array[direito]-> freq < arvore->array[menor]->freq){
    	menor = direito;
	}  
  
    if (menor != idx) { 
        trocaNode(&arvore->array[menor], &arvore->array[idx]); 
        minHeapify(arvore, menor); 
    } 
} 
   
int tamUm(struct Arvore* arvore) { 
  return (arvore->tamanho == 1); 
} 

struct Node* menorNode(struct Arvore* arvore) { 
  
    struct Node* temp = arvore->array[0]; 
    arvore->array[0] = arvore->array[arvore->tamanho - 1]; 
  
    --arvore->tamanho; 
    minHeapify(arvore, 0); 
  
    return temp; 
} 

void insereArvore(struct Arvore* arvore, struct Node* node) { 
  
    ++arvore->tamanho; 
    int i = arvore->tamanho - 1; 
  
    while (i && node->freq < arvore->array[(i - 1) / 2]->freq) { 
  
        arvore->array[i] = arvore->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    arvore->array[i] = node; 
} 
  
void constroiArvore(struct Arvore* arvore) { 
  
    int n = arvore->tamanho - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i){
    	minHeapify(arvore, i); 
	}
        
}  
void printArr(int arr[], int n) { 
    int i; 
    for (i = 0; i < n; ++i){
    	printf("%d", arr[i]); 
	} 
  
    printf("\n"); 
} 
   
int folha(struct Node* raiz) { 
    return !(raiz->esquerdo) && !(raiz->direito); 
} 

struct Arvore* criaConstroiArvore(char dado[], int freq[], int tamanho) { 
  
    struct Arvore* arvore = criaArvore(tamanho); 
  	
  	int i;
    for (i = 0; i < tamanho; ++i) {
    	arvore->array[i] = new(dado[i], freq[i]);
	}
        
    arvore->tamanho = tamanho; 
    constroiArvore(arvore); 
  
    return arvore; 
} 
   
struct Node* constroiHuffman(char dado[], int freq[], int tamanho) { 
    struct Node *esquerdo, *direito, *top; 
  
    struct Arvore* arvore = criaConstroiArvore(dado, freq, tamanho); 
    
    while (!tamUm(arvore)) { 
  
        esquerdo = menorNode(arvore); 
        direito = menorNode(arvore); 
  
        top = new('$', esquerdo->freq + direito->freq); 
  
        top->esquerdo = esquerdo; 
        top->direito = direito; 
  
        insereArvore(arvore, top); 
    } 
    return menorNode(arvore); 
} 
  
void imprime(struct Node* raiz, int arr[], int top) { 
  
     if (raiz->esquerdo) { 
        arr[top] = 0; 
        imprime(raiz->esquerdo, arr, top + 1); 
    } 
  
    if (raiz->direito) { 
        arr[top] = 1; 
        imprime(raiz->direito, arr, top + 1); 
    } 
	 
    if (folha(raiz)) { 
        printf("%c: ", raiz->dado); 
        printArr(arr, top); 
    } 
} 
  
void Huffman(char dado[], double freq[], int tamanho) { 
    struct Node* raiz = constroiHuffman(dado, freq, tamanho); 
   
    int arr[MAX_TREE_HT], top = 0; 
  
    imprime(raiz, arr, top); 
} 
   
int main() { 
  
  	//paralelepipedo
    char arr[] = { 'r', 'o', 'd', 'i', 'l', 'a', 'e', 'p' }; 
	int freq[] = { 1, 1, 1, 1, 2, 2, 3, 3 }; 
  
    int tamanho = sizeof(arr); 
  
    Huffman(arr, freq, tamanho); 
  
    return 0; 
} 
