#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Filtragem de dados
//Função que faz uma cópia de cada uma das listas iniciais (paises e cidades) ja organizadas
void make_copies (data_scan *head_country, data_scan *filtered_country, data_scan* head_cities, data_scan* filtered_city) {
  data_scan *new_node1 = NULL; //novo nó da nova lista de paises
  data_scan *new_node2=NULL; //novo nó da nova lista de cidades
  data_scan *aux = NULL; //nó que diz que elemento da lista original está a ser copiado
  data_scan *tmp = NULL;  //nó que diz em que elemento da lista cópia está para de seguida inserir um novo nó (já copiado) após este

  //cópia da lista dos países
  aux = head_country->next; //começa-se por dizer que o aux é o primeiro elemento logo a seguir à cabeça da lista original, já que esta é uma dummy head
  tmp = filtered_country->next; //começa-se a dizer que o tmp é a cabeça da lista cópia (pois é uma lista circular), pois esta é uma dummy head e queremos adicionar um novo nó após esta.

  while (aux != head_country) { // este ciclo tem que correr até ao fim da lista. Como a lista é circular, quando chegar ao fim irá ser dito que este aux passa a ser aux->next, ou seja, a cabeça da lista e queremos que o ciclo pare neste ponto
    new_node1 = (data_scan *)malloc(sizeof(data_scan)); //alocação de memória para o novo nó
    if(new_node1 == NULL) { //verificação se a alocação foi feita corretamente
      printf("Memory allocation error!");
      exit(EXIT_FAILURE);
    }

    new_node1->payload.pais = (char *)malloc((strlen(aux->payload.pais) + 1)*sizeof(char)); //alocação de memória para nome do pais na lista, consoante o comprimento da string deste
    if(new_node1->payload.pais == NULL) { //verificação se a alocação foi feita corretamente
      printf("Memory allocation error!");
      exit(EXIT_FAILURE);
    }

    //cópia dita do nó da lista original para o novo nó que irá ser adicionado na lsita cópia. Cada elemento da estrutura do novo nó da lista tem que ser igual ao elemento correspondente do nó aux
    new_node1->payload.dt.ano = aux->payload.dt.ano;
    new_node1->payload.dt.mes = aux->payload.dt.mes;
    new_node1->payload.dt.dia = aux->payload.dt.dia;
    new_node1->payload.temperatura = aux->payload.temperatura;
    new_node1->payload.incerteza = aux->payload.incerteza;
    strcpy(new_node1->payload.pais, aux->payload.pais);

    //inserção do novo nó na lista cópia
    new_node1->prev = tmp; //o apontador do elemento anterior ao novo nó será o ultimo elemento da lista cópia
    new_node1->next = filtered_country; //O apontador do novo nó para o elemento a seguir a este na lista será a cabeça da lista. Isto tem que acontecer pois a lista é circular
    tmp->next = new_node1; //O apontador do último nó lista cópia para o elemento seguinte da lista ficará a apontar para o novo nó
    filtered_country->prev = new_node1; //o apontador da cabeça da lista que diz qual o elemento que é anterior a este (o último elemento da lista) aponta para o novo nó. Isto tem que acontecer pois a lista é circular

    aux = aux->next; //o aux passa a ser o elemento seguinte da lista original para repetir o ciclo
    tmp = tmp->next; //o tmp passa a ser o elemento seguinte da lista copia, ou seja, o novo nó que foi inserido na lista neste mesmo ciclo
  }

  //cópia da lista dos países
  //o raciocínio é o mesmo, portanto é escusado explicação
  aux = head_cities->next;
  tmp = filtered_city->next;

  while (aux != head_cities) {
    new_node2 = (data_scan *)malloc(sizeof(data_scan));
    if(new_node2 == NULL) {
      printf("Memory allocation error!");
      exit(EXIT_FAILURE);
    }

    new_node2->payload.pais = (char *)malloc((strlen(aux->payload.pais) + 1)*sizeof(char));
    if(new_node2->payload.pais == NULL) {
      printf("Memory allocation error!");
      exit(EXIT_FAILURE);
    }

    new_node2->payload.cidade = (char *)malloc((strlen(aux->payload.cidade) + 1)*sizeof(char));
    if(new_node2->payload.cidade == NULL) {
      printf("Memory allocation error!");
      exit(EXIT_FAILURE);
    }

    new_node2->payload.dt.ano = aux->payload.dt.ano;
    new_node2->payload.dt.mes = aux->payload.dt.mes;
    new_node2->payload.dt.dia = aux->payload.dt.dia;
    new_node2->payload.temperatura = aux->payload.temperatura;
    new_node2->payload.incerteza = aux->payload.incerteza;
    new_node2->payload.lat.angle = aux->payload.lat.angle;
    new_node2->payload.longi.angle = aux->payload.longi.angle;
    strcpy(new_node2->payload.pais, aux->payload.pais);
    strcpy(new_node2->payload.cidade,aux->payload.cidade);
    new_node2->payload.lat.hemisferio = aux->payload.lat.hemisferio;
    new_node2->payload.longi.hemisferio = aux->payload.longi.hemisferio;

    new_node2->prev = tmp;
    new_node2->next = filtered_city;
    tmp->next = new_node2;
    filtered_city->prev = new_node2;

    aux = aux->next;
    tmp = tmp->next;
  }
}

