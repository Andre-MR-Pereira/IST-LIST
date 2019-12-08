#ifndef _STRUCTS_H
#define _STRUCTS_H

#define FILE1 17
#define FILE2 14
#define STRING_SIZE 110
#define COUNTRY_SIZE 50
#define VECTOR_SIZE_ANALYSIS 20
#define WINDOW_POSX 15
#define WINDOW_POSY 10
#define TABLE_SIZE 850

typedef struct {
  int dia; //para guardar o dia
  int mes; //para guardar o mes
  int ano; //para guardar o ano
} data;

typedef struct {
  float angle; //angulo da latitude ou longitude
  char hemisferio; //hemisferio da latitude ou longitude
} geo_coord;

typedef struct {
  data dt; //para guardar a data
  float temperatura; //para guardar a temperatura
  float incerteza; //para guardar a incerteza
  char *pais; //para guardar o nome do país
  char *cidade; //para guardar o nome da cidade (só é utilizado na leitura do ficheiro das cidades)
  geo_coord lat; //para guardar a latitude
  geo_coord longi; //para guardar a longitude
} dados_temp;

typedef struct node {
  dados_temp payload; //guarda os dados que cada nó
  struct node *next; //guarda o endereço de memória do elemento seguinte da lista
  struct node *prev; //guarda o endereço de memória do elemento anterior da lista
} data_scan;

#endif
