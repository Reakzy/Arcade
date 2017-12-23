//
// core.hpp for arcade in /home/costa_d/Documents/TEK2/CPP/Arcad/cpp_arcade/include
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Tue Mar 21 16:36:00 2017 Arnaud Costa
// Last update Fri Mar 31 10:22:53 2017 Arnaud Costa
//

#ifndef CORE_HPP
# define CORE_HPP

# include <dirent.h>
# include <string>
# include <iostream>
# include <sstream>
# include <vector>
# include "DLLoader.hpp"
# include "Protocol.hpp"
# include "Elem.hh"

class	Core
{
  std::vector<std::string>		libsListPath;
  std::vector<std::string>		gamesListPath;
  std::vector<std::string>::iterator	itLib;
  std::vector<std::string>::iterator	itGame;
  size_t				key;
  size_t				start;
  size_t 				gameMenuPos;
  size_t 				libMenuPos;
  std::string 				curentGame;
  DLLoader				libLoad;
  DLLoader				gameLoad;
  IDisplayModule			*lib;
  IGameModule				*game;
  std::string				nickname;
 public:
  Core();
  Core(const Core &other) = delete;
  Core &operator=(const Core &other) = delete;
  ~Core();
  void	mainCore(std::string lib_path);
  int	swapLib(std::string lib_path);
  int	swapGame(std::string gamePath);
  int	loadGame(std::string game);
  void 	exitCore();
  int	setLibListPath();
  int	setGameListPath();
  int	printElemList();
  int	keyManager();
  int	printPseudo();
  void	libManager();
  int	gameManager();
  int	menu();
  void	moveplayer();
  int 	libKeyManager(size_t tmpKey);
  void	printLibList(size_t x, size_t y);
  int	printGameList(size_t x, size_t y);
  void 	printMenu();
  void  youLoose();
  void youWin();
};

#endif /* CORE_HPP */
