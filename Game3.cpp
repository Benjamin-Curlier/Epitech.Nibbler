#include <vector>
#include <utility>
#include <unistd.h>
#include <tr1/tuple>
#include "Game.hh"
#include "Graphic.hh"

extern Graphic *display;

std::string	Game::round_two_palyer(Snake *snake, char *food, std::string str, long *b, bool *d, int *grow, bool one)
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
  if (one == 1)
    {
      if (str[head.first + head.second * this->_max.first] == '1' || snake->test(head.first, head.second) == 1 || _snake2->test(head.first, head.second) == 1 || _snake2->test2(head.first, head.second) == 1)
	return ("");
    }
  else
    {
      if (str[head.first + head.second * this->_max.first] == '1' || snake->test(head.first, head.second) == 1 || _snake->test(head.first, head.second) == 1 || _snake->test2(head.first, head.second) == 1)
	return ("");
    }
  return (str);
}

std::string	Game::my_food_two_player(long *b, long *c, bool *d, std::string map, char *food)
{
  if (*c > 0 && *d == 1)
    *c = *c -1;
  else if (*c == 0 && *d == 1)
    {
      *d = 0;
      *b = xrandom(100) + 10;
      map = remove_bonus_food(map);
    }
  *b = *b - 1;
  if (*b == 0 && test_bonus_food(map) == 0)
    {
      *d = 1;
      *c = (_max.second + _max.first) / 2;
      map = put_food_two_player(map, '3');
    }
  if (*food == 0)
    {
      map = put_food_two_player(map, '2');
      *food = *food + 1;
    }
  return (map);
}

std::string	Game::put_food_two_player(std::string str, char food)
{
  int	x = xrandom(this->_max.first);
  int	y = xrandom(this->_max.second);

  while (1)
    {
      if (str[x + this->_max.first * y] == '0' && this->_snake->test(x, y) == 0 && this->_snake->test2(x, y) == 0 && this->_snake2->test(x, y) == 0 && this->_snake2->test2(x, y) == 0)
	{
	  str[x + this->_max.first * y] = food;
	  return (str);
	}
      x = xrandom(this->_max.first);
      y = xrandom(this->_max.second);
    }
  return NULL;
}


void	Game::launch_two_player(std::string map)
{
  int	nround = 0;
  int	grow = 0;
  char	food = 1;
  char	touch;
  char	touch2;
  long	b = xrandom(100) + 10;
  long	c;
  bool	d = 0;

  map = put_food(map, '2');
  while (!display->displayGame_two_player(_max.second, _max.first, (char*)map.c_str(), _snake, _snake2))
    {
      touch = 'a';
      touch2 = 'a';
      my_sleep_for_snake(nround++);
      display->getInput_two_player(&touch, &touch2);
      map = my_food_two_player(&b, &c, &d, map, &food);
      if (touch == 'E')
	break;
      if (touch != 'a')
	this->_snake->changeDirection(touch);
      if (touch2 != 'a')
	this->_snake2->changeDirection(touch2);
      if ((map = round_two_palyer(this->_snake, &food, map, &b, &d, &grow, true)) == "")
	break;
      if ((map = round_two_palyer(this->_snake2, &food, map, &b, &d, &grow, false)) == "")
	break;
    }
  delete this->_snake;
  display->displayEnd(this->_max.second, this->_max.first);
}

Game::Game(int widht,int height, bool a)
{
  (void)a;
  this->_max = std::pair<int,int>(widht, height);
  this->_snake = new Snake(this->_max, false);
  this->_snake2 = new Snake(this->_max, true);
  this->_score = 0;
}
