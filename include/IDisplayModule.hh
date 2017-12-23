//
// IDisplayModule.cpp for IDisplayModules in /home/costa_d/Documents/TEK2/CPP/Arcad/bootstrap
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Tue Mar  7 16:00:56 2017 Arnaud Costa
// Last update Thu Mar 30 14:05:45 2017 Arnaud Costa
//

#ifndef IDisplayModule_HPP_
# define IDisplayModule_HPP_

# include <string>
# include <vector>
# include "Elem.hh"

class IDisplayModule
{
public:
  virtual ~IDisplayModule() {}
  virtual int   createWindow() = 0;
  virtual void  closeWindow() = 0;
  virtual void  cleanWindow() = 0;
  virtual void  refreshWindow() = 0;
  virtual int   printElem(elem Cet_elem) = 0;
  virtual int	getEvent() = 0;
  virtual int	printMap(std::vector<std::string> map) = 0;
  virtual int	printText(int x, int y, std::string text) = 0;
};

#endif /* IDisplayModule_HPP_ */
