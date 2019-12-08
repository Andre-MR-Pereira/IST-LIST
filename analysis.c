#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//analise de anos
//funcao que analisa um ano no ficheiro de paises
void country_analysis(data_scan* filtered_country,int ano_analise,int quantity_select)
{
  data_scan* aux=0; //ponteiro para percorrer a lista
  float min[VECTOR_SIZE_ANALYSIS]={0},max[VECTOR_SIZE_ANALYSIS]={0},extreme[VECTOR_SIZE_ANALYSIS]={0};  //valores da temperatura registados:minimo;maximo;extremos
  int begin=1,mode=1;  //primeira iteracao do programa;modo 1 indica tratar-se da funcao de paises
  char* min_country[VECTOR_SIZE_ANALYSIS]={0}; //guarda os paises com a menor temperatura
  char* max_country[VECTOR_SIZE_ANALYSIS]={0}; //guarda os paises com a maior temperatura
  char* extreme_country[VECTOR_SIZE_ANALYSIS]={0};  //guarda os paises com as maiores diferenças de temperatura
  int quantity_counter_min=0,quantity_counter_max=0,quantity_counter_ext=0; //conta quantos paises estao guardados por funcao:min;,ax;extremos
  char country_analized[COUNTRY_SIZE]={0};  //vector que guarda o ultimo pais analisado

  aux=filtered_country->next; //comeca no primeiro elemento da lista

  while(aux->payload.dt.ano != ano_analise) //percorrer a lista toda ate encontrar o ano pedido
  {
    aux=aux->next;
    if(aux==filtered_country) //caso esse ano nao se encontre na lista
    {
      printf("Esse ano não se encontra no intervalo de analise.\n");
      exit(EXIT_SUCCESS);
    }
  }

  while(aux !=filtered_country) //percorrer a lista ate ao final do ano
  {
    if(aux->payload.dt.ano == ano_analise)  //somente quando encontra um no com o anp a ser analisado
    {
      if(begin==1)  //caso seja o primeiro no a ser analisado pela funcao
      { //e necessario guardar o pais para realizar a analise de extremos.Ao guardar o pais e somente correr a funcao quando encontra um pais novo,diminui-se a quantidade de vezes correr a funçao que calcula extremos que e uma funcao demorada
        strcpy(country_analized,aux->payload.pais); //guardar o pais anlisado para uma variavel
        check_extremes_analysis(aux,filtered_country,mode,extreme,extreme_country,&quantity_counter_ext,quantity_select); //calcular os extremos desse pais nesse ano
      }

      check_min_analysis(aux,begin,min,min_country,mode,&quantity_counter_min,quantity_select); //atualizar os valores minimos encontrados
      check_max_analysis(aux,begin,max,max_country,mode,&quantity_counter_max,quantity_select); //atualizar os valores maximos encontrados
      begin=0;  //desligar a flag que indica que e o primeiro pais encontrado e analisado

      if(strcmp(country_analized,aux->payload.pais)!=0) //caso o pais analisado seja diferente do anteriormente analisado
      {
        check_extremes_analysis(aux,filtered_country,mode,extreme,extreme_country,&quantity_counter_ext,quantity_select); //verifica os extremos do novo pais em analise nesse ano
        strcpy(country_analized,aux->payload.pais); //guarda o novo pais analisado
      }
    }
    aux=aux->next;   //analisa o proximo no da lista
  }
  print_results(min,min_country,max,max_country,extreme,extreme_country,quantity_counter_min,quantity_counter_max,quantity_counter_ext,quantity_select);  //imprime os resultados ao utilizador
}

