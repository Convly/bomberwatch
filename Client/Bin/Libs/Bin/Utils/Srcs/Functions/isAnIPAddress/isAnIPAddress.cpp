//
// isAnIPAddress.cpp for  in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Libs/Bin/Utils/Srcs/Functions/isAnIPAddress/
//
// Made by Maxime Cauvin
// Login   <maxime.cauvin@epitech.eu>
//
// Started on  Sun Jun 18 17:02:27 2017 Maxime Cauvin
// Last update Sun Jun 18 17:46:48 2017 Maxime Cauvin
//

#include "isAnIPAddress.hpp"
#include "split.hpp"
#include "isANumber.hpp"
#include <iostream>
bool      utils::isAnIPAddress(std::string const& str)
{
  std::vector<std::string>  tab = utils::split(str, '.', true);

  if (tab.size() != 4 || str.substr(str.size() - 1) == ".")
    return (false);
  for (size_t i = 0; i < tab.size(); i++)
  {
    if (!utils::isANumber(tab[i]) || std::stoi(tab[i]) < 0 || std::stoi(tab[i]) > 255)
      return (false);
  }
  return (true);
}
