#include "functions.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void graphic_mode(data_scan *head_cities)
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  TTF_Font *sans = NULL;
  SDL_Surface *imgs[1];
  SDL_Event event;
  data_scan* cities_temp_organized=NULL;
  data_scan* new_node=NULL;
  data_scan* aux=NULL;
  data_scan* tmp=NULL;
  int width = 650;
  int height = 250;
  int quit = 0;
  int square_size_px = 0, board_size_px[2] = {0};
  int board_pos_x=0,board_pos_y=0;
  int ano_ver=0;

  cities_temp_organized=create_dummy(); //organizar a lista de cidades por data de forma a facilitar a atualizaçao dos pontos a um unico ano

  aux=head_cities->next;  //aponta para o primeiro no da lista das cidades
  tmp=cities_temp_organized->next;  //aponta para o primeiro no onde iremos guardar por data

  while(aux!=head_cities)
  {
    new_node = (data_scan *)malloc(sizeof(data_scan));  //alocar memoria para o no
    if(new_node == NULL) {
      printf("Memory allocation error!");
      exit(EXIT_FAILURE);
    }

    new_node->payload.pais = (char *)malloc((strlen(aux->payload.pais) + 1)*sizeof(char));  //alocar memoria para o pais
    if(new_node->payload.pais == NULL) {
      printf("Memory allocation error!");
      exit(EXIT_FAILURE);
    }

    new_node->payload.cidade = (char *)malloc((strlen(aux->payload.cidade) + 1)*sizeof(char));  //alocar memoria para a cidade
    if(new_node->payload.cidade == NULL) {
      printf("Memory allocation error!");
      exit(EXIT_FAILURE);
    }
    //passar todos os valores para o novo no
    new_node->payload.dt.ano = aux->payload.dt.ano;
    new_node->payload.dt.mes = aux->payload.dt.mes;
    new_node->payload.dt.dia = aux->payload.dt.dia;
    new_node->payload.temperatura = aux->payload.temperatura;
    new_node->payload.incerteza = aux->payload.incerteza;
    new_node->payload.lat.angle = aux->payload.lat.angle;
    new_node->payload.longi.angle = aux->payload.longi.angle;
    strcpy(new_node->payload.pais, aux->payload.pais);
    strcpy(new_node->payload.cidade,aux->payload.cidade);
    new_node->payload.lat.hemisferio = aux->payload.lat.hemisferio;
    new_node->payload.longi.hemisferio = aux->payload.longi.hemisferio;

    insertionSort(cities_temp_organized,new_node);  //inserir organizadamente na nova lista
    //passar ao proximo no
    aux = aux->next;
    tmp = tmp->next;
  }

  // inicializa os graficos
  InitEverything(width, height,&sans,imgs, &window, &renderer);

  board_pos_x = 5;
  board_pos_y = 5;

  while( quit == 0 )
  {
    // while there's events to handle
    while( SDL_PollEvent( &event ) )
    {
      if( event.type == SDL_QUIT )
      {
        // fecha a janela do mapa
        quit = 1;
        return;
      }
      else if ( event.type == SDL_KEYDOWN )
      {
        switch ( event.key.keysym.sym )
        {
          case SDLK_z:
          {
            //faz zoom (to implement)
            break;
          }
          default:
            break;
        }
      }
    }
    //cria e atualiza a janela do mapa
    square_size_px = RenderWindow(cities_temp_organized,board_pos_x, board_pos_y, board_size_px,sans, imgs, renderer);
    point_generator(cities_temp_organized,&ano_ver,sans,renderer);
    year_string(ano_ver,sans,renderer);  //mostra o ano a ser analizado ao utilizador
    //mostra as atualizaçoes da janela no ecra
    SDL_RenderPresent(renderer);

    SDL_Delay(35);
  }

  // free memory allocated for images and textures and closes everything including fonts
  TTF_CloseFont(sans);
  SDL_FreeSurface(imgs[0]);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}





