#include "functions.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char const *argv[]) {
  char cntr[FILE1] = {0}; //variável que irá guardar o nome do ficheiro dos países
  char cty[FILE2] = {0}; //variável que irá guardar o nome do ficheiro das cidades
  int t = 0; // variável que diz se o utilizador pretende o modo textual ou o modo gráfico

  InitProg(argc, argv, cntr, cty, &t); //é chamada a função que irá ler os argumentos quando o programa é iniciado e irá guardar os nomes de cada ficheiro a ser lido e modificar a variável t, para determinar se é feito o modo gráfico ou textual

  clock_t begin = clock();
  InitList(cntr, cty,t); //aqui é chamada a função que irá ler os ficheiros e guardá-los em listas e mostrar os menus
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("fun() took %f seconds to execute \n", time_spent);

  return EXIT_SUCCESS;
}
