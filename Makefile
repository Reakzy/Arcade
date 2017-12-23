##
## Makefile for santa in /home/costa_d/Documents/TEK2/cpp_santa
## 
## Made by Arnaud Costa
## Login   <costa_d@epitech.net>
## 
## Started on  Sun Jan 15 01:56:26 2017 Arnaud Costa
## Last update Sun Apr  9 19:40:16 2017 Arnaud Costa
##

CC			= g++

RM			= rm -f

MK			= mkdir

CPPFLAGS		= -Iinclude -std=c++11 -I/home/${USER}/.froot/include -g

SFMLFLAGS		= -lsfml-graphics -lsfml-window -lsfml-system

NCURSESFLAGS		= -lncurses

LAPINFLAGS		= -L/home/${USER}/.froot/lib	\
			  -llapin -lsfml-audio		\
			  -lsfml-graphics -lsfml-window \
			  -lsfml-system -lstdc++	\
		   	  -ldl -lm

SRCDIR			= src/

OBJDIR			= obj/

LIBDIR			= lib/

GAMEDIR			= games/

OBJLIBDIR		= obj_lib/

SRCLIBDIR		= src_lib/

CORE_NAME		= arcade

SFML_NAME		= lib_arcade_sfml.so

NCURSES_NAME		= lib_arcade_ncurses.so

LAPIN_NAME		= lib_arcade_liblapin.so

PACMAN_NAME		= lib_arcade_pacman.so

SNAKE_NAME		= lib_arcade_snake.so

CORE_SRCS		= main.cpp Core.cpp DLLoader.cpp

LIB_SFML_SRCS		= libSfml.cpp

LIB_LAPIN_SRCS		= lib_liblapin.cpp

LIB_NCURSES_SRCS	= libNcurses.cpp

PACMAN_SRCS		= pacman.cpp

SNAKE_SRCS		= snake.cpp

OBJS			= $(addprefix $(OBJDIR), $(CORE_SRCS:.cpp=.o))

LIB_SFML_OBJS		= $(addprefix $(OBJLIBDIR), $(LIB_SFML_SRCS:.cpp=.o))

LIB_NCURSES_OBJS 	= $(addprefix $(OBJLIBDIR), $(LIB_NCURSES_SRCS:.cpp=.o))

LIB_LAPIN_OBJS 		= $(addprefix $(OBJLIBDIR), $(LIB_LAPIN_SRCS:.cpp=.o))

PACMAN_OBJS 		= $(addprefix $(OBJLIBDIR), $(PACMAN_SRCS:.cpp=.o))

SNAKE_OBJS 		= $(addprefix $(OBJLIBDIR), $(SNAKE_SRCS:.cpp=.o))

all:			$(CORE_NAME) $(PACMAN_NAME) $(SNAKE_NAME)

$(CORE_NAME):		$(OBJS)
			$(CC) -o $(CORE_NAME) $(OBJS) -ldl

$(SFML_NAME):		$(LIB_SFML_OBJS)
			$(CC) -shared $(LIB_SFML_OBJS) -o $(addprefix $(LIBDIR), $(SFML_NAME)) $(SFMLFLAGS)

$(NCURSES_NAME):	$(LIB_NCURSES_OBJS)
			$(CC) -shared $(LIB_NCURSES_OBJS) -o $(addprefix $(LIBDIR), $(NCURSES_NAME)) $(NCURSESFLAGS)

$(LAPIN_NAME):		$(LIB_LAPIN_OBJS)
			$(CC) -shared $(LIB_LAPIN_OBJS) -o $(addprefix $(LIBDIR), $(LAPIN_NAME)) $(LAPINFLAGS)

$(PACMAN_NAME):		$(PACMAN_OBJS)
			$(CC) -shared $(PACMAN_OBJS) -o $(addprefix $(GAMEDIR), $(PACMAN_NAME))

$(SNAKE_NAME):		$(SNAKE_OBJS)
			$(CC) -shared $(SNAKE_OBJS) -o $(GAMEDIR)$(SNAKE_NAME)

$(OBJDIR)%.o:   	$(SRCDIR)%.cpp
			@$(MK) -p $(OBJDIR)
			@echo -n "Linkag Core Programme" $(notdir $<);
	        	@$(CC) $(CPPFLAGS) -c $< -o $@ &&						\
			(tput hpa $$(($$(tput cols) - 12)); echo "-=[\033[32m  OK  \033[39m]=-") ||	\
			(tput hpa $$(($$(tput cols) - 12)); echo "-=[\033[31m FAIL \033[39m]=-")

$(OBJLIBDIR)%.o: 	$(SRCLIBDIR)%.cpp
			@$(MK) -p $(OBJLIBDIR)
			@$(MK) -p $(GAMEDIR)
			@$(MK) -p $(LIBDIR)
			@echo -n "Linkag Lib" $(notdir $<);
	        	@$(CC) -c -fPIC $(CPPFLAGS) $< -o $@ &&						\
			(tput hpa $$(($$(tput cols) - 12)); echo "-=[\033[32m  OK  \033[39m]=-") ||	\
			(tput hpa $$(($$(tput cols) - 12)); echo "-=[\033[31m FAIL \033[39m]=-")

core:			$(CORE_NAME)

lib:			$(SFML_NAME) $(NCURSES_NAME) $(LAPIN_NAME)

game:           $(PACMAN_NAME) $(SNAKE_NAME)

sfml:			$(SFML_NAME)

ncurses:		$(NCURSES_NAME)

lapin:			$(LAPIN_NAME)

pacman:			$(PACMAN_NAME)

snake:			$(SNAKE_NAME)

clean:
			$(RM) $(OBJS) $(LIB_OBJS)
			$(RM) -r $(OBJDIR) $(OBJLIBDIR)
cleanlib:
			$(RM) $(LIB_SFML_OBJS) $(LIB_NCURSES_OBJS) $(LIB_LAPIN_OBJS)
			$(RM) -r $(OBJLIBDIR)

fclean:			clean
			$(RM) $(CORE_NAME)

fcleanlib:		cleanlib
			$(RM) -r $(LIBDIR)

fcleangame:
			$(RM) -r $(GAMEDIR)

re:			fclean all

.PHONY:			all clean fclean re
