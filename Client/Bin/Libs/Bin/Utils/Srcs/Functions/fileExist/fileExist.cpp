//
// fileExist.cpp for File Exist in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Bin/Libs/Bin/Utils/Srcs/Functions/fileExist/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  1 01:32:01 2017 jsx
// Last update Mon May  1 01:32:05 2017 jsx
//

#include "fileExist.hpp"

/* FILE EXIST */
bool                  utils::fileExist(std::string const& filepath)
{
  std::ifstream       ifs(filepath);
  bool                doesExist;

  doesExist = ifs.good();
  ifs.close();
  return (doesExist);
}
