//
// Graphic.hh for cpp_nibbler in /home/ambroi_s/rendu/cpp_nibbler
// 
// Made by Simon Ambroise
// Login   <ambroi_s@epitech.net>
// 
// Started on  jeu. avril 02 13:17:34 2015 Simon Ambroise
// Last update Sun Apr  5 18:28:16 2015 Benjamin Curlier
//

#ifndef __GRAPHIC_HH__
#define __GRAPHIC_HH__

#include <string>
#include "Snake.hh"

class Graphic
{
private:
  std::string _libName;
public:
  Graphic(std::string);
  ~Graphic();
  bool isExisting();
  bool displayGame(int, int, char*, Snake*);
  bool displayGame_two_player(int, int, char*, Snake*, Snake*);
  bool displayMenu(int,int, char);
  bool displayOption(int,int, char);
  bool displayEnd(int,int);
  void getInput(char *);
  void getInput_two_player(char *, char *);
  bool getInputGame(char *);
  void init(int, int);
  void *_library;
  bool _isExistant;
};

#endif /* __GRAPHIC_HH__*/
