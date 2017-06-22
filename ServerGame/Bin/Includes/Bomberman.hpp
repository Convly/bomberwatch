/*
** Bomberman.hpp for cpp_indie_studio in /Users/metge_q/rendu/cpp_indie_studio/ServerGame/Bin/Includes
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Fri Jun 16 11:45:47 2017 Quentin Metge
** Last update Sun Jun 18 17:45:54 2017 Quentin Metge
*/

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <utility>
#include <ctime>
#include <thread>
#include "StructServer.hpp"
#include "ServerEntity.hpp"

#ifndef BOMBERMAN_HPP_
# define BOMBERMAN_HPP_

namespace bwsg{

  class Referee;

  struct PowerUpInfos {
    bwsg::ObjectType      _type;
    std::pair<int, int>   _randRange;
  };

  struct PowerUp {
    PowerUp(){}
    PowerUp(int id, std::vector<float> pos) : _id(id), _pos(pos) {}
    virtual ~PowerUp(){}

  public:
    int                   _id;
    std::vector<float>    _pos;
  };

  struct Player{
    Player(){}
    Player(int id, int ownerId) : _id(id), _ownerId(ownerId){}
    virtual ~Player(){}

  public:
    int                                                 _id;
    int                                                 _ownerId;
    int                                                 _power = 1;
    int                                                 _nbBombs = 1;
    bool                                                _ghost = false;
    bool                                                _penetration = false;
    std::chrono::time_point<std::chrono::system_clock>  _ghostStartTime;
    std::chrono::time_point<std::chrono::system_clock>  _penetrationStartTime;
  };

  struct Bomb{
    Bomb(){}
    Bomb(std::chrono::time_point<std::chrono::system_clock> const& startTime, int id, int ownerId, std::vector<float> pos) : _startTime(startTime), _id(id), _ownerId(ownerId), _pos(pos){}
    virtual ~Bomb(){}

  public:
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    int               _id;
    int               _ownerId;
    std::vector<float> _pos;
    bool              _explosed = false;

  };

  class Bomberman
  {
  public:
    Bomberman(Referee& referee);
    virtual ~Bomberman();

  public:
    static std::vector<float>   findCenterOfCase(std::vector<float>& pos);
    bool                        canPutBomb(int id, std::vector<int> pos);
    void                        checkBombExplosion();
    void                        bombExplosion(Bomb& bomb);

  public:
    void          lap();
    void          generateMap();
    void          resolvePowerUpsInfos();

  public:
    std::vector<std::vector<int>>&    getMap(){return this->_map;}

  public:
    void      addPlayer(int id, int ownerId){this->_players[id] = Player(id, ownerId);}
    void      addBomb(std::chrono::time_point<std::chrono::system_clock> const& startTime, int id, int ownerId, std::vector<float> pos){this->_bombs[id] = Bomb(startTime, id, ownerId, pos);}

  public:
    Player&   getPlayerById(int id);
    Bomb&     getBombById(int id);

  public:
    void      reset();
    bool      generatePowerUps(bwsg::ServerEntity&);
    void      getPowerUps();
    void      checkPowerUpTimer();

  private:
    Referee&  _referee;

  private:
    std::vector<std::vector<int>> _map;
    std::unordered_map<int, Player>           _players;
    std::unordered_map<int, Bomb>             _bombs;
    std::unordered_map<int, PowerUp>          _powerUps;
    std::vector<bwsg::PowerUpInfos>           _powerUpsInfos;
  };
}

#endif
