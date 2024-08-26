#include "include/estoque.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct medicamento{
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};

struct arvore{
    Medicamento* m;
    Arvore* esq;
    Arvore* dir;
};

Medicamento* CriaMedicamento(char* nome, int codigo, float valor, int* data_de_validade){
    Medicamento* novo_med = (Medicamento *) malloc (sizeof(Medicamento));

    if(novo_med == NULL){
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    strcpy(novo_med->nome,nome);
    novo_med->codigo = codigo;
    novo_med->valor = valor;
    // Copiando data
    for(int i = 0; i < 3; i++){
        novo_med->data[i] = data_de_validade[i];
    }

    return novo_med;
}

Arvore* CriaArvore(){
    return NULL;
}

Arvore* LiberaArvore(Arvore* arv){
    if(arv != NULL){
        LiberaArvore(arv->esq); /* Libera a sub-árvore esquerda. */
        LiberaArvore(arv->dir); /* Libera a sub-árvore direita. */
        free(arv->m); /* Libera medicamento da raiz. */
        free(arv); /* Libera raiz. */
    }
    return NULL;
}

Arvore* InsereArvoreMedicamento(Arvore* arv, Medicamento* med, FILE* file_pointer){
    
    if(arv == NULL){
        arv = (Arvore*) malloc (sizeof(Arvore));
        arv->m = med;
        arv->esq = arv->dir = NULL;

        fprintf(file_pointer,"MEDICAMENTO %s %d ADICIONADO\n",med->nome,med->codigo);
    }

    else if (med->codigo < arv->m->codigo)
        arv->esq = InsereArvoreMedicamento(arv->esq, med, file_pointer);

    else if (med->codigo > arv->m->codigo)
        arv->esq = InsereArvoreMedicamento(arv->dir, med, file_pointer);
        
    return arv;
}