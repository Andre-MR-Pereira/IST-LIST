#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//função que lê os argumentos metidos pelo utilizador quando inicia o programa
void InitProg (int argc, char const *argv[], char _cntr[FILE1], char _cty[FILE2], int *_t) {
  int argument = 1; //variável que dita que argumento está a ler. É colocado a 1 porque o primeiro argumento (nome do executável) não é necessário ser lido

  if (argc != 6) { //se o número de argumentos for diferente de seis é verificado qual o erro quando se iniciou o programa na consola
    if (argc < 6) { //se o número de argumentos é menor do que seis
      printf("\nInsufficient arguments! Please specify all arguments.\nSpecify the 2 documents to read and the operating mode(-g or -t).\n\n");
      exit(EXIT_FAILURE);
    }else if (argc > 6) { // se o número de argumentos é maior do que seis
      printf("\nError!! Too many arguments.\n\n");
      exit(EXIT_FAILURE);
    }
  }

  while (argument < argc) { //enquanto o argumento que está a ser lido é menor do que o número total de argumentos tem que se repetir este ciclo
    if (strcmp(argv[argument], "-f1") == 0) { //se for encontrado nos argumentos "-f1"
      strcpy(_cntr, argv[argument+1]); //o ficheiro a ser lido tem o nome do argumento a seguir a "-f1"
      if (strcmp(_cntr,"tempcountries.csv") != 0) { //se o argumento a seguir a "-f1" (com o nome ficheiro que o utilizador pretende ler) for diferente do esperado (tempcountries.csv)
        printf("Wrong order of arguments\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[argument], "-f2") == 0) { //se for encontrado nos argumentos "-f2"
      strcpy(_cty, argv[argument+1]); //o ficheiro a ser lido tem o nome do argumento a seguir a "-f2"
      if (strcmp(_cty,"tempcities.csv") != 0) { //se o argumento a seguir a "-f2" (com o nome ficheiro que o utilizador pretende ler) for diferente do esperado (tempcities.csv)
        printf("Wrong order of arguments\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[argument], "-t") == 0) { //se o utilizador pretende o modo textual
      *_t = 1;
    } else if (strcmp(argv[argument], "-g") == 0) { //se o utilizador pretende o modo gráfico
      *_t = 0;
    }
    argument++; //incrementa-se para seja lido o próximo argumento
  }
}
//função que lê os ficheiros e cria duas listas (paises e cidades) em que cada linha do ficheiro é um nó da lista e tambem cria duas listas cópia para não ser necessário ler os ficheiros outra vez, já que, no caso dos países, quando se insere de forma ordenada é demorado
void InitList(char _cntr[FILE1], char _cty[FILE2],int _t) {
  data_scan *head_country = NULL, *head_cities = NULL; //criação de cada head de cada lista

  //as heads são dummys
  head_cities = create_dummy();
  head_country = create_dummy();

  creat_cty_list(_cty, head_cities); //ler o ficheiro das cidades e colocá-lo numa lista circular duplamente ligada
  creat_countr_list(_cntr, head_country); //ler o ficheiro dos países e colocá-lo numa lista circular duplamente ligada de forma ordenada

  data_scan *filtered_country = create_dummy(); //a head da lista cópia dos países também é dummy
  data_scan *filtered_city = create_dummy(); //a head da lista cópia das cidades também é dummy

  make_copies(head_country, filtered_country, head_cities, filtered_city); //faz as cópias das duas listas originais
  //print_list(filtered_country);
  if(_t==1)
  {
    showInitMenu(head_country, filtered_country, head_cities, filtered_city); //é apresentado o menu incial
    //libertar todas as listas criadas
    free_alocated_list_country(head_country);
    free_alocated_list_country(filtered_country);
    free_alocated_list_city(head_cities);
    free_alocated_list_city(filtered_city);
  }
  else if(_t==0)
  {
    free_alocated_list_country(head_country); //estas 3 listas nao sao usadas
    free_alocated_list_country(filtered_country);
    free_alocated_list_city(filtered_city);
    graphic_mode(head_cities);
    free_alocated_list_city(head_cities);
  }

  printf("Passou\n");
}
//função que vê qual elemento (a ser inserido e o que já está na lista) é maior para que se insira na lista de forma ordenada
int checkBigger (data_scan *checker) {
  int soma = 0,ano=0,mes=0,dia=0;

  ano = checker->payload.dt.ano; //o ano do nó a verificar
  mes = checker->payload.dt.mes; //o mes do nó a verificar
  dia = checker->payload.dt.dia; //o dia do nó a verificar
  soma = (ano*10000) + (mes*100) + (dia); //desta maneira conseguimos ver qual a data maior (por exemplo 1922-11-18 ficará 19221118)

  return soma;
}

//funções remetentes à criação das listas
//função que cria uma dummy head
data_scan *create_dummy () {
  data_scan *new_node = NULL;

  new_node = (data_scan *)malloc(sizeof(data_scan)); //alocação de memória para a dummy head
  if (new_node == NULL) { //se a alocação falhar
  printf("Memory allocation error!\n");
  exit (-1);
  }

  new_node->payload.pais = (char *)malloc(6*sizeof(char)); //alocação de memória para o nome do país da head, que nest caso é "dummy" e portanto tem tamanho 6
  if (new_node->payload.pais== NULL) { //se a alocação falhar
      printf("Memory allocation error!\n");
      exit (-1);
  }

  new_node->payload.cidade = (char *)malloc(6*sizeof(char)); //alocação de memória para o nome da cidade da head, que nest caso é "dummy" e portanto tem tamanho 6
  if (new_node->payload.cidade== NULL) { //se a alocação falhar
      printf("Memory allocation error!\n");
      exit (-1);
  }

  //determinação do que é cada elemento da dummy head
  new_node->payload.dt.ano = 0;
  new_node->payload.dt.mes = 0;
  new_node->payload.dt.dia = 0;
  new_node->payload.temperatura = 0;
  new_node->payload.incerteza = 0;
  new_node->payload.lat.angle = 0;
  new_node->payload.lat.hemisferio = 'N';
  new_node->payload.longi.angle = 0;
  new_node->payload.longi.hemisferio = 'E';
  strcpy(new_node->payload.pais,"dummy");
  strcpy(new_node->payload.cidade,"dummy");
  new_node->next=new_node;
  new_node->prev=new_node;

  return new_node;
}


//função que insere um novo elemento na lista metendo os novos nós sempre atrás da cabeça (só é usado quando se lê o ficheiro das cidades pois já está organizado)
void insert_tail(data_scan *_tail, data_scan *new_node) {
    new_node->prev = _tail->prev; //o elemento anterior ao novo nó é o que era anterior à cabeça
    new_node->next = _tail; //o elemento a seguir ao novo nó é a cabeça
    _tail->prev->next = new_node; //o elemento a seguir ao anterior da cabeça passa a ser o novo nó
    _tail->prev = new_node; //o elemento anterior à cabeça passa a ser o novo nó
}
//função aqui deixada, mesmo sem ser utilizada no programa, para que o professor a avaliar possa imprimir a lista na ocorrência de algum erro
void print_list(data_scan *_head) {
  data_scan *aux = _head->next;

  while (aux != _head) {
    printf("%d-%d-%d,%f,%f,%s,%s,%.2f%c,%.2f%c\n", aux->payload.dt.ano, aux->payload.dt.mes, aux->payload.dt.dia, aux->payload.temperatura, aux->payload.incerteza, aux->payload.cidade, aux->payload.pais, aux->payload.lat.angle, aux->payload.lat.hemisferio, aux->payload.longi.angle, aux->payload.longi.hemisferio);
    aux = aux->next;
  }
}
//função qe insere um novo nó na lista dos países de forma ordenada
void insertionSort (data_scan* _head, data_scan* new_node) {
  data_scan *aux = NULL; //um nó auxiliar utilizado para fazer a comparação entre o nó que esta a ser inserido e cada nó da lista (o aux vai percorrendo a lista feita até ao momento)
  int soma_n = 0, soma_a = 0; //variáveis utilizadas para fazer a comparação entre o novo nó e a o aux respetivamente

  soma_n = checkBigger(new_node); //converte a data do novo nó para um número que possa ser distinguido e comparado como explicado anteriormente

  aux = _head->next; //o aux começa por ser o elemento logo a seguir à cabeça, pois esta é dummy
  soma_a = checkBigger(aux); //converte a data do aux para um número que possa ser distinguido e comparado como explicado anteriormente

  //este ciclo tem de se repetir enquanto a data do novo nó for maior que o elemento da lista a que está a ser comparado (o aux)
  //ou seja, quando a data do novo nó for menor do que o aux ele é inserido antes desse aux, ficando assim a lista ordenada por data
  //também é de reparar que quando o aux for igual à head (isto é uma lista circular) o ciclo tem que parar e mete o novo nó antes da head, e faz sentido porque se percorreu a lista toda quer dizer que o novo nó tem a maior data até ao momento
  while ( soma_n > soma_a && aux != _head )
  {
    aux = aux->next; //quando se confirma as condições do ciclo o aux é o próximo elemento da lista
    soma_a = checkBigger(aux); //é necessário converter a data do aux outra vez, pois este é diferente, para que se possa comparar
  }

  new_node->next = aux; //o elemento a seguir ao nó a ser inserido é o aux (como já se tinha dito)
  new_node->prev = aux->prev; //o ponteiro que aponta para o elemento anterior ao novo nó é o elemento anterior ao aux
  aux->prev->next = new_node; //o elemento a seguir ao anterior ao aux passa a ser o novo nó (em vez de ser o aux)
  aux->prev = new_node; //o elemento anterior ao aux passa a ser o novo nó
}

void creat_countr_list (char _cntr[FILE1], data_scan *head_country) { //cria a lista do ficheiro dos paises
  FILE *cntr_fl = NULL; //ponteiro para o ficheiro
  char string_buffer[STRING_SIZE]={0};  //vetor para guardar linhas do ficheiro
  data_scan *country = NULL;  //nos novos onde vao ser guardadas informacoes
  int invalid_sentence = 0;  //flag para indicar se a frase e valida ou nao
  int x = 0, ano = 0, mes = 0, dia = 0; //caracter a ler;guarda o ano;mes;dia
  float temp = 0, inc = 0;  //guarda temperatura;incerteza
  char *token = NULL; //guarda o nome do pais

  cntr_fl = fopen(_cntr, "r");  //abre o ficheiro dos paises
  if (cntr_fl == NULL) {  //caso o ficheiro nao seja encontrado
    printf("No such file found!2\n");
    exit(EXIT_FAILURE);
  }

  printf("A ler dados. Por favor aguarde...\n");
  while(fgets(string_buffer,STRING_SIZE,cntr_fl) != NULL) { //analisa o ficheiro inteiro,retirando frase a frase
    x = 0;  //inicializar o x a 0
    invalid_sentence=0; //desligar a flag da frase ser invalida

    while(x != 109) { //enquanto nao analisar os caracteres todos da frase
      if(string_buffer[x] == 44 && string_buffer[x+1] == 44) {  //caso encontre duas virgulas seguidas
        invalid_sentence = 1; //nao deve considerar a frase por faltar algum campo
      }
      x++;  //passar para o proximo caracter
    }

    if(invalid_sentence != 1) { //caso a frase seja valida

      country = (data_scan *)malloc(sizeof(data_scan)); //alocar memoria para o novo no
      if(country == NULL) { //caso nao seja possivel alocar memoria
        printf("Memory allocation error!");
        exit(EXIT_FAILURE);
      }

      ano = atoi(strtok(string_buffer, "-")); //retira da string e converte o ano para um inteiro
      country->payload.dt.ano = ano;

      mes = atoi(strtok(NULL, "-"));  //retira da string converte o mes para um inteiro
      country->payload.dt.mes = mes;

      dia = atoi(strtok(NULL, ","));  //retira da string e converte o dia para um inteiro
      country->payload.dt.dia = dia;

      temp = atof(strtok(NULL, ",")); //retira da string e converte em float
      country->payload.temperatura = temp;

      inc = atof(strtok(NULL, ","));  //retira da string e converte em float
      country->payload.incerteza = inc;

      token = strtok(NULL, "\r"); //retira da string o pais

      country->payload.pais = (char *)malloc((strlen(token) + 1)*sizeof(char)); //alocar memoria para gravar o nome do pais
      if(country->payload.pais == NULL) {
        printf("Memory allocation error!");
        exit(EXIT_FAILURE);
      }

      strcpy(country->payload.pais, token); //passa o pais para o no

      insertionSort(head_country, country);  //insere o no na lista
    }
  }
  fclose(cntr_fl);  //fechar o fichiero dos paises
}

void creat_cty_list (char _cty[FILE2], data_scan *head_cities) { //cria a lista do ficheiro das cidades
  FILE *cty_fl = NULL;  //ponteiro para a localizacao do ficheiro
  char string_buffer[STRING_SIZE] = {0};  //string para guardar a frase do ficheiro
  data_scan *city = NULL; //no que ira guardar a informacao
  int invalid_sentence = 0;  //flag para saber se a frase e invalidade
  int ano = 0, mes = 0, dia = 0, first = 1;  //guarda o ano;mes;dia;legenda para ser ignorada
  float temp = 0, inc = 0, lat_angle = 0, longi_angle = 0;  //guarda temperatura;incerteza;latitude;longitude
  char *cidade = NULL, *pais = NULL, *lat = NULL, *longi = NULL;  //guarda a cidade;pais;latitude;longitude
  char lat_hemis = '0', longi_hemis ='0';

  cty_fl = fopen(_cty, "r");  //abre o ficheiro das cidades
  if (cty_fl == NULL) { //caso nao encontre o ficheiro
    printf("No such file found!\n");
    exit(EXIT_FAILURE);
  }

  printf("A ler dados. Por favor aguarde...\n");
  while(fgets(string_buffer,STRING_SIZE,cty_fl) != NULL) {  //analisa o ficheiro inteiro retirando frase a frase
    invalid_sentence=0; //da reset a flag da frase ser invalida
    if (first == 1) { //ignora a primeira linha
      first = 0;
    } else if (first == 0) {  //para qualquer outra linha do ficheiro

      ano = atoi(MyStrtok(string_buffer, "-")); //retira o ano da string
      mes = atoi(MyStrtok(NULL, "-"));  //retira o mes da string
      dia = atoi(MyStrtok(NULL, ","));  //retira o dia da string
      temp = atof(MyStrtok(NULL, ",")); //retira a temperatura da string
      inc = atof(MyStrtok(NULL, ","));  //retira a incerteza da string
      cidade = MyStrtok(NULL, ","); //reitra a cidade da string
      pais = MyStrtok(NULL, ","); //retira o pais da string
      lat = MyStrtok(NULL, ",");  //retira a latitude da string
      sscanf(lat, "%f%c", &lat_angle, &lat_hemis);  //separa da lat o angulo e o hemisferio
      longi = MyStrtok(NULL, "\r"); //retira da string a longitude
      sscanf(longi, "%f%c", &longi_angle, &longi_hemis);  //retira da longitude o angulo e o hemisferio

      if (temp == 0.000 || ano == 0 || mes == 0 || dia == 0) {  //caso algum deles seja 0,a frase e invalida
        invalid_sentence = 1;
      }

      if (invalid_sentence != 1) {  //caso a frase seja valida

        city = (data_scan *)malloc(sizeof(data_scan));  //aloca memoria para o no
        if(city == NULL) {  //caso nao seja possivel
          printf("Memory allocation error!");
          exit(EXIT_FAILURE);
        }

        city->payload.pais = (char *)malloc((strlen(pais) + 1)*sizeof(char)); //aloca memoria para guardar o pais
        if(city->payload.pais == NULL) {  //caso nao seja possivel
          printf("Memory allocation error!");
          exit(EXIT_FAILURE);
        }

        city->payload.cidade = (char *)malloc((strlen(cidade) + 1)*sizeof(char)); //aloca memoria para guardar a cidade
        if(city->payload.pais == NULL) {  //caso nao seja possivel
          printf("Memory allocation error!");
          exit(EXIT_FAILURE);
        }

        city->payload.dt.ano = ano; //guarda o ano no no
        city->payload.dt.mes = mes; //guarda o mes no no
        city->payload.dt.dia = dia; //guarda o dia no no
        city->payload.temperatura = temp; //guarda a temperatura no no
        city->payload.incerteza = inc;  //guarda a incerteza no no
        city->payload.lat.angle = lat_angle;  //guarda a latitude no no
        city->payload.longi.angle = longi_angle;  //guarda a longitude no no

        strcpy(city->payload.pais, pais); //guarda o pais no no
        strcpy(city->payload.cidade, cidade); //guarda a cidade no no
        city->payload.lat.hemisferio = lat_hemis; //guarda a latitude no no
        city->payload.longi.hemisferio = longi_hemis; //guarda a longitude no no

        insert_tail(head_cities, city); //insere o no na lista
      }
    }
  }
  fclose(cty_fl); //fecha o ficheiro
}
//função semelhante ao strtok mas que agora nos diz quando falta algum elemento
char *MyStrtok (char * str, char const * delims) {
  static char  *src = NULL;
  char  *p = NULL,  *ret = NULL;

  if (str != NULL)
    src = str;

  if (src == NULL)
    return NULL;

  if ((p = strpbrk (src, delims)) != NULL) {
    *p = 0;
    ret = src;
    src = ++p;

  } else if (*src) {
    ret = src;
    src = NULL;
  }

  return ret;
}
