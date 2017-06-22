/*
** GameObject.hpp for cpp_indie_studio in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Game/GameInfos
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon Jun 12 11:58:59 2017 Quentin Metge
** Last update Fri Jun 16 01:46:47 2017 Quentin Metge
*/

#ifndef GAME_OBJECT_HPP_
# define GAME_OBJECT_HPP_

#include "StructServer.hpp"
#include "GameServerInfos.hpp"
#include "IScope.hpp"
#include "UTILS/http.hpp"

namespace indie {
  namespace module {

    class GameObject{
    public:
      GameObject(){}
      GameObject(kirr::Scene::ISceneNode* mesh, int const objType);
      virtual ~GameObject();

    public:
      void                      setAnimation(int const animation = static_cast<int>(kirr::OBJ_ACTION::STAND));
      void                      setScale(int const objType, kirr::vector3df const& scale);

    public:
      kirr::Scene::ISceneNode*  getMesh() const{return this->_mesh;}

    private:
      kirr::Scene::ISceneNode*  _mesh;
      std::unordered_map<int, kirr::Pos<int>> _animations;
    };

  }
}

#endif
