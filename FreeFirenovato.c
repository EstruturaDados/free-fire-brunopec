#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char nome[30];     // nome do item
    char tipo[20];     // tipo do item
    int quantidade;    // quantidade do item
    struct No* proximo;
} No;

typedef No* Mochila;

// ===== PROTÓTIPOS =====
void layout(const char* texto, const Mochila lista);
void escolha();
void inicializaMochila(Mochila *lista);
void adicionarNaMochila(Mochila *lista);
void removerDaMochila(Mochila *lista, const char *item);
void listarMochila(const Mochila lista);
void liberarMochila(Mochila *lista);
int contarItensMochila(const Mochila lista);

// ===== PROGRAMA PRINCIPAL =====
int main() {
    Mochila lista;
    inicializaMochila(&lista);

    int opcao;
    char item[30];

    do {
        layout("MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA", lista);
        escolha();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarNaMochila(&lista);
                break;
            case 2:
                printf("Digite o nome do item a remover: ");
                scanf("%s", item);
                removerDaMochila(&lista, item);
                break;
            case 3:
                listarMochila(lista);
                break;
            case 0:
                printf("Saindo do programa...\n");
                liberarMochila(&lista);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

// ===== FUNÇÕES AUXILIARES =====
void layout(const char* texto, const Mochila lista){
    printf("==============================================\n");
    printf("    %s\n", texto);
    printf("==============================================\n");
    printf("Itens na mochila: %d/10 \n\n", contarItensMochila(lista));
    printf("1. Adicionar Itens\n");
    printf("2. Remover Itens\n");
    printf("3. Listar Itens\n");
    printf("0. Sair\n");
}

void escolha(){
    printf("\nEscolha uma opcao: ");
}

void inicializaMochila(Mochila *lista){
    *lista = NULL;
}
//-----Adicionando itens na mochila
void adicionarNaMochila(Mochila *lista){
    No* novoNo = (No*) malloc(sizeof(No));
    if(novoNo == NULL){
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    printf("--- Adicionar Itens ---\n");
    printf("Digite o item a ser adicionado: ");
    scanf("%s", novoNo->nome);

    printf("Tipo do item (arma, cura, etc): ");
    scanf("%s", novoNo->tipo);

    printf("Quantidade: ");
    scanf("%d", &novoNo->quantidade);

    novoNo->proximo = *lista; // insere no início
    *lista = novoNo;

    printf("\nItem '%s' adicionado com sucesso!\n", novoNo->nome);
}
//-----Listando itens na mochila
void listarMochila(const Mochila lista) {
    No* temp = lista;
    if(temp == NULL) {
        printf("\nMochila esta vazia!\n");
        return;
    }

    
    printf("\n--- ITENS DA MOCHILA (%d/10) ---\n");
    printf("-------------------------------------------\n");
    printf("NOME       | TIPO       | QUANTIDADE\n");
    printf("-------------------------------------------\n");
    while(temp != NULL) {
        printf("%s       | %s       | %d\n", temp->nome, temp->tipo, temp->quantidade);
        temp = temp->proximo;
    }
}



//-----Removendo itens da mochila
void removerDaMochila(Mochila *lista, const char *nome) {
    No *atual = *lista, *anterior = NULL;

    while(atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual == NULL) {
        printf("Erro: Item '%s' nao encontrado!\n", nome);
        return;
    }

    if(anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Item '%s' removido com sucesso!\n", nome);
}


//-----Liberando memória da mochila
void liberarMochila(Mochila *lista) {
    No *atual = *lista, *proximo;
    while(atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *lista = NULL;
}


//-----Contando itens na mochila
int contarItensMochila(const Mochila lista) {
    int contador = 0;
    No* temp = lista;
    while(temp != NULL) {
        contador++;
        temp = temp->proximo;
    }
    return contador;
}
