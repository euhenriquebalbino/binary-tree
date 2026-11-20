#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó
typedef struct Node{
  int value;                 // Valor armazenado neste nó
  struct Node* left;         // Ponteiro para a subárvore com valores menores
  struct Node* right;        // Ponteiro para a subárvore com valores maiores
} Node;

// Criar um nó
Node* createNode(int value){
  // Reserva memória para um novo nó
  Node* new = malloc(sizeof(Node));

  // Se a alocação falhar, informa o erro e retorna NULL
  if (new == NULL){
    printf("Memory allocation failed.\n");
    return NULL;
  }

  // Define o valor do nó e inicia seus filhos como vazios
  new->value = value;
  new->left = NULL;
  new->right = NULL;

  // Retorna o endereço do nó criado
  return new;
}

// Inserir um nó na árvore
Node* insertNode(Node* root, int value) {
  // Verifica se a raiz é vazia. Se for, não existe árvore, cria o nó
  if (root == NULL){
    return createNode(value);
  }

  // Verifica se o valor do nó é maior ou menor que o valor da raiz
  if (value < root->value){
    // Se for menor, continua a busca pelo lugar correto à esquerda
    root->left = insertNode(root->left, value);
  } else if (value > root->value) {
    // Se for maior, continua a busca pelo lugar correto à direita
    root->right = insertNode(root->right, value);
  } else {
    // Valores repetidos não são inseridos nesta implementação
    printf("value %d already exists\n", value);
  }

  // Retorna a raiz para manter a ligação com esta parte da árvore
  return root;
}

// Buscar um nó na árvore
Node* searchNode(Node* root, int value) {
  // Chegar a um ponteiro vazio significa que o valor não foi encontrado
  if (root == NULL) {
    return NULL;
  }

  // Se o valor do nó atual for o procurado, retorna esse nó
  if (root->value == value) {
    return root;
  }

  // Compara com o nó atual para escolher qual subárvore consultar
  if (value < root->value) {
    return searchNode(root->left, value);
  }

  // Se não é menor nem igual, continua a busca à direita
  return searchNode(root->right, value);
}

// Percurso Em Ordem
void inOrderTraversal(Node* root){
  // Uma subárvore vazia não tem nós para visitar
  if (root != NULL) {
    // Esquerda, nó atual, direita: exibe os valores em ordem crescente
    inOrderTraversal(root->left);
    printf("%d ", root->value);
    inOrderTraversal(root->right);
  }
}

// Percurso Pré Ordem
void preOrderTraversal(Node* root) {
  if (root != NULL) {
    // Nó atual, esquerda, direita
    printf("%d ", root->value);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
  }
}

// Percurso Pós Ordem
void postOrderTraversal(Node* root) {
  if (root != NULL) {
    // Esquerda, direita, nó atual
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->value);
  }
}

int main() {
  // A árvore começa vazia; value guarda valores e option guarda a escolha do menu
  Node* root = NULL;
  int value;
  char option;

  // Repete o menu até que a opção de encerramento seja escolhida
  do {
    printf("\n\n1. Inserir valor\n");
    printf("2. Buscar valor\n");
    printf("3. Mostrar em ordem\n");
    printf("4. Mostrar pré ordem\n");
    printf("5. Mostrar pós ordem\n");
    printf("0. Encerrar programa\n");
    printf("Escolha a opção: ");

    // O espaço antes de %c ignora espaços e quebras de linha pendentes
    if (scanf(" %c", &option) != 1) {
      // Sai do laço se não for possível ler uma opção
      break;
    }

    // Executa a ação correspondente à opção digitada
    switch (option) {
    case '1':
      // Lê um valor e insere-o na árvore
      printf("\nDigite um valor para inserir: ");
      scanf("%d", &value);

      root = insertNode(root, value);
      printf("Valor %d inserido", value);
      break;

    case '2':
      // Lê um valor e informa se ele existe na árvore
      printf("\nDigite um valor para buscar: ");
      scanf("%d", &value);

      if (searchNode(root, value) != NULL) {
        printf("Valor %d encontrado na árvore", value);
      } else {
        printf("Valor %d não encontrado na árvore :C", value);
      }
      break;

    case '3':
      // Percorre e exibe os valores em ordem crescente
      printf("\nValores em ordem: ");
      inOrderTraversal(root);
      break;

    case '4':
      // Exibe cada nó antes de percorrer seus filhos
      printf("\nValores em pré-ordem: ");
      preOrderTraversal(root);
      break;

    case '5':
      // Exibe cada nó depois de percorrer seus filhos
      printf("\nValores em pós-ordem: ");
      postOrderTraversal(root);
      break;

    case '0':
      // A condição do laço encerra o menu após este case
      printf("\nEncerrando o programa...\n");
      break;

    default:
      // Qualquer entrada diferente das opções disponíveis é inválida
      printf("\nOpção inválida\n");
      break;
    }
  } while (option != '0');

  return 0;
}
