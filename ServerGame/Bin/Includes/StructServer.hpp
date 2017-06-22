//
// Struct.hpp for struct in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Libs/Bin/Utils/Srcs/Includes/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Wed May 10 17:29:06 2017 JSX
// Last update Fri Jun 16 03:27:05 2017 JSX
//

#ifndef STRUCTS_SERVER_HPP_
#define STRUCTS_SERVER_HPP_

#include <iostream>

namespace bwsg {

  # define MM_PI 3.1416

  struct      EnumClassHash
  {
    template <typename T>
    std::size_t operator()(T t) const
      {
        return static_cast<std::size_t>(t);
      }
  };

  enum class CommandType{
    UNKNOWN = -1,
    ACTION_PLAYER = 0,
    AS = 1,
    REGISTER = 2
  };

  const short NB_ACTION = 9;

  enum class ActionType{
    MOVE_FORWARD = 0,
    MOVE_BACK = 1,
    MOVE_LEFT,
    MOVE_RIGHT,
    ACTION1,
    ACTION2,
    ACTION3,
    ACTION4,
    PAUSE,
    LAP,
    INITENV
  };

  enum class CommandIdentifier {
    UNKNOWN = -1,
    CREATE_OBJECT = 0,
    MOVE_OBJECT = 1,
    ROTATE_OBJECT,
    REMOVE_OBJECT,
    SET_OBJECT_VISIBILITY,
    SET_OBJECT_ANIMATION,
    SET_SCALE,
    CREATE_EXPLO
  };

  enum class TriggerType {
    ALL_USERS = 0,
    O_ONLY = 1,
    U_ONLY = 2
  };

  enum class ObjectType{
    UNKNOWN = -1,
    PLAYER = 0,
    D_CUBE = 1,
    ND_CUBE = 2,
    PU_POWER = 3,
    PU_AMOUNT = 4,
    PU_GHOST = 5,
    PU_PENETRATION = 6,
    BOMB = 7,
  };

  enum class OBJ_ACTION
    {
      STAND,
      PUT,
      MOVE_1,
      MOVE_2,
      MOVE_BACK,
      SHOOT_1,
      SHOOT_2,
      DEATH_1,
      DEATH_2,
      DEAD_1,
      DEAD_2,
      DEFAULT,
    };

  enum class EmitterActionState {
    OFF = 0,
    ON = 1,
    LOCKED = 2
  };

  struct      socketInfosReceiver
  {
    int       objId;
    int       playerId;
    short     command;
    float     data[5];
  };

  struct      socketInfosEmitter
  {
    int       playerId;
    short     commandType;
    float     angleY;
    short     data[NB_ACTION];
  };
} /* utils */

#endif /* end of include guard: STRUCTS_UTILS_HPP_ */
