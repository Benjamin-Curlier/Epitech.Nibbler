#ifndef _SNAKE_
#define _SNAKE_

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Snake
{
public:
  Snake(std::pair<int,int>, bool);
  ~Snake();
  void	setSnake(std::vector<std::pair<int, int> >);
  void	setDirection(char);
  void	setMovespeed(int);
  void	setHead(char);
  void	setPoshead(int, int);
  std::vector<std::pair<int, int> > getSnake() const;
  char	getDirection() const;
  int	getMovespeed() const;
  char	getHead() const;
  void	changeDirectionIA(std::string, int);
  std::pair<int,int>	getPoshead() const;
  bool	test(int x, int y);
  bool	test2(int x, int y);
  void	changeDirection(char);
private:
  std::vector<std::pair<int, int> > _snake;
  char	_direction;
  int	_movespeed;
  char	_head;
  std::pair<int, int> _poshead;
};

#endif
