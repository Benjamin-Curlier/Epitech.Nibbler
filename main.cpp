//
// main.cpp for snake in /home/ambroi_s/rendu/snake
// 
// Made by Simon Ambroise
// Login   <ambroi_s@epitech.net>
// 
// Started on  lun. mars 23 14:49:59 2015 Simon Ambroise
// Last update Tue Mar 31 21:45:57 2015 Benjamin Curlier
//

#include <sstream>
#include "Menu.hh"
#include "Graphic.hh"
#include "include.hh"

extern Graphic *display;

int	main(int ac, char **av)
{
  Menu 	*menu;
  int 	ymax;
  int 	xmax;
  std::istringstream *ss;

  try
    {
      if (ac == 4)
	{
	  display = new Graphic(av[3]);
	  if (display->_isExistant == false)
	    return (-1);
	  ss = new std::istringstream(av[1]);
	  *ss >> xmax;
	  delete ss;
	  ss = new std::istringstream(av[2]);
	  *ss >> ymax;
	  delete ss;
	  menu = new Menu(xmax, ymax);
	  menu->start();
	  delete menu;
	}
    }
  catch (const std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }
  return (0);
}