/**
 * InitEverything: Initializes the SDL2 library and all graphical components: font, window, renderer
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _font font that will be used to render the text
 * \param _img surface to be created with the table background and IST logo
 * \param _window represents the window of the application
 * \param _renderer renderer to handle all rendering in a window
 */
void InitEverything(int width, int height, TTF_Font **_font,SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height); //cria a janela
    *_renderer = CreateRenderer(width, height, *_window); //cria o atualizador de janela para o ecra

    //carrega o mapa
    _img[0] = IMG_Load("mundo.jpg");
    if (_img[0] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //carrega a fonte

    *_font = TTF_OpenFont("OpenSans.ttf", 15);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

}

/**
 * InitSDL: Initializes the SDL2 graphic library
 */
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
    window = SDL_CreateWindow( "Mapa Mundo", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}

/*
 * RenderTable: Draws the table where the game will be played, namely:
 * -  some texture for the background
 * -  the right part with the IST logo and the student name and number
 * -  the grid for game board with squares and seperator lines
 * \param _board_pos_x number of positions in the board (x axis)
 * \param _board_pos_y number of positions in the board (y axis)
 * \param _board_size_px size of the board
 * \param _font font used to render the text
 * \param _img surfaces with the table background and IST logo (already loaded)
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderWindow(data_scan* head_cities,int _board_pos_x, int _board_pos_y, int _board_size_px[],TTF_Font *_font, SDL_Surface *_img[], SDL_Renderer* _renderer )
{
    //cores usadas nas fontes de letra
    SDL_Color black = {0,0,0};
    SDL_Color light = {205,193,181};
    SDL_Color dark = {120,110,102};

    SDL_Texture *table_texture;
    SDL_Rect tableSrc, tableDest, board, board_square;
    int height, board_size, square_size_px, max_pos;
    int n=0,h=0;

    //cria a cor do fundo da janela
    SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );

    //apaga a janela
    SDL_RenderClear( _renderer );
    //volta a cria a janela
    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = _img[0]->w;
    tableSrc.h = _img[0]->h;
    tableDest.w = 500;
    tableDest.h = 250;

    //carrega a imagem do mundo para a janela
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);

/*
    // compute and adjust the size of the table and squares
    max_pos = MAX(_board_pos_x, _board_pos_y);
    board_size = (int)(BOARD_SIZE_PER*TABLE_SIZE);
    square_size_px = (board_size - (max_pos+1)*SQUARE_SEPARATOR) / max_pos;
    _board_size_px[0] = _board_pos_x*(square_size_px+SQUARE_SEPARATOR)+SQUARE_SEPARATOR;
    _board_size_px[1] = _board_pos_y*(square_size_px+SQUARE_SEPARATOR)+SQUARE_SEPARATOR;

    // renders the entire board background
    SDL_SetRenderDrawColor(_renderer, dark.r, dark.g, dark.b, dark.a );
    board.x = (TABLE_SIZE - _board_size_px[0]) >> 1;
    board.y = (TABLE_SIZE - _board_size_px[1] - 15);
    board.w = _board_size_px[0];
    board.h = _board_size_px[1];
    SDL_RenderFillRect(_renderer, &board);

    // renders the squares where the numbers will appear
    SDL_SetRenderDrawColor(_renderer, light.r, light.g, light.b, light.a );
*/
    // destroy everything
    SDL_DestroyTexture(table_texture);
    // return for later use
    return square_size_px;
}


