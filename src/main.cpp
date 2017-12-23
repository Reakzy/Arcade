//
// main.cpp for wegr in /home/costa_d/Documents/TEK2/CPP/Arcad/bootstrap
//
// Made by Arnaud Costa
// Login   <costa_d@epitech.net>
//
// Started on  Tue Mar  7 16:52:54 2017 Arnaud Costa
// Last update Thu Mar 30 13:35:46 2017 Arnaud Costa
//

#include "Core.hh"

int	main(int ac, char **av)
{
  if (ac == 1)
    {
      std::cout << "Usage: " << av[0] << " ./lib_path/" << std::endl;
      return (84);
    }
  Core	core;
  core.mainCore(av[1]);
  return (0);
}
