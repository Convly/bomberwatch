//
// main.cpp for main.cpp in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Srcs/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  1 01:00:49 2017 jsx
// Last update Thu Jun 15 05:16:04 2017 Maxime Cauvin
//

#include "Error.hpp"
#include "Indie.hpp"

int main(int ac, char** av)
{
  std::string defaultModule = "Splashscreen";
  if (ac >= 2) defaultModule = av[1];
  try {
    indie::core::Indie indie(defaultModule);
    indie.start();
  } catch (...) {
    return -1;
  }

  return (0);
}
