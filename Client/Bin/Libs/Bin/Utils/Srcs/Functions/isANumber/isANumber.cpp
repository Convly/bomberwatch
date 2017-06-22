//
// isANumber.cpp for  in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Libs/Bin/Utils/Srcs/Functions/isANumber/
//
// Made by Maxime Cauvin
// Login   <maxime.cauvin@epitech.eu>
//
// Started on  Mon Jun 12 18:43:41 2017 Maxime Cauvin
// Last update Mon Jun 12 18:45:40 2017 Maxime Cauvin
//

#include "isANumber.hpp"

bool   utils::isANumber(std::string const& str)
{
  double  nb;
  std::istringstream is(str);

  is >> nb;
  return (!is.fail() && is.eof());
}
