//
// Created by counil_m on 25/03/17.
//

#include <unistd.h>
#include "snake.hh"
#include "Protocol.hpp"

Snake::Snake()
{
  this->score = 0;
  this->powerUp = 0;
  createMap();
  createElemList();
}

Snake::~Snake()
{}

int	Snake::isColider()
{
  elem	tmp;
  std::vector<elem>::iterator it;
  int	i;

  i = 0;
  it = this->elemList.begin() + 2;
  while (it != this->elemList.end())
    {
      tmp = *it;
      if (this->elemList[0].pos.y == tmp.pos.y &&
        this->elemList[0].pos.x == tmp.pos.x)
	return (1);
      i++;
      ++it;
    }
  return (0);
}

int     Snake::canMove(arcade::Position pos, int elemPos, int move)
{
  if (this->map[pos.y][pos.x] == '1')
    return (1);
  else
  {
    this->elemList[elemPos].pos.y = pos.y;
    this->elemList[elemPos].pos.x = pos.x;
    this->elemList[elemPos].direction = move;
    return (0);
  }
}

int     Snake::moveTo(arcade::Position pos, int elemPos, int move)
{
  if (move == 1 && this->elemList[elemPos].direction != 2) {
    pos.y -= 1;
    return (this->canMove(pos, elemPos, move));
  }
  else if (move == 2 && this->elemList[elemPos].direction != 1) {
    pos.y += 1;
    return (this->canMove(pos, elemPos, move));
  }
  else if (move == 3 && this->elemList[elemPos].direction != 4) {
    pos.x -= 1;
    return (this->canMove(pos, elemPos, move));
  }
  else if (move == 4 && this->elemList[elemPos].direction != 3){
    pos.x += 1;
    return (this->canMove(pos, elemPos, move));
  }
  return (1);
}

int     Snake::update(int direction)
{
  arcade::Position			pos;
  std::vector<std::string>::size_type	len;
  int					tmp;
  std::stringstream			path;
  
  if (direction == 4 && this->elemList[0].direction == 0)
    return (0);
  tmp = this->isColider();
  if (takePowerUp() == 1)
    len = this->elemList.size() - 1;
  else
    len = this->elemList.size() - 1;
  pos.x = this->elemList[0].pos.x;
  pos.y = this->elemList[0].pos.y;
  while (len >= 3 && direction != 0)
    {
      this->elemList[len].pos.x = this->elemList[len - 1].pos.x;
      this->elemList[len].pos.y = this->elemList[len - 1].pos.y;
      len--;
    }
  if (direction != 0)
    {
      this->elemList[2].pos.x = this->elemList[0].pos.x;
      this->elemList[2].pos.y = this->elemList[0].pos.y;
    }
  if (this->moveTo(pos, 0, direction) == 1)
    this->moveTo(pos, 0, this->elemList[0].direction);
  if (this->elemList[0].direction != 0 && this->elemList[0].direction != -1)
    {
      path << "./sprite/snake_head" << this->elemList[0].direction << ".png";
      this->elemList[0].sprite = path.str();
    }
  return (tmp);
 }

 int	Snake::takePowerUp()
 {
   std::vector<std::string>::size_type	len;
   std::vector<elem>::iterator 		it;
   elem					*tmp;
   int	i;

   i = 2;
   len = this->elemList.size();
   it = this->elemList.begin() + 2;
  if (this->elemList[0].pos.x == this->elemList[1].pos.x &&
   this->elemList[0].pos.y == this->elemList[1].pos.y)
    {
      this->elemList.push_back(this->createElem(this->elemList[len - 1].pos.y, this->elemList[len - 1].pos.x,
						arcade::TileType::OBSTACLE, this->elemList[len - 1].direction, "./sprite/snake_body.png"));
      this->elemList[1].pos.y = rand() % 18 + 1;
      this->elemList[1].pos.x = rand() % 19 + 1;
      while (i < len)
	{
	  if (this->elemList[i].pos.y == this->elemList[1].pos.y
	      && this->elemList[i].pos.x == this->elemList[1].pos.x)
	    {
              this->elemList[1].pos.y = rand() % 18 + 1;
              this->elemList[1].pos.x = rand() % 19 + 1;
	      i = 1;
	    }
	  i++;
	}
      incScore(10);
      return (1);
    }
  return (0);
}

void    Snake::incScore(int plus)
{
  this->score += plus;
  return;
}

int     Snake::getScore() const
{
  return (this->score);
}

