//
// lib_ncurses.cpp for arcade in /home/costa_d/Documents/TEK2/CPP/Arcad/cpp_arcade
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Tue Mar 21 16:15:10 2017 Arnaud Costa
// Last update Sun Apr  9 21:17:56 2017 Arnaud Costa
//

#include "libNcurses.hh"

libNcurses::libNcurses()
{}

libNcurses::~libNcurses()
{}

int	libNcurses::createWindow()
{
  initscr();
  keypad(stdscr, true);
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  set_escdelay(1);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(7, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(10, COLOR_BLUE, COLOR_BLACK);
  refresh();
  return (0);
}

void	libNcurses::closeWindow()
{
  endwin();
  return ;
}

void	libNcurses::cleanWindow()
{
  clear();
  return ;
}

void	libNcurses::refreshWindow()
{
  refresh();
  return ;
}

int	libNcurses::printElem(elem Cet_elem)
{
  start_color();
  attron(COLOR_PAIR(static_cast<int>(Cet_elem.type) + 1));
  mvprintw(Cet_elem.pos.y * 2, Cet_elem.pos.x * 2, "**");
  mvprintw(Cet_elem.pos.y * 2 + 1, Cet_elem.pos.x * 2, "**");
  attroff(COLOR_PAIR(static_cast<int>(Cet_elem.type) + 1));
  return (0);
}

int	libNcurses::getEvent()
{
  size_t	key;

  key = getch();
  if (key < 128)
    return (key);
  return (0);
}

extern "C"
{
  IDisplayModule	*entryPoint()
  {
    return (new libNcurses());
  }
}

int	libNcurses::printMap(std::vector<std::string> map)
{
  const char		*parce;
  std::string		ligne;
  size_t		x;
  size_t		y;
  size_t		i;
  std::vector<std::string>::iterator it;

  it = map.begin();
  y = 0;
  while (it != map.end())
    {
      ligne = *it;
      parce = ligne.c_str();
      x = 0;
      i = 0;
      while (parce[i] != '\0')
  	{
  	  if (parce[i] == '1')
	    {
	      attron(COLOR_PAIR(10));
	      mvprintw(y, x, "##");
	      mvprintw(y + 1, x, "##");
	      attroff(COLOR_PAIR(10));
	    }
  	  else if (parce[i] == '0')
	    {
	      mvprintw(y, x, "  ");
	      mvprintw(y + 1, x, "  ");
	    }
  	  i++;
  	  x += 2;
  	}
      y += 2;
      ++it;
    }
  return (0);
}

int	libNcurses::printText(int x, int y, std::string text)
{
  mvprintw(y / 16, x / 16, "%s", text.c_str());
  return (0);
}