void clear_crit (data_scan *head_country, data_scan *filtered_country, data_scan *head_cities, data_scan *filtered_city) {
  data_scan *aux = NULL;  //ponteiro auxiliar para percorrer a lista
  data_scan *tmp = NULL;

  aux = filtered_country->next; //vetor que percorre a lista comeca a seguir ao dummy head

  while (aux != filtered_country) { //enquanto o ponteiro nao percorre a lista toda
    aux->prev->next = aux->next;  //quebrar as ligacoes a partir de onde esta o aux
    aux->next->prev = aux->prev;  //ligando a dummy head ao no a seguir ao do auxiliar
    tmp = aux;    //apontar o temporario para onde esta o auxiliar para poder libertar a memoria posteriormente
    aux = aux->next;  //passar o aux para o no seguinte
    free(tmp->payload.pais);  //desalocar memoria para a cidade
    free(tmp);  //efetivamente removendo as ligacoes do temp e libertando a memoria
  }

  if (aux == filtered_country) {  //finalmente,apos a lista toda ser percorrida e so faltar a cabeca
    free(aux->payload.pais);
    free(aux->payload.cidade);
    free(aux);  //libertar a cabeça
  }

  filtered_country = create_dummy();  //criar uma nova cabeca caso seja necessario uma nova lista

  aux = filtered_city->next;  //o processo repete-se para a lista das cidades

  while (aux != filtered_city) {
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
    tmp = aux;
    aux = aux->next;
    free(tmp->payload.pais);
    free(tmp->payload.cidade);
    free(tmp);
  }

  if (aux == filtered_city) {
    free(aux->payload.pais);
    free(aux->payload.cidade);
    free(aux);
  }

  filtered_city = create_dummy();

  make_copies(head_country, filtered_country,head_cities,filtered_city);  //encher as dummy heads novamente para poderem ser filtradas
} //funcao para dar reset aos criterios //limpa os criterios previamente escolhidos

void interval_analysis (data_scan *filtered_country, data_scan *filtered_city) {
  int ano = 0, mes = 0; //variaveis para guardar mes e ano
  data_scan *aux = NULL;  //ponteiro auxiliar para percorrer a lista

  printf("\nQual a data mínima que pretende?\n(por favor escreva o ano e o mês correspondentes no formato---> ano-mes)\n");
  scanf("%d-%d", &ano, &mes); //guardar o intervalo de tempo do utilizador

  while (mes > 12 || mes < 0) { //verificar se o mes e valido
    printf("\nMês inválido!\n\n");
    printf("\nQual a data mínima que pretende?\n(por favor escreva o ano e o mês correspondentes no formato---> ano-mes)\n");
    scanf("%d-%d", &ano, &mes); //voltar a pedir o intervalo de tempo caso nao seja
  }

  while (ano > filtered_country->prev->payload.dt.ano || ano > filtered_city->prev->payload.dt.ano) { //se o ano pedido for maior que o maior ano dos ficheiros
    printf("O maior ano encontrado foi: %d e %d.Escolha um ano menor que um dos dois.\n", filtered_country->prev->payload.dt.ano,filtered_city->prev->payload.dt.ano);
    printf("\nQual a data mínima que pretende?\n(por favor escreva o ano e o mês correspondentes no formato---> ano-mes)\n");
    scanf("%d-%d", &ano, &mes); //novamente caso o intervalo de tempo nao seja valido voltar a pedir
  }

  aux = filtered_country->next; //apontar o apontador auxiliar para a seguir a dummy head

  while (aux->payload.dt.ano < ano) { //enquanto o ano for menor que o inserido pelo utilizador
    aux = aux->next;  //mover o auxiliar para o proximo no
    free(aux->prev);  //apagar o no anterior,visto ter ano menor
    filtered_country->next = aux; //a cabeca fica a apontar para o no do aux
    aux->prev = filtered_country; //o no fica a apontar para a dummy head
  }

  while (aux->payload.dt.mes < mes && aux->payload.dt.ano == ano) { //tendo encontrado o ano pedido mas meses menores que o intervalo pedido
    aux = aux->next;  //repetir o processo de eliminacao de nos
    free(aux->prev);
    filtered_country->next = aux;
    aux->prev = filtered_country;
  }

  aux=filtered_city->next;  //repetir o processo mas agora para a lista de cidade

  while(aux != filtered_city)
  {
    while (aux->payload.dt.ano < ano) {
      aux = aux->next;
      free(aux->prev);
      filtered_city->next = aux;
      aux->prev = filtered_city;
    }

    while (aux->payload.dt.mes < mes && aux->payload.dt.ano == ano) {
      aux = aux->next;
      free(aux->prev);
      filtered_city->next = aux;
      aux->prev = filtered_city;
    }
    aux=aux->next;
  }
} //funcao para fazer filtragem por intervalo temporal