//funcao que analisa um ano no ficheiro das cidades
void city_analysis(data_scan* filtered_city,int ano_analise,int quantity_select)
{
  data_scan* aux=0; //ponteiro para percorrer a lista
  float min[VECTOR_SIZE_ANALYSIS]={0},max[VECTOR_SIZE_ANALYSIS]={0};  //valores da temperatura registados:minimo;maximo;
  float extreme[VECTOR_SIZE_ANALYSIS]={0};  //guarda os valores de extremos
  int begin=1,mode=2;  //primeira iteracao do programa;modo 2 indica tratar-se da funcao de cidades
  char* min_city[VECTOR_SIZE_ANALYSIS]={0}; //guarda as cidades com a menor temperatura
  char* max_city[VECTOR_SIZE_ANALYSIS]={0}; //guarda as cidades com a maior temperatura
  char* extreme_city[VECTOR_SIZE_ANALYSIS]={0}; //guarda as cidades com maiores extremos de temperatura
  int quantity_counter_min=0,quantity_counter_max=0,quantity_counter_ext=0; //conta quantos países estao guardados por funcao:min;max;extremos
  char city_analized[COUNTRY_SIZE]={0}; //ultima cidade analizada

  aux=filtered_city->next; //comeca no primeiro elemento da lista
  while(aux->payload.dt.ano != ano_analise) //percorrer a lista toda ate encontrar o ano pedido
  {
    aux=aux->next;  //percorre a lista
    if(aux==filtered_city) //caso esse ano nao se encontre na lista
    {
      printf("Esse ano não se encontra no intervalo de analise.\n");
      exit(EXIT_SUCCESS);
    }
  }

  while(aux != filtered_city) //percorrer a lista ate ao final do ano
  {
    if(aux->payload.dt.ano == ano_analise)  //analisa somente os nos com o ano pedido de analise
    {
      if(begin==1)  //caso seja a primeira cidade encontrada desse ano na lista
      {
        strcpy(city_analized,aux->payload.cidade);  //guarda a primeira cidade analisada para uma variavel
        check_extremes_analysis(aux,filtered_city,mode,extreme,extreme_city,&quantity_counter_ext,quantity_select); //tal como na funcao country,pretende-se correr esta funçao o minimo de vezes possivel,correndo-a somente quando encontra uma nova cidade
      }

      check_min_analysis(aux,begin,min,min_city,mode,&quantity_counter_min,quantity_select);  //atualiza os valores de minimo encontrados
      check_max_analysis(aux,begin,max,max_city,mode,&quantity_counter_max,quantity_select);  //atualiza os valores de maximo encontrados
      begin=0;  //desliga a flag que indica que ja foi analisada pelo menos uma cidade

      if(strcmp(city_analized,aux->payload.cidade)!=0)  //caso seja analisada uma cidade nova
      {
        check_extremes_analysis(aux,filtered_city,mode,extreme,extreme_city,&quantity_counter_ext,quantity_select); //calcular os valores de extremo dessa cidade para o ano em analise
        strcpy(city_analized,aux->payload.cidade);  //guardar a ultima cidade analisada numa variavel
      }
    }
    aux=aux->next;  //analisar o proximo no da lista
  }
  print_results(min,min_city,max,max_city,extreme,extreme_city,quantity_counter_min,quantity_counter_max,quantity_counter_ext,quantity_select); //imprimir os resultados ao utilizador
}

