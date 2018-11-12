//
// menu.cpp for snake in /home/ambroi_s/rendu/snake
// 
// Made by Simon Ambroise
// Login   <ambroi_s@epitech.net>
// 
// Started on  lun. mars 23 14:50:10 2015 Simon Ambroise
// Last update Sun Apr  5 20:10:51 2015 Benjamin Curlier
//

#include <iostream>
#include <vector>
#include <ios>
#include <fstream>
#include <sstream>
#include <utility>
#include "Menu.hh"
#include "Graphic.hh"
#include "Game.hh"
#include "Snake.hh"

Graphic *display;

/* LA LICHE */

std::vector<std::string> &split(std::string s, char delim, std::vector<std::string> &elems) 
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) 
    elems.push_back(item);
  return elems;
}


std::vector<std::string> split(const std::string &s, char delim) 
{
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

Menu::Menu(int width, int height)
{
  int 		x;
  int 		y;
  int		i;
  std::fstream myfile;
  std::string 	line;
  std::stringstream *ss;

  if (width < 20)
    width = 20;
  if (height < 20)
    height = 20;
  this->_width = width;
  this->_height = height;
  this->_accel = false;
  this->_grow = false;
  display->init(height, width);
  for (y = 0; y < height; y++)
    {
      for (x = 0; x < width; x++)
	{
	  if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
	    this->_map.append("1");
	  else
	    this->_map.append("0");
	}
    }
  myfile.open(".highscoreliche");
  if (myfile.is_open())
    {
      while (std::getline(myfile, line))
	{
	  std::vector<std::string> splittedString;
	  splittedString = split(line, ' ');
	  ss = new std::stringstream(splittedString[1]); 
	  *ss >> i;
	  this->_highscore.insert(std::pair<std::string, int>(splittedString[0], i));
	}
    }
  else
    myfile.open(".highscoreliche", std::ios::out);
  myfile.close();
  /*  myfile.open(".map1");
      if (myfile.is_open())
      {
      this->_map = "";
      while (std::getline(myfile, line))
      this->_map += line;
      std::cout << this->_map << std::endl;
      }*/
}

Menu::~Menu()
{
}

void	Menu::start()
{
  Game	*newGame;
  int 	whereIAm;
  char touch = 'a';
  std::ofstream my_file;

  whereIAm = 0;
  while (!display->displayMenu(this->_height, this->_width, (char)whereIAm))
    {
      touch = 'a';
      display->getInput(&touch);
      if (touch == '3')
	whereIAm--;
      else if (touch == '2')
	whereIAm++;
      else if (touch == '1' && whereIAm == 0)
	{
	  newGame = new Game(this->_width, this->_height);
	  newGame->setIsacceleration(this->_accel);
	  newGame->setIsxgrow(this->_grow);
	  newGame->launch(this->_map);
	  my_file.open(".highscoreliche", std::ios::app);
	  my_file << newGame->getName() << " " << newGame->getScore() << std::endl;
	  my_file.close();
	  delete newGame;
	}
      else if (touch == '1' && whereIAm == 1)
	{
	  newGame = new Game(this->_width, this->_height, 0);
	  newGame->setIsacceleration(this->_accel);
	  newGame->setIsxgrow(this->_grow);
	  newGame->launch_two_player(this->_map);
	  my_file.open(".highscoreliche", std::ios::app);
	  my_file << newGame->getName() << " " << newGame->getScore() << std::endl;
	  my_file.close();
	  delete newGame;
	}
      else if (touch == '1' && whereIAm == 2)
	this->options();
      else if (touch == '1' && whereIAm == 3)
	return;
      else if (touch == 'E')
	return;
      else if (touch == '5')
	{
	  std::cout << "lol" << std::endl;
	  newGame = new Game(this->_width, this->_height);
	  newGame->setIsacceleration(this->_accel);
	  newGame->setIsxgrow(this->_grow);
	  newGame->launch_IA(this->_map);
	}
      if (whereIAm >= 4)
	whereIAm %= 4;
      else if (whereIAm < 0)
	whereIAm = 3;
    }
}

void 	Menu::options()
{
  int 	whereIAm = 0;
  char 	touch = 'a';

  while (!display->displayOption(this->_height, this->_width, (char)whereIAm))
    {
      touch = 'a';
      display->getInput(&touch);
      if (touch == '3')
	whereIAm--;
      else if (touch == '2')
	whereIAm++;
      else if (touch == '1' && whereIAm == 0)
	{
	  if (this->_accel == false)
	    this->_accel = true;
	  else
	    this->_accel = false;
	  std::cout << "Acceleration : " << std::boolalpha << this->_accel << std::endl;
	}
      else if (touch == '1' && whereIAm == 1)
	{
	  if (this->_grow == false)
	    this->_grow = true;
	  else
	    this->_grow = false;
	  std::cout << "Agrandissement : " << std::boolalpha << this->_grow << std::endl;
	}
      else if (touch == '1' && whereIAm == 2)
	{
	}
      else if (touch == 'E')
	return;
      if (whereIAm >= 3)
	whereIAm %= 3;
      else if (whereIAm < 0)
	whereIAm = 2;
    }
}

void	Menu::setMap(std::string map)
{
  this->_map = map;
}

std::string	Menu::getMap() const
{
  return (this->_map);
}

std::map<std::string, int> Menu::getScore() const
{
  return (this->_highscore);
}

bool	Menu::getMulti() const
{
  return _multi;
}

void	Menu::setMulti(bool a)
{
  _multi = a;
}
