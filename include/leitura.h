#include <stdio.h>

/* Retorna um ponteiro *FILE "r" do arquivo a ser lido. */
FILE* abreArquivoLeitura(char* caminho);

/* Retorna um ponteiro *FILE "w" do arquivo a ser escrito. */
FILE* abreArquivoEscrita(char* caminho);

/* Retorna um valor inteiro que representa qual token foi lido.

-1 - Nenhuma palavra reconhecida
1 - MEDICAMENTO
2 - RETIRA
3 - IMPRIME_LISTA
4 - ATUALIZA_PRECO
5 - VERIFICA_VALIDADE
6 - VERIFICA_ARVORE
7 - FIM

*/
int ReconhecerPalavra(char* palavra);