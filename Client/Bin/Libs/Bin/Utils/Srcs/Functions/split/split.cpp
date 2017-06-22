//
// split.cpp for Split in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Bin/Libs/Bin/Utils/Srcs/Functions/split/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  1 01:39:13 2017 jsx
// Last update Sun Jun 18 17:30:45 2017 Maxime Cauvin
//

#include "split.hpp"

/* SPLIT */
template<typename Out>
void utils::split(const std::string &s, char delim, Out result, bool addEmpty) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    if (item != "" || addEmpty)
      *(result++) = item;
  }
}

std::vector<std::string> utils::split(const std::string &s, char delim, bool addEmpty) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems), addEmpty);
  return elems;
}
/* -------- */
