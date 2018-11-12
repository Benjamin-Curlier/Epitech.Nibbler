#include <vector>
#include <utility>
#include <map>
#include "Snake.hh"
#include <cmath>
#include "include.hh"
#include <unistd.h>
void	Snake::changeDirectionIA(std::string str, int x)
{
  int fx = str.find('2') % x;;
  int fy = str.find('2') / x;
  int	vx = -(_poshead.first - fx);
  int	vy = -(_poshead.second - fy);
 

  if (std::abs(vx) - std::abs(vy) > 0)
    {
      if (vx != 0)
	{
	  if (vx > 0 && test(_poshead.first + 1, _poshead.second) == 0)
	    {
	      _direction = '1';
	      return;
	    }
	  if (vx < 0 && test(_poshead.first - 1, _poshead.second) == 0)
	    {
	      _direction = '2';
	      return;
	    }
	}
      if (vy != 0)
	{
	  if (vy > 0 && test(_poshead.first, _poshead.second + 1) == 0)
	    {
	      _direction = '0';
	      return;
	    }
	  if (vy < 0 && test(_poshead.first, _poshead.second - 1) == 0)
	    {
	      _direction = '3';
	      return;
	    }
	}
    }
  if (vy != 0)
    {
      if (vy > 0 && test(_poshead.first, _poshead.second + 1) == 0)
	{
	  _direction = '0';
	  return;
	}
      if (vy < 0 && test(_poshead.first, _poshead.second - 1) == 0)
	{
	  _direction = '3';
	  return;
	}
    }
  if (vx != 0)
    {
      if (vx > 0 && test(_poshead.first + 1, _poshead.second) == 0)
	{
	  _direction = '1';
	  return;
	    }
      if (vx < 0 && test(_poshead.first - 1, _poshead.second) == 0)
	{
	  _direction = '2';
	  return;
	}
    }
  int i = 0;
  int a;
  while (i++ != 1000)
    {
      a = xrandom(4);
      if (a == 0 && test(_poshead.first, _poshead.second + 1) == 0)
	{
	  _direction = '0';
	  return;
	}
      if (a == 1 && test(_poshead.first + 1, _poshead.second) == 0)
	{
	  _direction = '1';
	  return;
	}
      if (a == 2 && test(_poshead.first - 1, _poshead.second) == 0)
	{
	  _direction = '2';
	  return;
	}
      if (a == 3 && test(_poshead.first, _poshead.second - 1) == 0)
	{
	  _direction = '3';
	  return;
	}
    }
}

Snake::Snake(std::pair<int,int> max, bool a)
{
  this->_poshead.first = max.first / 2;
  this->_poshead.second = max.second / 2;
  if (a == true)
    {
      this->_poshead.first += 3;
      this->_direction = '2';
      this->_snake.push_back(std::pair<int,int>(this->_poshead.first + 1, this->_poshead.second));
      this->_snake.push_back(std::pair<int,int>(this->_poshead.first + 2, this->_poshead.second));
      this->_snake.push_back(std::pair<int,int>(this->_poshead.first + 3, this->_poshead.second));
    }
  else
    {
      this->_poshead.first -= 3;
      this->_direction = '3';
      this->_snake.push_back(std::pair<int,int>(this->_poshead.first - 1, this->_poshead.second));
      this->_snake.push_back(std::pair<int,int>(this->_poshead.first - 2, this->_poshead.second));
      this->_snake.push_back(std::pair<int,int>(this->_poshead.first - 3, this->_poshead.second));
    }
}

Snake::~Snake()
{
}

void	Snake::setSnake(std::vector<std::pair<int, int> > snake)
{
  _snake = snake;
}

void	Snake::setDirection(char direction)
{
  _direction = direction;
}

void	Snake::setMovespeed(int movespeed)
{
  _movespeed = movespeed;
}

void	Snake::setHead(char head)
{
  _head = head;
}

void	Snake::setPoshead(int x, int y)
{
  _poshead.first = x;
  _poshead.second = y;
}

std::vector<std::pair<int, int> > Snake::getSnake() const
{
  return (_snake);
}

void	Snake::changeDirection(char touch)
{
  if (touch == '4' && _direction == '0')
    _direction = '1';
  else if (touch == '4' && _direction == '1')
    _direction = '3';
  else if (touch == '4' && _direction == '2')
    _direction = '0';
  else if (touch == '4' && _direction == '3')
    _direction = '2';
  else if (touch == '5' && _direction == '0')
    _direction = '2';
  else if (touch == '5' && _direction == '1')
    _direction = '0';
  else if (touch == '5' && _direction == '2')
    _direction = '3';
  else if (touch == '5' && _direction == '3')
    _direction = '1';
}

char	Snake::getDirection() const
{
  return (_direction);
}

int	Snake::getMovespeed() const
{
  return (_movespeed);
}

char	Snake::getHead() const
{
  return (_head);
}

std::pair<int,int> Snake::getPoshead() const
{
  return (_poshead);
}

bool	Snake::test(int x, int y)
{
  for (std::vector<std::pair<int, int> >::iterator it = this->_snake.begin(); it != this->_snake.end(); ++it)
    if (it->first == x && it->second == y)
      return (1);
  return (0);
}

bool	Snake::test2(int x, int y)
{
  if (_poshead.first == x && _poshead.second == y)
    return (1);
  return (0);
}
