//
// ServerEntity.cpp for serverEntity in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/ServerGame/Bin/Srcs/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Tue May 30 18:17:04 2017 JSX
// Last update Thu Jun 15 00:14:43 2017 JSX
//

#include "ServerEntity.hpp"

static int C_ENTITY_ID = 0;

bwsg::ServerEntity::ServerEntity(bwsg::ObjectType objType, std::vector<float> pos, std::vector<float> view, std::vector<float> scale, bool collider, bwsg::OBJ_ACTION animation, int playerId)
:
  _objId(C_ENTITY_ID),
  _objType(objType),
  _pos(pos),
  _view(view),
  _scale(scale),
  _collider(collider),
  _animation(animation),
  _owner(playerId)
{
  C_ENTITY_ID++;
}

bwsg::ServerEntity::~ServerEntity() {

}

// ------------------------------------

std::vector<float>&     bwsg::ServerEntity::getPosition()         {return this->_pos;}
std::vector<float>&     bwsg::ServerEntity::getView()             {return this->_view;}
std::vector<float>&     bwsg::ServerEntity::getScale()            {return this->_scale;}
int                     bwsg::ServerEntity::getID() const         {return this->_objId;}
bwsg::ObjectType        bwsg::ServerEntity::getType() const       {return this->_objType;}
int                     bwsg::ServerEntity::getOwner() const      {return this->_owner;}
bool                    bwsg::ServerEntity::getCollider() const   {return this->_collider;}
bwsg::OBJ_ACTION        bwsg::ServerEntity::getAnimation() const  {return this->_animation;}

void                    bwsg::ServerEntity::setCollider(bool collider)                    {this->_collider = collider;}
void                    bwsg::ServerEntity::setPosition(const std::vector<float>& pos)    {this->_pos = pos;}
void                    bwsg::ServerEntity::setView(const std::vector<float>& view)       {this->_view = view;}
void                    bwsg::ServerEntity::setScale(const std::vector<float>& scale)     {this->_scale = scale;}
void                    bwsg::ServerEntity::setId(int id)                                 {this->_objId = id;}
void                    bwsg::ServerEntity::setAnimation(bwsg::OBJ_ACTION animation)      {this->_animation = animation;}
