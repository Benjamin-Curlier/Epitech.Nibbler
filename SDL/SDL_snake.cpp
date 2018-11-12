/*
** SDL_snake.cpp for SDL in /home/camila/rendu/cpp_nibbler/SDL
**
** Made by Camila Chabane
** Login  <@epitech.eu>
**
** Started on  jeu. mars 26 14:45:08 2015 
** Last update dim. avril 05 21:08:48 2015 
*/

#include "../Snake.hh"
#include "graph.h"

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gStretchedSurface = NULL;

void	 		init(int height, int width)
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
  else
    {
      gWindow = SDL_CreateWindow( "SNAKE.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
      if( gWindow == NULL )
	printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      else
	gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
}

void 			close()
{
  SDL_FreeSurface( gStretchedSurface );
  gStretchedSurface = NULL;
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  SDL_Quit();
}

SDL_Surface* 		loadSurface(std::string path)
{
  SDL_Surface* optimizedSurface = NULL;
  SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );

  if( loadedSurface == NULL )
    printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
  else
    {
      optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, (Uint32)NULL );
      if( optimizedSurface == NULL )
	printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
      SDL_FreeSurface( loadedSurface );
    }
  return optimizedSurface;
}

void 			loadMedia(std::string path)
{
  gStretchedSurface = loadSurface(path.c_str());
  if( gStretchedSurface == NULL )
    printf( "Failed to load stretching image!\n" );
}

void			addMediaPos(int x, int y, std::string path)
{
  SDL_Surface		*you = NULL;
  SDL_Rect		pos;

  pos.x = x;
  pos.y = y;
  you = loadSurface(path);
  SDL_SetColorKey(you, SDL_TRUE, SDL_MapRGB(you->format, 0, 0, 255));
  SDL_BlitSurface(you, NULL, gScreenSurface, &pos);
}

void			create_map(char *map, int width)
{
  int			a = 1;
  int			x = 0;
  int			y = 0;
  int			i = 0;

  while (map[i] != '\0')
    {
      if (map[i] == '1')
	addMediaPos(x, y, "./Nibbler/mur.bmp");
      else if (map[i] == '2')
      {
	addMediaPos(x, y, "./Nibbler/square.bmp");
	if (xrandom(3) == 0)
	  addMediaPos(x, y, "./Nibbler/ange.bmp");
	else if (xrandom(3) == 1)
	  addMediaPos(x, y, "./Nibbler/ange_right.bmp");
	else if (xrandom(3) == 2)
	  addMediaPos(x, y, "./Nibbler/ange_left.bmp");
	else
	  addMediaPos(x, y, "./Nibbler/ange_back.bmp");
      }
      else if (map[i] == '3')
      {
	addMediaPos(x, y, "./Nibbler/square.bmp");
	if (xrandom(3) == 0)
	  addMediaPos(x, y, "./Nibbler/red_ange_head.bmp");
	else if (xrandom(3) == 1)
	  addMediaPos(x, y, "./Nibbler/red_ange_right.bmp");
	else if (xrandom(3) == 2)
	  addMediaPos(x, y, "./Nibbler/red_ange_left.bmp");
	else
	  addMediaPos(x, y, "./Nibbler/red_ange_back.bmp");
      }
      else
	addMediaPos(x, y, "./Nibbler/square.bmp");
      x += 45;
      if (a % width == 0)
	{
	  y += 45;
	  x = 0;
	}
      a++;
      i++;
    }
}

void			where_is_snake(std::vector<std::pair<int,int> > *caca, std::pair<int,int> *poshead, char direction)
{
  for (std::vector<std::pair<int, int> >::iterator it = caca->begin(); it != caca->end(); ++it)
    addMediaPos(it->first * 45, it->second * 45, "./Nibbler/soul.bmp");
  if (direction == '1')
    addMediaPos(poshead->first * 45, poshead->second * 45, "./Nibbler/liche_right.bmp");
  else if (direction == '2')
    addMediaPos(poshead->first * 45, poshead->second * 45, "./Nibbler/liche_left.bmp");
  else if (direction == '3')
    addMediaPos(poshead->first * 45, poshead->second * 45, "./Nibbler/liche_back.bmp");
  else
    addMediaPos(poshead->first * 45, poshead->second * 45, "./Nibbler/liche_head.bmp");
}

