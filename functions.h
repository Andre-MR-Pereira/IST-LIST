#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include "structs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//InitialLists
void InitProg (int, char const *[],char [FILE1],char [FILE2], int *);
void InitList (char [FILE1],char [FILE2],int);
void creat_countr_list (char [FILE1], data_scan *);
void creat_cty_list (char [FILE2], data_scan *);
char *MyStrtok (char *, char const *);

//Menus
void showInitMenu (data_scan *, data_scan *, data_scan *, data_scan *);
void Menu1 (data_scan *, data_scan *, data_scan *, data_scan *);
void Menu2 (data_scan *, data_scan *, data_scan *, data_scan *);
void Menu3 (data_scan *, data_scan *, data_scan *, data_scan *);
void Menu4 (data_scan *, data_scan *, data_scan *, data_scan *);

//funções remetentes à criação das listas
data_scan *create_dummy ();
/*void insert_head (data_scan *, data_scan *);*/
void insert_tail(data_scan *, data_scan *);
void print_list (data_scan *);
void insertionSort (data_scan *, data_scan *);
void free_alocated_list_country(data_scan*);
void free_alocated_list_city(data_scan*);
int checkBigger (data_scan *);

//funçoes remetentes a cada opçao dos menus
////Filtragem de dados
void make_copies (data_scan *, data_scan *, data_scan *, data_scan *);
void clear_crit (data_scan *, data_scan *, data_scan *,data_scan *);
void interval_analysis (data_scan *, data_scan *);
void month_analysis (data_scan *, data_scan *);
////Hist de Temperaturas
void global_history(data_scan *, int);
void country_history(data_scan *,int);
void city_history(data_scan*,int);
void check_max (data_scan *, float *, int);
void check_min(data_scan *, float *, int);
void check_avg(data_scan *, float *,int);
void create_avg(int*,float *);
void check_new_cycle(data_scan *, int ,int ,int* , int *, int *);
void make_print(float *, float *, float *, int*, int, int*,int*,int *);
//analise de anos
void country_analysis(data_scan* ,int ,int);
void city_analysis(data_scan* ,int ,int);
void check_min_analysis(data_scan*,int ,float [VECTOR_SIZE_ANALYSIS],char *[VECTOR_SIZE_ANALYSIS],int ,int *,int);
void check_max_analysis(data_scan*,int ,float [VECTOR_SIZE_ANALYSIS],char *[VECTOR_SIZE_ANALYSIS],int ,int *,int);
void check_extremes_analysis(data_scan* ,data_scan* ,int ,float [VECTOR_SIZE_ANALYSIS],char* [VECTOR_SIZE_ANALYSIS],int* ,int);
void print_results(float [VECTOR_SIZE_ANALYSIS],char *[VECTOR_SIZE_ANALYSIS],float [VECTOR_SIZE_ANALYSIS],char *[VECTOR_SIZE_ANALYSIS],float [VECTOR_SIZE_ANALYSIS],char* [VECTOR_SIZE_ANALYSIS],int ,int ,int ,int);

//funçoes relacionadas com o modo grafico
void graphic_mode(data_scan*);
void InitEverything(int , int , TTF_Font **,SDL_Surface **, SDL_Window ** , SDL_Renderer ** );
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int , int );
SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
int RenderWindow(data_scan* ,int, int, int [],TTF_Font *, SDL_Surface **, SDL_Renderer *);
void point_generator(data_scan* ,int *,TTF_Font *,SDL_Renderer* );
void year_string(int,TTF_Font *,SDL_Renderer* );

#endif
