//
// DLLoader.hpp for Arcad in /home/costa_d/Documents/TEK2/CPP/Arcad/bootstrap
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Mon Mar 13 17:44:42 2017 Arnaud Costa
// Last update Fri Mar 24 14:53:53 2017 Arnaud Costa
//

#ifndef DLLOADER_HPP
# define DLLOADER_HPP

# include <dlfcn.h>
# include <string>
# include <iostream>
# include <vector>
# include "IDisplayModule.hh"
# include "IGameModule.hh"

class	DLLoader
{
  void			*handler;
public:
  DLLoader();
  DLLoader(const DLLoader &other) = delete;
  DLLoader &operator=(const DLLoader &other) = delete;
  ~DLLoader();
  int	openLib(std::string lib_path);
  template <typename T>
  T	*getInstance(int load);
  void	closeInstance();
};

template <typename T>
T	*DLLoader::getInstance(int load)
{
  T	*(*entry)();
  T	*(*play)();

 play = reinterpret_cast<T* (*)()>(dlsym(this->handler, "Play"));
 if (!dlerror() && load == 1) {
    std::cerr << "[Error] can't open lib Play"<< std::endl;
    return (NULL);
 }
  entry = reinterpret_cast<T* (*)()>(dlsym(this->handler, "entryPoint"));
  if (dlerror()) {
    std::cerr << "[Error] can't open lib"<< std::endl;
    return (NULL);
  }
  return ((*entry)());
}

#endif /* DLLOADER_HPP_ */
