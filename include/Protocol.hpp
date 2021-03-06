//
// Protocol.hpp for Arcade in /home/costa_d/Documents/TEK2/CPP/Arcad/bootstrap/cpp_arcade
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Tue Mar 14 14:24:26 2017 Arnaud Costa
// Last update Tue Mar 28 19:59:14 2017 Arnaud Costa
//

#ifndef __ARCADE_PROTOCOL_HPP__
# define __ARCADE_PROTOCOL_HPP__

# include <stdint.h>

namespace arcade
{
  enum class CommandType: uint16_t
  {
    WHERE_AM_I = 0,
      GET_MAP = 1,
      GO_UP = 2,
      GO_DOWN = 3,
      GO_LEFT = 4,
      GO_RIGHT = 5,
      GO_FORWARD = 6,
      SHOOT = 7,
      ILLEGAL = 8,
      PLAY = 9
      };

  enum class TileType: uint16_t
  {
    EMPTY = 0,
      BLOCK = 1,
      OBSTACLE = 2,
      EVIL_DUDE = 3,
      EVIL_SHOOT = 4,
      MY_SHOOT = 5,
      POWERUP = 6,
      OTHER = 7
      };

  struct GetMap
  {
    CommandType	type;
    uint16_t	width;
    uint16_t	height;
    TileType	tile[0];
  } __attribute__ ((packed));

  struct	Position
  {
    uint16_t	x;
    uint16_t	y;
  } __attribute__ ((packed));

  struct	WhereAmI
  {
    CommandType	type;
    uint16_t	lenght;
    Position	position[0];
  } __attribute__ ((packed));
}

#endif /* __ARCADE_PROTOCOL_HPP__ */