//funcao que verifica o minimo do intervalo
void check_min_analysis(data_scan* aux,int _begin,float min[VECTOR_SIZE_ANALYSIS],char* min_country[VECTOR_SIZE_ANALYSIS],int mode,int *quantity_counter,int quantity_select)
{
  int i=0,j=0;  //utilizado em ciclos for
  int placed=0,position=0;  //indica se o pais ja foi guardado e se e necessario sobrepor informacao;indica onde esta guardado
  float switcher=0; //variavel usada para trocar as temperaturas do vetor
  char* name_switcher=0;  //variavel usada para trocar os ponteiros de frase de um vetor

  if(mode==1) //modo para os paises
  {
    if(_begin==1) //na primeira iteracao do intervalo,temos que comecar com o no inicial
    {
      min[0]=aux->payload.temperatura;  //minimo e o valor do no
      min_country[0]=aux->payload.pais; //guardar o pais juntamente com o minimo
      *quantity_counter=1;  //primeiro elemento a ser colocado na lista
    }

    if(_begin==0) //caso nao seja a primeira iteracao da funcao
    {
      for(i=0;i<(*quantity_counter);i++) //percorrer a lista existente
      {
        if(strcmp(aux->payload.pais,min_country[i])==0) //saber se esse pais ja foi analisado e se e um dos minimos
        {
          placed=1; //caso seja,ativar a flag de ja estar posicionado
          position=i; //guardar o lugar onde esta posicionado
        }
      }

      if((*quantity_counter)==quantity_select) //caso os vetores estejam totalmente preenchidos
      {
        if(placed==1 && min[position] > aux->payload.temperatura) //caso esse pais tenha sido previamente colocado e esta nova iteracao do pais tenha um minimo menor
        {
          min[position]=aux->payload.temperatura; //atualizar a temperatura minima desse pais
        }

        if(placed==0 && min[*quantity_counter-1] > aux->payload.temperatura)  //caso nao tenha sido colocado,e a temperatura minima seja maior que a minima guardada(o vetor esta ordenado por ordem decrescente de temperaturas),atualizar
        { //mudar o valor da temperatura e o pais
          min[*quantity_counter-1]=aux->payload.temperatura;
          min_country[*quantity_counter-1]=aux->payload.pais;
        }
      }

      else if((*quantity_counter) < quantity_select) //caso o vetor nao tenha sido totalmente preenchido antes
      {
        if(placed==1 && min[position] > aux->payload.temperatura) //caso o pais ja tenha sido colocado previamente e a ultima iteracao deste tenha um valor de temperatura menor
        { //atualizar a temperatura registada
          min[position]=aux->payload.temperatura;
        }

        else if(placed==0)  //caso o pais nao tenha sido colocado ainda,como existem espaços no vetor e so colocar
        {
          min[*quantity_counter]=aux->payload.temperatura;  //guardar a informacao do no sobre a temperatura
          min_country[*quantity_counter]=aux->payload.pais;  //guardar o pais juntamente com a temperatura
          *quantity_counter= *quantity_counter+1;  //indicar que foi colocado mais um elemento na lista
        }
      }
    }
    //no final de cada ciclo,organizar o vetor por ordem decrescente,de forma a facilitar o acesso e a impressao da informaçao
    for(i=0;i<(*quantity_counter);i++) //comecando no primeiro elemento e dai em diante
    {
      for(j=i+1;j<(*quantity_counter);j++) //olhando sempre para o elemento seguinte e comparando os dois
      {
        if(min[i]>min[j]) //caso a temperatura seja menor no elemento posterior da lista,trocar ambos os elementos
        {
          switcher=min[i];  //guardar um dos valores numa variavel e trocar os dois elementos
          min[i]=min[j];
          min[j]=switcher;

          name_switcher=min_country[i]; //guardar o ponteiro que aponta para o pais e trocar ambos os elementos
          min_country[i]=min_country[j];
          min_country[j]=name_switcher;
        }
      }
    }
  }

  if(mode==2) //modo para as cidades
  {
    if(_begin==1) //na primeira iteracao do intervalo,temos que comecar com o no inicial
    {
      min[0]=aux->payload.temperatura;  //minimo e o valor do no
      min_country[0]=aux->payload.cidade; //guardar o pais juntamente com o minimo
      *quantity_counter=1;  //primeiro elemento a ser colocado na lista
    }

    if(_begin==0) //caso nao seja a primeira iteracao da funcao
    {
      for(i=0;i<(*quantity_counter);i++) //percorrer a lista existente
      {
        if(strcmp(aux->payload.cidade,min_country[i])==0) //saber se esse pais ja foi analisado e se e um dos minimos
        {
          placed=1; //caso seja,ativar a flag de ja estar posicionado
          position=i; //guardar o lugar onde esta posicionado
        }
      }
      if((*quantity_counter)==quantity_select) //caso os vetores estejam totalmente preenchidos
      {
        if(placed==1 && min[position] > aux->payload.temperatura) //caso esse pais tenha sido previamente colocado e esta nova iteracao do pais tenha um minimo menor
        {
          min[position]=aux->payload.temperatura; //atualizar a temperatura minima desse pais
        }
        if(placed==0 && min[*quantity_counter - 1] > aux->payload.temperatura)  //caso nao tenha sido colocado,e a temperatura minima seja maior que a minima guardada(o vetor esta ordenado por ordem decrescente de temperaturas),atualizar
        { //mudar o valor da temperatura e o pais
          min[*quantity_counter-1]=aux->payload.temperatura;
          min_country[*quantity_counter-1]=aux->payload.cidade;
        }
      }

      else if((*quantity_counter) < quantity_select) //caso o vetor nao tenha sido totalmente preenchido antes
      {
        if(placed==1 && min[position] > aux->payload.temperatura) //caso o pais ja tenha sido colocado previamente e a ultima iteracao deste tenha um valor de temperatura menor
        { //atualizar a temperatura registada
          min[position]=aux->payload.temperatura;
        }

        else if(placed==0)  //caso o pais nao tenha sido colocado ainda,como existem espaços no vetor e so colocar
        {
          min[*quantity_counter]=aux->payload.temperatura;  //guardar a informacao do no sobre a temperatura
          min_country[*quantity_counter]=aux->payload.cidade;  //guardar o pais juntamente com a temperatura
          *quantity_counter= *quantity_counter+1;  //indicar que foi colocado mais um elemento na lista
        }
      }
    }
    //no final de cada ciclo,organizar o vetor por ordem decrescente,de forma a facilitar o acesso e a impressao da informaçao
    for(i=0;i<(*quantity_counter);i++) //comecando no primeiro elemento e dai em diante
    {
      for(j=i+1;j<(*quantity_counter);j++) //olhando sempre para o elemento seguinte e comparando os dois
      {
        if(min[i]>min[j]) //caso a temperatura seja menor no elemento posterior da lista,trocar ambos os elementos
        {
          switcher=min[i];  //guardar um dos valores numa variavel e trocar os dois elementos
          min[i]=min[j];
          min[j]=switcher;

          name_switcher=min_country[i]; //guardar o ponteiro que aponta para o pais e trocar ambos os elementos
          min_country[i]=min_country[j];
          min_country[j]=name_switcher;
        }
      }
    }
  }
}

