#include <vector>
#include <utility>
#include <unistd.h>
#include <tr1/tuple>
#include "Game.hh"
#include "Graphic.hh"

extern Graphic *display;

void	Game::my_sleep_for_snake(int a)
{
  if (_Isacceleration == 0)
    usleep(350000);
  else
    {
      if (500000 - a * 700 - _score * 4000 > 150000)
	usleep(500000 - a * 700 - _score * 4000);
      else
	usleep(150000);
    }
}

std::string	Game::my_food(long *b, long *c, bool *d, std::string map, char *food)
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
      map = put_food(map, '3');
    }
  if (*food == 0)
    {
      map = put_food(map, '2');
      *food = *food + 1;
    }
  return (map);
}

bool	Game::test_bonus_food(std::string map)
{
  if ((int)map.find('3') == -1)
    return (0);
  return (1);
}

std::string	Game::remove_bonus_food(std::string str)
{
  str[str.find('3')] = '0';
  return (str);
}

std::string	Game::put_food(std::string str, char food)
{
  int	x = xrandom(this->_max.first);
  int	y = xrandom(this->_max.second);

  while (1)
    {
      if (str[x + this->_max.first * y] == '0' && this->_snake->test(x, y) == 0 && this->_snake->test2(x, y) == 0)
	{
	  str[x + this->_max.first * y] = food;
	  return (str);
	}
      x = xrandom(this->_max.first);
      y = xrandom(this->_max.second);
    }
  return NULL;
}
