//
// Created by alis_a on 3/14/17.
//

#ifndef ARCADE_LIB_NCURSES_HPP
# define ARCADE_LIB_NCURSES_HPP

# include <iostream>
# include <curses.h>
# include "IDisplayModule.hh"

class libNcurses: public IDisplayModule
{
 public:
  libNcurses();
  libNcurses(const libNcurses &other) = delete;
  libNcurses &operator=(const libNcurses &other) = delete;
  virtual ~libNcurses();
  virtual int   createWindow();
  virtual void  closeWindow();
  virtual void  cleanWindow();
  virtual void  refreshWindow();
  virtual int	printElem(elem Cet_elem);
  virtual int	getEvent();
  virtual int   printMap(std::vector<std::string> map);
  virtual int   printText(int x, int y, std::string text);
};

extern "C" IDisplayModule	*entry_point();

#endif //ARCADE_LIB_NCURSES_HPP
