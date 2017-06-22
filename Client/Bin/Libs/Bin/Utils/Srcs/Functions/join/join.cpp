//
// join.cpp for Join in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Bin/Libs/Bin/Utils/Srcs/Functions/join/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  1 01:38:56 2017 jsx
// Last update Mon May  1 01:39:02 2017 jsx
//

#include "join.hpp"

/* JOIN */
std::string   utils::join(std::vector<std::string> v, std::string j) {
  std::string result = "";
  int count = 0;
  int size = v.size();
  for (auto it = v.begin(); it != v.end(); it++) {
    result += *it;
    if (count < size - 1)
      result += j;
    count++;
  }
  return result;
}