void    Snake::createMap()
{
  this->map.push_back("111111111111111111111\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("100000000000000000001\0");
  this->map.push_back("111111111111111111111\0");
}

elem    Snake::createElem(int x, int y, arcade::TileType type, int direction, std::string path)
{
  elem  ret;

  ret.pos.x = x;
  ret.pos.y = y;
  ret.type = type;
  ret.direction = direction;
  ret.sprite = path;
  return (ret);
}

void     Snake::createElemList()
{
  this->elemList.push_back(this->createElem(11, 10, arcade::TileType::OBSTACLE, 0, "./sprite/snake_head3.png"));
  this->elemList.push_back(this->createElem(2, 2, arcade::TileType::POWERUP, 0, "./sprite/snake_powerup.png"));
  this->elemList.push_back(this->createElem(12, 10, arcade::TileType::OBSTACLE, 0, "./sprite/snake_body.png"));
  this->elemList.push_back(this->createElem(13, 10, arcade::TileType::OBSTACLE, 0, "./sprite/snake_body.png"));
  this->elemList.push_back(this->createElem(14, 10, arcade::TileType::OBSTACLE, 0, "./sprite/snake_body.png"));
}

void    Snake::eraseElem(elem *elem)
{
  return ;
}

std::vector<elem>	Snake::getElemList() const
{
  return (this->elemList);
}

std::vector<std::string>	Snake::getMap() const
{
  return (this->map);
}

extern "C"
{
  IGameModule *entryPoint()
  {
    return (new Snake());
  }

void Play() {
  Snake snake;
  std::vector<std::string> gameMap = snake.getMap();
  arcade::CommandType input;
  arcade::GetMap *map;
  arcade::WhereAmI *where;
  std::vector<std::string>::iterator it;
  size_t i;
  size_t cmdDirection = 3;
  const char *parce;
  int 		a;
  int 		aff_tile;

  while (42)
  {
    std::cin.read(reinterpret_cast<char *>(&input), sizeof(input));
    if (std::cin.eof())
      return;

    if (input == arcade::CommandType::GET_MAP) {
      aff_tile = 0;
      map = new arcade::GetMap[21 * 21 * sizeof(arcade::TileType) + sizeof(arcade::GetMap)];
      map->width = 21;
      map->height = 21;
      map->type = arcade::CommandType::GET_MAP;
      it = gameMap.begin();
      while (it != gameMap.end())
      {
	std::string ligne = *it;
	parce = ligne.c_str();
	a = 0;
	while (parce[a] != '\0') {
	  if (parce[a] == '1')
	    map->tile[aff_tile] = arcade::TileType::BLOCK;
	  else if (parce[a] == '0')
	    map->tile[aff_tile] = arcade::TileType::EMPTY;
	  a++;
	  aff_tile++;
	}
	++it;
      }
      std::cout.write(reinterpret_cast<char *>(map), 21 * 21 * sizeof(arcade::TileType) + sizeof(arcade::GetMap));
      delete(map);
    }
      if (input == arcade::CommandType::WHERE_AM_I)
    {
      i = 1;
      size_t lensnake = snake.getElemList().size();
      where = new arcade::WhereAmI[(lensnake - 1) * sizeof(arcade::Position) + sizeof(arcade::GetMap)];
      where->type = arcade::CommandType::WHERE_AM_I;
      where->lenght = lensnake - 1;
      where->position[0].x = snake.getElemList()[0].pos.x;
      where->position[0].y = snake.getElemList()[0].pos.y;
      while (i < lensnake - 1) {
	  where->position[i].x = snake.getElemList()[i + 1].pos.x;
	  where->position[i].y = snake.getElemList()[i + 1].pos.y;
	i++;
      }
      std::cout.write(reinterpret_cast<char *>(where), (lensnake - 1) * sizeof(arcade::Position) + sizeof(arcade::WhereAmI));
      delete(where);
    }
    if (input == arcade::CommandType::GO_UP)
      cmdDirection = 1;
    if (input == arcade::CommandType::GO_DOWN)
      cmdDirection = 2;
    if (input == arcade::CommandType::GO_LEFT)
      cmdDirection = 3;
    if (input == arcade::CommandType::GO_RIGHT)
      cmdDirection = 4;
    if (input == arcade::CommandType::GO_FORWARD)
      cmdDirection = 0;
    if (input == arcade::CommandType::PLAY)
      snake.update(cmdDirection);
   }
  }
}