void month_analysis(data_scan *filtered_country, data_scan *filtered_city) {
  int mes1 = 0, mes2 = 0, elim = 0; //variavel para guardar ambos os meses do intervalo e uma flag se diz ser necessario apagar ou nao o no
  data_scan *aux = NULL;  //ponteiro auxiliar para percorrer a lista
  data_scan *tmp = NULL;  //ponteiro auxiliar para apagar nos

  printf("\nQual o intervalo de meses que pretende?\n(por favor escreva no formato---> mes1-mes2)\n");
  scanf("%d-%d", &mes1, &mes2); //guardar os meses do utilizador

  while (mes1 > 12 || mes2 > 12 || mes1 < 1 || mes2 < 1) {  //verificar se os meses sao validos
    printf("\nMês inválido!\n\n");
    printf("\nQual a data mínima que pretende?\n(por favor escreva o ano e o mês correspondentes no formato---> ano-mes)\n");
    scanf("%d-%d", &mes1, &mes2); //voltar a pedir os meses caso nao sejam
  }

  aux = filtered_country->next; //apontador a apontar para a seguir a dummy head

  while (aux != filtered_country) { //enquanto nao percorre a lista toda
    if (aux->payload.dt.mes < mes1 || aux->payload.dt.mes > mes2) { //se o no nao estiver dentro do intervalo de tempo
      aux->prev->next = aux->next;  //ligar p no anterior ao proximo no
      aux->next->prev = aux->prev;  //e remover as ligacoes a esse no
      tmp = aux;  //colocar o temporario no mesmo sitio que o aux
      elim = 1; //indicar que vai ser necessario apagar o no
    }
    aux = aux->next;  //mover o aux para o seguinte

    if (elim != 0) {  //se for necessario eliminar
      free(tmp);  //eliminar o no
      elim = 0; //voltar a fazer reset a flag
    }
  }

  aux=filtered_city->next;  //repetir o processo mas para a lista de cidades

  while (aux != filtered_city) {
    if (aux->payload.dt.mes < mes1 || aux->payload.dt.mes > mes2) {
      aux->prev->next = aux->next;
      aux->next->prev = aux->prev;
      tmp = aux;
      elim = 1;
    }
    aux = aux->next;

    if (elim != 0) {
      free(tmp);
      elim = 0;
    }
  }
} //funcao para fazer filtragem atraves de intervalo de meses

//funçao que realiza o free de qualquer lista criada
void free_alocated_list_country(data_scan* head)
{
  data_scan* aux=NULL;  //ponteiro para percorrer a lista
  data_scan* tmp=NULL;  //ponteiro para eliminar no

  aux=head->next; //comecar no primeiro no da lista

  while(aux!=head)  //libertar a memoria alocada para guardar o pais e o proprio no
  {
    tmp=aux;  //apontar para o no a ser apagado
    aux=aux->next;  //apontar para o proximo no para alterar as ligacoes da lista
    aux->prev=head; //refazer as ligacoes da lista sem o no a ser eliminado
    head->next=aux;
    free(tmp->payload.pais);  //libertar a memoria alocada para guardar o pais
    free(tmp);  //libertar a memoria alocada para o no
  }
  //quando finalmente so falta o dummy head da lista(qualquer dummy tem alocaçao para a cidade,sendo para pais ou nao)
  free(aux->payload.pais);
  free(aux->payload.cidade);
  free(aux);
}

void free_alocated_list_city(data_scan* head)
{
  data_scan* aux=NULL;  //ponteiro para percorrer a lista
  data_scan* tmp=NULL;  //ponteiro para eliminar no


  aux=head->next; //comecar no primeiro no da lista

  while(aux!=head)//libertar a memoria alocada para guardar o pais,a cidade e o proprio no
  {
    tmp=aux;  //apontar para o no a ser eliminado
    aux=aux->next;  //passar para o proximo no
    aux->prev=head; //eliminar as ligacoes da lista ao no
    head->next=aux;
    free(tmp->payload.pais);  //eliminar a memoria alocada para guardar o pais
    free(tmp->payload.cidade);  //eliminar a memoria alocada para guardar a cidade
    free(tmp);  //libertar a memoria alocada para o no
  }
  //quando finalmente so falta o dummy head da lista
  free(aux->payload.pais);
  free(aux->payload.cidade);
  free(aux);
}

