#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct tabela {
    long int * vetor;
    long int elementos;
    long int tamanho;
} tabela;

void adicionar(tabela * tab, long int numero, int isAlocar, int aumento);
tabela * alocar_tabela();
long int * alocar_vetor(long int tamanho);
long int * copiar_vetor(long int *vetor, long int *vetor2, long int tamanho);
void mostra_vetor(long int * vet , long int tamanho);
void remover(tabela * tab, int isAlocar, int reducao);

int main()
{    
    tabela * tab = alocar_tabela();
    int i;
    clock_t t;
    double tempo;
    setlocale(LC_ALL, "Portuguese");
    
    // Exercício letra A (inserir e remover 100.000.000 elementos com um array fixo)
    tab->vetor = alocar_vetor(100000000);
    tab->tamanho = 100000001;    
    for(i = 0; i < 5; i++) {
	    t = clock();
	    for(i = 0; i < 100000000; i++) {
	    	adicionar(tab, 1, 0, 2);
		}
		
		for(i = 0; i < 100000000; i++) {
	    	remover(tab, 0, 2);
		}
		t = clock() - t;
		tempo += ((double)t)/((CLOCKS_PER_SEC/1000));	
	}    	
    printf("Tempo médio da execução da letra A em milisegundos: %lf\n", tempo/5);
    // Fim do exercício letra A.
    
    // Exercício letra B (inserir e remover 100.000.000 elementos com um array dinâmico com aumento de 2 e diminuição de 2)
    for(i = 0; i < 5; i++) {
		free(tab);   	
    	tab = alocar_tabela();
	    t = clock();
	    for(i = 0; i < 100000000; i++) {	    	
	    	adicionar(tab, 1, 1, 2);
		}
		
		for(i = 0; i < 100000000; i++) {
	    	remover(tab, 1, 2);
		}
		t = clock() - t;
		tempo += ((double)t)/((CLOCKS_PER_SEC/1000));		
	} 
	printf("Tempo médio da execução da letra B em milisegundos: %lf\n", tempo/5);
    // Fim do exercício letra B.
    
        // Exercício letra C (inserir e remover 100.000.000 elementos com um array dinâmico com aumento de 3 e diminuição de 3)
    for(i = 0; i < 5; i++) {
    	free(tab);
    	tab = alocar_tabela();
	    t = clock();
	    for(i = 0; i < 100000000; i++) {
	    	adicionar(tab, 1, 1, 3);
		}
		
		for(i = 0; i < 100000000; i++) {
	    	remover(tab, 1, 3);
		}
		t = clock() - t;
		tempo += ((double)t)/((CLOCKS_PER_SEC/1000));	
	} 
	printf("Tempo médio da execução da letra C em milisegundos: %lf\n", tempo/5);
    // Fim do exercício letra C.
    
    return 0;
}

tabela * alocar_tabela() {
    tabela * tab;
    tab = (tabela *)malloc(sizeof(tabela));
    tab->elementos = 0;
    tab->tamanho = 0;
    tab->vetor = NULL;
    
    return tab;
}

long int * alocar_vetor(long int tamanho) {
    return (long int *)malloc(sizeof(long int) * tamanho);
}

void remover(tabela * tab, int isAlocar, int reducao) {
	// Caso o array esteja vazio
	if(tab->elementos == 0) {
		printf("Array vazio, não foi possível remover nada.");
	} else {
		tab->vetor[tab->elementos - 1] = 0;
		tab->elementos--;	
		
		long int divisao = tab->tamanho/4;
		long int * aux;
		if(tab->elementos == divisao && isAlocar == 1) {
			aux = alocar_vetor(tab->tamanho/reducao);
			aux = copiar_vetor(tab->vetor, aux, tab->elementos);
			free(tab->vetor);
			tab->vetor = aux;
			tab->tamanho = tab->tamanho/reducao;
		}
	}
	
	if(isAlocar == 1) {
	}
}

void adicionar(tabela * tab, long int numero, int isAlocar, int aumento) {
    // Caso o array esteja vazio
    if(tab->elementos == 0 && isAlocar == 1) {
        tab->vetor = alocar_vetor(1);
        tab->tamanho = 1;        
    }    
    
    // Caso o array esteja cheio
    long int * aux = NULL;
    if(tab->tamanho == tab->elementos) {
    	long int tamanho_vetor = tab->tamanho * aumento;
        aux = alocar_vetor(tamanho_vetor);
        aux = copiar_vetor(tab->vetor, aux, tab->elementos);
        free(tab->vetor);
        tab->vetor = aux;        
        tab->tamanho = tamanho_vetor;
    }
    
    tab->vetor[tab->elementos++] = numero; 
}

void mostra_vetor(long int * vet, long int tamanho) {
    int i;
    for(i=0; i < tamanho; i++) {
        printf(" %ld", vet[i]);
    }
}

long int * copiar_vetor(long int *vetor, long int *vetor2, long int tamanho) {
    int i;
    for(i = 0; i < tamanho; i++) {
        vetor2[i] = vetor[i];        
    }
    
    return vetor2;
}
