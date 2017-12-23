//
// Created by alis_a on 3/22/17.
//

#include "Pacman.hh"
#include "Protocol.hpp"

Pacman::Pacman()
{
  this->score = 0;
  this->powerUp = 0;
  this->gum = 150;
  createMap();
  createElemList();
}

Pacman::~Pacman()
{}

void    Pacman::updateEnemies(int num)
{
  int   i;
  int   r;
  int	tmp;

  i = 0;
  r = rand() % 4 + 1;
  tmp = 1;
  while (i != 10 && tmp != 0)
    {
      if (this->elemList[num].pos.y == 9 && this->elemList[num].pos.x >= 9 && this->elemList[num].pos.x <= 11)
	tmp = this->moveTo(elemList[num].pos, num, r, 1);
      else
	tmp = this->moveTo(elemList[num].pos, num, r, 0);
      r = rand() % 4 + 1;
      i++;
    }
}


void    Pacman::findEnemies()
{
  std::vector<elem>::size_type  len;
  int   rand;
  int   i;

  len = elemList.size();
  i = 1;
  while (i != len)
    {
      if (elemList[i].type == arcade::TileType::EVIL_DUDE)
	this->updateEnemies(i);
     i++;
    }
}

int     Pacman::canMove(arcade::Position pos,
                         int elemPos, int move)
{
  if (this->map[pos.y][pos.x] == '1')
    return (1);
  else
  {
    if (this->elemList[elemPos].pos.x == 0 && move == 3)
      pos.x = 20;
    this->elemList[elemPos].pos.y = pos.y;
    this->elemList[elemPos].pos.x = pos.x;
    if (pos.x == 21 && move == 4)
      this->elemList[elemPos].pos.x = 0;
    this->elemList[elemPos].direction = move;
    return (0);
  }
}

int     Pacman::moveTo(arcade::Position pos, int elemPos, int move, int canRotate)
{
  if (move == 1 && (canRotate == 1 || this->elemList[elemPos].direction != 2)) {
    pos.y -= 1;
    return (this->canMove(pos, elemPos, move));
  }
  else if (move == 2 && (canRotate == 1 || this->elemList[elemPos].direction != 1)) {
    pos.y += 1;
    return (this->canMove(pos, elemPos, move));
  }
  else if (move == 3 && (canRotate == 1 || this->elemList[elemPos].direction != 4)) {
    pos.x -= 1;
    return (this->canMove(pos, elemPos, move));
  }
  else if (move == 4 && (canRotate == 1 || this->elemList[elemPos].direction != 3)) {
    pos.x += 1;
    return (this->canMove(pos, elemPos, move));
  }
  return (1);
}

int	Pacman::checkCollision()
{
  std::vector<elem>::iterator  it;
  int				i;
  elem				*Elem;
  elem				*Debut;
  
  i = 1;
  it = this->elemList.begin();
  Debut = &(*it);
  while (++it < this->elemList.end())
    {
      Elem = &(*it);
      if (Debut->pos.x == Elem->pos.x &&
	  Debut->pos.y == Elem->pos.y)
	{
	  if (Elem->type == arcade::TileType::EVIL_DUDE)
	    {
	      if (this->powerUp > 0)
		{
		  Elem->pos.x = 10;
		  Elem->pos.y = 9;
		  Elem->direction = 0;
		}
	      else
		return (1);
	    }
	  if ((Elem->type == arcade::TileType::OTHER) && Elem->direction != -1)
	    {
	      elemList.erase(it);
	      incScore(10);
	      this->gum--;
	    }
	  else if (Elem->type == arcade::TileType::POWERUP && Elem->direction != -1)
	    {
	      elemList.erase(it);
	      takePowerUp();
	    }
	}
    }
  return (0);
}

void	Pacman::powerUpActive()
{
  int	y;

  y = 0;
  while (y != 7)
    {
      if (this->elemList[y].type == arcade::TileType::EVIL_DUDE)
	this->elemList[y].sprite = "./sprite/ghost_afraid.png";
      y++;
    }
}

void	Pacman::powerUpUnactive()
{
  this->elemList[1].sprite = "./sprite/ghost_blue.png";
  this->elemList[2].sprite = "./sprite/ghost_orange.png";
  this->elemList[3].sprite = "./sprite/ghost_red.png";
}

int     Pacman::update(int direction)
{
  int       a;
  int       i;
  arcade::Position  pos;
  std::stringstream	path;
  std::string		img_path;

  if (this->gum <= 0)
    return (2);
  if (this->elemList[0].direction == 0 && direction == 0)
    return (0);
  if (this->elemList[0].direction == -1)
    return (1);
  if (this->checkCollision() == 1)
    return (1);
  a = 1;
  if (this->powerUp > 0)
    {
      this->powerUp -= 1;
      powerUpActive();
    }
  else
    powerUpUnactive();
  i = 1;
  pos.x = this->elemList[0].pos.x;
  pos.y = this->elemList[0].pos.y;
  if (this->moveTo(pos, 0, direction, 1) == 1)
    this->moveTo(pos, 0, this->elemList[0].direction, 1);
  if (this->checkCollision() == 1)
    {
      this->elemList[0].direction = -1;
      return (0);
    }
  this->findEnemies();
  if (this->checkCollision() == 1)
    {
      this->elemList[0].direction = -1;
      return (0);
    }
  if (this->elemList[0].direction != 0 && this->elemList[0].direction != -1)
    {
      if ((this->elemList[0].pos.x + this->elemList[0].pos.y) % 2 == 0)
	path << "./sprite/pacman_1_" << this->elemList[0].direction << ".png";
      else
	path << "./sprite/pacman_2_" << this->elemList[0].direction << ".png";
      this->elemList[0].sprite = path.str();
    }
  return (0);
}

