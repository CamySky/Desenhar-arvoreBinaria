#include <stdio.h>
#include <stdlib.h>		 
#include <math.h>
#include<locale.h>

typedef struct no {
    int valor;
    struct no *direita, *esquerda;
} NoArv;


//inser��o iterativa
void inserir(NoArv **raiz, int num) {
    NoArv *aux = *raiz;
    while (aux) {
        if (num < aux->valor) {
            raiz = &aux->esquerda;
        } else {
            raiz = &aux->direita;
        }
        aux = *raiz;
    }
    aux = malloc(sizeof(NoArv));
    aux->valor = num;
    aux->esquerda = NULL;
    aux->direita = NULL;
    *raiz = aux;
}

//Ter a altura da �rvore de forma din�nmica auxilia na forma��o da matriz, para a crai��o do desenho da �rvore.
int altura(NoArv *raiz){
	if(raiz == NULL){
		return -1;
	}else{
		int esq = altura(raiz->esquerda);
		int dir = altura(raiz->direita);
		if(esq > dir){
			return esq + 1;
		}else{  
			return dir + 1;
		}
	}
}

//Aloca dinamicamente na matriz os valores inseridos.
void alocar_pre_ordem(NoArv *raiz, int **arvore, int linha, int coluna, int i, int j) {
    if (raiz == NULL) {
        return;
    }
    arvore[i][j] = raiz->valor;
    alocar_pre_ordem(raiz->esquerda, arvore, linha, coluna, i + 1, j - (int)pow(2, linha - i - 2));
    alocar_pre_ordem(raiz->direita, arvore, linha, coluna, i + 1, j + (int)pow(2, linha - i - 2));
}

void imprimir(NoArv *raiz) {
    int linha, coluna, i, j;
    int **arvore;

    linha = altura(raiz) + 1;
    coluna = (int)pow(2, linha) - 1;

	//Cria��o da matriz din�mica:
    arvore = malloc(linha * sizeof(int*));
    for (i = 0; i < linha; i++) {
        arvore[i] = malloc(coluna * sizeof(int));
        for (j = 0; j < coluna; j++) {
            arvore[i][j] = -1;
        }
    }
	
    alocar_pre_ordem(raiz, arvore, linha, coluna, 0, (coluna - 1) / 2);

	//Sempre que n�o haver um valor de inser��o(-1), um espa�o em branco ser� dado para a forma��o do desenho.
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            if (arvore[i][j] == -1) {
                printf("   ");
            } else {
                printf("%3d", arvore[i][j]);
            }
        }
        printf("\n");
    }

    for (i = 0; i < linha; i++) {
        free(arvore[i]);
    }
    free(arvore);
}

int main(void) {
	setlocale(LC_ALL, "Portuguese");
    NoArv *busca, *raiz = NULL;
    int opcao, valor, contQuinze;

    do {
        printf("\n0 - Sair\n1 - Inserir\n2 - Imprimir\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
            	if(contQuinze < 15){
            		printf("\nValor: ");
	                scanf("%d", &valor);
	                contQuinze++;
	                inserir_v3(&raiz, valor);
				}else{
					printf("O n�mero de inser��es chegou ao limite.");
				}
                break;
            case 2:
                imprimir(raiz);
                break;
            default:
                if (opcao != 0) {
                    printf("\nOp��o inv�lida.\n");
                }
        }
    } while (opcao != 0);
    return 0;
}
