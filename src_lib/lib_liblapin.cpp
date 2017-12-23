//
// Created by counil_m on 24/03/17.
//

#include "lib_liblapin.hh"

libLiblapin::libLiblapin()
{
  int	y;
  int	x;
  elem	tmp;

  x = 0;
  y = 0;
  tmp.type = arcade::TileType::EMPTY;
  while (y < 32)
    {
      std::vector<elem> temp;
      x = 0;
      while (x < 32)
	{
	  temp.push_back(tmp);
	  x++;
	}
      y++;
      this->map.push_back(temp);
    }
  this->cnt = 0;
}

extern "C"
{
  IDisplayModule	*entryPoint()
  {
    return (new libLiblapin());
  }
}

libLiblapin::~libLiblapin()
{
}

int	libLiblapin::createWindow()
{
  window = bunny_start(1000, 1000, 0, "Arcade");
  if (!window)
    return (-1);
 if ((floor = bunny_load_picture("./sprite/floor.png")) == NULL)
   return (-1);
 load.insert(std::pair<std::string, t_bunny_picture *>("./sprite/3D/losange1.png", bunny_load_picture("./sprite/3D/losange1.png")));
 load.insert(std::pair<std::string, t_bunny_picture *>("./sprite/3D/losange10.png", bunny_load_picture("./sprite/3D/losange10.png")));
 load.insert(std::pair<std::string, t_bunny_picture *>("./sprite/3D/losange11.png", bunny_load_picture("./sprite/3D/losange11.png")));
 if ((font = bunny_load_picture("./font/font.png")) == NULL)
    return (-1);
    return (0);
}

void  libLiblapin::refreshWindow()
{
  int	y;
  int	x;
  t_bunny_position	my_pos;

  y = 0;
  while (y != 32)
    {
      x = 31;
      while (x >= 0)
	{
	  if (static_cast<int>(this->map[y][x].type) != 0)
	    {
	      my_pos.y = 400 + ((y - x) * 7);
	      my_pos.x = ((y + x) * 14);
	      std::stringstream	path;
	      if (this->map[y][x].type == arcade::TileType::OBSTACLE)
		{
		  path << map[y][x].sprite;
		}
	      else
		path << "./sprite/3D/losange" << static_cast<int>(this->map[y][x].type) << ".png";
	      bunny_blit(&window->buffer, load[path.str()], &my_pos);
	    }
	  x--;
	}
      y++;
    }
  if (cnt % 2 == 0)
    this->cnt = 0;
  else
    this->cnt = 0;
  bunny_display(window);
  return ;
}

void	libLiblapin::closeWindow()
{
  std::map<std::string, t_bunny_picture*>::iterator delme;

  if (!floor)
    bunny_delete_clipable(floor);
  if (!font)
    bunny_delete_clipable(font);
  delme = load.begin();
  while (delme != load.end())
  {
    if (delme->second)
      bunny_delete_clipable(delme->second);
    ++delme;
  }
  bunny_stop(window);
}

void	libLiblapin::cleanWindow()
{
  int	y;
  int	x;
  elem	tmp;

  y = 0;
  x = 0;
  while (y < 32)
    {
      std::vector<elem> temp;
      x = 0;
      while (x < 32)
	{
	  this->map[y][x].type = arcade::TileType::EMPTY;
	  x++;
	}
      y++;
    }
  bunny_clear(&window->buffer, BLACK);
}

int	libLiblapin::printElem(elem CetElem)
{
  t_bunny_picture	*text;
  std::map<std::string, t_bunny_picture*>::iterator it;
  std::stringstream	path;
  std::string		tmp;

  this->map[CetElem.pos.y][CetElem.pos.x].type = CetElem.type;
  path << "./sprite/3D/losange" << static_cast<int>(CetElem.type) << ".png";
  tmp = path.str();
  if (CetElem.type == arcade::TileType::OBSTACLE)
    {
      std::stringstream	path;
      if (CetElem.type == arcade::TileType::OBSTACLE)
	{
	  path << "./sprite/3D/losange" << 10 + this->cnt % 2 << ".png";
	}
      this->map[CetElem.pos.y][CetElem.pos.x].sprite = path.str();
      this->cnt++;
    }
  else
    {
      if ((it = load.find(path.str())) == load.end()) {
	if ((text = bunny_load_picture(tmp.c_str())) == NULL)
	  return (-1);
	load.insert(std::pair<std::string, t_bunny_picture *>(path.str(), bunny_load_picture(tmp.c_str())));
      }
    }
  return (0);
}

int   libLiblapin::getEvent()
{
  struct bunny_window   *win = (struct bunny_window*)window;
  sf::Event	event;

  while (win->window->pollEvent(event)) {
    if (event.type == sf::Event::TextEntered)
    {
      if (event.text.unicode < 128)
	return (static_cast<int>(event.text.unicode));
    }
  }
  return (0);
}

int	libLiblapin::printMap(std::vector<std::string> map)
{
  int	y;
  int	x;
  int	tmp;
  std::vector<std::string>::size_type	len;

  len = map.size();
  x = 0;
  y = 0;
  while (y != len)
    {
      x = 0;
      while (map[y][x])
	{
	  tmp = map[y][x] - 48;
	  this->map[y][x].type = (arcade::TileType)tmp;
	  x++;
	}
      y++;
    }
}

int    libLiblapin::printText(int x, int y, std::string text)
{
  t_bunny_position      pos;
  int                   i;
  const char 		*str;

  str = text.c_str();
  pos.x = x;
  pos.y = y;
  i = 0;
  font->scale.x = 2;
  font->scale.y = 3;
  font->clip_y_position = 0;
  font->clip_width = 5;
  font->clip_height = 7;
  while (str[i])
  {
    if (str[i] == ' ')
      pos.x += font->scale.x * 5;
    else
      {
	font->clip_x_position = str[i] * 5;
	bunny_blit(&window->buffer, font, &pos);
	pos.x += font->scale.x * 7;
      }
    i++;
  }
  return (0);
}
