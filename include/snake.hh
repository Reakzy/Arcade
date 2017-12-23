//
// Created by counil_m on 25/03/17.
//

#ifndef CPP_ARCADE_SNAKE_HPP
#define CPP_ARCADE_SNAKE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Protocol.hpp"
#include "Elem.hh"
#include "IGameModule.hh"

class Snake : public IGameModule
{
  int 					score;
  int 					powerUp;
  std::vector<elem>			elemList;
  std::vector<std::string>		map;
public:
  Snake();
  Snake(const Snake &other) = delete;
  Snake &operator=(const Snake &other) = delete;
  virtual ~Snake();
  virtual int				getScore() const;
  virtual std::vector<elem>		getElemList() const;
  virtual std::vector<std::string>	getMap() const;
  virtual int     			update(int direction);
  int     canMove(arcade::Position pos, int elemPos, int move);
  int     moveTo(arcade::Position pos, int elemPos, int move);
  int     takePowerUp();
  int	  isColider();
  void    incScore(int plus);
  void    createMap();
  elem    createElem(int x, int y, arcade::TileType type, int direction, std::string path);
  void    createElemList();
  void    eraseElem(elem *elem);
};

#endif //CPP_ARCADE_SNAKE_HPP
