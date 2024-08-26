#include "include/leitura.h"

#include <stdio.h>
#include <string.h>

FILE* abreArquivoLeitura(char* caminho){
    FILE * file_pointer;
    file_pointer = fopen(caminho,"r");

    if(file_pointer == NULL){
        printf("O arquivo \"%s\" não foi encontrado.\n",caminho);
        return NULL;
    }

    // Verifica se o arquivo está vazio.
    if(fgetc(file_pointer) == EOF){
        printf("O arquivo \"%s\" está vazio.\n",caminho);
        return NULL;
    }

    rewind(file_pointer);
    return file_pointer;
}

FILE* abreArquivoEscrita(char* caminho){
    FILE * file_pointer;
    file_pointer = fopen(caminho,"w");
    return file_pointer;
}


int ReconhecerPalavra(char* palavra){
    if(!strcmp(palavra,"MEDICAMENTO")){
        return 1;
    } else if(!strcmp(palavra,"RETIRA")){
        return 2;
    } else if(!strcmp(palavra,"IMPRIME_LISTA")){
        return 3;
    } else if(!strcmp(palavra,"ATUALIZA_PRECO")){
        return 4;
    } else if(!strcmp(palavra,"VERIFICA_VALIDADE")){
        return 5;
    } else if(!strcmp(palavra,"VERIFICA_ARVORE")){
        return 6;
    } else if(!strcmp(palavra,"FIM")){
        return 7;
    } 
    return -1;
}