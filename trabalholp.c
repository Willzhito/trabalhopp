#include <stdio.h>
#include <stdbool.h>

#define TAMANHO_HEAP 20

typedef struct {
    int inicio;
    int tamanho;
} AreaLivre;

int heap[TAMANHO_HEAP] = {0}; // Simulando a memória do heap
AreaLivre areasLivres[TAMANHO_HEAP]; // Lista de áreas livres
int totalAreasLivres = 1; // Inicialmente, toda a memória está livre

void inicializarHeap() {
    areasLivres[0].inicio = 0;
    areasLivres[0].tamanho = TAMANHO_HEAP;
}

void exibirHeap() {
    printf("Estado atual da memoria heap:\n");
    for (int i = 0; i < TAMANHO_HEAP; i++) {
        printf("[%d] ", heap[i]);
    }
    printf("\n");
}

void exibirAreasLivres() {
    printf("\nLista de areas livres:\n");
    for (int i = 0; i < totalAreasLivres; i++) {
        printf("Inicio: %d, Tamanho: %d\n", areasLivres[i].inicio, areasLivres[i].tamanho);
    }
    printf("\n");
}

void alocarMemoria(int tamanho, bool firstFit) {
    for (int i = 0; i < totalAreasLivres; i++) {
        if (areasLivres[i].tamanho >= tamanho) {
            printf("Alocando %d unidades na area iniciada em %d\n", tamanho, areasLivres[i].inicio);
            // Aloca memória no heap
            for (int j = 0; j < tamanho; j++) {
                heap[areasLivres[i].inicio + j] = 1;
            }
            // Atualiza a lista de áreas livres
            areasLivres[i].inicio += tamanho;
            areasLivres[i].tamanho -= tamanho;
            if (areasLivres[i].tamanho == 0) {
                for (int k = i; k < totalAreasLivres - 1; k++) {
                    areasLivres[k] = areasLivres[k + 1];
                }
                totalAreasLivres--;
            }
            return;
        }
        if (!firstFit) {
            break; // Best Fit verifica apenas a primeira área suficiente
        }
    }
    printf("Erro: Memoria insuficiente para alocar %d unidades!\n", tamanho);
}

void liberarMemoria(int inicio, int tamanho) {
    printf("Liberando %d unidades a partir da posicao %d\n", tamanho, inicio);
    for (int i = inicio; i < inicio + tamanho; i++) {
        heap[i] = 0;
    }
    // Adiciona a área liberada na lista de áreas livres
    areasLivres[totalAreasLivres].inicio = inicio;
    areasLivres[totalAreasLivres].tamanho = tamanho;
    totalAreasLivres++;
    // Organiza a lista de áreas livres
    for (int i = 0; i < totalAreasLivres - 1; i++) {
        for (int j = 0; j < totalAreasLivres - i - 1; j++) {
            if (areasLivres[j].inicio > areasLivres[j + 1].inicio) {
                AreaLivre temp = areasLivres[j];
                areasLivres[j] = areasLivres[j + 1];
                areasLivres[j + 1] = temp;
            }
        }
    }
}

void menu() {
    inicializarHeap();
    int opcao;

    do {
        printf("\n==============================Menu==============================\n");
        printf("Escolha uma opcao: \n");
        printf("1 - Alocar memoria (First Fit);\n");
        printf("2 - Alocar memoria (Best Fit);\n");
        printf("3 - Liberar memoria;\n");
        printf("4 - Exibir estado do heap;\n");
        printf("5 - Exibir areas livres;\n");
        printf("6 - Sair.\n");
        printf("================================================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int tamanho;
                printf("Digite o tamanho da memoria a ser alocada: ");
                scanf("%d", &tamanho);
                alocarMemoria(tamanho, true);
                break;
            }
            case 2: {
                int tamanho;
                printf("Digite o tamanho da memoria a ser alocada: ");
                scanf("%d", &tamanho);
                alocarMemoria(tamanho, false);
                break;
            }
            case 3: {
                int inicio, tamanho;
                printf("Digite a posicao inicial da memoria a ser liberada: ");
                scanf("%d", &inicio);
                printf("Digite o tamanho da memoria a ser liberada: ");
                scanf("%d", &tamanho);
                liberarMemoria(inicio, tamanho);
                break;
            }
            case 4:
                exibirHeap();
                break;
            case 5:
                exibirAreasLivres();
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);
}

int main() {
    menu();
    return 0;
}
