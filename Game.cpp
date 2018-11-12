#include <vector>
#include <utility>
#include <unistd.h>
#include <tr1/tuple>
#include "Game.hh"
#include "Graphic.hh"

extern Graphic *display;

std::string	Game::round(Snake *snake, char *food, std::string str, long *b, bool *d, int *grow)
{
  std::pair<int,int> head = snake->getPoshead();
  std::vector<std::pair<int,int> > oldSnake = snake->getSnake();
  std::vector<std::pair<int,int> >::iterator it;
  std::vector<std::pair<int,int> > newSnake;

  newSnake.push_back(std::pair<int,int>(head.first, head.second));
  it = oldSnake.begin();
  for (; it != oldSnake.end() - 1; ++it)
    newSnake.push_back(std::pair<int,int>(it->first, it->second));
  if (snake->getDirection() == '0')
    snake->setPoshead(head.first, head.second + 1);
  else if (snake->getDirection() == '1')
    snake->setPoshead(head.first + 1, head.second);
  else if (snake->getDirection() == '2')
    snake->setPoshead(head.first - 1, head.second);
  else if (snake->getDirection() == '3')
    snake->setPoshead(head.first, head.second - 1);
  head = snake->getPoshead();
  if (head.first == this->_max.first)
    head.first = 0;
  if (head.first == -1)
    head.first = this->_max.first - 1;
  if (head.second == this->_max.second)
    head.second = 0;
  if (head.second == -1)
    head.second = this->_max.second;
  snake->setPoshead(head.first, head.second);
  if (str[head.first + head.second * this->_max.first] == '2' || *grow > 0)
    {
      newSnake.push_back(std::pair<int, int>(it->first, it->second)); 
      if (*grow > 0)
	*grow = *grow - 1;
      if (str[head.first + head.second * this->_max.first] == '2')
	{
	  str[head.first + head.second * this->_max.first] = '0';
	  if (_Isxgrow == true)
	    *grow = *grow + xrandom(3);
	  *food = 0;
	  _score = _score + 1;
	}
    }
  if (str[head.first + head.second * this->_max.first] == '3')
    {
      *d = 0;
      *b = xrandom(100) + 10;
      newSnake.push_back(std::pair<int, int>(it->first, it->second)); 
      str[head.first + head.second * this->_max.first] = '0';
      _score = _score + 10;
    }
  snake->setSnake(newSnake);
  if (str[head.first + head.second * this->_max.first] == '1' || snake->test(head.first, head.second) == 1)
      return ("");
  return (str);
}

void Game::launch(std::string map)
{
  int	nround = 0;
  int	grow = 0;
  char	food = 1;
  char touch = 'a';
  long	b = xrandom(100) + 10;
  long	c;
  bool	d = 0;

  map = put_food(map, '2');
  while (!display->displayGame(this->_max.second, this->_max.first, (char*)map.c_str(), this->_snake))
    {
      touch = 'a';
      my_sleep_for_snake(nround++);
      display->getInput(&touch);
      map = my_food(&b, &c, &d, map, &food);
      if (touch == 'E')
	break;
      else if (touch != 'a')
	this->_snake->changeDirection(touch);
      if ((map = round(this->_snake, &food, map, &b, &d, &grow)) == "")
	break;
    }
  delete this->_snake;
  display->displayEnd(this->_max.second, this->_max.first);
}

Game::Game(int width, int height)
{
  this->_max = std::pair<int,int>(width, height);
  this->_snake = new Snake(this->_max, true);
  this->_score = 0;
  this->_Isxgrow = false;
}

Game::~Game()
{
}

void	Game::setName(std::string name)
{
  _name = name;
}

void	Game::setScore(int score)
{
  _score = score;
}

void	Game::setIsacceleration(bool a)
{
  _Isacceleration = a;
}

void	Game::setIsxgrow(bool a)
{
  _Isxgrow = a;
}

std::string	Game::getName() const
{
  return _name;
}

int	Game::getScore() const
{
  return _score;
}

bool	Game::getIsacceleration() const
{
  return _Isacceleration;
}

bool	Game::getIsxgrow() const
{
  return _Isxgrow;
}