//Histórico de Temperaturas
void global_history(data_scan *head_country, int time_frame) {  //funcao para obter as medias de temperatura globais ao longo de intervalos de tempo
  data_scan *aux = NULL;  //ponteiro auxiliar
  data_scan *temp=NULL; //ponteiro auxiliar
  int counter_avg = 0,year_start = 0,year_final=0;  //contador para a media;guarda o ano inicial;guarda o ano final;
  int first_cycle=1,begin=1,year_cycle=0; //indica se e o primeiro ciclo apos um print;inicio da funcao;guarda o ano que deve ser impresso(qual o programa esta a pensar)
  float avg = 0, max = 0, min = 0;  //guarda media;maximo;minimo
  int do_print=0,temporal_frame=0,fake_prints=0;  //flag para fazer print;quantidade de intervalos de tempo que tem que existir;flag para fazer prints indicando que nao tem informacao
  int temporal_frame_counter=0,page_counter=0; //conta quantos intervalos ja foram calculados;contador de linhas imprimidas por pagina

  aux = head_country->next;  //ponteiro que aponta para o elemento a seguir a dummy head(1 elemento efetivamente)
  temp= head_country->prev; //ponteiro que aponta para o elemento antes ao dummy head(ultimo elemento efetivamente)
  year_start = aux->payload.dt.ano; //ano inicial
  year_final= temp->payload.dt.ano; //ano final
  year_cycle=year_start;  //ano em que a funcao "pensa" comeca no ano inicial

  temporal_frame= (year_final-year_start)/(time_frame); //quantidade de intervalos de tempo que irao existir

  while (aux != head_country) //enquanto nao percorre a lista toda
  {
    if(begin==0)  //se nao for a primeira iteracao da funcao
    {
      check_new_cycle(aux,year_cycle,time_frame,&first_cycle,&do_print,&fake_prints); //verificar se estamos perante um novo intervalo de tempo
      if(do_print==1) //caso seja necessario imprimir
      {
        create_avg(&counter_avg,&avg);  //calcular a media
        make_print(&max,&min,&avg,&year_cycle,time_frame,&fake_prints,&temporal_frame_counter,&page_counter); //imprimir as informacoes ao utilizador
        do_print=0; //desligar a flag de print
        first_cycle=1;  //indicar que se trata do primeiro ciclo de um novo intervalo
      }
      check_max(aux,&max,first_cycle);  //verificar maximo
      check_min(aux,&min,first_cycle);  //verificar minimo
      check_avg(aux,&avg,first_cycle);  //somar para a media
      counter_avg++;  //incrementar contador da media
      first_cycle=0;  //desligar a flag de primeiro ciclo
    }
    if(begin==1)  //se for a primeira vez a ser corrida a funcao
    {
      max=aux->payload.temperatura; //maximo e igual a do primeiro no
      min=aux->payload.temperatura; //minimo e igual a do primeiro no
      avg=aux->payload.temperatura; //media e igual a do primeiro no
      begin=0;  //desliga a flag
      counter_avg++;  //incrementa o contador para a media
    }
    aux=aux->next;  //aponta para o proximo no
  }
  create_avg(&counter_avg,&avg);
  make_print(&max,&min,&avg,&year_cycle,time_frame,&fake_prints,&temporal_frame_counter,&page_counter); //no ultimo no,tem que voltar a imprimir para o ultimo intervalo de tempo
}

