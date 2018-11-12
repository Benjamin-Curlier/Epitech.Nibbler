//
// Graphic.cpp for cpp_nibbler in /home/ambroi_s/rendu/cpp_nibbler
// 
// Made by Simon Ambroise
// Login   <ambroi_s@epitech.net>
// 
// Started on  jeu. avril 02 13:27:10 2015 Simon Ambroise
// Last update Sun Apr  5 18:32:03 2015 Benjamin Curlier
//

#include <iostream>
#include <unistd.h>
#include <dlfcn.h>
#include "Snake.hh"
#include "Graphic.hh"

typedef bool (*func2_t)(int,int);
typedef bool (*func_t)(int,int, char);
typedef int (*create_t)(int,int);
typedef bool (*game_t)(int,int,char*,std::vector<std::pair<int,int> >*, std::pair<int,int>*, char);
typedef bool (*game_two_player_t)(int,int,char*,std::vector<std::pair<int,int> >*, std::pair<int,int>*, char,std::vector<std::pair<int,int> >*, std::pair<int,int>*, char);
typedef bool (*getInputGame_t)(char*);
typedef void (*getInput_t)(char*);
typedef void (*getInput_two_player_t)(char*, char*);

Graphic::Graphic(std::string libName)
{
  this->_libName = "./GraphicLibrary/" + libName;
  this->_library = dlopen(this->_libName.c_str(), RTLD_LAZY);
  if (this->_library == NULL)
    this->_isExistant = false;
  else
    this->_isExistant = true;
}

Graphic::~Graphic()
{
  dlclose(this->_library);
}

bool Graphic::displayGame(int y, int x, char *map, Snake *s)
{
  void* initializer = dlsym(this->_library,"game");

  std::pair<int,int> lol = s->getPoshead();
  std::vector<std::pair<int,int> > lolo = s->getSnake();
  char dir = s->getDirection();
  if (initializer == NULL)
    std::cout << "error game" << std::endl;
  else 
    { 
      game_t func = (game_t)initializer; 
      return (func(y, x, map, &lolo, &lol, dir));
    }
  return true;
}

bool Graphic::displayGame_two_player(int y, int x, char *map, Snake *s, Snake *s2)
{
  void* initializer = dlsym(this->_library,"game_two_player");

  std::pair<int,int> lol = s->getPoshead();
  std::vector<std::pair<int,int> > lolo = s->getSnake();
  char dir = s->getDirection();
  std::pair<int,int> lol2 = s2->getPoshead();
  std::vector<std::pair<int,int> > lolo2 = s2->getSnake();
  char dir2 = s2->getDirection();
  if (initializer == NULL)
    std::cout << "error game" << std::endl;
  else 
    { 
      game_two_player_t func = (game_two_player_t)initializer; 
      return (func(y, x, map, &lolo, &lol, dir, &lolo2, &lol2, dir2));
    }
  return true;
}

void Graphic::init(int y, int x)
{
  void* initializer = dlsym(this->_library,"create");
  if (initializer == NULL)
    std::cout << "error create" << std::endl;
  else 
    { 
      create_t func = (create_t)initializer; 
      func(y, x);
    }
}

bool Graphic::displayMenu(int y, int x, char a)
{
  void* initializer = dlsym(this->_library,"menu");

  if (initializer == NULL)
    std::cout << "error menu" << std::endl;
  else 
    { 
      func_t func = (func_t)initializer; 
      return (func(y, x, a));
    }
  return true;
}

bool Graphic::displayOption(int y, int x, char a)
{
  void* initializer = dlsym(this->_library,"option");

  if (initializer == NULL)
    std::cout << "error option" << std::endl;
  else 
    { 
      func_t func = (func_t)initializer; 
      return (func(y, x, a));
    }
  return true;
}

bool Graphic::displayEnd(int y, int x)
{
  void* initializer = dlsym(this->_library,"end");

  if (initializer == NULL)
    std::cout << "error menu" << std::endl;
  else 
    { 
      func2_t func = (func2_t)initializer; 
      return (func(y, x));
    }
  return true;
}


void Graphic::getInput(char *t)
{
  void* initializer = dlsym(this->_library,"getInput");

  if (initializer == NULL)
    std::cout << "error menu" << std::endl;
  else 
    { 
      getInput_t func = (getInput_t)initializer; 
      func(t);
    }
}

void Graphic::getInput_two_player(char *t, char *t2)
{
  void* initializer = dlsym(this->_library,"getInput_two_player");

  if (initializer == NULL)
    std::cout << "error menu" << std::endl;
  else 
    { 
      getInput_two_player_t func = (getInput_two_player_t)initializer; 
      func(t, t2);
    }
}

bool Graphic::getInputGame(char *t)
{
  void* initializer = dlsym(this->_library,"getInputlol");

  if (initializer == NULL)
    std::cout << "error menu" << std::endl;
  else 
    { 
      getInputGame_t func = (getInputGame_t)initializer; 
      return (func(t));
    }
  return true;
}
