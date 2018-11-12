#ifndef _GAME_
#define _GAME_

#include "include.hh"
#include "Snake.hh"

class Game
{
private:
  int _score;
  std::string _name;
  std::pair<int,int> _max;
  Snake *_snake;
  Snake *_snake2;
  bool	_Isacceleration;
  bool  _Isxgrow;
public:
  Game(int, int);
  Game(int, int, bool);
  ~Game();
  void	launch(std::string map);
  void	launch_IA(std::string map);
  void	launch_two_player(std::string map);
  void	setName(std::string);
  void	setScore(int);
  void	setIsacceleration(bool);
  std::string	getName() const;
  int	getScore() const;
  bool	getIsacceleration() const;
  bool	getIsxgrow() const;
  void	setIsxgrow(bool) ;
private:
  std::string	round_two_palyer(Snake *, char *, std::string, long *, bool *, int *, bool);
  std::string	my_food_two_player(long *b, long *c, bool *d, std::string map, char *food);
  std::string	put_food_two_player(std::string str, char food);
  void	my_sleep_for_snake(int);
  std::string	my_food(long *b, long *c, bool *d, std::string map, char *food);
  bool	test_bonus_food(std::string);
  std::string	remove_bonus_food(std::string);
  std::string	round(Snake *snake, char *food, std::string str, long *, bool *, int *);
  std::string	put_food(std::string str, char);
};

#endif