void country_history(data_scan *head_country, int time_frame) {  //funcao para obter as medias de temperatura por pais
  data_scan *aux = NULL;  //ponteiro auxiliar
  data_scan *temp=NULL; //ponteiro auxiliar
  int counter_avg = 0,year_start = 0,year_final=0;  //contador da media;guarda ano inicial;final
  int first_cycle=1,begin=1,year_cycle=0; //flag para primeiro ciclo de um novo intervalo;primeira iteracao da funcao para esse pais;ano em que a funcao"pensa"
  float avg = 0, max = 0, min = 0;  //guarda media;maximo;minimo
  int do_print=0,temporal_frame=0,fake_prints=0;  //flag para fazer print;quantidade de intervalos;flag para dar prints de nao ter informacao
  int temporal_frame_counter=0,pais_prev_true=0;  //contador da quantidade de intervalos;flag para indicar se nesse intervalo existe algum ano com o pais a analisar
  int page_counter=0; //contador de linhas imprimidas por pagina
  char pais_analise[COUNTRY_SIZE]={0};  //guarda o pais inserido pelo utilizador
  char aceitador=0; //opcao escolhida pelo utilizador

  aux = head_country->next; //ponteiro fica a apontar para o primeiro no
  temp= head_country->prev; //ponteiro fica a apontar para o ultimo no
  year_start = aux->payload.dt.ano; //guarda o ano inicial
  year_final= temp->payload.dt.ano; //guarda o ano final
  year_cycle=year_start;  //ano em que a funcao "pensa" e o ano inicial

  temporal_frame= (year_final-year_start)/(time_frame); //calcula a quantidade de intervalos que devem existir

  system("clear");  //limpa a consola
  printf("Qual é o país a analisar?\n");
  scanf("%s",pais_analise); //guarda o pais inserido pelo utilizador

  while (aux != head_country) //enquanto nao percorre a lista toda
  {
    if(begin==0)  //caso nao seja a primeira iteracao da funcao apos encontrar o pais
    {
      check_new_cycle(aux,year_cycle,time_frame,&first_cycle,&do_print,&fake_prints); //verificar se se encontra num novo intervalo de tempo
      if(do_print==1) //caso seja necessario imprimir
      {
        if(pais_prev_true==1) //caso um dos paises do intervalo seja o do utilizador
        {
          create_avg(&counter_avg,&avg);  //calcular a media
          make_print(&max,&min,&avg,&year_cycle,time_frame,&fake_prints,&temporal_frame_counter,&page_counter); //imprimir os valores ao utilizador
          do_print=0; //desligar a flag  de print
          first_cycle=1;  //indicar que se trata do primeiro ciclo de analise do pais apos um print
        }
        else if(pais_prev_true==0)  //caso nao exista nenhum pais igual ao do utilizador no intervalo
        {
          fake_prints++;  //adicionar 1 fake print(que e retirado na funcao check_new_cycle)
          while(fake_prints > 0)  //enquanto for necessario imprimir
          {
            if(page_counter==20)
            {
              aceitador=0;
              printf("\na:próxima página         q:sair\n\n");
              scanf("%c",&aceitador);
              while(aceitador!='a' && aceitador!='q')
              {
                scanf("%c",&aceitador);
              }
              if(aceitador=='q')
                exit(EXIT_SUCCESS);
              system("clear");
              page_counter=0;
            }
            printf("Não existem dados desde %d a %d.\n", year_cycle,(year_cycle + time_frame)); //indicar que nao tem informacao do pais nesse intervalo de tempo
            year_cycle=(year_cycle + time_frame); //atualizar o ano em que o programa "pensa" em intervalos de tempo
            fake_prints=fake_prints - 1;  //decrementar a quantidade de prints necessaria
            temporal_frame_counter=temporal_frame_counter + 1;  //incrementar o contador de intervalos existente
            do_print=0; //desligar a flag de print
            first_cycle=1;  //indicar que se trata do primeiro ciclo de analise do pais apos um print
            page_counter++; //indica a quantidade de linhas impressas por pagina
          }
        }
        pais_prev_true=0; //indicar que como se trata de um intervalo novo,nao existe nenhum pais igual ao do utilizador
      }

      if(strcmp(aux->payload.pais,pais_analise)==0) //se o pais do no for igual ao do utilizador,atualizar a media,maximo e minimo
      {
        check_max(aux,&max,first_cycle);  //verificar maximo
        check_min(aux,&min,first_cycle);  //verificar minimo
        check_avg(aux,&avg,first_cycle);  //verificar media
        counter_avg++;  //incrementar o contador de media
        first_cycle=0;  //desligar a flag de primeira iteracao do pais numintervalo novo
      }

      if(strcmp(aux->payload.pais,pais_analise)==0) //caso o intervalo tenha um pais igual ao do utilizador,ligar a flag
        pais_prev_true=1;
      else if(strcmp(aux->payload.pais,pais_analise)!=0 && pais_prev_true!=1) //caso ao longo do intervalo ainda nao exista um pais igual ao do utilizador,desligar a flag
        pais_prev_true=0;
    }

    if(begin==1 && strcmp(aux->payload.pais,pais_analise)==0) //caso seja a primeira iteracao da funcao a encontar o pais
    {
      max=aux->payload.temperatura; //maximo e igual ao desse pais
      min=aux->payload.temperatura; //minimo e igual ao desse pais
      avg=aux->payload.temperatura; //media e igual ao desse pais
      begin=0;  //desligar a flag de primeira iteracao
      counter_avg++;  //incrementar o contador da media
      pais_prev_true=1; //indicar que existe um pais igual ao do utilizador nesse intervalo temporal
    }
    else if(begin==1 && strcmp(aux->payload.pais,pais_analise)!=0)  //caso seja a primeira iteracao da funcao e o primeiro no nao seja o pais do utilizador
    {
      temp=aux; //temporario comeca no mesmo sitio que o auxiliar
      while(strcmp(temp->payload.pais,pais_analise)!=0) //enquanto o pais do temporario nao seja igual ao inserido pelo utilizador
      {
        temp=temp->next;  //mover o temporario para o no seguinte ate encontar um pais
        if(temp==head_country) //caso esse pais nao exista no ficheiro a analisar
        {
          printf("Nao existe esse pais na lista");
          exit(EXIT_SUCCESS);
        }
      }
      fake_prints= (temp->payload.dt.ano - aux->payload.dt.ano)/(time_frame); //a quantidade de prints sem inforamcao sera a quantidade de intervalos entre o pais inicial e o primeiro ano onde se regista o pais
      while(fake_prints > 0)  //enquanto for necessario imprimir
      {
        if(page_counter==20)
        {
          aceitador=0;
          printf("\na:próxima página         q:sair\n\n");
          scanf("%c",&aceitador);
          while(aceitador!='a' && aceitador!='q')
          {
            scanf("%c",&aceitador);
          }
          if(aceitador=='q')
            exit(EXIT_SUCCESS);
          system("clear");
          page_counter=0;
        }
        printf("Não existem dados desde %d a %d.\n", year_cycle,(year_cycle + time_frame)); //indicar que nao existe informacao durante esse intervalo temporal
        year_cycle=(year_cycle + time_frame); //atualizar o ano em que a funcao "pensa"
        fake_prints=fake_prints - 1;  //decrementar a quantidade de prints
        temporal_frame_counter=temporal_frame_counter + 1;  //atualizar o contador de intervalos analisados
        do_print=0; //desligar a flag de print
        page_counter++; //contador de linhas impressas
      }
      aux=temp->prev; //o auxiliar fica a apontar para o no anterior a primeira iteracao do pais pedido pelo utilizador visto que ira ser movido para a frente
    }

    aux=aux->next;  //apontar o aux para o proximo no
  }
  if(pais_prev_true==1) //caso exista um pais no ultimo intervalo dar print
  {
    create_avg(&counter_avg,&avg);
    make_print(&max,&min,&avg,&year_cycle,time_frame,&fake_prints,&temporal_frame_counter,&page_counter);
  }
  else if(pais_prev_true==0)  //caso nao exista indicar que nao existe informacao sobre o pais nesse intervalo de tempo
  {
    if(page_counter==20)
    {
      aceitador=0;
      printf("\na:próxima página         q:sair\n\n");
      scanf("%c",&aceitador);
      while(aceitador!='a' && aceitador!='q')
      {
        scanf("%c",&aceitador);
      }
      if(aceitador=='q')
        exit(EXIT_SUCCESS);
      system("clear");
      page_counter=0;
    }
    printf("Não existem dados desde %d a %d.\n", year_cycle,(year_cycle + time_frame));
  }

}

