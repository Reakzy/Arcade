//
// Created by counil_m on 23/03/17.
//

#ifndef CPP_ARCADE_LIB_LIBLAPIN_HPP
# define CPP_ARCADE_LIB_LIBLAPIN_HPP

# include <iostream>
# include <lapin.h>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <sstream>
# include "IDisplayModule.hh"

class libLiblapin: public IDisplayModule
{
  struct                          bunny_window
  {
    size_t                        type;
    sf::RenderWindow              *window;
    size_t                       width;
    size_t                       height;
    const char                    *window_name;
  };

  std::vector<std::vector<elem>>  		map;
  std::map<std::string, t_bunny_picture*>	load;
  t_bunny_window    *window;
  char               key;
  int			cnt;
  t_bunny_picture		*font;
  t_bunny_picture 		  *wall;
  t_bunny_picture 		  *floor;

public:
  libLiblapin();
  libLiblapin(const libLiblapin &other) = delete;
  libLiblapin &operator=(const libLiblapin &other) = delete;
  virtual ~libLiblapin();
  virtual int   createWindow();
  virtual void  closeWindow();
  virtual void  cleanWindow();
  virtual void  refreshWindow();
  virtual int	printElem(elem CetElem);
  virtual int	getEvent();
  virtual int	printMap(std::vector<std::string> map);
  virtual int   printText(int x, int y, std::string text);
};

extern "C" IDisplayModule	*entry_point();

#endif /* CPP_ARCADE_LIB_LIBLAPIN_HPP */
