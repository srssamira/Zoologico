#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

typedef struct {
  char nome[20];
  char codigo[10];
  char especie[20];
  float peso;
  float altura;
} info_animal;

// funçao p catalogar os setores
void catalogo(char ***nomes, int setores) {
  *nomes = (char **)malloc(setores * sizeof(char *));
  if (*nomes == NULL) {
    exit(1);
  }
  for (int i = 0; i < setores; i++) {
    (*nomes)[i] = (char *)malloc(10 * sizeof(char));
    if ((*nomes)[i] == NULL) {
      exit(1);
    }
    setbuf(stdin, NULL);
    printf("Digite o nome do setor %d: ", i + 1);
    scanf("%s", (*nomes)[i]);
  }
}

// funçao p inserir os animais em determinada jaula
void inserirAnimal(info_animal ***p, char ***nomes, int setores, int animais) {
  int jaula;
  char setor[10];

  printf("Digite o setor: ");
  scanf("%s", setor);
  setbuf(stdin, NULL);
  printf("Digite a jaula: ");
  scanf("%d", &jaula);
  setbuf(stdin, NULL);

  for (int i = 0; i < setores; i++) {
    // procura o setor comparando a variavel de busca c os nomes dos setores
    if (strcmp((*nomes)[i], setor) == 0) {
      for (int j = 0; j < animais; j++) {
        // procura espaço na jaula e adiciona o animal à estrutura dps
        if (p[i][jaula - 1][j].nome[0] == '0') { 
          printf("\nInformações do animal:\n");
          printf("Nome: ");
          scanf("%s", p[i][jaula - 1][j].nome);
          setbuf(stdin, NULL);
          printf("Codigo: ");
          scanf("%s", p[i][jaula - 1][j].codigo);
          setbuf(stdin, NULL);
          printf("Especie: ");
          scanf("%s", p[i][jaula - 1][j].especie);
          setbuf(stdin, NULL);
          printf("Peso: ");
          scanf("%f", &p[i][jaula - 1][j].peso);
          setbuf(stdin, NULL);
          printf("Altura: ");
          scanf("%f", &p[i][jaula - 1][j].altura);
          setbuf(stdin, NULL);
          break;
        } else if (j == animais) {
          printf("Não cabe mais animais");
        }
      }
      break;
    }
  }
}

// funçao p imprimir as informacoes dos animais em determinado setor
void imprime(info_animal ***p, int jaulas, int animais, int setores, char **nomes) {
  for (int j = 0; j < setores; j++) {
    printf("\nSetor %s: ", nomes[j]);
    for (int e = 0; e < jaulas; e++) {
      printf("\nJaula %d:", e + 1);
      for (int a = 0; a < animais; a++) {
        if (strcmp(p[j][e][a].nome, "A") != 0) {
          printf("\nNome: %s \n", p[j][e][a].nome);
          printf("Codigo: %s \n", p[j][e][a].codigo);
          printf("Espécie: %s \n", p[j][e][a].especie);
          printf("Peso: %f \n", p[j][e][a].peso);
          printf("Altura: %f \n", p[j][e][a].altura);
          printf("\n ----------------------------------- \n");
        }
      }
    }
  }
}

// funçao p iniciar a alocaçao de um setor
void iniciaSetor(info_animal ****p, int jaulas, int animais, int setor) {
  (*p)[setor] = (info_animal **)malloc(jaulas * sizeof(info_animal *));
  if ((*p)[setor] == NULL) {
    exit(1);
  }
  for (int j = 0; j < jaulas; j++) {
    (*p)[setor][j] = (info_animal *)malloc(animais * sizeof(info_animal));
    if ((*p)[setor][j] == NULL) {
      exit(1);
    }
    for (int a = 0; a < animais; a++) {
      (*p)[setor][j][a].nome[0] = '0'; // mudar para 0
    }
  }
}
void adiciona(info_animal ****p, int jaulas, int animais, int *setores, char ***nomes) {
  // adiciona nome do setor
  (*setores)++;
  (*nomes) = realloc((*nomes), (*setores) * sizeof(char *));

  (*nomes)[(*setores) - 1] = (char *)malloc(10 * sizeof(char));
  if ((*nomes)[(*setores) - 1] == NULL) {
    exit(1);
  }

  printf("Digite o nome do novo setor: \n");
  setbuf(stdin, NULL);
  scanf("%s", (*nomes)[(*setores) - 1]);

  (*p) = realloc((*p), ((*setores)) * sizeof(info_animal **));
  if ((*p) == NULL) {
    exit(1);
  }
  iniciaSetor(p, jaulas, animais, (*setores) - 1);
}

// funçao p liberar memoria
void retira(info_animal ****p, int jaulas, int animais, int *setores, char ***nomes) {
  char setor[10];
  printf("Digite o nome do setor: \n");
  setbuf(stdin, NULL);
  scanf("%s", setor);

  for (int i = 0; i < (*setores); i++) {
    if (strcmp((*nomes)[i], setor) == 0) {
      for (int j = i + 1; j < (*setores); j++) {
        strcpy((*nomes)[j - 1], (*nomes)[j]);
        for (int e = 0; e < jaulas; e++) {
          for (int a = 0; a < animais; a++) {
            (*p)[j - 1][e][a].altura = (*p)[j][e][a].altura;
            (*p)[j - 1][e][a].peso = (*p)[j][e][a].peso;
            strcpy((*p)[j - 1][e][a].codigo, (*p)[j][e][a].codigo);
            strcpy((*p)[j - 1][e][a].nome, (*p)[j][e][a].nome);
            strcpy((*p)[j - 1][e][a].especie, (*p)[j][e][a].especie);
          }
        }
      }
      break;
    }
  }
  (*setores)--;
  (*nomes) = realloc((*nomes), (*setores) * sizeof(char *));
  (*p) = realloc((*p), (*setores) * sizeof(info_animal **));
}