void city_history(data_scan* filtered_city, int time_frame)  /*funcao para obter as medias de temperatura por cidade */{
  data_scan *aux = NULL;  //ponteiro auxiliar
  data_scan *temp=NULL; //ponteiro auxiliar
  int counter_avg = 0,year_start = 0,year_final=0;  //contador da media;guarda ano inicial;final
  int first_cycle=1,begin=1,year_cycle=0; //flag para primeiro ciclo de um novo intervalo;primeira iteracao da funcao para essa cidade;ano em que a funcao"pensa"
  float avg = 0, max = 0, min = 0;  //guarda media;maximo;minimo
  int do_print=0,temporal_frame=0,fake_prints=0;  //flag para fazer print;quantidade de intervalos;flag para dar prints de nao ter informacao
  int temporal_frame_counter=0,cidade_prev_true=0;  //contador da quantidade de intervalos;flag para indicar se nesse intervalo existe algum ano com a cidade a analisar
  char cidade_analise[COUNTRY_SIZE]={0};  //guarda a cidade inserida pelo utilizador
  int page_counter=0; //contador de linhas impressas por pagina
  char aceitador=0; //opcao escolhida pelo utilizador

  aux = filtered_city->next;  //aponta para o primeiro elemento da lista
  temp= filtered_city->prev;  //aponta para o ultimo elemento da lista
  year_start = aux->payload.dt.ano; //ano inicial
  year_final= temp->payload.dt.ano; //ano final
  year_cycle=year_start;  //ano em que a funcao "pensa" comeca no inicial

  temporal_frame= (year_final-year_start)/(time_frame); //quantidade de intervalos que devem existir

  system("clear");  //limpa a consola
  printf("Qual é a cidade a analisar?\n");
  scanf("%s",cidade_analise); //guarda a cidade inserida pelo utilizador

  while (aux != filtered_city)  //percorre a lista toda
  {
    if(begin==0)  //caso nao seja a primeira iteracao da funcao
    {
      check_new_cycle(aux,year_cycle,time_frame,&first_cycle,&do_print,&fake_prints); //verificar se esta num novo intervalo de tempo
      if(do_print==1) //caso seja necesario imprimir
      {
        if(cidade_prev_true==1) //caso exista uma cidade no intervalo em analise
        {
          create_avg(&counter_avg,&avg);  //calcular media
          make_print(&max,&min,&avg,&year_cycle,time_frame,&fake_prints,&temporal_frame_counter,&page_counter); //imprimir
          do_print=0; //desligar a flag de print
          first_cycle=1;  //indicar que se trata de um novo intervalo em analise
        }
        else if(cidade_prev_true==0)  //caso nao exista nenhuma cidade no intervalo em analise
        {
          fake_prints++;  //aumentar em 1 o numero de prints sem informacao
          while(fake_prints > 0)  //enquanto for necessario fazer prints
          {
            if(page_counter==20)
            {
              aceitador=0;
              printf("\na:próxima página         q:sair\n\n");
              scanf("%c",&aceitador);
              while(aceitador!='a' && aceitador!='q')
              {
                scanf("%c",&aceitador);
              }
              if(aceitador=='q')
                exit(EXIT_SUCCESS);
              system("clear");
              page_counter=0;
            }
            printf("Não existem dados desde %d a %d.\n", year_cycle,(year_cycle + time_frame)); //imprimir a dizer que nao tem informacao da cidade nesse intervalo de tempo
            year_cycle=(year_cycle + time_frame); //atualizar o ano em que a funcao "pensa" em intervalos de tempo
            fake_prints=fake_prints - 1;  //decrementar a quantidade de prints sem informacao
            temporal_frame_counter=temporal_frame_counter + 1;  //incrementar o contador de intervalos temporais analisados
            do_print=0; //desligar a flag de print
            first_cycle=1;  //indicar que se trata de um novo intervalo de tempo em analise
            page_counter++; //indicar quantas linhas estao impressas
          }
        }
        cidade_prev_true=0; //indicar que como se esta num novo intervalo temporal de analise,ainda nao existe nenhuma cidade nesse intervalo
      }

      if(strcmp(aux->payload.cidade,cidade_analise)==0) //caso o no contenha a cidade pedida pelo utilizador
      {
        check_max(aux,&max,first_cycle);  //verificar maximo
        check_min(aux,&min,first_cycle);  //verificar minimo
        check_avg(aux,&avg,first_cycle);  //verificar average
        counter_avg++;  //incrementar contador da media
        first_cycle=0;  //indicar que ja foi encontrada a primeira cidade nesse intervalo
      }

      if(strcmp(aux->payload.cidade,cidade_analise)==0) //caso exista uma cidade nesse intervalo de tempo
        cidade_prev_true=1;
      else if(strcmp(aux->payload.cidade,cidade_analise)!=0 && cidade_prev_true!=1) //caso ainda nao tenha sido encontrada uma cidade nesse intervalo de tempo
        cidade_prev_true=0;
    }

    if(begin==1 && strcmp(aux->payload.cidade,cidade_analise)==0) //caso seja a primeira iteracao da funcao e encontre a cidade
    {
      max=aux->payload.temperatura; //maximo e o da cidade
      min=aux->payload.temperatura; //minimo e o da cidade
      avg=aux->payload.temperatura; //media e o da cidade
      begin=0;  //desligar a flag da primeira iteracao
      counter_avg++;  //incrementar o contador da media
      cidade_prev_true=1; //indicar que exite uma cidade no intervalo de tempo em analise
    }
    else if(begin==1 && strcmp(aux->payload.cidade,cidade_analise)!=0)  //caso seja a primeira iteracao da funcao e a cidade nao esteja no primeiro no
    {
      temp=aux; //comecar o temporario no mesmo sitio que o auxiliar
      while(strcmp(temp->payload.cidade,cidade_analise)!=0) //enquanto a cidade nao seja encontrada num no
      {
        temp=temp->next;  //avancar o temporario para o proximo no
        if(temp==filtered_city)  //caso percorra a lista toda e nunca encontre a cidade
        {
          printf("Nao existe essa cidade na lista");
          exit(EXIT_SUCCESS); //sair do programa
        }
      }
      fake_prints= (temp->payload.dt.ano - aux->payload.dt.ano)/(time_frame); //a quantidade de prints sem informacao sera a quantidade de intervalos entre o ano inicial e o ano do no com a primeira iteracao da cidade
      while(fake_prints > 0)  //enquanto for necessario imprimir
      {
        if(page_counter==20)
        {
          aceitador=0;
          printf("\na:próxima página         q:sair\n\n");
          scanf("%c",&aceitador);
          while(aceitador!='a' && aceitador!='q')
          {
            scanf("%c",&aceitador);
          }
          if(aceitador=='q')
            exit(EXIT_SUCCESS);
          system("clear");
          page_counter=0;
        }
        printf("Não existem dados desde %d a %d.\n", year_cycle,(year_cycle + time_frame)); //imprimir
        year_cycle=(year_cycle + time_frame); //atualizar o ano em que a funcao "pensa" em intervalos de tempo
        fake_prints=fake_prints - 1;  //decrementar a quantidade de prints
        temporal_frame_counter=temporal_frame_counter + 1;  //incrementar o contador de intevalos temporais analisados
        do_print=0; //desligar a flag de print
        page_counter++; //indicar quantas linhas estao impressas
      }
      aux=temp->prev; //passar o aux para o no anterior ao do temp pois este ira ser avancado
    }

    aux=aux->next;  //passar o aux para o proximo no
  }
  if(cidade_prev_true==1) //caso exista uma cidade no ultimo intervalo de analise,imprimir
  {
    create_avg(&counter_avg,&avg);
    make_print(&max,&min,&avg,&year_cycle,time_frame,&fake_prints,&temporal_frame_counter,&page_counter);
  }
  else if(cidade_prev_true==0)  //caso nao exista a cidade do utilizador no ultimo intervalos,imprimir a dizer que nao possui informacoes
  {
    if(page_counter==20)
    {
      aceitador=0;
      printf("\na:próxima página         q:sair\n\n");
      scanf("%c",&aceitador);
      while(aceitador!='a' && aceitador!='q')
      {
        scanf("%c",&aceitador);
      }
      if(aceitador=='q')
        exit(EXIT_SUCCESS);
      system("clear");
      page_counter=0;
    }
    printf("Não existem dados desde %d a %d.\n", year_cycle,(year_cycle + time_frame));
  }

}

