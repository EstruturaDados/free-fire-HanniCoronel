#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// ---------------------------------------------
// DEFINIÇÕES E ESTRUTURA PRINCIPAL
// ---------------------------------------------

#define MAX_ITENS 10 // Número máximo de itens na mochila

// Struct que representa um item no inventário
typedef struct {
    char nome[30];     // Nome do item (ex: Pistola, Kit Médico)
    char tipo[20];     // Tipo do item (ex: arma, munição, cura, ferramenta)
    int quantidade;    // Quantidade do item
} Item;

// Struct que representa a mochila (lista sequencial)
typedef struct {
    Item itens[MAX_ITENS]; // Vetor de até 10 itens
    int quantidade;        // Quantidade atual de itens cadastrados
} Mochila;


// ---------------------------------------------
// FUNÇÕES DE MANIPULAÇÃO DO INVENTÁRIO
// ---------------------------------------------

// Inicializa a mochila
void inicializarMochila(Mochila *mochila) {
    mochila->quantidade = 0;
    printf("Mochila inicializada. Pronta para coletar loot!\n");
}

// Cadastra um novo item na mochila
void inserirItem(Mochila *mochila) {
    if (mochila->quantidade == MAX_ITENS) {
        printf("Erro: a mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== CADASTRAR NOVO ITEM ===\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);  // Lê até o Enter
    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila->itens[mochila->quantidade] = novo;
    mochila->quantidade++;

    printf("Item \"%s\" adicionado com sucesso!\n", novo.nome);
}

// Remove um item pelo nome
void removerItem(Mochila *mochila) {
    if (mochila->quantidade == 0) {
        printf("A mochila esta vazia. Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== REMOVER ITEM ===\n");
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeBusca);

    int pos = -1;
    for (int i = 0; i < mochila->quantidade; i++) {
        if (strcmp(mochila->itens[i].nome, nomeBusca) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Erro: item \"%s\" nao encontrado na mochila.\n", nomeBusca);
        return;
    }

    // Move os itens seguintes uma posição para trás
    for (int i = pos; i < mochila->quantidade - 1; i++) {
        mochila->itens[i] = mochila->itens[i + 1];
    }

    mochila->quantidade--;
    printf("Item \"%s\" removido com sucesso!\n", nomeBusca);
}

// Lista todos os itens da mochila
void listarItens(const Mochila *mochila) {
    printf("\n=== ITENS NA MOCHILA ===\n");

    if (mochila->quantidade == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < mochila->quantidade; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila->itens[i].nome,
               mochila->itens[i].tipo,
               mochila->itens[i].quantidade);
    }
}

// Busca um item pelo nome
void buscarItem(const Mochila *mochila) {
    if (mochila->quantidade == 0) {
        printf("A mochila esta vazia. Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n=== BUSCAR ITEM ===\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < mochila->quantidade; i++) {
        if (strcmp(mochila->itens[i].nome, nomeBusca) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila->itens[i].nome,
                   mochila->itens[i].tipo,
                   mochila->itens[i].quantidade);
            return;
        }
    }

    printf("Item \"%s\" nao encontrado na mochila.\n", nomeBusca);
}


// ---------------------------------------------
// MENU PRINCIPAL
// ---------------------------------------------

void menu() {
    Mochila mochila;
    inicializarMochila(&mochila);

    int opcao;

    do {
        printf("\n==============================\n");
        printf("   SISTEMA DE INVENTARIO - JOGO\n");
        printf("==============================\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(&mochila);
                listarItens(&mochila);
                break;
            case 2:
                removerItem(&mochila);
                listarItens(&mochila);
                break;
            case 3:
                listarItens(&mochila);
                break;
            case 4:
                buscarItem(&mochila);
                break;
            case 0:
                printf("Saindo do inventario. Ate a proxima partida!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}


// ---------------------------------------------
// FUNÇÃO PRINCIPAL
// ---------------------------------------------

int main() {
    menu();
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