void    Pacman::takePowerUp()
{
  this->powerUp = 30;
  return;
}

void    Pacman::incScore(int plus)
{
  this->score += plus;
  return;
}

int     Pacman::getScore() const
{
  return (this->score);
}

void  Pacman::createMap()
{

  this->map.push_back("011111111111111111110\0");
  this->map.push_back("010000000010000000010\0");
  this->map.push_back("012110111010111011210\0");
  this->map.push_back("010000000000000000010\0");
  this->map.push_back("010110101111101011010\0");
  this->map.push_back("010000100010001000010\0");
  this->map.push_back("011110111010111011110\0");
  this->map.push_back("000010100000001010000\0");
  this->map.push_back("111110101101101011111\0");
  this->map.push_back("000000001000100000000\0");
  this->map.push_back("111110101111101011111\0");
  this->map.push_back("000010100000001010000\0");
  this->map.push_back("011110101111101011110\0");
  this->map.push_back("010000000010000000010\0");
  this->map.push_back("010110111010111011010\0");
  this->map.push_back("012010000030000010210\0");
  this->map.push_back("011010101111101010110\0");
  this->map.push_back("010000100010001000010\0");
  this->map.push_back("010111111010111111010\0");
  this->map.push_back("010000000000000000010\0");
  this->map.push_back("011111111111111111110\0");
  return ;
}

elem    Pacman::createElem(int y, int x, arcade::TileType type, int direction, std::string path)
{
  elem  ret;

  ret.pos.x = x;
  ret.pos.y = y;
  ret.type = type;
  ret.direction = direction;
  ret.sprite = path;
  return (ret);
}

void    Pacman::createElemList()
{
  int				y;
  int				x;

  this->elemList.push_back(this->createElem(15, 10, arcade::TileType::OBSTACLE, 0, "./sprite/pacman.png"));
  this->elemList.push_back(this->createElem(9, 9, arcade::TileType::EVIL_DUDE, 0, "./sprite/ghost_blue.png"));
  this->elemList.push_back(this->createElem(9, 10, arcade::TileType::EVIL_DUDE, 0, "./sprite/ghost_orange.png"));
  this->elemList.push_back(this->createElem(9, 11, arcade::TileType::EVIL_DUDE, 0, "./sprite/ghost_red.png"));
  this->elemList.push_back(this->createElem(2, 2, arcade::TileType::POWERUP, 0, "./sprite/pacman_powerup.png"));
  this->elemList.push_back(this->createElem(2, 18, arcade::TileType::POWERUP, 0, "./sprite/pacman_powerup.png"));
  this->elemList.push_back(this->createElem(15, 2, arcade::TileType::POWERUP, 0, "./sprite/pacman_powerup.png"));
  this->elemList.push_back(this->createElem(15, 18, arcade::TileType::POWERUP, 0, "./sprite/pacman_powerup.png"));
  y = 1;
  x = 1;
  while (y != 20)
    {
      while (x != 19)
	{
	  if (this->map[y][x] == '0' && (y < 7 || y > 11))
	    {
	      this->elemList.push_back(this->createElem(y, x, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
	    }
	  else if (this->map[y][x] != '1')
	    this->map[y][x] = '0';
	  x++;
	}
      x = 1;
      y++;
    }
  this->elemList.push_back(this->createElem(7, 5, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(8, 5, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(9, 5, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(10, 5, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(11, 5, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(7, 15, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(8, 15, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(9, 15, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(10, 15, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  this->elemList.push_back(this->createElem(11, 15, arcade::TileType::OTHER, 0, "./sprite/pacman_other.png"));
  return ;
}

void    Pacman::eraseElem(elem *elem)
{
  return ;
}

std::vector<elem>	Pacman::getElemList() const
{
  return (this->elemList);
}

std::vector<std::string>	Pacman::getMap() const
{
  return (this->map);
}

extern "C"
{
IGameModule *entryPoint() {
  return (new Pacman());
}

void Play() {
  Pacman pacman;
  std::vector<std::string> gameMap = pacman.getMap();
  arcade::CommandType input;
  arcade::GetMap *map;
  arcade::WhereAmI *where;
  std::vector<std::string>::iterator it;
  size_t cmdDirection = 3;
  const char *parce;
  int a;
  int aff_tile;
  std::string ligne;
  int 	u;

  while (42) {
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
      u = 0;
      while (u != 21) {
	ligne = gameMap[u];
	parce = ligne.c_str();
	a = 0;
	while (parce[a] != '\0')
	{
	  if (parce[a] == '1')
	    map->tile[aff_tile] = arcade::TileType::BLOCK;
	  else if (parce[a] == '0')
	    map->tile[aff_tile] = arcade::TileType::EMPTY;
	  a++;
	  aff_tile++;
	}
	++it;
	u++;
      }
      std::cout.write(reinterpret_cast<char *>(map), 21 * 21 * sizeof(arcade::TileType) + sizeof(arcade::GetMap));
      delete(map);
    }
    if (input == arcade::CommandType::WHERE_AM_I) {
      where = new arcade::WhereAmI[sizeof(arcade::Position) + sizeof(arcade::WhereAmI)];
      where->type = arcade::CommandType::WHERE_AM_I;
      where->lenght = 1;
      where->position[0].x = pacman.getElemList()[0].pos.x;
      where->position[0].y = pacman.getElemList()[0].pos.y;
      std::cout.write(reinterpret_cast<char *>(where), sizeof(arcade::Position) + sizeof(arcade::WhereAmI));
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
      pacman.update(cmdDirection);
  }
}
}
