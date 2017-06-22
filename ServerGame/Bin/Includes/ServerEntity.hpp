//
// ServerEntity.hpp for ServerEntity in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/ServerGame/Bin/Includes/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Tue May 30 18:12:49 2017 JSX
// Last update Thu Jun 15 00:07:46 2017 JSX
//

#ifndef SERVER_ENTITY_HPP_
#define SERVER_ENTITY_HPP_


#include <vector>
#include "StructServer.hpp"

namespace bwsg {
  class ServerEntity {
  private:
    int                       _objId;
    bwsg::ObjectType          _objType;
    std::vector<float>        _pos;
    std::vector<float>        _view;
    std::vector<float>        _scale;
    bool                      _collider;
    bwsg::OBJ_ACTION          _animation;
    int                       _owner;

  public:
    ServerEntity (bwsg::ObjectType, std::vector<float>, std::vector<float>, std::vector<float>, bool, bwsg::OBJ_ACTION, int playerId = -1);
    virtual ~ServerEntity ();

  public:
    std::vector<float>&     getPosition();
    std::vector<float>&     getView();
    std::vector<float>&     getScale();
    int                     getID() const;
    bwsg::ObjectType        getType() const;
    int                     getOwner() const;
    bool                    getCollider() const;
    bwsg::OBJ_ACTION        getAnimation() const;

  public:
    void                    setCollider(bool);
    void                    setPosition(const std::vector<float>&);
    void                    setView(const std::vector<float>&);
    void                    setScale(const std::vector<float>&);
    void                    setId(int);
    void                    setAnimation(bwsg::OBJ_ACTION);
 };
} /* bwsg */

#endif /* end of include guard: SERVER_ENTITY_HPP_ */
