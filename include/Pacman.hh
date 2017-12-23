//
// Created by alis_a on 3/22/17.
//

#ifndef ARCADE_PACMAN_HPP
#define ARCADE_PACMAN_HPP

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Protocol.hpp"
#include "Elem.hh"
#include "IGameModule.hh"

class Pacman : public IGameModule
{
  int 					score;
  int 					powerUp;
  int					gum;
  std::vector<elem>			elemList;
  std::vector<std::string>		map;
 public:
  Pacman();
  Pacman(const Pacman &other) = delete;
  Pacman &operator=(const Pacman &other) = delete;
  virtual ~Pacman();
  virtual int				getScore() const;
  virtual std::vector<elem>		getElemList() const;
  virtual std::vector<std::string>	getMap() const;
  virtual int     			update(int direction);
  void					powerUpActive();
  void					powerUpUnactive();
  int					checkCollision();
  void    				updateEnemies(int num);
  void    				findEnemies();
  int     				canMove(arcade::Position pos, int elemPos, int move);
  int     				moveTo(arcade::Position pos, int elemPos, int move, int canRotate);
  void    				takePowerUp();
  void    				incScore(int plus);
  void					createMap();
  elem    				createElem(int x, int y, arcade::TileType type, int direction, std::string path);
  void					createElemList();
  void    				eraseElem(elem *elem);
};

#endif /* ARCADE_PACMAN_HPP */
