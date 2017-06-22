//
// split.hpp for Split in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Bin/Libs/Bin/Utils/Srcs/Functions/split/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  1 01:39:20 2017 jsx
// Last update Sun Jun 18 17:29:16 2017 Maxime Cauvin
//

#ifndef UTILS_SPLIT_HPP_
#define UTILS_SPLIT_HPP_

#include <vector>
#include <string>
#include <sstream>

namespace utils {
  template<typename Out>
  void split(const std::string &s, char delim, Out result, bool addEmpty = false);
  std::vector<std::string> split(const std::string &s, char delim, bool addEmpty = false);
} /* utils */

#endif /* end of include guard: UTILS_SPLIT_HPP_ */
