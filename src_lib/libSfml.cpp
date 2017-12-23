//
// lib_sfml.cpp for arcade in /home/costa_d/Documents/TEK2/CPP/Arcad/cdd_arcade
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Tue Mar  7 16:39:54 2017 Arnaud Costa
// Last update Fri Mar 31 14:27:07 2017 Arnaud Costa
//

#include "libSfml.hh"

libSfml::libSfml()
{}

extern "C"
{
  IDisplayModule	*entryPoint()
  {
    return (new libSfml());
  }
}

libSfml::~libSfml()
{}

int	libSfml::createWindow()
{
  sf::RectangleShape	rectangle(sf::Vector2f(800, 800));

  window.create(sf::VideoMode(800, 800), "Arcade");
  rectangle.setSize(sf::Vector2f(800, 800));
  rectangle.setFillColor(sf::Color(0,0,0));
  window.draw(rectangle);
  if (!wall.loadFromFile("./sprite/wall.png",
                         sf::IntRect(0, 0, 32, 32)))
    return (-1);
  if (!floor.loadFromFile("./sprite/floor.png",
                          sf::IntRect(0, 0, 32, 32)))
    return (-1);

  return (0);
}

void	libSfml::closeWindow()
{
  window.close();
  return ;
}

void	libSfml::cleanWindow()
{
  window.clear();
  return ;
}

void	libSfml::refreshWindow()
{
  window.display();
  return ;
}

int	libSfml::printElem(elem CetElem)
{
  sf::Sprite	sprite;
  sf::Texture	texture;

  if (!texture.loadFromFile((CetElem.sprite.c_str()),
  			    sf::IntRect(0, 0, 32, 32)))
    return (-1);
  sprite.setTexture(texture);
  sprite.setPosition(CetElem.pos.x * 32, CetElem.pos.y * 32);
  window.draw(sprite);
  return (0);
}

int	libSfml::getEvent()
{
  sf::Event	event;

  while (window.pollEvent(event))
    {
      if (event.type == sf::Event::TextEntered)
	{
	  if (event.text.unicode < 128)
	    return (static_cast<int>(event.text.unicode));
	}
    }
  return (0);
}

int	libSfml::printMap(std::vector<std::string> map)
{
  size_t		i;
  size_t		x;
  size_t		y;
  std::string		ligne;
  sf::Sprite		sprite;
  const char		*parce;
  std::vector<std::string>::iterator it;

  y = 0;
  x = 0;
  it = map.begin();
  while (it != map.end())
    {
      x = 0;
      i = 0;
      ligne = *it;
      parce = ligne.c_str();
      while (parce[i] != '\0')
      	{
	  if (parce[i] == '1')
	    sprite.setTexture(wall);
	  else if (parce[i] == '0')
	    sprite.setTexture(floor);
	  sprite.setPosition(x, y);
	  window.draw(sprite);
	  i++;
	  x += 32;
      	}
      y += 32;
      ++it;
    }
  return (0);
}

int	libSfml::printText(int x, int y, std::string text)
{
  sf::Text	entity;
  sf::Font	font;

  if (!font.loadFromFile("./font/arial.ttf"))
    {
      std::cerr << "[ SFNL ERROR ] can't open ./font/arial.ttf"<< std::endl;
      return (-1);
    }
  entity.setFont(font);
  entity.setPosition(x, y);
  entity.setString(text);
  entity.setCharacterSize(24);
  entity.setColor(sf::Color::White);
  entity.setStyle(sf::Text::Regular);
  window.draw(entity);
  return (0);
}