void check_new_cycle(data_scan* _aux, int year_cycle, int time_frame, int *first_cycle, int *do_print, int *fake_prints) {
  if(*first_cycle==0) //caso nao seja o primeiro no de um novo intervalo
  {
    if((year_cycle + time_frame) <= _aux->payload.dt.ano) //caso o ano do no seja maior que o intervalo em analise
    {
      *do_print= 1; //ativar flag para proceder a impressao
      *fake_prints= (_aux->payload.dt.ano - year_cycle)/(time_frame) - 1; //imprimir a dizer que nao tem informacao entre os intervalos do ano em analise e o ano do no
    }
  }

  if(*first_cycle==1) //caso seja o primeiro no de um novo intervalo,repetir o processo mas desativar a flag de primeiro no de intervalo
  {
    if((year_cycle + time_frame) <= _aux->payload.dt.ano)
    {
      *do_print= 1;
      *first_cycle= 0;
      *fake_prints= (_aux->payload.dt.ano - year_cycle)/(time_frame) - 1;
    }
  }
}

void check_max (data_scan *_aux, float *max, int first_cycle) {
  if(first_cycle==1)  //caso seja o primeiro no desse intervalo temporal
  {
    *max=_aux->payload.temperatura; //comecar o maximo com o valor desse no
  }
  if (*max < _aux->payload.temperatura && first_cycle==0) { //caso nao seja,comparar com o valor guardado para saber qual a maior temperatura desse intervalo de tempo
    *max = _aux->payload.temperatura;
  }
}

