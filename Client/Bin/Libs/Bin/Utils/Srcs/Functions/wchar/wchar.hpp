//
// wchar.cpp for  in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Libs/Bin/Utils/Srcs/Functions/wchar/
//
// Made by Maxime Cauvin
// Login   <maxime.cauvin@epitech.eu>
//
// Started on  Thu May 25 00:27:28 2017 Maxime Cauvin
// Last update Thu May 25 00:59:40 2017 Maxime Cauvin
//

#ifndef WCHAR_T_HPP
#define  WCHAR_T_HPP

#include <string>

namespace utils
{
  std::string   getStrFromWStr(wchar_t const *wstr);
  std::wstring  getWStrFromStr(std::string const& str);
}

#endif
