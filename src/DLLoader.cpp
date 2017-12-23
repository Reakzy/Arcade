//
// DLLoader.cpp for arcade in /home/costa_d/Documents/TEK2/CPP/Arcad/cpp_arcade/src
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Wed Mar 22 11:26:34 2017 Arnaud Costa
// Last update Thu Mar 23 15:44:08 2017 Arnaud Costa
//

#include "DLLoader.hpp"

DLLoader::DLLoader()
{}

DLLoader::~DLLoader()
{}

int      DLLoader::openLib(std::string lib_path)
{
  handler = dlopen(lib_path.c_str(), RTLD_LAZY);
  if (!handler)
    {
      std::cerr << "[ DLLOADER - ERRROR ] " << dlerror() << std::endl;
      return (-1);
    }
  dlerror();
  return (0);
}

void      DLLoader::closeInstance()
{
  dlclose(handler);
}
