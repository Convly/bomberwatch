//
// wchar.cpp for  in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Libs/Bin/Utils/Srcs/Functions/wchar/
//
// Made by Maxime Cauvin
// Login   <maxime.cauvin@epitech.eu>
//
// Started on  Thu May 25 00:27:28 2017 Maxime Cauvin
// Last update Thu May 25 01:01:42 2017 Maxime Cauvin
//

#include "wchar.hpp"

#include <iostream>

std::string   utils::getStrFromWStr(wchar_t const *wstr)
{
  std::wstring ws(wstr);
  std::string str(ws.begin(), ws.end());
  return str;
}

std::wstring utils::getWStrFromStr(std::string const& str)
{
  return (std::wstring(str.begin(), str.end()));
}
