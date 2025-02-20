#include <stdio.h>

#define TAMANHO 10  // Tamanho do tabuleiro
#define NAVIO 3     // Representação dos navios
#define TAM_NAVIO 3 // Tamanho fixo dos navios
#define HABILIDADE 5 // Representação da área de efeito

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0; // Inicializa com água (0)
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int direcao) {
    if (direcao == 0) { // Horizontal
        if (coluna + TAM_NAVIO > TAMANHO) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0;
        }
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = NAVIO;
        }
    } else if (direcao == 1) { // Vertical
        if (linha + TAM_NAVIO > TAMANHO) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0;
        }
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    } else if (direcao == 2) { // Diagonal principal
        if (linha + TAM_NAVIO > TAMANHO || coluna + TAM_NAVIO > TAMANHO) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] != 0) return 0;
        }
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = NAVIO;
        }
    } else if (direcao == 3) { // Diagonal secundária
        if (linha + TAM_NAVIO > TAMANHO || coluna - TAM_NAVIO < -1) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna - i] != 0) return 0;
        }
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    }
    return 1;
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo) {
    int efeito[5][5] = {0};
    if (tipo == 0) { // Cone
        efeito[0][2] = 1;
        efeito[1][1] = efeito[1][2] = efeito[1][3] = 1;
        efeito[2][0] = efeito[2][1] = efeito[2][2] = efeito[2][3] = efeito[2][4] = 1;
    } else if (tipo == 1) { // Cruz
        efeito[0][2] = efeito[1][2] = efeito[2][0] = efeito[2][1] = efeito[2][2] = efeito[2][3] = efeito[2][4] = efeito[3][2] = efeito[4][2] = 1;
    } else if (tipo == 2) { // Octaedro
        efeito[0][2] = efeito[1][1] = efeito[1][3] = efeito[2][0] = efeito[2][1] = efeito[2][2] = efeito[2][3] = efeito[2][4] = efeito[3][1] = efeito[3][3] = efeito[4][2] = 1;
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int x = linha + i - 2;
            int y = coluna + j - 2;
            if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO && efeito[i][j] == 1) {
                tabuleiro[x][y] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);

    posicionarNavio(tabuleiro, 2, 3, 0);
    posicionarNavio(tabuleiro, 5, 6, 1);
    posicionarNavio(tabuleiro, 0, 0, 2);
    posicionarNavio(tabuleiro, 0, 9, 3);

    aplicarHabilidade(tabuleiro, 4, 4, 0);
    aplicarHabilidade(tabuleiro, 7, 7, 1);
    aplicarHabilidade(tabuleiro, 2, 2, 2);

    printf("Tabuleiro final:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
