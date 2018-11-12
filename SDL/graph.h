/*
** graph.h for PSU_2014_lemipc in /home/camila/rendu/PSU_2014_lemipc
**
** Made by Camila Chabane
** Login  <@epitech.eu>
**
** Started on  dim. mars 08 17:53:39 2015 
** Last update dim. avril 05 20:48:42 2015 
*/

#ifndef GRAPH_H_
# define GRAPH_H_

#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <math.h>
#include <float.h>
#include <iostream>
#include <string>

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gStretchedSurface;

int xrandom(int);
void init();
void Close();
int getPosX(int x);
int getPosY(int y);
int addYou(int nb, char *file);
void Do(char*);
int getNbChar(char *, char);

#endif /* !GRAPH_H_ */