//funcao que verifica o maximo do intervalo
void check_max_analysis(data_scan* aux,int _begin,float max[VECTOR_SIZE_ANALYSIS],char* max_country[VECTOR_SIZE_ANALYSIS],int mode,int *quantity_counter,int quantity_select)
{
  int i=0,j=0;  //utilizado em ciclos for
  int placed=0,position=0;  //indica se o pais ja foi guardado e se e necessario sobrepor informacao;indica onde esta guardado
  float switcher=0; //variavel usada para trocar as temperaturas do vetor
  char* name_switcher=0;  //variavel usada para trocar os ponteiros de frase de um vetor

  if(mode==1) //modo para os paises
  {
    if(_begin==1) //na primeira iteracao do intervalo,temos que comecar com o no inicial
    {
      max[0]=aux->payload.temperatura;  //maximo e o valor do no
      max_country[0]=aux->payload.pais; //guardar o pais juntamente com o maximo
      *quantity_counter=1;  //primeiro elemento a ser colocado na lista
    }

    if(_begin==0) //caso nao seja a primeira iteracao da funcao
    {
      for(i=0;i< (*quantity_counter);i++) //percorrer a lista existente
      {
        if(strcmp(aux->payload.pais,max_country[i])==0) //saber se esse pais ja foi analisado e se e um dos maximos
        {
          placed=1; //caso seja,ativar a flag de ja estar posicionado
          position=i; //guardar o lugar onde esta posicionado
        }
      }

      if((*quantity_counter)==quantity_select) //caso os vetores estejam totalmente preenchidos
      {
        if(placed==1 && max[position] < aux->payload.temperatura) //caso esse pais tenha sido previamente colocado e esta nova iteracao do pais tenha um maximo maior
        {
          max[position]=aux->payload.temperatura; //atualizar a temperatura maxima desse pais
        }

        if(placed==0 && max[0] < aux->payload.temperatura)  //caso nao tenha sido colocado,e a temperatura maxima seja menor que a minima guardada(o vetor esta ordenado por ordem crescente de temperaturas),atualizar
        { //mudar o valor da temperatura e o pais
          max[0]=aux->payload.temperatura;
          max_country[0]=aux->payload.pais;
        }
      }

      else if((*quantity_counter) < quantity_select) //caso o vetor nao tenha sido totalmente preenchido antes
      {
        if(placed==1 && max[position] < aux->payload.temperatura) //caso o pais ja tenha sido colocado previamente e a ultima iteracao deste tenha um valor de temperatura maior
        { //atualizar a temperatura registada
          max[position]=aux->payload.temperatura;
        }

        else if(placed==0)  //caso o pais nao tenha sido colocado ainda,como existem espaços no vetor e so colocar
        {
          max[*quantity_counter]=aux->payload.temperatura;  //guardar a informacao do no sobre a temperatura
          max_country[*quantity_counter]=aux->payload.pais;  //guardar o pais juntamente com a temperatura
          *quantity_counter= *quantity_counter+1;  //indicar que foi colocado mais um elemento na lista
        }
      }
    }
    //no final de cada ciclo,organizar o vetor por ordem crescente,de forma a facilitar o acesso e a impressao da informaçao
    for(i=0;i<(*quantity_counter);i++) //comecando no primeiro elemento e dai em diante
    {
      for(j=i+1;j<(*quantity_counter);j++) //olhando sempre para o elemento seguinte e comparando os dois
      {
        if(max[i]>max[j]) //caso a temperatura seja maior no elemento posterior da lista,trocar ambos os elementos
        {
          switcher=max[i];  //guardar um dos valores numa variavel e trocar os dois elementos
          max[i]=max[j];
          max[j]=switcher;

          name_switcher=max_country[i]; //guardar o ponteiro que aponta para o pais e trocar ambos os elementos
          max_country[i]=max_country[j];
          max_country[j]=name_switcher;
        }
      }
    }
  }

  if(mode==2) //modo para as cidades
  {
    if(_begin==1) //na primeira iteracao do intervalo,temos que comecar com o no inicial
    {
      max[0]=aux->payload.temperatura;  //maximo e o valor do no
      max_country[0]=aux->payload.cidade; //guardar a cidade juntamente com o maximo
      *quantity_counter=1;  //primeiro elemento a ser colocado na lista
    }

    if(_begin==0) //caso nao seja a primeira iteracao da funcao
    {
      for(i=0;i<(*quantity_counter);i++) //percorrer a lista existente
      {
        if(strcmp(aux->payload.cidade,max_country[i])==0) //saber se essa cidade ja foi analisado e se e um dos maximos
        {
          placed=1; //caso seja,ativar a flag de ja estar posicionada
          position=i; //guardar o lugar onde esta posicionada
        }
      }

      if((*quantity_counter)==quantity_select) //caso os vetores estejam totalmente preenchidos
      {
        if(placed==1 && max[position] < aux->payload.temperatura) //caso essa cidade tenha sido previamente colocada e esta nova iteracao da cidade tenha um maximo maior
        {
          max[position]=aux->payload.temperatura; //atualizar a temperatura maxima dessa cidade
        }

        if(placed==0 && max[0] < aux->payload.temperatura)  //caso nao tenha sido colocada,e a temperatura maxima seja menor que a minima guardada(o vetor esta ordenado por ordem crescente de temperaturas),atualizar
        { //mudar o valor da temperatura e a cidade
          max[0]=aux->payload.temperatura;
          max_country[0]=aux->payload.cidade;
        }
      }

      else if((*quantity_counter) < quantity_select) //caso o vetor nao tenha sido totalmente preenchido antes
      {
        if(placed==1 && max[position] < aux->payload.temperatura) //caso a cidade ja tenha sido colocada previamente e a ultima iteracao desta tenha um valor de temperatura maior
        { //atualizar a temperatura registada
          max[position]=aux->payload.temperatura;
        }

        else if(placed==0)  //caso a cidade nao tenha sido colocada ainda,como existem espaços no vetor e so colocar
        {
          max[*quantity_counter]=aux->payload.temperatura;  //guardar a informacao do no sobre a temperatura
          max_country[*quantity_counter]=aux->payload.cidade;  //guardar a cidade juntamente com a temperatura
          *quantity_counter= *quantity_counter+1;  //indicar que foi colocado mais um elemento na lista
        }
      }
    }
    //no final de cada ciclo,organizar o vetor por ordem crescente,de forma a facilitar o acesso e a impressao da informaçao
    for(i=0;i<(*quantity_counter);i++) //comecando no primeiro elemento e dai em diante
    {
      for(j=i+1;j<(*quantity_counter);j++) //olhando sempre para o elemento seguinte e comparando os dois
      {
        if(max[i]>max[j]) //caso a temperatura seja maior no elemento posterior da lista,trocar ambos os elementos
        {
          switcher=max[i];  //guardar um dos valores numa variavel e trocar os dois elementos
          max[i]=max[j];
          max[j]=switcher;

          name_switcher=max_country[i]; //guardar o ponteiro que aponta para a cidade e trocar ambos os elementos
          max_country[i]=max_country[j];
          max_country[j]=name_switcher;
        }
      }
    }
  }
}
//funcao que trata dos extremos do ano de cada pais

