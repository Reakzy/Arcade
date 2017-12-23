//
// Created by alis_a on 3/22/17.
//

#ifndef ARCADE_IGAMEMODULE_HPP
#define ARCADE_IGAMEMODULE_HPP

# include <vector>

class IGameModule
{
 public:
  virtual				~IGameModule() {}
  virtual int				getScore() const = 0;
  virtual std::vector<elem>		getElemList() const = 0;
  virtual std::vector<std::string>	getMap() const = 0;
  virtual int				update(int direction) = 0;
};

#endif //ARCADE_IGAMEMODULE_HPP
