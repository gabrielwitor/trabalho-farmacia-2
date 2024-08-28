#include <stdio.h>

// Tipo que define o Medicamento.
typedef struct medicamento Medicamento;

// Tipo que define a Árvore.
typedef struct arvore Arvore;

/* Cria um novo medicamento */
Medicamento* CriaMedicamento(char* nome, int codigo, float valor, int* data_de_validade);

/* Cria uma árvore vazia. */
Arvore* CriaArvore();

/* Libera a árvore da memória */
Arvore* LiberaArvore();

/* Insere um medicamento pelo código na árvore. */
Arvore* InsereArvoreMedicamento(Arvore* arv, Medicamento* med, FILE* file_pointer);

/* Retira um medicamento de uma determinada árvore. */
Arvore* RetiraArvoreMedicamento(Arvore* arv, int id_medicamento, FILE* file_pointer);

/* Atualiza o preço de um medicamento na árvore */
Arvore* AtualizaArvoreMedicamento(Arvore* arv, int id_medicamento, float valor, FILE* file_pointer);

/* Busca um medicamento na árvore */
Arvore* BuscaArvoreMedicamento(Arvore* arv, int id_medicamento);

/* Verifica se um medicamento está presente em uma determinada árvore. */
int VerificaArvoreMedicamento(Arvore* arv, int id_medicamento);

/* Verifica se existe um medicamento vencido em uma determinada árvore. */
int VerificaArvoreValidade(Arvore* arv, int* data, FILE* file_pointer);

/* Imprime em ordem pelo codigo todos os medicamentos de uma árvore. */
void ImprimeArvoreMedicamento(Arvore* arv, FILE* file_pointer);