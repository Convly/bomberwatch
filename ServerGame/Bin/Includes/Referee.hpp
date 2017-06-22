//
// Referee.hpp for referee in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/ServerGame/Bin/Srcs/Referee/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Sat May 13 14:27:57 2017 JSX
// Last update Fri Jun 16 19:36:46 2017 JSX
//

#ifndef REFEREE_HPP_
#define REFEREE_HPP_

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "StructServer.hpp"
#include "ServerEntity.hpp"
#include "Bomberman.hpp"

namespace bwsg {
    struct                        RefereeEnv
    {
      bool                        _pause;
      bool                        _running;
      int                         _error;
      std::vector<ServerEntity>   _entities;
    };
  class IndieDedicated;
}

namespace bwsg {

  class Referee {
  private:
    bwsg::IndieDedicated &                                                  _indie;
    std::string                                                             _refereePath;
    std::unordered_map<bwsg::ActionType, std::string, bwsg::EnumClassHash>  _actions;
    std::unordered_map<std::string, std::function<bool(int)>>               _defaultFunctions;
    bwsg::RefereeEnv                                                        _env;
    bool                                                                    _io;
    std::unordered_map<int, bool>                                           _lockers;
    std::unordered_map<int, bwsg::socketInfosEmitter>                       _eventsEmitters;
    bwsg::Bomberman                                                         _bomberman;

  public:
    Referee (const std::string &, bwsg::IndieDedicated &);
    virtual ~Referee ();


  /*
  *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *
  *
  *                         DEFAULT ACTIONS MANAGER
  *
  *
  *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  public:
    bool    defaultActionMoveForward(int);
    bool    defaultActionMoveBack(int);
    bool    defaultActionMoveLeft(int);
    bool    defaultActionMoveRight(int);
    bool    defaultAction1(int);
    bool    defaultAction2(int);
    bool    defaultAction3(int);
    bool    defaultAction4(int);
    bool    defaultActionPause(int);
    bool    defaultActionLap(int);




  /*
  *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *
  *
  *                             UTILS FUNCTIONS
  *
  *
  *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  public:
    void                    checkLockactions        (int, bwsg::socketInfosEmitter&);
    bool                    checkCollision          (std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float>);
    void                    dispObj                 (bwsg::ServerEntity&, TriggerType, int);
    bwsg::ServerEntity&     getObjById              (int);
    bwsg::ServerEntity&     getPlayerObjByPlayerId  (int);
    bwsg::ServerEntity&     addObject               (bwsg::ObjectType, std::vector<float>, std::vector<float>, std::vector<float>, bool, bwsg::OBJ_ACTION, int);
    void                    setEventEmitter         (const bwsg::socketInfosEmitter &, size_t);
    void                    checkPlayerAnimation    (int, bwsg::socketInfosEmitter&);
    bool                    redirectAction          (const std::string &, int);
    bool                    startGame               ();
    bool                    initEnv                 (int);
    bool                    core                    ();
    void                    execStates              ();
    void                    kill                    ();



  /*
  *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *
  *
  *                     SERVER --/-> CLIENT INTERACTION
  *
  *
  *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  public:
    bool    sendReceiver    (int, const bwsg::socketInfosReceiver&, bwsg::TriggerType);
    bool    createObject    (int, bwsg::ServerEntity&, bwsg::TriggerType);
    bool    setScale        (int, bwsg::ServerEntity&, std::vector<float>, bwsg::TriggerType);
    bool    setVisibility   (int, bwsg::ServerEntity&, float, bwsg::TriggerType);
    bool    moveObject      (int, bwsg::ServerEntity&, std::vector<float>, bwsg::TriggerType);
    bool    rotateObject    (int, bwsg::ServerEntity&, std::vector<float>, bwsg::TriggerType);
    bool    deleteObject    (int, bwsg::ServerEntity&, bwsg::TriggerType);
    bool    setAnimation    (int, bwsg::ServerEntity&, bwsg::OBJ_ACTION, bwsg::TriggerType);
    bool    createExplosion (int playerID, float length, std::vector<float> pos, std::vector<float> dir, bwsg::TriggerType flag);





  /*
  *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *
  *
  *                                 GETTERS
  *
  *
  *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  public:
    std::unordered_map<int, bool>&                                              getLocks();
    bwsg::IndieDedicated &                                                      getIndie();
    const std::string &                                                         getRefereePath() const;
    std::unordered_map<bwsg::ActionType, std::string, bwsg::EnumClassHash> &    getActions();
    std::unordered_map<std::string, std::function<bool(int)>> &                 getDefaultFunctions();
    bwsg::RefereeEnv &                                                          getEnv();
    bool                                                                        getIo();
    std::unordered_map<int, bwsg::socketInfosEmitter> &                         getEventEmitters();

  };
} /* bwsg */

#endif /* end of include guard: REFEREE_HPP_ */
