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
        arv->dir = InsereArvoreMedicamento(arv->dir, med, file_pointer);
        
    return arv;
}

Arvore* RetiraArvoreMedicamento(Arvore* arv, int id_medicamento, FILE* file_pointer){

    if (arv == NULL){
        fprintf(file_pointer,"MEDICAMENTO NAO ENCONTRADO NA LISTA\n");
        return NULL;
    }

    else if(arv->m->codigo > id_medicamento){
        arv-> esq = RetiraArvoreMedicamento(arv->esq, id_medicamento, file_pointer);
    }

    else if(arv->m->codigo < id_medicamento){
        arv-> dir = RetiraArvoreMedicamento(arv->dir, id_medicamento, file_pointer);
    }

    else{ /* Nó a ser removido foi encontrado (arv->m->codigo == id_medicamento) */

        /* Nó a ser removido não possui filhos. */
        if(arv->esq == NULL && arv->dir == NULL){
            fprintf(file_pointer,"MEDICAMENTO %s %d RETIRADO\n",arv->m->nome, id_medicamento);
            free(arv->m);
            free(arv);
            return NULL;
        }

        /* Nó só tem filhos à direita. */
        else if(arv->esq == NULL){
            fprintf(file_pointer,"MEDICAMENTO %s %d RETIRADO\n",arv->m->nome, id_medicamento);
            Arvore* temp = arv;
            arv = arv->dir;
            free(temp->m);
            free(temp);
        }
 
        /* Nó só tem filhos à esquerda. */
        else if(arv->dir == NULL){
            fprintf(file_pointer,"MEDICAMENTO %s %d RETIRADO\n",arv->m->nome, id_medicamento);
            Arvore* temp = arv;
            arv = arv->esq;
            free(temp->m);
            free(temp);
        }

        /* Nó tem os dois filhos. */
        else{
            Arvore* filho = arv->esq;
            while(filho->dir != NULL){
                filho = filho->dir;
            }

            /* Trocando as informações. */
            Medicamento* med_temp = arv->m;
            arv->m = filho->m;
            filho->m = med_temp;

            arv->esq = RetiraArvoreMedicamento(arv->esq, id_medicamento, file_pointer);
        }
    }
    return arv;
}

Arvore* AtualizaArvoreMedicamento(Arvore* arv, int id_medicamento, float valor, FILE* file_pointer){

    Arvore* buscar = BuscaArvoreMedicamento(arv, id_medicamento);

    if(buscar == NULL)
        fprintf(file_pointer, "MEDICAMENTO %d ENCONTRADO NA ARVORE\n",id_medicamento);
    else{
        buscar->m->valor = valor;
        fprintf(file_pointer,"PRECO ATUALIZADO %s %d %.1f\n",arv->m->nome, id_medicamento, valor);
    }
        
    return arv;
}

Arvore* BuscaArvoreMedicamento(Arvore* arv, int id_medicamento){
    if(arv == NULL)
        return NULL;
    else if (arv->m->codigo > id_medicamento)
        return BuscaArvoreMedicamento(arv->esq, id_medicamento);
    else if(arv->m->codigo < id_medicamento)
        return BuscaArvoreMedicamento(arv->dir, id_medicamento);
    else /* arv->m->codigo == id_medicamento */
        return arv;
}

int VerificaArvoreMedicamento(Arvore* arv, int id_medicamento){
    if(arv == NULL)
        return 0; /* árvore vazia: não encontrou. */
    else
        return arv->m->codigo == id_medicamento || 
        VerificaArvoreMedicamento(arv->esq, id_medicamento) || 
        VerificaArvoreMedicamento(arv->dir, id_medicamento );
}

int VerificaArvoreValidade(Arvore* arv, int* data, FILE* file_pointer){
    int vencido = 0;

    if(arv != NULL){
        

        if(data[2] > arv->m->data[2]){ // Verificando o ano
            vencido = 1;
            
        } else if(data[2] >= arv->m->data[2] && data[1] > arv->m->data[1]){ // Verificando o mês
            vencido = 1;


        } else if(data[2] >= arv->m->data[2] && data[1] >= arv->m->data[1] && data[0] > arv->m->data[0]){ // Verificando o dia
            vencido = 1;

        }
        
        if(vencido) fprintf(file_pointer,"MEDICAMENTO %s %d VENCIDO\n",arv->m->nome, arv->m->codigo);
        return VerificaArvoreValidade(arv->esq, data, file_pointer) || VerificaArvoreValidade(arv->dir, data, file_pointer);
    }
    return vencido;
}

void ImprimeArvoreMedicamento(Arvore* arv, FILE* file_pointer){
    if(arv != NULL){
        ImprimeArvoreMedicamento(arv->esq, file_pointer);
        fprintf(file_pointer,"%s %d %.1f %d %d %d\n",arv->m->nome,arv->m->codigo,arv->m->valor,arv->m->data[0],arv->m->data[1],arv->m->data[2]);
        ImprimeArvoreMedicamento(arv->dir, file_pointer);
    }
}