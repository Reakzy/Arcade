//
// lib_sfml.hpp for arcade in /home/costa_d/Documents/TEK2/CPP/Arcad/cpp_arcade
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Tue Mar  7 16:42:12 2017 Arnaud Costa
// Last update Thu Mar 30 14:04:15 2017 Arnaud Costa
//

#ifndef LIB_SFML_HPP
# define LIB_SFML_HPP

# include <string>
# include <iostream>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "IDisplayModule.hh"

class	libSfml: public IDisplayModule
{
  sf::RenderWindow	window;
  sf::Texture		wall;
  sf::Texture		floor;

 public:
  libSfml();
  libSfml(const libSfml &other) = delete;
  libSfml &operator=(const libSfml &other) = delete;
  virtual ~libSfml();
  virtual int	createWindow();
  virtual void	closeWindow();
  virtual void	cleanWindow();
  virtual void	refreshWindow();
  virtual int	printElem(elem CetElem);
  virtual int	getEvent();
  virtual int   printMap(std::vector<std::string> map);
  virtual int   printText(int x, int y, std::string text);
};

extern "C" IDisplayModule	*entry_point();

# endif /* LIB_SFML_HPP */
