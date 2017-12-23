//
// core.cpp for arcade in /home/costa_d/Documents/TEK2/CPP/Arcad/cpp_arcade/src
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Tue Mar 21 16:46:05 2017 Arnaud Costa
// Last update Sat Apr  1 15:02:25 2017 Arnaud Costa
//

#include <chrono>
#include <thread>
#include <algorithm>
#include "Core.hh"

Core::Core()
{
  this->key = 0;
  this->start = 0;
  this->gameMenuPos = 0;
  this->libMenuPos = 0;
}

Core::~Core() {}

void	Core::libManager()
{
  size_t	tmp;

  if (this->key == 51)
    {
      if (this->itLib == this->libsListPath.end())
	this->itLib = this->libsListPath.begin();
      if (this->swapLib(*itLib) == -1)
	return ;
      ++this->itLib;
    }
  if (key == 50)
    {
      tmp = 0;
      if (this->itLib == this->libsListPath.begin())
	{
	  this->itLib = this->libsListPath.end();
	  --this->itLib;
	  tmp = 1;
	}
      if (tmp == 0)
	--this->itLib;
      if (this->swapLib(*itLib) == -1)
	return ;
    }
  return ;
}

void Core::youLoose()
{
  std::stringstream	s;

  s << game->getScore();
  lib->cleanWindow();
  lib->printText(250, 300, "Score : ");
  lib->printText(340, 300, s.str());
  lib->printText(250, 350, "YOU LOOSE TRY AGAIN");
  lib->refreshWindow();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  start = 0;
}

void 	Core::youWin()
{
  std::stringstream	s;

  s << game->getScore();
  lib->cleanWindow();
  lib->printText(250, 300, "Score : ");
  lib->printText(340, 300, s.str());
  lib->printText(250, 350, "NICE YOU WON");
  lib->refreshWindow();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  start = 0;
}

void	Core::moveplayer()
{
  const char 	cmd[5] = "zsqd";
  int 		i;
  int 		isKey;
  int 		save;

  i = 0;
  isKey = 0;
  while (cmd[i] != '\0')
  {
    if (this->key == cmd[i])
    {
      isKey = 1;
      save = this->game->update(i + 1);
      if (save == 1)
	youLoose();
      else if (save == 2)
	youWin();
    }
    i++;
  }
  if (isKey == 0)
  {
    if (this->game->update(0) == 1)
    {
      this->start = 0;
      return;
    }
  }
  return;
}

int	Core::gameManager()
{
  size_t	tmp;

  if (this->key == '5')
    {
      if (this->itGame == this->gamesListPath.end())
	this->itGame = this->gamesListPath.begin();
      if (this->swapGame(*this->itGame) == -1)
	return (-1);
      ++this->itGame;
    }
  else if (this->key == '4')
    {
      tmp = 0;
      if (this->itGame == this->gamesListPath.begin())
	{
	  this->itGame = this->gamesListPath.end();
	  --this->itGame;
	  tmp = 1;
	}
      if (tmp == 0)
	--this->itGame;
      if (this->swapGame(*this->itGame) == -1)
	return (-1);
    }
  return (0);
}

int 	Core::libKeyManager(size_t tmpKey)
{
  if (tmpKey == '2' || tmpKey == '3')
  {
    this->key = tmpKey;
    this->libManager();
  }
  else if (tmpKey == '4' || tmpKey == '5')
  {
    this->key = tmpKey;
    if (this->gameManager() == -1)
      return (1);
  }
}

