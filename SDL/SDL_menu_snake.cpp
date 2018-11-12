/*
** SDL_snake.cpp for SDL in /home/camila/rendu/cpp_nibbler/SDL
**
** Made by Camila Chabane
** Login  <@epitech.eu>
**
** Started on  jeu. mars 26 14:45:08 2015 
** Last update dim. avril 05 23:23:37 2015 
*/

#include "../Snake.hh"
#include "graph.h"

SDL_Window* mWindow = NULL;
SDL_Surface* mScreenSurface = NULL;
SDL_Surface* mStretchedSurface = NULL;

void	 		menu_init(int height, int width)
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
  else
    {
      mWindow = SDL_CreateWindow( "SNAKE.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
      if( mWindow == NULL )
	printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      else
	mScreenSurface = SDL_GetWindowSurface( mWindow );
    }
}

void 			menu_close()
{
  SDL_FreeSurface( mStretchedSurface );
  mStretchedSurface = NULL;
  SDL_DestroyWindow( mWindow );
  mWindow = NULL;
  SDL_Quit();
}

SDL_Surface* 		menu_loadSurface(std::string path)
{
  SDL_Surface* optimizedSurface = NULL;
  SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );

  if( loadedSurface == NULL )
    printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
  else
    {
      optimizedSurface = SDL_ConvertSurface( loadedSurface, mScreenSurface->format, (Uint32)NULL );
      if( optimizedSurface == NULL )
	printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
      SDL_FreeSurface( loadedSurface );
    }
  return optimizedSurface;
}

void 			menu_loadMedia(std::string path)
{
  mStretchedSurface = menu_loadSurface(path.c_str());
  if( mStretchedSurface == NULL )
    printf( "Failed to load stretching image!\n" );
}

void			menu_addMediaPos(int x, int y, std::string path)
{
  SDL_Surface		*you = NULL;
  SDL_Rect		pos;

  pos.x = x;
  pos.y = y;
  you = menu_loadSurface(path);
  SDL_SetColorKey(you, SDL_TRUE, SDL_MapRGB(you->format, 0, 0, 255));
  SDL_BlitSurface(you, NULL, mScreenSurface, &pos);
}

std::string	menu_create_map(int a)
{
  std::string	map;
  int	x = 1000;
  int	y = 200;
  int	j = 0;
  int	i;

  if (a == 1)
  {
    while (j < 20)
    {
      for (i = 0; i < 20; ++i)
      {
	menu_addMediaPos(x, y, "./Nibbler/mini_square.bmp");
	x += 10;
	map.append("0");
      }
      j++;
      x = 1000;
      y += 10;
    }
  }
  else if (a == 2)
  {
  j = 0;
    while (j < 20)
    {
      for (i = 0; i < 20; ++i)
      {
	if (xrandom(20) == 0 || xrandom(20) == 1)
	{
	  menu_addMediaPos(x, y, "./Nibbler/mini_wall.bmp");
	map.append("1");
	}
	else
	{
	  menu_addMediaPos(x, y, "./Nibbler/mini_square.bmp");
	map.append("0");
	}
	a++;
	x += 10;
      }
      j++;
      x = 1000;
      y += 10;
    }
  }
  return map;
}

void			menu_lel_map(char *map)
{
  int			a = 1;
  int			x = 0;
  int			y = 0;
  int			i = 0;

  while (map[i] != '\0')
    {
      if (map[i] == '1')
	menu_addMediaPos(x, y, "./Nibbler/mur.bmp");
      else if (map[i] == '2')
      {
	menu_addMediaPos(x, y, "./Nibbler/square.bmp");
	if (xrandom(3) == 0)
	  menu_addMediaPos(x, y, "./Nibbler/ange.bmp");
	else if (xrandom(3) == 1)
	  menu_addMediaPos(x, y, "./Nibbler/ange_right.bmp");
	else if (xrandom(3) == 2)
	  menu_addMediaPos(x, y, "./Nibbler/ange_left.bmp");
	else
	  menu_addMediaPos(x, y, "./Nibbler/ange_back.bmp");
      }
      else
	menu_addMediaPos(x, y, "./Nibbler/square.bmp");
      x += 45;
      if (a % 30 == 0)
	{
	  y += 45;
	  x = 0;
	}
      a++;
      i++;
    }
}

void			menu_where_is_snake(std::vector<std::pair<int,int> > *caca, std::pair<int,int> *poshead, char direction)
{
  for (std::vector<std::pair<int, int> >::iterator it = caca->begin(); it != caca->end(); ++it)
    menu_addMediaPos(it->first * 45, it->second * 45, "./Nibbler/soul.bmp");
  if (direction == '1')
    menu_addMediaPos(poshead->first * 45, poshead->second * 45, "./Nibbler/liche_right.bmp");
  else if (direction == '2')
    menu_addMediaPos(poshead->first * 45, poshead->second * 45, "./Nibbler/liche_left.bmp");
  else if (direction == '3')
    menu_addMediaPos(poshead->first * 45, poshead->second * 45, "./Nibbler/liche_back.bmp");
  else
    menu_addMediaPos(poshead->first * 45, poshead->second * 45, "./Nibbler/liche_head.bmp");
}

extern "C" bool			_menu(int height, int width, char *map, std::vector<std::pair<int, int> > *caca, std::pair<int, int> *poshead, char direction)
{
  menu_loadMedia("./Nibbler/menu_start.bmp");
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = width * 45;
  stretchRect.h = height * 45;
  SDL_BlitScaled( mStretchedSurface, NULL, mScreenSurface, &stretchRect );
  menu_where_is_snake(caca, poshead, direction);
  menu_lel_map(map);
  SDL_UpdateWindowSurface(mWindow);
  return (false);
}

extern "C" int 			menu_create()
{
  menu_init(30 * 45, 20 * 45);
  return (0);
}
