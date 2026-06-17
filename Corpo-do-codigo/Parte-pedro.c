#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Definição de constantes

#define MAX 8
#define MINAS_CURTO 2
#define MINAS_MEDIO 6
#define MINAS_LONGO 10

// Struct que representa cada célula do tabuleiro

typedef struct
{
    int temMina;
    int revelado;
    char dono;
} Celula;

// Variáveis globais do tabuleiro

Celula tabuleiro[MAX][MAX];
int tamanhoTabuleiro;
int totalMinas;

// Converte letra da coluna (ex: 'A') para índice da matriz

int letraParaIndice(char letra)
{
    return letra - 'A';
}

// Inicializa o tabuleiro: zera todas as células e distribui as minas aleatoriamente

void inicializarTabuleiro(int tamanho, int minas)
{
    tamanhoTabuleiro = tamanho;
    totalMinas = minas;

    // Preenche todo o tabuleiro zerado
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            tabuleiro[i][j].temMina = 0;
            tabuleiro[i][j].revelado = 0;
            tabuleiro[i][j].dono = ' ';
        }
    }

    // Distribui as minas de forma aleatória
    int colocadas = 0;
    while (colocadas < minas)
    {
        int i = rand() % tamanho;
        int j = rand() % tamanho;
        if (tabuleiro[i][j].temMina == 0)
        {
            tabuleiro[i][j].temMina = 1;
            colocadas++;
        }
    }
}

// Exibe o tabuleiro no terminal (modo debug)

void mostrarTabuleiroDebug()
{
    printf("   ");
    for (int j = 0; j < tamanhoTabuleiro; j++)
    {
        printf(" %c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < tamanhoTabuleiro; i++)
    {
        printf(" %d ", i + 1);
        for (int j = 0; j < tamanhoTabuleiro; j++)
        {
            if (tabuleiro[i][j].revelado)
            {
                if (tabuleiro[i][j].temMina)
                    printf(" * ");
                else
                    printf(" %c ", tabuleiro[i][j].dono);
            }
            else
            {
                printf(" # ");
            }
        }
        printf("\n");
    }
}

// Revela uma célula do tabuleiro
// Retorna:  1 = mina encontrada | 0 = célula segura | -1 = fora do tabuleiro | -2 = já revelada

int revelarCelula(char jogador, char colunaLetra, int linha)
{
    // Converte a entrada do jogador para índices da matriz
    int i = linha - 1;
    int j = letraParaIndice(colunaLetra);

    // Valida se está dentro do tabuleiro
    if (i < 0 || i >= tamanhoTabuleiro || j < 0 || j >= tamanhoTabuleiro)
        return -1;

    // Verifica se a célula já foi revelada
    if (tabuleiro[i][j].revelado)
        return -2;

    // Revela a célula e marca o dono
    tabuleiro[i][j].revelado = 1;
    tabuleiro[i][j].dono = jogador;

    if (tabuleiro[i][j].temMina)
        return 1;
    else
        return 0;
}

// Resumo da etapa (Pedro):
// - Estrutura do tabuleiro e das células (struct Celula)
// - Inicialização e distribuição aleatória das minas
// - Visualização do tabuleiro no terminal (modo debug)
// - Lógica de revelação de células com validação de jogada
