#include <vector>
#include <utility>
#include <unistd.h>
#include <tr1/tuple>
#include "Game.hh"
#include "Graphic.hh"
#include "Snake.hh"

extern Graphic *display;

void	Game::launch_IA(std::string map)
{
  int	grow = 0;
  char	food = 1;
  long	b = xrandom(100) + 10;
  long	c;
  bool	d = 0;

  map = put_food(map, '2');
  while (!display->displayGame(this->_max.second, this->_max.first, (char*)map.c_str(), this->_snake))
    {
      usleep(100000);
      if (food == 0)
	{
	  map = put_food(map, '2');
	  food = food + 1;
	}
      map = my_food(&b, &c, &d, map, &food);
      this->_snake->changeDirectionIA(map, _max.first);
      if ((map = round(this->_snake, &food, map, &b, &d, &grow)) == "")
	break;
    }
  delete this->_snake;
}