void check_extremes_analysis(data_scan* aux,data_scan* head,int mode,float extreme[VECTOR_SIZE_ANALYSIS],char* extreme_place[VECTOR_SIZE_ANALYSIS],int *quantity_counter_ext,int quantity_select)
{
  data_scan* temp=NULL; //ponteiro auxiliar para percorrer a lista
  float max=0,min=0,extremo=0;  //guarda os valores de maximo;mínimo;extremo
  int begin=1,placed=0;  //primeira iteracao da funcao;se ja existe um pais/cidade guardado igual
  float switcher=0; //usado para organizar o vetor de temperaturas
  char* name_switcher=NULL; //usado para organizar o vetor de nomes
  int i=0,j=0;  //para ciclos for

  if(mode==1) //caso seja o modo dos paises
  {
    temp=head->next;  //comecar no primeiro elemento da lista
    while(temp!=head) //percorrer a lista toda
    { //sempre que encontrar o pais a analisar,no ano a analisar:
      if(strcmp(temp->payload.pais,aux->payload.pais)==0 && temp->payload.dt.ano == aux->payload.dt.ano)
      {
        if(begin==0)  //caso nao seja a primeira iteracao da funcao
        { //comparar o maximo e o minimo desse pais em todos os meses
          if(temp->payload.temperatura > max) //se for maior que o maximo detetado,trocar
            max=temp->payload.temperatura;

          if(temp->payload.temperatura < min) //se for menor que o minimo detetado,trocar
            min=temp->payload.temperatura;
        }

        if(begin==1)  //caso seja a primeira iteracao da funcao
        { //guardar os valores detetados para comecar as comparacoes
          max=temp->payload.temperatura;
          min=temp->payload.temperatura;
          begin=0;
        }
      }
      temp=temp->next; //analisar o proximo no
    }
    extremo=(max-min);  //no final de percorrer a lista toda,calcular o extremo de temperaturas nesse ano

    for(i=0;i<(*quantity_counter_ext);i++)  //percorrer os extremos ja guardados
    {
      if(strcmp(extreme_place[i],aux->payload.pais)==0) //caso esse pais ja tenha sido analisado e seja um dos maiores extremos
      {
        placed=1; //basta indicar que ja foi analisado,e como em qualquer iteracao da funcao o valor do extremo ira dar sempre o mesmo,entao nao e necessario realizar alguma alteracao a esse extremo
      }
    }

    if(placed==0) //caso esse pais nao esteja colocado na lista de extremos
    {
      if((*quantity_counter_ext)==quantity_select && extremo > extreme[0])  //se nao existirem mais espacos livres e este possuir um extremo maior que um listado,adicionar aos vetores
      { //basta trocar com o primeiro pois os vetores irao estar organizador sempre por ordem crescente,logo o menor extremo sera sempre a primeira posiçao do vetor
        extreme[0]=extremo;
        extreme_place[0]=aux->payload.pais;
      }

      if((*quantity_counter_ext)<quantity_select) //caso ainda existam espaços livres para se colocar a listagem do extremos sem retirar outros
      { //colocar as informaçoes no espaço livre que existe e avançar a posiçao onde se guarda no vetor
        extreme[*quantity_counter_ext]=extremo;
        extreme_place[*quantity_counter_ext]=aux->payload.pais;
        *quantity_counter_ext=*quantity_counter_ext+1;
      }

    }

    for(i=0;i<(*quantity_counter_ext);i++)  //no final de cada iteracao da funcao,organizar o vetor dos extremos por ordem crescente
    {
      for(j=i+1;j<(*quantity_counter_ext);j++)
      {
        if(extreme[i] > extreme[j])
        { //troca os valores de temperatura caso os extremos nao estejam ordenados de forma crescente
          switcher=extreme[i];
          extreme[i]=extreme[j];
          extreme[j]=switcher;
          //troca os nomes juntamente com as temperaturas
          name_switcher=extreme_place[i];
          extreme_place[i]=extreme_place[j];
          extreme_place[j]=name_switcher;
        }
      }
    }
  }

  if(mode==2) //caso seja o modo das cidades,repetir o processo inteiro supracitado mas em vez de guardar paises guarda-se cidades
  {
    temp=head->next;
    while(temp!=head)
    {
      if(strcmp(temp->payload.cidade,aux->payload.cidade)==0 && temp->payload.dt.ano == aux->payload.dt.ano)
      {
        if(begin==0)
        {
          if(temp->payload.temperatura > max)
            max=temp->payload.temperatura;

          if(temp->payload.temperatura < min)
            min=temp->payload.temperatura;
        }

        if(begin==1)
        {
          max=temp->payload.temperatura;
          min=temp->payload.temperatura;
          begin=0;
        }
      }
      temp=temp->next;
    }

    extremo=(max-min);  //calculo do extremo dessa cidade

    for(i=0;i<(*quantity_counter_ext);i++)
    {
      if(strcmp(extreme_place[i],aux->payload.cidade)==0)
      {
        placed=1;
      }
    }

    if(placed==0)
    {
      if((*quantity_counter_ext)==quantity_select && extremo > extreme[0])
      {
        extreme[0]=extremo;
        extreme_place[0]=aux->payload.cidade;
      }

      if((*quantity_counter_ext)<quantity_select)
      {
        extreme[*quantity_counter_ext]=extremo;
        extreme_place[*quantity_counter_ext]=aux->payload.cidade;
        *quantity_counter_ext=*quantity_counter_ext+1;
      }

    }

    for(i=0;i<(*quantity_counter_ext);i++)  //organizar o vetor por ordem crescente
    {
      for(j=i+1;j<(*quantity_counter_ext);j++)
      {
        if(extreme[i] > extreme[j])
        { //troca os valores de temperatura caso os extremos nao estejam ordenados de forma crescente
          switcher=extreme[i];
          extreme[i]=extreme[j];
          extreme[j]=switcher;
          //troca os nomes juntamente com as temperaturas
          name_switcher=extreme_place[i];
          extreme_place[i]=extreme_place[j];
          extreme_place[j]=name_switcher;
        }
      }
    }
  }

}

