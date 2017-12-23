//
// elem.hpp for arcade in /home/costa_d/Documents/TEK2/CPP/Arcad/cpp_arcade
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Thu Mar 23 18:33:33 2017 Arnaud Costa
// Last update Tue Mar 28 15:42:24 2017 Arnaud Costa
//

#ifndef ARCADE_ELEM_HPP
# define ARCADE_ELEM_HPP

# include "Protocol.hpp"

typedef struct		s_elem
{
  arcade::Position      pos;
  arcade::TileType      type;
  int                   direction;
  std::string		sprite;
}			elem;

#endif /* ARCADE_ELEM_HPP */
