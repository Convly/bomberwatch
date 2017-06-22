/*
** GameObject.cpp for cpp_indie_studio in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Game/GameInfos
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon Jun 12 12:03:37 2017 Quentin Metge
** Last update Fri Jun 16 01:31:59 2017 Quentin Metge
*/

#include "GameObject.hpp"

using namespace indie;
using namespace module;

static std::unordered_map<int, kirr::vector3df> g_scale;

GameObject::GameObject(kirr::Scene::ISceneNode* mesh, int const objType)
:
_mesh(mesh),
_animations({
  {static_cast<int>(kirr::OBJ_ACTION::STAND), kirr::Pos<int>(2, 62)},
  {static_cast<int>(kirr::OBJ_ACTION::PUT), kirr::Pos<int>(63, 138)},
  {static_cast<int>(kirr::OBJ_ACTION::MOVE_1), kirr::Pos<int>(139, 170)},
  {static_cast<int>(kirr::OBJ_ACTION::MOVE_2), kirr::Pos<int>(171, 202)},
  {static_cast<int>(kirr::OBJ_ACTION::SHOOT_1), kirr::Pos<int>(203, 238)},
  {static_cast<int>(kirr::OBJ_ACTION::SHOOT_2), kirr::Pos<int>(239, 274)},
  {static_cast<int>(kirr::OBJ_ACTION::DEAD_1), kirr::Pos<int>(275, 366)},
  {static_cast<int>(kirr::OBJ_ACTION::DEAD_2), kirr::Pos<int>(367, 470)},
  {static_cast<int>(kirr::OBJ_ACTION::DEATH_1), kirr::Pos<int>(366, 366)},
  {static_cast<int>(kirr::OBJ_ACTION::DEATH_2), kirr::Pos<int>(470, 470)},
  {static_cast<int>(kirr::OBJ_ACTION::DEFAULT), kirr::Pos<int>()},
  }){
  if (g_scale.find(objType) == g_scale.end()){
    g_scale[objType] = kirr::vector3df(1 / this->_mesh->getTransformedBoundingBox().getExtent().X, 1 / this->_mesh->getTransformedBoundingBox().getExtent().Y, 1 / this->_mesh->getTransformedBoundingBox().getExtent().Z);
  }
  this->setScale(objType, kirr::vector3df(1, 1, 1));
  this->setAnimation(kirr::OBJ_ACTION::STAND);
}

GameObject::~GameObject(){

}

void              GameObject::setScale(int const objType, kirr::vector3df const& scale){
  kirr::vector3df extent;

  extent.X = g_scale[objType].X * scale.X;
  extent.Y = g_scale[objType].Y * scale.Y;
  extent.Z = g_scale[objType].Z * scale.Z;
  this->_mesh->setScale(extent);
}

void              GameObject::setAnimation(int const animation){
  kirr::Scene::IAnimatedMeshSceneNode* mesh;

  if (this->_animations.find(animation) == this->_animations.end())
    return ;
  if (!(mesh = reinterpret_cast<kirr::Scene::IAnimatedMeshSceneNode*>(this->_mesh)))
    return ;
  mesh->setFrameLoop(this->_animations[animation].x, this->_animations[animation].y);
}
