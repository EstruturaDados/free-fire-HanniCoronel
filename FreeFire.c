
  /*
  Plano de Fuga - Módulo de Organização de Componentes (Nivel Mestre)
  - Estruturas:
      Componente { nome[30], tipo[20], prioridade }
  - Operações:
      cadastro (até 20), remoção por nome, listagem formatada
      ordenações: bubbleSort por nome, insertionSort por tipo, selectionSort por prioridade
      busca binária por nome (após ordenar por nome)
      medição de comparações e tempo (clock())
  - Entrada de strings com fgets (segura) e tratamento de nova linha
  - Código modularizado e comentado
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define NOME_LEN 30
#define TIPO_LEN 20

typedef struct {
    char nome[NOME_LEN];
    char tipo[TIPO_LEN];
    int prioridade;
} Componente;

typedef struct {
    long comparacoes;
    double tempo_seg; // segundos
} ResultadoMedicao;

/* ---------- Funções utilitárias ---------- */

// Remove newline final de fgets
void trim_newline(char* s) {
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len - 1] == '\n') s[len - 1] = '\0';
}

// Mostra cabeçalho e componentes em formato tabular
void mostrarComponentes(Componente arr[], int n) {
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", n, MAX_COMPONENTES);
    printf("-----------------------------------------------------------------\n");
    printf("%-30s | %-15s | %-9s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-30s | %-15s | %-9d\n", arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("-----------------------------------------------------------------\n");
}

/* ---------- Ordenações e medições ---------- */

/*
  Bubble Sort por nome (alfabético).
  Retorna struct ResultadoMedicao com comparações e tempo gasto.
*/
ResultadoMedicao bubbleSortNome(Componente arr[], int n) {
    ResultadoMedicao res = {0, 0.0};
    clock_t start = clock();

    if (n <= 1) {
        res.tempo_seg = (double)(clock() - start) / CLOCKS_PER_SEC;
        return res;
    }

    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            res.comparacoes++;
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                Componente tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break; // otimização
    }

    res.tempo_seg = (double)(clock() - start) / CLOCKS_PER_SEC;
    return res;
}

