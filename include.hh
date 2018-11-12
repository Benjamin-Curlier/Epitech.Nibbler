#ifndef _DEFINE_
#define _DEFINE_

#include "Snake.hh"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

bool			end(int, int);
void			close();
int			xrandom(int i);
int			create(int, int);
bool			game(int, int, char*, Snake*);
char			getInput(char *);
bool			menu(int, int);

#endif
