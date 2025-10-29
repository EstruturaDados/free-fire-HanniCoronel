#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 100

//==============================
// ESTRUTURAS
//==============================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

//==============================
// VARIÁVEIS GLOBAIS
//==============================
Item mochilaVetor[MAX_ITENS];
int tamanhoVetor = 0;
No* inicioLista = NULL;
int contadorComparacoes = 0;

//==============================
// FUNÇÕES AUXILIARES
//==============================
void imprimirItem(Item i) {
    printf("Nome: %-15s | Tipo: %-10s | Qtd: %d\n", i.nome, i.tipo, i.quantidade);
}

//==============================
// OPERAÇÕES VETOR
//==============================
void inserirItemVetor() {
    if (tamanhoVetor >= MAX_ITENS) {
        printf("⚠️  Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    mochilaVetor[tamanhoVetor++] = novo;
    printf("✅ Item adicionado ao vetor!\n");
}

void removerItemVetor() {
    char nome[30];
    printf("Digite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < tamanhoVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < tamanhoVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            tamanhoVetor--;
            printf("🗑️  Item removido!\n");
            return;
        }
    }
    printf("❌ Item não encontrado.\n");
}

void listarItensVetor() {
    if (tamanhoVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("=== Itens da Mochila (Vetor) ===\n");
    for (int i = 0; i < tamanhoVetor; i++)
        imprimirItem(mochilaVetor[i]);
}

void ordenarVetor() {
    for (int i = 0; i < tamanhoVetor - 1; i++) {
        for (int j = 0; j < tamanhoVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("✅ Mochila ordenada por nome!\n");
}

int buscarSequencialVetor(char* nome) {
    contadorComparacoes = 0;
    for (int i = 0; i < tamanhoVetor; i++) {
        contadorComparacoes++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int buscarBinariaVetor(char* nome) {
    contadorComparacoes = 0;
    int inicio = 0, fim = tamanhoVetor - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        contadorComparacoes++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

//==============================
// OPERAÇÕES LISTA ENCADEADA
//==============================
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocação!\n");
        return;
    }
    printf("Nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = inicioLista;
    inicioLista = novo;
    printf("✅ Item adicionado à lista!\n");
}

void removerItemLista() {
    char nome[30];
    printf("Digite o nome do item para remover: ");
    scanf(" %[^\n]", nome);
    No *atual = inicioLista, *anterior = NULL;

    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("❌ Item não encontrado.\n");
        return;
    }

    if (!anterior)
        inicioLista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("🗑️  Item removido da lista!\n");
}

void listarItensLista() {
    if (!inicioLista) {
        printf("Mochila (lista) vazia.\n");
        return;
    }
    printf("=== Itens da Mochila (Lista Encadeada) ===\n");
    No* atual = inicioLista;
    while (atual) {
        imprimirItem(atual->dados);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(char* nome) {
    contadorComparacoes = 0;
    No* atual = inicioLista;
    while (atual) {
        contadorComparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

//==============================
// MENUS
//==============================
void menuVetor() {
    int opc;
    char nome[30];
    do {
        printf("\n===== MOCHILA COM VETOR =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar sequencial\n");
        printf("5. Ordenar\n");
        printf("6. Buscar binária\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4:
                printf("Nome do item: ");
                scanf(" %[^\n]", nome);
                {
                    clock_t inicio = clock();
                    int idx = buscarSequencialVetor(nome);
                    clock_t fim = clock();
                    if (idx != -1)
                        imprimirItem(mochilaVetor[idx]);
                    else
                        printf("Item não encontrado.\n");
                    printf("Comparações: %d | Tempo: %.5f s\n", contadorComparacoes, (double)(fim - inicio) / CLOCKS_PER_SEC);
                }
                break;
            case 5: ordenarVetor(); break;
            case 6:
                printf("Nome do item: ");
                scanf(" %[^\n]", nome);
                {
                    clock_t inicio = clock();
                    int idx = buscarBinariaVetor(nome);
                    clock_t fim = clock();
                    if (idx != -1)
                        imprimirItem(mochilaVetor[idx]);
                    else
                        printf("Item não encontrado.\n");
                    printf("Comparações: %d | Tempo: %.5f s\n", contadorComparacoes, (double)(fim - inicio) / CLOCKS_PER_SEC);
                }
                break;
        }
    } while (opc != 0);
}

void menuLista() {
    int opc;
    char nome[30];
    do {
        printf("\n===== MOCHILA COM LISTA =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar sequencial\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4:
                printf("Nome do item: ");
                scanf(" %[^\n]", nome);
                {
                    clock_t inicio = clock();
                    No* achado = buscarSequencialLista(nome);
                    clock_t fim = clock();
                    if (achado)
                        imprimirItem(achado->dados);
                    else
                        printf("Item não encontrado.\n");
                    printf("Comparações: %d | Tempo: %.5f s\n", contadorComparacoes, (double)(fim - inicio) / CLOCKS_PER_SEC);
                }
                break;
        }
    } while (opc != 0);
}

//==============================
// MAIN
//==============================
int main() {
    int opc;
    do {
        printf("\n========= FREE FIRE - SISTEMA DE MOCHILA =========\n");
        printf("1. Mochila com Vetor (Lista Sequencial)\n");
        printf("2. Mochila com Lista Encadeada (Dinâmica)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("Saindo do jogo... 🧨\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opc != 0);

    return 0;
}


// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.


// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
