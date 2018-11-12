##
## Makefile for cpp_nibbler in /home/ambroi_s/rendu/cpp_nibbler
## 
## Made by Simon Ambroise
## Login   <ambroi_s@epitech.net>
## 
## Started on  mar. mars 24 12:49:23 2015 Simon Ambroise
## Last update dim. avril 05 23:26:48 2015 
##

SRC	= 	main.cpp \
		Snake.cpp \
		Menu.cpp \
		Game.cpp \
		Game2.cpp \
		Game3.cpp \
		Game4.cpp \
		xfunction.cpp \
		Graphic.cpp \

SRCSDL 	=	./SDL/SDL_snake.cpp \
		./xfunction.cpp \

NAME	= nibbler

SDLNAME = ./GraphicLibrary/lib_nibbler_sdl.so

FLAG	= -Wall -Wextra -W -g -fPIC -Werror
FLAG 	+=  -lSDL2 -ldl

LDFLAGS += $(FLAG)

CPPFLAGS = $(FLAG)

OBJ	= $(SRC:.cpp=.o)

OBJSDL	= $(SRCSDL:.cpp=.o)

RM	= rm -f

CC	= g++

all: $(NAME) $(SDLNAME)

$(SDLNAME): $(OBJSDL)
	$(CC) -o $(SDLNAME) $(OBJSDL) -shared -lSDL2

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ) *.swp *~ $(OBJSDL)

fclean: clean
	$(RM) $(NAME) $(SDLNAME)

re: fclean all

.PHONY: all clean fclean re

