#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

//Apresentação do menu inicial
void showInitMenu (data_scan *head_country, data_scan *filtered_country, data_scan *head_cities, data_scan *filtered_city) {
  int option_1 = 0;

  printf("\n=================[Menu]=================\n---Please select one of the following---\n\n\n1.  Filtragem de dados\n2.  Histórico de temperaturas\n3.  Análise da temperatura por ano\n4.  Análise da temperatura global.\n\n\n\n\n\n\n6.Sair\n\n");
  scanf("%d", &option_1); //lê qual opção o utilizador escolheu

  if (option_1 == 1 || option_1 == 2 || option_1 == 3 || option_1 == 4 || option_1 == 6) { //condição posta para ter a certeza que o utilizador só escolheu uma das opções apresentadas
    switch (option_1) {
      case 1: //se o utilizador introduzir o número 1, este é dirigido para o menu da filtragem de dados
       Menu1(head_country, filtered_country, head_cities, filtered_city); break;
      case 2: //se o utilizador introduzir o número 2, este é dirigido para o menu do histórico de temperaturas
       Menu2(head_country, filtered_country, head_cities, filtered_city); break;
      case 3: //se o utilizador introduzir o número 3, este é dirigido para o menu da análise da temperatura por ano
       Menu3(head_country, filtered_country, head_cities, filtered_city); break;
      case 4: //se o utilizador introduzir o número 4, este é dirigido para o menu da análise da temperatura global
       Menu4(head_country, filtered_country, head_cities, filtered_city); break;
      case 6: //se o utilizador introduzir o número 6 sai do programa
       system("clear");
       return;
    }
  } else { //se o utilizador não escolheu uma das opções apresentadas apresenta-se o menu outra vez
    showInitMenu(head_country, filtered_country, head_cities, filtered_city);
  }
}
//Apresentação do menu da filtragem de dados
void Menu1(data_scan *head_country, data_scan *filtered_country, data_scan *head_cities, data_scan *filtered_city) {
  int option_2 = 0;

  system("clear");

  printf("\n\n\n1.  Limpa Critérios\n2.  Escolhe intervalo para análise\n3.  Escolhe mês para análise\n\n\n\n\n\n5.Voltar\n6.Sair\n\n");
  scanf("%d", &option_2); //lê qual opção o utilizador escolheu

  if (option_2 == 1 || option_2 == 2 || option_2 == 3 || option_2 == 5 || option_2 == 6) { //condição posta para ter a certeza que o utilizador só escolheu uma das opções apresentadas
    switch (option_2) {
      case 1: //se o utilizador introduzir o número 1 é chamada a função que limpa os critérios postos anteriormente e de seguida volta ao menu inicial
       system("clear");
       clear_crit(head_country, filtered_country, head_cities, filtered_city);
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 2: //se o utilizador introduzir o número 1 é chamada a função em que o utilizador escolhe como critérios um ano e um mês mínimo para análise e de seguida volta ao menu inicial
       system("clear");
       interval_analysis(filtered_country, filtered_city);
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 3: //se o utilizador introduzir o número 1 é chamada a função em que o utilizador escolhe como critérios um intervalo de meses para análise e de seguida volta ao menu inicial
       system("clear");
       month_analysis(filtered_country, filtered_city);
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 5: //se o utilizador introduzir o número 5, este volta atrás (para o menu inicial)
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 6: //se o utilizador introduzir o número 6 sai do programa
       system("clear");
       return;
    }
  } else { //se o utilizador não escolheu uma das opções apresentadas apresenta-se o menu outra vez
    Menu1(head_country, filtered_country, head_cities, filtered_city);
  }
}
//Apresentação do menu do histórico de temperaturas
void Menu2(data_scan *head_country, data_scan *filtered_country, data_scan *head_cities, data_scan *filtered_city) {
  int option_2 = 0, time_frame = 0;

  system("clear");

  printf("Qual é o intervalo de tempo?\n");
  scanf("%d", &time_frame); //lê qual o intervalo de tempo escolhido pelo utilizador para depois ser passado para as funções que irão precisar deste valor

  system("clear");

  printf("\n\n\n1.  Global\n2.  Por País\n3.  Por Cidade\n\n\n\n\n\n5.Voltar\n6.Sair\n\n");
  scanf("%d", &option_2); //lê qual opção o utilizador escolheu

  if (option_2 == 1 || option_2 == 2 || option_2 == 3 || option_2 == 5 || option_2 == 6) { //condição posta para ter a certeza que o utilizador só escolheu uma das opções apresentadas
    switch (option_2) {
      case 1: //se o utilizador introduzir o número 1 é chamada a função que apresenta o histórico global de temperaturas e de seguida volta ao menu incial
       system("clear");
       global_history(filtered_country, time_frame);
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 2: //se o utilizador introduzir o número 2 é chamada a função que apresenta o histórico de temperaturas por país e de seguida volta ao menu incial
       system("clear");
       country_history(filtered_country, time_frame);
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 3: //se o utilizador introduzir o número 3 é chamada a função que apresenta o histórico de temperaturas por cidade e de seguida volta ao menu incial
       system("clear");
       city_history(filtered_city, time_frame);
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 5: //se o utilizador introduzir o número 5, este volta atrás (para o menu incial)
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 6: //se o utilizador introduzir o número 6 sai do programa
       system("clear");
       return;
    }
  } else { //se o utilizador não escolheu uma das opções apresentadas apresenta-se o menu outra vez
    Menu2(head_country, filtered_country, head_cities, filtered_city);
  }
}
//Apresentação do menu da análise de temperatura por ano/anual
void Menu3(data_scan *head_country, data_scan *filtered_country, data_scan *head_cities, data_scan *filtered_city) {
  int option_2 = 0;
  int ano_analise=0,quantity_select=0;  //recebe o ano de analise;recebe o intervalo

  system("clear");

  printf("Qual o ano a analisar?\n");
  scanf("%d",&ano_analise);
  printf("\n E quantas cidades/paises devem ser impressos?\n");
  scanf("%d",&quantity_select);

  while(quantity_select<1 || quantity_select >20)
  {
    printf("Apenas pode pedir entre 1 e 20.Volte a inserir\n");
    scanf("%d",&quantity_select);
  }

  system("clear");

  printf("\n\n\n1.  Análise por país\n2.  Análise por cidade\n\n\n\n\n\n5.Voltar\n6.Sair\n\n");
  scanf("%d", &option_2); //lê qual opção o utilizador escolheu

  if (option_2 == 1 || option_2 == 2 || option_2 == 5 || option_2 == 6) { //condição posta para ter a certeza que o utilizador só escolheu uma das opções apresentadas
    switch (option_2) {
      case 1: //se o utilizador introduzir o número 1 é chamada a função que faz a análise de temperatura anual por país e de seguida volta ao menu incial
       system("clear");
       country_analysis(filtered_country,ano_analise,quantity_select);
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 2: //se o utilizador introduzir o número 2 é chamada a função que faz a análise de temperatura anual por cidade e de seguida volta ao menu incial
       system("clear");
       city_analysis(filtered_city,ano_analise,quantity_select);
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 5: //se o utilizador introduzir o número 5, este volta atrás (para o menu incial)
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 6: //se o utilizador introduzir o número 6 sai do programa
       system("clear");
       return;
    }
  } else { //se o utilizador não escolheu uma das opções apresentadas apresenta-se o menu outra vez
    Menu3(head_country, filtered_country, head_cities, filtered_city);
  }
}
//Apresentação do menu da análise de temperatura global
void Menu4(data_scan *head_country, data_scan *filtered_country, data_scan *head_cities, data_scan *filtered_city) {
  int option_2 = 0;

  system("clear");

  printf("\n\n\n1.  Aumento da temperatura global do planeta\n2.  Aumento da temperatura global de um país\n3.  Aumento da temperatura global de uma cidade\n\n\n\n\n\n5.Voltar\n6.Sair\n\n");
  scanf("%d", &option_2); //lê qual opção o utilizador escolheu

  if (option_2 == 1 || option_2 == 2 || option_2 == 3 || option_2 == 5 || option_2 == 6) { //condição posta para ter a certeza que o utilizador só escolheu uma das opções apresentadas
    switch (option_2) {
      case 1: //se o utilizador introduzir o número 1 é chamada a função que faz a análise de temperatura global do planeta e de seguida volta ao menu incial
       system("clear");
       /*implementar*/
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 2: //se o utilizador introduzir o número 1 é chamada a função que faz a análise de temperatura global de um país e de seguida volta ao menu incial
       system("clear");
       /*implementar*/
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 3: //se o utilizador introduzir o número 1 é chamada a função que faz a análise de temperatura global de um cidade e de seguida volta ao menu incial
       system("clear");
       /*implementar*/
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 5: //se o utilizador introduzir o número 5, este volta atrás (para o menu incial)
       showInitMenu(head_country, filtered_country, head_cities, filtered_city); break;
      case 6: //se o utilizador introduzir o número 6 sai do programa
       system("clear");
       return;
    }
  } else { //se o utilizador não escolheu uma das opções apresentadas apresenta-se o menu outra vez
    Menu4(head_country, filtered_country, head_cities, filtered_city);
  }
}
