//
// Referee.cpp for referee in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/ServerGame/Bin/Srcs/Referee/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Sat May 13 18:40:52 2017 JSX
// Last update Fri Jun 16 19:57:59 2017 JSX
//

#include "Referee.hpp"
#include "IndieDedicated.hpp"

static const int FPS_RATE = 100;
static const float BS_SPEED = 1;
static const short X = 0;
static const short Y = 1;
static const short Z = 2;

bwsg::Referee::Referee(const std::string & referee, bwsg::IndieDedicated & indie)
:
  _indie(indie),
  _refereePath(referee),
  _actions({
    {bwsg::ActionType::MOVE_FORWARD,  "FORWARD"},
    {bwsg::ActionType::MOVE_BACK,     "BACK"},
    {bwsg::ActionType::MOVE_LEFT,     "LEFT"},
    {bwsg::ActionType::MOVE_RIGHT,    "RIGHT"},
    {bwsg::ActionType::ACTION1,       "ACTION1"},
    {bwsg::ActionType::ACTION2,       "ACTION2"},
    {bwsg::ActionType::ACTION3,       "ACTION3"},
    {bwsg::ActionType::ACTION4,       "ACTION4"},
    {bwsg::ActionType::PAUSE,         "PAUSE"},
    {bwsg::ActionType::LAP,           "LAP"},
    {bwsg::ActionType::INITENV,       "INITENV"},
  }),
  _defaultFunctions({
    {"FORWARD",   [&](int playerId){return this->defaultActionMoveForward(playerId);}},
    {"BACK",      [&](int playerId){return this->defaultActionMoveBack(playerId);}},
    {"LEFT",      [&](int playerId){return this->defaultActionMoveLeft(playerId);}},
    {"RIGHT",     [&](int playerId){return this->defaultActionMoveRight(playerId);}},
    {"ACTION1",   [&](int playerId){return this->defaultAction1(playerId);}},
    {"ACTION2",   [&](int playerId){return this->defaultAction2(playerId);}},
    {"ACTION3",   [&](int playerId){return this->defaultAction3(playerId);}},
    {"ACTION4",   [&](int playerId){return this->defaultAction4(playerId);}},
    {"PAUSE",     [&](int playerId){return this->defaultActionPause(playerId);}},
    {"LAP",       [&](int playerId){return this->defaultActionLap(playerId);}},
    {"INITENV",   [&](int playerId){return this->initEnv(playerId);}}
  }),
  _io(true),
  _bomberman(*this)
{
  std::srand(std::time(0));
}

bwsg::Referee::~Referee() {

}

/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*
*                        DEFAULT ACTIONS MANAGER
*
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/