// funçao p encontrar o animal mais pesado de um dado setor
char *maisPesado(info_animal ***p, char **nomes, int setores, int animais, int jaulas) {
  char setor[10];
  setbuf(stdin, NULL);
  scanf("%s", setor);

  float pesoMaximo = 0;
  char *nomeMaisPesado = NULL;

  for (int i = 0; i < setores; i++) {
    if (strcmp(nomes[i], setor) == 0) {
      for (int j = 0; j < jaulas; j++) {
        for (int k = 0; k < animais; k++) {
          if (p[i][j][k].nome[0] != '0' && p[i][j][k].peso > pesoMaximo) {
            pesoMaximo = p[i][j][k].peso;
            nomeMaisPesado = p[i][j][k].nome;
          }
        }
      }
      break;
    }
  }

  if (nomeMaisPesado == NULL) {
    return "Não existe um animal neste setor.";
  }

  return nomeMaisPesado;
}

// funçao p calcular a media do peso OU da altura (usuario decide) dos animais de determinado setor
float calcularMedia(info_animal ***p, int setor, int jaulas, int animais, char **nomes, char *tipo) {
  float total = 0;
  int contador = 0;

  for (int i = 0; i < setor; i++) {
    for (int j = 0; j < jaulas; j++) {
      for (int k = 0; k < animais; k++) {
        // verifica se existe animal no setor
        if (p[i][j][k].nome[0] != '0') {
          if (strcmp(tipo, "peso") == 0) {
            total += p[i][j][k].peso;
          } else if (strcmp(tipo, "altura") == 0) {
            total += p[i][j][k].altura;
          }
          contador++;
        }
      }
    }
  }

  if (contador > 0) {
    return total / contador;
  } else {
    return 0;
  }
}

void inicializa(info_animal ****p, int jaulas, int animais, int setores) {
  //  inicializa(&setores, &jaulas, &animais);
  (*p) = (info_animal ***)malloc(setores * sizeof(info_animal **));

  if ((*p) == NULL) {
    exit(1);
  }
  for (int i = 0; i < setores; i++) {
    iniciaSetor(p, jaulas, animais, i);
  }
}

// funçao p chamar o menu

int menu(int init) {

/* tanto a opçao 1 quanto a opcao 2 tem q ser inicializadas obrigatoriamente antes do restante do codigo, 
por isso elas sao atribuídas como opções unicas p usuario inserir*/

  int opcao, status = 0;

  while (status == 0) {
    if (init == 0) {
      printf("\nDigite uma opção: \n\n");
      printf("1- Inicialização do sistema.\n");
      scanf("%d", &opcao);
      setbuf(stdin, NULL);
      if (opcao == 1) {
        return opcao;
      } else
        printf("Opção inválida!\n");
    } else if (init == 1) {
      printf("\nDigite uma opção:\n\n");
      printf("2 - Inserir catálogo de setores.\n");
      scanf("%d", &opcao);
      setbuf(stdin, NULL);
      if (opcao == 2) {
        return opcao;
      } else
        printf("Opção inválida!\n");
    } else {
      printf("\nDigite uma opção:\n\n");
      printf("3 - Inserir novo animal.\n");
      printf("4 - Imprimir informações.\n");
      printf("5 - Inserir novo setor.\n");
      printf("6 - Animai mais pesado.\n");
      printf("7 - Calcular média de peso ou altura.\n");
      printf("0 - Liberar memória.\n");
      scanf("%d", &opcao);
      setbuf(stdin, NULL);

      if (opcao == 3 || opcao == 4 || opcao == 5 || opcao == 6 || opcao == 7 || opcao == 0) {
        return opcao;
      } else
        printf("\nOpção inválida!");
    }
  }
}

int main() {

  setlocale(LC_ALL, "Portuguese"); // seta locale como portugues p imprimir acento e cedilha

  int setores, jaulas, animais, init = 0;
  info_animal ***p;
  char **nomes;
  int op;

  do {

    op = menu(init);

    switch (op){
      case 0:
        retira(&p, jaulas, animais, &setores, &nomes);
        break;

      case 1:
        printf("Digite o numero de setores: ");
        scanf("%d", &setores);
        printf("Digite o numero de jaulas: ");
        scanf("%d", &jaulas);
        printf("Digite o numero de animais: ");
        scanf("%d", &animais);

        inicializa(&p, jaulas, animais, setores);
        init++;
        break;

      case 2:
        catalogo(&nomes, setores);
        init++;
        break;

      case 3:
        inserirAnimal(p, &nomes, setores, animais);
        break;

      case 4:
        imprime(p, jaulas, animais, setores, nomes);
        break;

      case 5:
        adiciona(&p, jaulas, animais, &setores, &nomes);
        break;

      case 6:
        printf("\n%s\n", maisPesado(p, nomes, setores, animais, jaulas));
        break;

      case 7:
        {
          char tipo[10];
          printf("Digite o tipo (peso ou altura): ");
          scanf("%s", tipo);
          printf("\nMédia de %s dos animais: %f\n", tipo, calcularMedia(p, setores, jaulas, animais, nomes, tipo));
          break;
        }
    }
  } while (op != 0);

  return 0;
}