/**
 * filledCircleRGBA: renders a filled circle
 * \param _circleX x pos
 * \param _circleY y pos
 * \param _circleR radius
 * \param _r red
 * \param _g gree
 * \param _b blue
 */
 /*
void filledCircleRGBA(SDL_Renderer * _renderer, int _circleX, int _circleY, int _circleR, int _r, int _g, int _b)
{
    int off_x = 0;
    int off_y = 0;
    float degree = 0.0;
    float step = M_PI / (_circleR*8);

    SDL_SetRenderDrawColor(_renderer, _r, _g, _b, 255);

    while (_circleR > 0)
    {
        for (degree = 0.0; degree < M_PI/2; degree+=step)
        {
            off_x = (int)(_circleR * cos(degree));
            off_y = (int)(_circleR * sin(degree));
            SDL_RenderDrawPoint(_renderer, _circleX+off_x, _circleY+off_y);
            SDL_RenderDrawPoint(_renderer, _circleX-off_y, _circleY+off_x);
            SDL_RenderDrawPoint(_renderer, _circleX-off_x, _circleY-off_y);
            SDL_RenderDrawPoint(_renderer, _circleX+off_y, _circleY-off_x);
        }
        _circleR--;
    }
}
*/
void point_generator(data_scan* cities_temp_organized,int *ano_ver,TTF_Font *_font,SDL_Renderer* _renderer)
{
  /*
  //cor para a apresentaçao do ano
  SDL_Color dark={120,110,102};
  //palete de cores usada na marcaçao de pontos com as temperaturas
  SDL_Color dark_blue_dark = {0,0,139}; //cor 1
  SDL_Color dark_blue_light = {0,0,205};  //cor 2
  SDL_Color light_blue_dark = {65,105,225}; //cor 3
  SDL_Color light_blue_light = {135,206,250}; //cor 4
  SDL_Color dark_orange = {255,140,0};  //cor 5
  SDL_Color light_orange = {255,165,0}; //cor 6
  SDL_Color light_red_light = {220,20,60};  //cor 7
  SDL_Color light_red_dark = {255,0,0}; //cor 8
  SDL_Color dark_red_light = {178,34,34}; //cor 9
  SDL_Color dark_red_dark = {139,0,0};  //cor 10

  data_scan* aux=NULL;  //ponteiro auxiliar para percorrer a lista
  char year_screen[COUNTRY_SIZE]={0};
  float min= -20.0,max=50.0;
  float color_range=0.0;

  aux=head_cities->next;
  color_range= (max-min)/(10);
  while(aux!=cities_temp_organized)
  {
    if(aux->payload.temperatura<=(min + color_range*1))
    { //ir buscar latitude e longitude do ponto,coloca-lo no mapa e preenche-lo com cores
      /*aux->payload.lat.angle
      aux->payload.lat.hemisferio
      aux->payload.longi.angle
      aux->payload.longi.hemisferio
      find_map_place();
      SDL_RenderDrawPoint(_renderer,)

    }
    else if(aux->payload.temperatura<=(min + color_range*2))
    {

    }
    else if(aux->payload.temperatura<=(min + color_range*3))
    {

    }
    else if(aux->payload.temperatura<=(min + color_range*4))
    {

    }
    else if(aux->payload.temperatura<=(min + color_range*5))
    {

    }
    else if(aux->payload.temperatura<=(min + color_range*6))
    {

    }
    else if(aux->payload.temperatura<=(min + color_range*7))
    {

    }
    else if(aux->payload.temperatura<=(min + color_range*8))
    {

    }
    else if(aux->payload.temperatura<=(min + color_range*9))
    {

    }
    else if(aux->payload.temperatura<=(min + color_range*10))
    {

    }
    aux=aux->next;
  }
*/
}

void year_string(int ano_ver,TTF_Font *_font,SDL_Renderer* _renderer)
{
  //cor para a apresentaçao do ano
  SDL_Color dark={120,110,102};

  char year_screen[COUNTRY_SIZE]={0};
  sprintf(year_screen,"Year analysing: %d",ano_ver);

  SDL_Rect year_display;
  year_display.x=510;
  year_display.y=20;

  RenderText(year_display.x,year_display.y,year_screen,_font,&dark,_renderer);
}

/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}