/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                     DEFAULT ACTION : MOVE FORWARD
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultActionMoveForward(int playerId) {

  float viewX = -MM_PI * ((this->_eventsEmitters[playerId].angleY + 90) / 180);

  return this->moveObject(playerId, this->getPlayerObjByPlayerId(playerId), {
    BS_SPEED * static_cast<float>(std::cos(viewX)),
    0,
    BS_SPEED * static_cast<float>(std::sin(viewX))
  }, bwsg::TriggerType::ALL_USERS);
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                     DEFAULT ACTION : MOVE BACKWARD
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultActionMoveBack(int playerId) {

  float viewX = -MM_PI * ((this->_eventsEmitters[playerId].angleY + 90) / 180);

  return this->moveObject(playerId, this->getPlayerObjByPlayerId(playerId), {
    -BS_SPEED * static_cast<float>(std::cos(viewX)),
    0,
    -BS_SPEED * static_cast<float>(std::sin(viewX))
  }, bwsg::TriggerType::ALL_USERS);
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                      DEFAULT ACTION : MOVE LEFT
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultActionMoveLeft(int playerId) {

  float viewX = -MM_PI * ((this->_eventsEmitters[playerId].angleY + 90) / 180);

  return this->moveObject(playerId, this->getPlayerObjByPlayerId(playerId), {
    BS_SPEED * static_cast<float>(std::cos(viewX + (MM_PI / 2))),
    0,
    BS_SPEED * static_cast<float>(std::sin(viewX + (MM_PI / 2)))
  }, bwsg::TriggerType::ALL_USERS);
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                     DEFAULT ACTION : MOVE RIGHT
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultActionMoveRight(int playerId) {

  float viewX = -MM_PI * ((this->_eventsEmitters[playerId].angleY + 90) / 180);

  return this->moveObject(playerId, this->getPlayerObjByPlayerId(playerId), {
    -BS_SPEED * static_cast<float>(std::cos(viewX + (MM_PI / 2))),
    0,
    -BS_SPEED * static_cast<float>(std::sin(viewX + (MM_PI / 2)))
  }, bwsg::TriggerType::ALL_USERS);
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                     DEFAULT ACTION : ACTION 1
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultAction1(int playerId) {
  auto player = this->getPlayerObjByPlayerId(playerId);
  auto pos = Bomberman::findCenterOfCase(player.getPosition());
  if (this->_bomberman.canPutBomb(playerId, std::vector<int>({static_cast<int>(pos.at(0)), static_cast<int>(pos.at(1)), static_cast<int>(pos.at(2))})))
    this->dispObj(this->addObject(bwsg::ObjectType::BOMB, pos, player.getView(), {20, 20, 20}, false, bwsg::OBJ_ACTION::DEFAULT, playerId), TriggerType::ALL_USERS, playerId);
  this->_eventsEmitters[playerId].data[static_cast<int>(ActionType::ACTION1)] = 2;
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                    DEFAULT ACTION : ACTION 2
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultAction2(int playerId) {
  this->_eventsEmitters[playerId].data[static_cast<int>(ActionType::ACTION2)] = 2;
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                    DEFAULT ACTION : ACTION 3
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultAction3(int playerId) {
  this->_eventsEmitters[playerId].data[static_cast<int>(ActionType::ACTION3)] = 2;
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                     DEFAULT ACTION : ACTION 4
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultAction4(int playerId) {
  this->_eventsEmitters[playerId].data[static_cast<int>(ActionType::ACTION4)] = 2;
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                     DEFAULT ACTION : PAUSE
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultActionPause(int playerId) {
  this->setScale(playerId, this->_env._entities.back(), {5, 5, 5}, bwsg::TriggerType::ALL_USERS);
  std::cout << "Halt, pause ! " << "(" << playerId <<")" << std::endl;
  this->_eventsEmitters[playerId].data[static_cast<int>(ActionType::PAUSE)] = 2;
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                     DEFAULT ACTION : LAP
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::defaultActionLap(int) {
  return true;
}




/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*
*                             UTILS FUNCTIONS
*
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/




/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                  CHECK AND MODIFY ANIMATION FOR PLAYERS
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

void        bwsg::Referee::checkPlayerAnimation(int playerId, bwsg::socketInfosEmitter& tpInfos) {
  bool isW = false;
  bool cmW = false;

  bwsg::ServerEntity& pl = this->getPlayerObjByPlayerId(playerId);

  for (int i = 0; i < 4; i++) {
    isW = isW || (this->_eventsEmitters[playerId].data[i] == 1);
    cmW = cmW || (tpInfos.data[i] == 1);
  }

  if (!isW && cmW) {
    this->setAnimation(playerId, pl, bwsg::OBJ_ACTION::MOVE_2, bwsg::TriggerType::ALL_USERS);
  } else if (isW && !cmW) {
    this->setAnimation(playerId, pl, bwsg::OBJ_ACTION::STAND, bwsg::TriggerType::ALL_USERS);
  }
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                  CHECK AND PREVENT USE OF LOCKED ACTION
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

void        bwsg::Referee::checkLockactions(int slotId, bwsg::socketInfosEmitter& tpInfos) {
  for (short i = 4; i < NB_ACTION; i++) {
    if (  this->_eventsEmitters[slotId].data[i] == static_cast<int>(bwsg::EmitterActionState::LOCKED) &&
          tpInfos.data[i] == static_cast<int>(bwsg::EmitterActionState::ON))
      tpInfos.data[i] = static_cast<int>(bwsg::EmitterActionState::LOCKED);
    else if (tpInfos.data[i] == static_cast<int>(bwsg::EmitterActionState::OFF))
      tpInfos.data[i] = static_cast<int>(bwsg::EmitterActionState::OFF);
    else if ( this->_eventsEmitters[slotId].data[i] == static_cast<int>(bwsg::EmitterActionState::OFF) &&
              tpInfos.data[i] == static_cast<int>(bwsg::EmitterActionState::ON))
      tpInfos.data[i] = static_cast<int>(bwsg::EmitterActionState::ON);
  }
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                           SET EVENT EMITTER
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

void    bwsg::Referee::setEventEmitter(const bwsg::socketInfosEmitter & infos, size_t playerId) {
  bwsg::socketInfosEmitter tpInfos = infos;
  /*
  * Check for SIGKILL
  */
  if (static_cast<bwsg::CommandType>(infos.commandType) == bwsg::CommandType::AS && infos.data[0] == 1) {
    this->kill();
    return;
  }

  /*
  *  Catch if the player slot is locked (eg: when his player has been destroyed)
  */
  if (this->_lockers[playerId]) return;


  if (this->_io && this->_env._running && !(this->_env._error)) {
    /*
    *   If the view has change from the last record, we update it
    */
    if (this->_eventsEmitters[playerId].angleY != tpInfos.angleY) {
      bwsg::ServerEntity& pl = this->getPlayerObjByPlayerId(playerId);
      this->rotateObject(playerId, pl, {pl.getView().at(0), tpInfos.angleY, pl.getView().at(2)}, bwsg::TriggerType::O_ONLY);
    }

    /*
    *   Check / Assign new event emitter
    */
    this->checkLockactions(playerId, tpInfos);
    this->checkPlayerAnimation(playerId, tpInfos);
    this->_eventsEmitters[playerId] = tpInfos;
  }
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                           KILL && QUIT REFEREE
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

void          bwsg::Referee::kill() {
  this->_io = false;
  this->_env._running = false;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                CORE METHOD / ENTRY POINT OF THE REFEREEE
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::core() {
  while (this->_io) {
    std::cout << "Starting new game in 5 seconds" << std::endl;
    this->redirectAction("INITENV", -1);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    if (!this->startGame()) {
      this->_io = false;
    }
  }
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                REDIRECT ACTION (CHAISCRIPT / DEFAULT)
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::redirectAction(const std::string & action, int playerId) {
  if (false) {
    std::cout << "Call chaiscript function interpretor" << std::endl;
    return true;
  } else {
    return this->_defaultFunctions[action](playerId);
  }
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                    EXEC ALL ACTIONS BY THEIR STATES
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

void    bwsg::Referee::execStates() {
  for (auto it = this->_eventsEmitters.begin(); it != this->_eventsEmitters.end(); it++) {
    for (short i = 0; i < NB_ACTION; i++) {
      if (it->second.data[i] == 1) {
        this->redirectAction(this->_actions[static_cast<bwsg::ActionType>(i)], it->first);
      }
    }
  }
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*          INIT ALL THE REFEREE ENVIRONEMENT (CUBE CREATION, ETC...)
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::initEnv(int pid) {
  std::vector<std::vector<int>>& map = this->_bomberman.getMap();

  this->_env = {0, 1, 0, {}};
  for (auto it = this->_env._entities.begin(); it != this->_env._entities.end(); it++) {
    this->deleteObject(pid, *it, bwsg::TriggerType::ALL_USERS);
  }

  for (size_t y = 0; y < map.size(); y++){
    for (size_t x = 0; x < map[y].size(); x++){
      if (static_cast<bwsg::ObjectType>(map[y][x]) != bwsg::ObjectType::UNKNOWN){
        this->addObject(static_cast<bwsg::ObjectType>(map[y][x]), {static_cast<float>(x) * 30 - 360, 5, static_cast<float>(y) * 30 - 360}, {0, 0, 0}, {30, 30, 30}, true, bwsg::OBJ_ACTION::DEFAULT, -1);
      }
    }
  }

  for (auto it = this->_env._entities.begin(); it != this->_env._entities.end(); it++) {
    this->dispObj(*it, TriggerType::ALL_USERS, pid);
  }
  std::cout << "Initializing the game... (" << this->_env._entities.size() << ")" << std::endl;
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*            START A NEW GAME AND CONTAIN ASSOCIATED MAIN LOOP
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::startGame() {
  while (this->_env._running && !this->_env._error) {
    this->_bomberman.lap();
    this->execStates();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS_RATE));
  }
  return this->_env._error == 0;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                           CHECK COLLISION
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool                    bwsg::Referee::checkCollision(std::vector<float> pA, std::vector<float> sA, std::vector<float> pB, std::vector<float> sB){
  std::vector<float>    AMin = {pA.at(0) - (sA.at(0) / 2), pA.at(1) - (sA.at(1) / 2), pA.at(2) - (sA.at(2) / 2)};
  std::vector<float>    AMax = {AMin.at(0) + sA.at(0), AMin.at(1) + sA.at(1), AMin.at(2) + sA.at(2)};
  std::vector<float>    BMin = {pB.at(0) - (sB.at(0) / 2), pB.at(1) - (sB.at(1) / 2), pB.at(2) - (sB.at(2) / 2)};
  std::vector<float>    BMax = {BMin.at(0) + sB.at(0), BMin.at(1) + sB.at(1), BMin.at(2) + sB.at(2)};

  return (AMin[X] <= BMax[X] && AMax[X] >= BMin[X])
          && (AMin[Y] <= BMax[Y] && AMax[Y] >= BMin[Y])
          && (AMin[Z] <= BMax[Z] && AMax[Z] >= BMin[Z]);
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                           GET OBJECT BY IT'S ID
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bwsg::ServerEntity&     bwsg::Referee::getObjById(int objId) {
  return *(std::find_if (this->_env._entities.begin(), this->_env._entities.end(), [&](bwsg::ServerEntity& item) {
    return item.getID() == objId;
  }));
}


/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                      GET OBJECT ASSOCIATED TO A PLAYER
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bwsg::ServerEntity&     bwsg::Referee::getPlayerObjByPlayerId(int slotID) {
  return *(std::find_if (this->_env._entities.begin(), this->_env._entities.end(), [&](bwsg::ServerEntity& item) {
    return item.getType() == bwsg::ObjectType::PLAYER && item.getOwner() == slotID;
  }));
}


/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                                 ADD OBJECT
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bwsg::ServerEntity&     bwsg::Referee::addObject(bwsg::ObjectType type, std::vector<float> pos, std::vector<float> view, std::vector<float> scale, bool collider, bwsg::OBJ_ACTION animation, int playerId) {
  this->_env._entities.push_back(ServerEntity(type, pos, view, scale, collider, animation, playerId));
  switch (static_cast<int>(this->_env._entities.back().getType())){
    case static_cast<int>(ObjectType::PLAYER):
      this->_bomberman.addPlayer(this->_env._entities.back().getID(), this->_env._entities.back().getOwner());
      break;
    case static_cast<int>(ObjectType::BOMB):
      this->_bomberman.addBomb(std::chrono::system_clock::now(), this->_env._entities.back().getID(), this->_env._entities.back().getOwner(), this->_env._entities.back().getPosition());
      break;
  }
  return this->_env._entities.back();
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*   DISPLAY OBJECT (CALL SUB METHODS SUCH AS CREATE, SCALE, ROTATE, VISIBILITY)
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

void                    bwsg::Referee::dispObj(bwsg::ServerEntity& item, TriggerType trigger, int playerID) {
  this->createObject(playerID, item, trigger);
  this->setScale(playerID, item, item.getScale(), trigger);
  this->rotateObject(playerID, item, item.getView(), trigger);
  this->setVisibility(playerID, item, 1, trigger);
}





/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*
*                     SERVER --/-> CLIENT INTERACTION
*
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/




/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                           TRIGGER CLIENT BY FLAG
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::sendReceiver(int playerID, const bwsg::socketInfosReceiver& ret, bwsg::TriggerType trigger) {
  if (trigger == TriggerType::ALL_USERS) {
    this->_indie.getServerManager().getServerGame().commandWriteAll(ret);
  } else if (trigger == TriggerType::O_ONLY){
    this->_indie.getServerManager().getServerGame().commandWriteOthers(playerID, ret);
  } else if (trigger == TriggerType::U_ONLY) {
    this->_indie.getServerManager().getServerGame().commandWrite(playerID, ret);
  } else {
    return false;
  }
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                               CREATE OBJECT
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::createObject(int playerID, bwsg::ServerEntity& item, bwsg::TriggerType flag) {
  auto pos = item.getPosition();
  return this->sendReceiver(playerID, // ID of the player who send the command
    {
      item.getID(),         // ID of the object
      item.getOwner(),      // Owner for the object (useful when it's about the creation of a player)
      static_cast<short>(bwsg::CommandIdentifier::CREATE_OBJECT), // 'create' method identifier
      {
        static_cast<float>(item.getType()),   // Type of the object
        pos.at(0), pos.at(1), pos.at(2)       // Initial position for the object
      }
    }, flag); // Trigger type
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                               SET OBJECT SCALE
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::setScale(int playerID, bwsg::ServerEntity& item, std::vector<float> scales, bwsg::TriggerType flag){
  /*
  * Set scale of the local object
  */
  item.setScale(scales);

  return this->sendReceiver(playerID, // ID of the player who send the command
    {
      item.getID(),         // ID of the object
      item.getOwner(),      // Owner for the object (useful when it's about the creation of a player)
      static_cast<short>(bwsg::CommandIdentifier::SET_SCALE),   // 'scale' method identifier
      {scales.at(0), scales.at(1), scales.at(2), static_cast<float>(item.getType())}    // New scale for the object + item type
    }, flag); // Trigger type
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                            SET OBJECT VISIBILITY
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::setVisibility(int playerID, bwsg::ServerEntity& item, float visibility, bwsg::TriggerType flag) {
  return this->sendReceiver(playerID,   // ID of the player who send the command
    {
      item.getID(),         // ID of the object
      item.getOwner(),      // Owner for the object (useful when it's about the creation of a player)
      static_cast<short>(bwsg::CommandIdentifier::SET_OBJECT_VISIBILITY), // 'visibility' method identifier
      {visibility}    // new visibility for the object
    }, flag); // Trigger type
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                            SET OBJECT ANIMATION
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::setAnimation(int playerID, bwsg::ServerEntity& item, bwsg::OBJ_ACTION animation, bwsg::TriggerType flag) {
  return this->sendReceiver(playerID,   // ID of the player who send the command
    {
      item.getID(),         // ID of the object
      item.getOwner(),      // Owner for the object (useful when it's about the creation of a player)
      static_cast<short>(bwsg::CommandIdentifier::SET_OBJECT_ANIMATION), // 'set animation' method identifier
      {static_cast<float>(animation)}    // new visibility for the object
    }, flag); // Trigger type
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                                 MOVE OBJECT
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool    bwsg::Referee::moveObject(int playerID, bwsg::ServerEntity& item, std::vector<float> dir, bwsg::TriggerType flag)
{
  /*
  * Check and get new position for the playerID
  */
  std::vector<float>& pos = item.getPosition();
  std::vector<float> npos = {pos.at(0) + dir.at(0), pos.at(1) + dir.at(1), pos.at(2) + dir.at(2)};
  for (auto it = this->_env._entities.begin(); it != this->_env._entities.end(); it++) {
    if (it->getID() != item.getID() && it->getCollider() && checkCollision(npos, item.getScale(), it->getPosition(), it->getScale())) {
      return false;
    }
  }

  /*
  * Set local position of the object
  */
  item.setPosition(npos);

  this->sendReceiver(playerID,    // ID of the player who send the command
    {
      item.getID(),     // ID of the object
      item.getOwner(),  // Owner for the object (useful when it's about the creation of a player)
      static_cast<short>(bwsg::CommandIdentifier::MOVE_OBJECT), // 'move' method identifier
      {pos.at(0), pos.at(1), pos.at(2)} // New position for the object
  }, flag); // Trigger type
  return true;
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                                 ROTATE OBJECT
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
bool   bwsg::Referee::rotateObject(int playerID, bwsg::ServerEntity& item, std::vector<float> gview, bwsg::TriggerType flag) {
  item.setView(gview); // Set the veiw for the local object
  return this->sendReceiver(playerID,   // ID of the player who send the command
    {
      item.getID(),       // ID of the object
      item.getOwner(),    // Owner for the object (useful when it's about the creation of a player)
      static_cast<short>(bwsg::CommandIdentifier::ROTATE_OBJECT), // 'rotate' method identifier
      {item.getView().at(0), item.getView().at(1), item.getView().at(2)} // New rotation for the object
    }, flag);   // Trigger type
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                             CREATE EXPLOSION
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool   bwsg::Referee::createExplosion(int playerID, float length, std::vector<float> pos, std::vector<float> dir, bwsg::TriggerType flag) {
  return this->sendReceiver(playerID,   // ID of the player who send the command
    {
      -1,       // ID of the object
      -1,       // Owner for the object (useful when it's about the creation of a player)
      static_cast<short>(bwsg::CommandIdentifier::CREATE_EXPLO), // 'rotate' method identifier
      {length, pos.at(0), pos.at(2), dir.at(0), dir.at(2)} // New rotation for the object
    }, flag);   // Trigger type
}



/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*                               DELETE OBJECT
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

bool   bwsg::Referee::deleteObject(int playerID, bwsg::ServerEntity& item, bwsg::TriggerType flag) {
  bool search = false;

  /*
  * If the removed item is a player, we prevent him to send other commands
  */
  if (item.getType() == bwsg::ObjectType::PLAYER) {
    this->_lockers[item.getOwner()] = true;
    for (int i = 0; i < bwsg::NB_ACTION; i++) {
      this->_eventsEmitters[item.getOwner()].data[i] = 0;
    }
  }

  bwsg::socketInfosReceiver ret = {
    item.getID(),      // ID of the object
    item.getOwner(),   // Owner for the object (useful when it's about the creation of a player)
    static_cast<short>(bwsg::CommandIdentifier::REMOVE_OBJECT),   // 'remove' method identifier
    {0}  // Empty params
  };

  /*
  * We erase the object associated in the entity vector
  */

  for (auto it = this->_env._entities.begin(); it != this->_env._entities.end();) {
    if (it->getID() == item.getID()) {
      search = true;
      it = this->_env._entities.erase(it);
      break;
    }
    else
      ++it;
  }

  /*
  * If the object exist, we send the delete action message
  */
  if (search) {
    return this->sendReceiver(playerID, ret, flag);
  }

  return false;
}





/*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*
*                                 GETTERS
*
*
*  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/



bwsg::IndieDedicated &                                                       bwsg::Referee::getIndie()               {return this->_indie;}
const std::string &                                                          bwsg::Referee::getRefereePath() const   {return this->_refereePath;}
std::unordered_map<bwsg::ActionType, std::string, bwsg::EnumClassHash> &     bwsg::Referee::getActions()             {return this->_actions;}
std::unordered_map<std::string, std::function<bool(int)>> &                  bwsg::Referee::getDefaultFunctions()    {return this->_defaultFunctions;}
bwsg::RefereeEnv &                                                           bwsg::Referee::getEnv()                 {return this->_env;}
bool                                                                         bwsg::Referee::getIo()                  {return this->_io;}
std::unordered_map<int, bwsg::socketInfosEmitter> &                          bwsg::Referee::getEventEmitters()       {return this->_eventsEmitters;}
std::unordered_map<int, bool>&                                               bwsg::Referee::getLocks()               {return this->_lockers;}


// ======================================== END ================================================ //