/*
  Insertion Sort por tipo (string)
*/
ResultadoMedicao insertionSortTipo(Componente arr[], int n) {
    ResultadoMedicao res = {0, 0.0};
    clock_t start = clock();

    for (int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;

        // enquanto j >=0 e arr[j].tipo > chave.tipo
        while (j >= 0) {
            res.comparacoes++;
            if (strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }

    res.tempo_seg = (double)(clock() - start) / CLOCKS_PER_SEC;
    return res;
}

/*
  Selection Sort por prioridade (int) - ordena crescente (prioridade 1 = mais urgente)
*/
ResultadoMedicao selectionSortPrioridade(Componente arr[], int n) {
    ResultadoMedicao res = {0, 0.0};
    clock_t start = clock();

    for (int i = 0; i < n - 1; i++) {
        int idxMin = i;
        for (int j = i + 1; j < n; j++) {
            res.comparacoes++;
            if (arr[j].prioridade < arr[idxMin].prioridade) {
                idxMin = j;
            }
        }
        if (idxMin != i) {
            Componente tmp = arr[i];
            arr[i] = arr[idxMin];
            arr[idxMin] = tmp;
        }
    }

    res.tempo_seg = (double)(clock() - start) / CLOCKS_PER_SEC;
    return res;
}

/* ---------- Busca binária (após ordenação por nome) ---------- */

/*
  Busca binária por nome. Conta comparações em *comparacoes.
  Retorna índice se encontrado ou -1 se não encontrado.
*/
int buscaBinariaPorNome(Componente arr[], int n, const char nome_chave[], long* comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++;
        int cmp = strcmp(arr[meio].nome, nome_chave);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

/* ---------- Menu e operações CRUD ---------- */

// Adicionar componente (usa fgets para strings)
void adicionarComponente(Componente arr[], int* n) {
    if (*n >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido (%d).\n", MAX_COMPONENTES);
        return;
    }
    Componente c;
    printf("Digite o nome do componente: ");
    fgets(c.nome, NOME_LEN, stdin);
    trim_newline(c.nome);

    printf("Digite o tipo do componente: ");
    fgets(c.tipo, TIPO_LEN, stdin);
    trim_newline(c.tipo);

    printf("Digite a prioridade (1-10): ");
    while (scanf("%d", &c.prioridade) != 1 || c.prioridade < 1 || c.prioridade > 10) {
        printf("Entrada invalida. Digite prioridade entre 1 e 10: ");
        while (getchar() != '\n'); // limpa buffer
    }
    while (getchar() != '\n'); // limpa \n remanescente

    arr[*n] = c;
    (*n)++;
    printf("Componente \"%s\" adicionado.\n", c.nome);
}

// Remover por nome
void removerComponente(Componente arr[], int* n) {
    if (*n == 0) {
        printf("Nenhum componente para remover.\n");
        return;
    }
    char chave[NOME_LEN];
    printf("Digite o nome do componente a remover: ");
    fgets(chave, NOME_LEN, stdin);
    trim_newline(chave);

    int pos = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(arr[i].nome, chave) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Componente \"%s\" nao encontrado.\n", chave);
        return;
    }
    // desloca
    for (int i = pos; i < *n - 1; i++) arr[i] = arr[i + 1];
    (*n)--;
    printf("Componente \"%s\" removido.\n", chave);
}

/* ---------- Interface principal ---------- */

void menuPrincipal() {
    Componente componentes[MAX_COMPONENTES];
    int qtd = 0;
    int ordenadoPorNome = 0; // flag que indica se vetor atualmente está ordenado por nome

    while (1) {
        printf("\n===============================================\n");
        printf("  PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("===============================================\n");
        printf("Items na Mochila: %d/%d\n", qtd, MAX_COMPONENTES);
        printf("Status da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("\n1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Escolher Algoritmo)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome) [Requer ordenacao por nome]\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("-----------------------------------------------\n");
        printf("Escolha uma opcao: ");

        int opc = 0;
        if (scanf("%d", &opc) != 1) {
            // limpar buffer e repetir
            while (getchar() != '\n');
            printf("Opcao invalida.\n");
            continue;
        }
        while (getchar() != '\n'); // limpar \n

        if (opc == 0) {
            printf("Ativando torre de fuga... Ate a proxima.\n");
            break;
        }

        switch (opc) {
            case 1:
                adicionarComponente(componentes, &qtd);
                ordenadoPorNome = 0;
                break;
            case 2:
                removerComponente(componentes, &qtd);
                ordenadoPorNome = 0;
                break;
            case 3:
                mostrarComponentes(componentes, qtd);
                break;
            case 4: {
                if (qtd == 0) {
                    printf("Nenhum componente para ordenar.\n");
                    break;
                }
                printf("\nEscolha algoritmo de ordenacao:\n");
                printf("1. Bubble Sort (ordenar por NOME)\n");
                printf("2. Insertion Sort (ordenar por TIPO)\n");
                printf("3. Selection Sort (ordenar por PRIORIDADE)\n");
                printf("0. Cancelar\n");
                printf("Escolha: ");
                int alg = -1;
                if (scanf("%d", &alg) != 1) {
                    while (getchar() != '\n');
                    printf("Opcao invalida.\n");
                    break;
                }
                while (getchar() != '\n');

                if (alg == 0) break;

                ResultadoMedicao resultado;
                Componente copia[MAX_COMPONENTES];
                // trabalhar sobre copia para mostrar antes/depois comparativo opcional
                for (int i = 0; i < qtd; i++) copia[i] = componentes[i];

                if (alg == 1) {
                    printf("Executando Bubble Sort por NOME...\n");
                    resultado = bubbleSortNome(copia, qtd);
                    // aplicar ordenação ao vetor original
                    for (int i = 0; i < qtd; i++) componentes[i] = copia[i];
                    ordenadoPorNome = 1;
                    printf("Ordenacao por NOME concluida.\n");
                    printf("Comparacoes: %ld | Tempo: %.6f s\n", resultado.comparacoes, resultado.tempo_seg);
                } else if (alg == 2) {
                    printf("Executando Insertion Sort por TIPO...\n");
                    resultado = insertionSortTipo(copia, qtd);
                    for (int i = 0; i < qtd; i++) componentes[i] = copia[i];
                    ordenadoPorNome = 0;
                    printf("Ordenacao por TIPO concluida.\n");
                    printf("Comparacoes: %ld | Tempo: %.6f s\n", resultado.comparacoes, resultado.tempo_seg);
                } else if (alg == 3) {
                    printf("Executando Selection Sort por PRIORIDADE...\n");
                    resultado = selectionSortPrioridade(copia, qtd);
                    for (int i = 0; i < qtd; i++) componentes[i] = copia[i];
                    ordenadoPorNome = 0;
                    printf("Ordenacao por PRIORIDADE concluida.\n");
                    printf("Comparacoes: %ld | Tempo: %.6f s\n", resultado.comparacoes, resultado.tempo_seg);
                } else {
                    printf("Opcao invalida.\n");
                }

                // mostrar lista ordenada após a operacao
                mostrarComponentes(componentes, qtd);
                break;
            }
            case 5: {
                if (!ordenadoPorNome) {
                    printf("A busca binaria exige que a lista esteja ordenada por NOME.\n");
                    printf("Use a opcao 'Organizar Mochila' e escolha Bubble Sort por NOME.\n");
                    break;
                }
                if (qtd == 0) {
                    printf("Inventario vazio.\n");
                    break;
                }
                char chave[NOME_LEN];
                printf("Digite o nome do componente-chave a procurar: ");
                fgets(chave, NOME_LEN, stdin);
                trim_newline(chave);

                long comps = 0;
                clock_t t0 = clock();
                int idx = buscaBinariaPorNome(componentes, qtd, chave, &comps);
                double tempo = (double)(clock() - t0) / CLOCKS_PER_SEC;

                if (idx != -1) {
                    printf("Componente-CHAVE encontrado!\n");
                    printf("Posicao: %d\n", idx);
                    printf("Detalhes: ");
                    printf("%-30s | %-15s | %-9d\n", componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                } else {
                    printf("Componente-CHAVE \"%s\" nao encontrado.\n", chave);
                }
                printf("Comparacoes na busca binaria: %ld | Tempo: %.6f s\n", comps, tempo);
                break;
            }
            default:
                printf("Opcao invalida.\n");
        }
    }
}

int main(void) {
    // Executa o menu principal
    menuPrincipal();
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
