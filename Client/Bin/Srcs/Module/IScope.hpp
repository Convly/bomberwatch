/*
** IScope.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 13:13:19 2017 Quentin Metge
** Last update Wed May 24 16:28:53 2017 Maxime Cauvin
*/

#ifndef ISCOPE_HPP_
# define ISCOPE_HPP_

#include <iostream>
#include <unordered_map>
#include <functional>
#include "UTILS/all.hpp"
#include "Kirrlicht.hpp"

namespace indie{
  namespace module{

    class IScope
    {
    public:
      virtual ~IScope(){}

    public:
      virtual bool               pollEvent(kirr::GlobalEvent const &) = 0;
      virtual kirr::Pos<float>   getPosCamera() const = 0;
      virtual std::vector<std::pair<std::string const, std::vector<kirr::Scene::IMeshSceneNode *>>> & getWordsMesh() = 0;

      virtual bool              loop() = 0;

      virtual bool              load() = 0;
      virtual void              disable() = 0;
      virtual void              enable() = 0;
      virtual bool              toogleAccess() = 0;
    };

  } /* scope */
} /* indie */

#endif