int	Core::keyManager()
{
  int	i;
  int	tmp;

  i = 0;
  if (start == 0)
    {
      key = this->lib->getEvent();
      if (key == 27)
	return (1);
      else if (key == 50 || key == 51)
	this->libManager();
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      return (0);
    }
  while (i != 32)
    {
      tmp = this->lib->getEvent();
      i++;
      if (tmp == 27)
	return (1);
      else if (tmp == '2' || tmp == '3' || tmp == '4' || tmp == '5')
      	libKeyManager(tmp);
      else if (tmp == '9')
	{
	  this->key = tmp;
	  this->start = 0;
	  return (0);
	}
      else if (tmp == '8')
	{
	  this->key = tmp;
	  if (swapGame(this->curentGame) == -1)
	    return (-1);
	  return (0);
	}
      if (tmp == 'z' || tmp == 's' || tmp == 'q' || tmp == 'd')
	this->key = tmp;
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
  if (this->start == 1)
    this->moveplayer();
  return (0);
}

int	Core::loadGame(std::string game)
{
  this->start = 1;
  if (this->gameLoad.openLib(game) == -1)
    {
      std::cerr << "[ Error CORE ] can't open game" << game << std::endl;
      return (-1);
    }
  if ((this->game = this->gameLoad.getInstance<IGameModule>(0)) == NULL)
    return (-1);
  return (0);
}

void	Core::printMenu()
{
  this->lib->printText(100, 300, "Nickname : ");
  this->lib->printText(100, 340, "===>");
  this->lib->printText(100, 380, "Arcade Keys Maping:");
  this->lib->printText(100, 430, "Keys in Menu :");
  this->lib->printText(80, 460, "-> Z and S to select an Arcade Games");
  this->lib->printText(80, 490, "-> D and E to select an Arcade Libs");
  this->lib->printText(80, 520, "-> Y to put your Nickname and Enter to confirm");
  this->lib->printText(100, 570, "Keys in Games :");
  this->lib->printText(80, 600, "-> Z to Move Forward");
  this->lib->printText(450, 600, "-> S to Move Backward");
  this->lib->printText(80, 630, "-> Q to Move on the Left");
  this->lib->printText(450, 630, "-> D to Move on the Right");
}

int	Core::menu()
{
  size_t				x;
  size_t				y;

  x = 145;
  y = 45;
  this->lib->printText(100, 10, "Arcade Games");
  y = static_cast<size_t >(this->printGameList(x, y));
  this->printLibList(x ,y);
  printMenu();
  if (this->key == 'z')
    this->gameMenuPos--;
  else if (this->key == 's')
    this->gameMenuPos++;
  else if (this->key == 'e')
    this->libMenuPos--;
  else if (this->key == 'd')
    this->libMenuPos++;
  else if (this->key == 'y')
    this->printPseudo();
  else if (this->key == '\n' || this->key == 13)
  {
    if (loadGame(this->gamesListPath[this->gameMenuPos]) == -1)
      return (-1);
    if (swapLib(this->libsListPath[this->libMenuPos]) == -1)
      return (-1);
  }
  lib->printText(170, 340, nickname);
  this->gameMenuPos = (this->gameMenuPos + this->gamesListPath.size()) % this->gamesListPath.size();
  this->libMenuPos = (this->libMenuPos + this->libsListPath.size()) % this->libsListPath.size();
  this->key = 0;
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  return (0);
}

int 	Core::printGameList(size_t x, size_t y)
{
  std::vector<std::string>::iterator 	it;
  int					cursLib;

  it = this->gamesListPath.begin();
  cursLib = 0;
  while (it != this->gamesListPath.end())
  {
    if (cursLib != this->gameMenuPos)
      this->lib->printText(x, y, "[   ]");
    else
      this->lib->printText(x, y, "[ * ]");
    this->lib->printText(x + 128, y, static_cast<std::string>(*it));
    y += 32;
    cursLib++;
    ++it;
  }
  return (y);
}

void	Core::printLibList(size_t x, size_t y)
{
  int					cursGame;
  std::vector<std::string>::iterator 	libs;

  cursGame = 0;
  libs = this->libsListPath.begin();
  this->lib->printText(100, 150, "Arcade Libs");
  while (libs != this->libsListPath.end())
  {
    if (cursGame != this->libMenuPos)
      this->lib->printText(x, y + 70, "[   ]");
    else
      this->lib->printText(x, y + 70, "[ * ]");
    this->lib->printText(x + 128, y + 70, static_cast<std::string>(*libs));
    y += 32;
    cursGame++;
    ++libs;
  }
}

void    Core::mainCore(std::string libPath)
{
  std::stringstream	ss;

  if (this->setLibListPath() == -1)
    return ;
  if (this->setGameListPath() == -1)
    return ;
  if (this->libLoad.openLib(libPath) == -1)
    {
      std::cerr << "[ Error CORE ] can't open lib" << libPath << std::endl;
      return ;
    }
  this->itLib = this->libsListPath.begin();
  if ((this->lib = this->libLoad.getInstance<IDisplayModule>(1)) == NULL)
    return ;
  std::vector<std::string>::iterator tmp = std::find(this->libsListPath.begin(), this->libsListPath.end(), libPath);
  this->libMenuPos = tmp - this->libsListPath.begin();
  if (this->lib->createWindow() == -1)
  {
    this->exitCore();
    return ;
  }
  while (42)
    {
      this->lib->cleanWindow();
      if (this->start == 0)
      {
	if (this->menu() == -1)
	  return ;
      }
      else
	{
	  if (this->lib->printMap(this->game->getMap()) == -1)
	  {
	    this->exitCore();
	    return ;
	  }
	  if (this->printElemList() == -1)
	    return ;
	  this->lib->printText(680, 10, "Pseudo :");
	  this->lib->printText(680, 70, "Score :");
	  ss << this->game->getScore();
	  this->lib->printText(680, 40, nickname);
	  this->lib->printText(680, 95, ss.str());
	  ss.str("");
	}
      if (this->keyManager() == 1)
      {
	this->exitCore();
	return;
      }
      this->lib->refreshWindow();
    }
}

int	Core::swapLib(std::string lib_path)
{
  this->lib->closeWindow();
  delete (lib);
  this->libLoad.closeInstance();
  if (this->libLoad.openLib(lib_path) == -1)
    {
      std::cerr << "[ Error CORE ] can't open lib" << std::endl;
      return (-1);
    }
  if ((this->lib = libLoad.getInstance<IDisplayModule>(1)) == NULL)
    return (-1);
  if (this->lib->createWindow() == -1)
    return (-1);
  return (0);
}

int	Core::swapGame(std::string gamePath)
{
  delete (game);
  this->gameLoad.closeInstance();
  if (this->gameLoad.openLib(gamePath) == -1)
    {
      std::cerr << "[ Error CORE ] can't open game" << std::endl;
      return (-1);
    }
  this->curentGame = gamePath;
  if ((this->game = this->gameLoad.getInstance<IGameModule>(0)) == NULL)
    return (-1);
  return (0);
}

int	Core::setLibListPath()
{
  DIR				*rep;
  std::string			tmp;
  struct dirent			*read;
  std::string::size_type	sz;

  if ((rep = opendir("./lib/")) == NULL)
    return (-1);
  while ((read = readdir(rep)) != NULL)
    {
      tmp = read->d_name;
      if ((sz = tmp.find_last_of('.')) != std::string::npos &&
	  tmp.substr(sz) == ".so")
	{
	  tmp = "./lib/" + tmp;
	  this->libsListPath.push_back(tmp);
	}
    }
  return (0);
}

int	Core::setGameListPath()
{
  DIR				*rep;
  std::string			tmp;
  struct dirent			*read;
  std::string::size_type	sz;

  if ((rep = opendir("./games/")) == NULL)
    return (-1);
  while ((read = readdir(rep)) != NULL)
    {
      tmp = read->d_name;
      if ((sz = tmp.find_last_of('.')) != std::string::npos &&
	  tmp.substr(sz) == ".so")
	{
	  tmp = "./games/" + tmp;
	  this->gamesListPath.push_back(tmp);
	}
    }
  this->itGame = this->gamesListPath.begin();
  return (0);
}

int	Core::printElemList()
{
  std::vector<elem>	tmpElemList;
  std::vector<elem>::iterator it;

  tmpElemList = this->game->getElemList();
  it = tmpElemList.end() - 1;
  while (it >= tmpElemList.begin())
    {
      if (this->lib->printElem(*it) == -1)
      {
	this->exitCore();
	return (-1);
      }
      --it;
    }
  return (0);
}

void	Core::exitCore()
{
  this->lib->closeWindow();
  delete (lib);
  this->libLoad.closeInstance();
  if (this->start == 1)
  {
    delete (game);
    this->gameLoad.closeInstance();
  }
 return ;
}

int	Core::printPseudo()
{
  static int 		tx = 170;
  static int 		ty = 340;
  int 			i;
  int 			save;
  std::stringstream	ss;

  i = 0;
  this->nickname.clear();
  save = lib->getEvent();
  while (save != 13)
  {
    if (save == '\n')
      return (0);
    save = this->lib->getEvent();
    if ((save >= '1' && save <= '9') || (save >='A' && save <= 'Z') || (save >= 'a' && save <= 'z') && i < 7)
    {
      ss.str("");
      ss << static_cast<char>(save);
      this->lib->printText(tx, ty, ss.str());
      this->nickname += ss.str();
      this->lib->refreshWindow();
      if (save == 'm')
	tx += 16;
      else
	tx += 14;
      i++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  };
  ss.clear();
  return (0);
}