extern "C" bool			end(int height, int width)
{
  loadMedia("./Nibbler/gameover.bmp");
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = width * 45;
  stretchRect.h = height * 45;
  SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
  SDL_UpdateWindowSurface(gWindow);
  sleep(3);
  return (false);
}

extern "C" bool			game(int height, int width, char *map,std::vector<std::pair<int,int> > *caca, std::pair<int,int> *poshead, char direction)
{
  loadMedia("./Nibbler/back.bmp");
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = width * 45;
  stretchRect.h = height * 45;
  SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
  create_map(map, width);
  where_is_snake(caca, poshead, direction);
  SDL_UpdateWindowSurface(gWindow);
  return (false);
}

extern "C" bool			game_two_player(int height, int width, char *map,std::vector<std::pair<int,int> > *caca, std::pair<int,int> *poshead, char direction, std::vector<std::pair<int,int> > *caca2, std::pair<int,int> *poshead2, char direction2)
{
  loadMedia("./Nibbler/back.bmp");
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = width * 45;
  stretchRect.h = height * 45;
  SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
  create_map(map, width);
  where_is_snake(caca, poshead, direction);
  where_is_snake(caca2, poshead2, direction2);
  SDL_UpdateWindowSurface(gWindow);
  return (false);
}

extern "C" void			getInput(char *touch)
{
  SDL_Event	e;

  while (SDL_PollEvent(&e) != 0)
    {
      switch(e.type)
	{
	case SDL_QUIT:
	  *touch = 'E';
	  break;
	case SDL_KEYDOWN:
	  switch (e.key.keysym.sym)
	    {
	    case SDLK_RIGHT:
	      *touch = '5';
	      break;
	    case SDLK_LEFT:
	      *touch = '4';
	      break;
	    case SDLK_UP:
	      *touch = '3';
	      break;
	    case SDLK_DOWN:
	      *touch = '2';
	      break;
	    case SDLK_RETURN:
	      *touch = '1';
	      break;
	    case SDLK_ESCAPE:
	      *touch = 'E';
	      break;
	    }
	}
    }
}

extern "C" void			getInput_two_player(char *touch, char *touch2)
{
  SDL_Event	e;

  while (SDL_PollEvent(&e) != 0)
    {
      switch(e.type)
	{
	case SDL_KEYDOWN:
	  switch (e.key.keysym.sym)
	    {
	    case SDLK_RIGHT:
	      *touch = '5';
	      break;
	    case SDLK_LEFT:
	      *touch = '4';
	      break;
	    case SDLK_w:
	      *touch2 = '5';
	      break;
	    case SDLK_c:
	      *touch2 = '4';
	      break;
	    }
	}
    }
}

extern "C" bool			menu(int height, int width, char touch)
{
  if (touch == 2)
    loadMedia("./Nibbler/menu_options.bmp");
  else if (touch == 0)
    loadMedia("./Nibbler/menu_start.bmp");
  else if (touch == 3)
    loadMedia("./Nibbler/menu_exit.bmp");
  else if (touch == 1)
    loadMedia("./Nibbler/menu_two.bmp");
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = width * 45;
  stretchRect.h = height * 45;
  SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
  SDL_UpdateWindowSurface(gWindow);
  return (false);
}

extern "C" bool			option(int height, int width, char touch)
{
  if (touch == 0)
    loadMedia("./Nibbler/menu_options_snake.bmp");
  else if (touch == 1)
    loadMedia("./Nibbler/menu_options_random.bmp");
  else if (touch == 2)
    loadMedia("./Nibbler/menu_options_map.bmp");
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = width * 45;
  stretchRect.h = height * 45;
  SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
  SDL_UpdateWindowSurface(gWindow);
  return (false);
}

extern "C" int 			create(int height, int width)
{
  init(height * 45, width * 45);
  return (0);
}