//imprime os valores dos resultados ao utilizador
void print_results(float min[VECTOR_SIZE_ANALYSIS],char* min_place[VECTOR_SIZE_ANALYSIS],float max[VECTOR_SIZE_ANALYSIS],char* max_place[VECTOR_SIZE_ANALYSIS],float extreme[VECTOR_SIZE_ANALYSIS],char* extreme_place[VECTOR_SIZE_ANALYSIS],int quantity_counter_min,int quantity_counter_max,int quantity_counter_ext,int quantity_select)
{
  int i=0;  //para os ciclos for

  printf("\nOs valores mínimos de temperatura são:\n");
  for(i=0;i<quantity_counter_min;i++) //imprime os valores minimos
  {
    printf("%.3f para %s/",min[i],min_place[i]);
  }
  if(i<quantity_select) //caso nao consiga imprimir os pedidos pelo utilizador
  {
    printf("\nNão foi possível reunir as condições para imprimir todos os %d paises pedidos\n",quantity_select);
  }

  printf("\nOs valores máximos de temperatura são:\n");
  for(i=0;i<quantity_counter_max;i++) //imprime os valores maximos
  {
    printf("%.3f para %s/",max[i],max_place[i]);
  }
  if(i<quantity_select) //caso nao consiga imprimir os pedidos pelo utilizador
  {
    printf("\nNão foi possível reunir as condições para imprimir todos os %d paises pedidos\n",quantity_select);
  }

  printf("\nOs valores máximos de extremo são:\n");
  for(i=0;i<quantity_counter_ext;i++) //imprime os valores de extremo
  {
    printf("%.3f para %s/",extreme[i],extreme_place[i]);
  }
  if(i<quantity_select) //caso nao consiga imprimir a quantidade pedida pelo utilizador
  {
    printf("\nNão foi possível reunir as condições para imprimir todos os %d paises pedidos\n",quantity_select);
  }
}