void check_min(data_scan *_aux, float *min, int first_cycle) {
  if(first_cycle==1)  //caso seja o primeiro no desse intervalo de tempo
  {
    *min=_aux->payload.temperatura; //comecar o minimo com o valor da temperatura desse no
  }
  if (*min > _aux->payload.temperatura && first_cycle==0) { //caso nao seja,comparar com o valor trocado e ver qual o menor dos dois
    *min = _aux->payload.temperatura;
  }
}

void check_avg(data_scan *_aux, float *avg, int first_cycle) {
  if(first_cycle==1)  //caso seja o primeiro no de um novo intervalo,dar reset ao valor da media
  {
    *avg=0;
  }
  *avg = *avg + (_aux->payload.temperatura);  //adicionar a media o valor da temperatura
}

void create_avg(int *counter_avg, float *avg) {
  *avg=(*avg)/(float)(*counter_avg);  //dividir o valor da media pela quantidade de elementos que fazem parte dessa media
  *counter_avg=0; //colocar o contador de elementos a 0 para um novo intervalo
}

void make_print(float *max, float *min, float *avg, int *year_cycle, int time_frame, int *fake_prints, int *temporal_frame_counter,int *page_counter) {
  char aceitador=0; //opcao escolhida pelo utilizador
  //imprimir os valores de maximo,minimo e media do ultimo intervalo em analise
  if(*page_counter==20)
  {
    printf("\na:próxima página         q:sair\n\n");
    scanf("%c",&aceitador);
    while(aceitador!='a' && aceitador!='q')
    {
      scanf("%c",&aceitador);
    }
    if(aceitador=='q')
      exit(EXIT_SUCCESS);
    system("clear");
    *page_counter=0;
  }
  printf("Temperaturas máxima, mínima e media de %d a %d: %f / %f / %f\n", *year_cycle, (*year_cycle + time_frame), *max, *min, *avg);
  *page_counter=*page_counter+1;
  if(*page_counter==20)
  {
    printf("\na:próxima página         q:sair\n\n");
    scanf("%c",&aceitador);
    while(aceitador!='a' && aceitador!='q')
    {
      scanf("%c",&aceitador);
    }
    if(aceitador=='q')
      exit(EXIT_SUCCESS);
    system("clear");
    *page_counter=0;
  }
  *year_cycle=(*year_cycle + time_frame); //atualizar o ano em que a funcao "pensa" em intervalo temporal
  *temporal_frame_counter= *temporal_frame_counter + 1; //incrementar o contador de intervalos analisados

  while(*fake_prints > 0) //enquanto existam intervalos que nao tem nenhum elemento para a sua analise
  {
    if(*page_counter==20)
    {
      printf("\na:próxima página         q:sair\n\n");
      scanf("%c",&aceitador);
      while(aceitador!='a' && aceitador!='q')
      {
        scanf("%c",&aceitador);
      }
      if(aceitador=='q')
        exit(EXIT_SUCCESS);
      system("clear");
      *page_counter=0;
    }
    printf("Não existem dados desde %d a %d.\n", *year_cycle,(*year_cycle + time_frame)); //imprimir dizendo que nao possui dados para efetuar calculos
    *year_cycle=(*year_cycle + time_frame); //atualizar o ano em que a funcao "pensa"
    *fake_prints=*fake_prints - 1;  //decrementar a quantidade de prints
    *temporal_frame_counter=*temporal_frame_counter + 1;  //incrementar o contador de intervalos analisados
    *page_counter=*page_counter+1;  //contador de linhas impressas
  }
  //apos analisar o intervalos,voltar a por os valores de maximo,minimo e avg a 0 para um novo intervalo
  *max=0;
  *min=0;
  *avg=0;
}
