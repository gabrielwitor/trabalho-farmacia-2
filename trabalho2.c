#include <stdio.h>
#include <stdlib.h>

#include "include/estoque.h"
#include "include/leitura.h"

#define MAX_SIZE 255

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Quantidade de argumentos insuficiente.\nPara rodar o programa, utilize: ./trabalho {arquivoDeEntrada.txt} {arquivoDeSaida.txt}\n");
        return 0;
    }

    FILE* arquivo_leitura = abreArquivoLeitura(argv[1]);
    FILE* arquivo_escrita = abreArquivoEscrita(argv[2]);

    if(arquivo_leitura == NULL){
        printf("Houve um erro na leitura do arquivo \"%s\".\n",argv[1]);
        exit(1);
    }

    if(arquivo_escrita == NULL){
        printf("Houve um erro na criação do rquivo de escrita \"%s\".\n",argv[2]);
        exit(1);
    }

    // Árvore binária de busca.
    Arvore* arvore = CriaArvore();

    // Loop de leitura do arquivo.
    char palavra_lida[MAX_SIZE];

    // Informações do medicamento lido pelo arquivo.
    char nome[MAX_SIZE];
    int codigo;
    float valor;
    int data_de_validade[3];
    
    do{
        fscanf(arquivo_leitura,"%s",palavra_lida);
        printf("Palavra lida: %s\n",palavra_lida);

        switch (ReconhecerPalavra(palavra_lida)){
            
            case 1: // Leitura: MEDICAMENTO 
                fscanf(arquivo_leitura,"%s %d %f %d %d %d",nome, &codigo, &valor, &data_de_validade[0], &data_de_validade[1], &data_de_validade[2]);
                arvore = InsereArvoreMedicamento(arvore, CriaMedicamento(nome, codigo, valor, data_de_validade), arquivo_escrita);
                break;

            case 2: // Leitura: RETIRA
                fscanf(arquivo_leitura,"%d",&codigo);
                arvore = RetiraArvoreMedicamento(arvore, codigo, arquivo_escrita);
                break;

            case 3: // Leitura: IMPRIME_ARVORE
                ImprimeArvoreMedicamento(arvore,arquivo_escrita);
                break;

            case 4: // Leitura: ATUALIZA_PRECO
                fscanf(arquivo_leitura,"%d %f", &codigo, &valor);
                arvore = AtualizaArvoreMedicamento(arvore, codigo, valor, arquivo_escrita);
                break;

            case 5: // Leitura: VERIFICA_VALIDADE
                fscanf(arquivo_leitura,"%d %d %d", &data_de_validade[0], &data_de_validade[1], &data_de_validade[2]);
                VerificaArvoreValidade(arvore, data_de_validade, arquivo_escrita);
                break;

            case 6: // Leitura: VERIFICA_ARVORE
                fscanf(arquivo_leitura,"%d",&codigo);
                if(VerificaArvoreMedicamento(arvore, codigo))
                    fprintf(arquivo_escrita, "MEDICAMENTO %d ENCONTRADO NA ARVORE\n",codigo);
                else
                    fprintf(arquivo_escrita, "MEDICAMENTO %d NÃO ENCONTRADO NA ARVORE\n",codigo);
                break;

            case 7: // Leitura: QUEBRA_LINHA
                fprintf(arquivo_escrita, "\n");
                break;

            default:
                break;
        }

    } while (ReconhecerPalavra(palavra_lida) != 8);

    // Fechando os arquivos (necessário para salvar o texto).
    fclose(arquivo_leitura);
    fclose(arquivo_escrita);

    arvore = LiberaArvore(arvore);

    return 0;
}