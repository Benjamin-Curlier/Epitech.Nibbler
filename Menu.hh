#ifndef _MENU_
#define _MENU_

#include <map>
#include "include.hh"
#include "Snake.hh"

class Menu
{
public:
  Menu(int, int);
  ~Menu();
  void	start();
  void	setMap(std::string);
  std::string	getMap() const;
  std::map<std::string, int> getScore() const;
  void	setMulti(bool);
  bool	getMulti() const;
  void 	options();
private:
  class Option
  {
    Option();
    ~Option();
    void Choose_map();
    void Set_movespeed();
  };
  std::string _map;
  std::map<std::string, int> _highscore;
  int 	_width;
  int 	_height;
  bool	_multi;
  bool 	_grow;
  bool 	_accel;
};

#endif
