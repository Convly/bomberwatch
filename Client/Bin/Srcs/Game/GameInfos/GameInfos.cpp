//
// GameInfos.cpp for GameInfos in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/GameInfos/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 23:43:09 2017 jsx
// Last update Sat Jun 17 08:53:12 2017 Maxime Cauvin
//

#include "GameClient.hpp"
#include "GameInfos.hpp"

std::vector<std::string> skins = {
  {"./Client/Assets/Textures/Player/soldier_gold.jpg"},
  {"./Client/Assets/Textures/Player/soldier_aqua.jpg"},
  {"./Client/Assets/Textures/Player/soldier_aqua_all.jpg"},
  {"./Client/Assets/Textures/Player/soldier_blue.jpg"},
  {"./Client/Assets/Textures/Player/soldier_blue_all.jpg"},
  {"./Client/Assets/Textures/Player/soldier_camo.jpg"},
  {"./Client/Assets/Textures/Player/soldier_dark_green.jpg"},
  {"./Client/Assets/Textures/Player/soldier_dark_green_red.jpg"},
  {"./Client/Assets/Textures/Player/soldier_fire.jpg"},
  {"./Client/Assets/Textures/Player/soldier_green.jpg"}
};

indie::module::GameInfos::GameInfos(GameClient& gameClient, kirr::Kirrlicht & kirrlicht)
:
  _gameClient(gameClient),
  _serverInfos(*this),
  _kirrlicht(kirrlicht),
  _objectCreation({
    {static_cast<int>(bwsg::ObjectType::PLAYER), [&] (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){this->createPlayer(playerId, objId, pos, rotation);}},
    {static_cast<int>(bwsg::ObjectType::D_CUBE), [&] (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){this->createDCube(playerId, objId, pos, rotation);}},
    {static_cast<int>(bwsg::ObjectType::ND_CUBE), [&] (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){this->createNDCube(playerId, objId, pos, rotation);}},
    {static_cast<int>(bwsg::ObjectType::PU_POWER), [&] (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){this->createPUPower(playerId, objId, pos, rotation);}},
    {static_cast<int>(bwsg::ObjectType::PU_AMOUNT), [&] (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){this->createPUAmount(playerId, objId, pos, rotation);}},
    {static_cast<int>(bwsg::ObjectType::PU_GHOST), [&] (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){this->createPUGhost(playerId, objId, pos, rotation);}},
    {static_cast<int>(bwsg::ObjectType::PU_PENETRATION), [&] (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){this->createPUPenetration(playerId, objId, pos, rotation);}},
    {static_cast<int>(bwsg::ObjectType::BOMB), [&] (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){this->createBomb(playerId, objId, pos, rotation);}}
  }),
  _isConnect(false),
  _commands({
    {static_cast<int>(bwsg::CommandIdentifier::CREATE_OBJECT), [&] (const bwsg::socketInfosReceiver& info){this->createObject(info);}},
    {static_cast<int>(bwsg::CommandIdentifier::CREATE_EXPLO), [&] (const bwsg::socketInfosReceiver& info){this->createExplosion(info);}},
    {static_cast<int>(bwsg::CommandIdentifier::REMOVE_OBJECT), [&] (const bwsg::socketInfosReceiver& info){this->removeObject(info);}},
    {static_cast<int>(bwsg::CommandIdentifier::SET_OBJECT_VISIBILITY), [&] (const bwsg::socketInfosReceiver& info){this->setObjectVisibility(info);}},
    {static_cast<int>(bwsg::CommandIdentifier::SET_OBJECT_ANIMATION), [&] (const bwsg::socketInfosReceiver& info){this->setObjectAnimation(info);}},
    {static_cast<int>(bwsg::CommandIdentifier::MOVE_OBJECT), [&] (const bwsg::socketInfosReceiver& info){this->setObjectPosition(info);}},
    {static_cast<int>(bwsg::CommandIdentifier::ROTATE_OBJECT), [&] (const bwsg::socketInfosReceiver& info){this->setObjectRotation(info);}},
    {static_cast<int>(bwsg::CommandIdentifier::SET_SCALE), [&] (const bwsg::socketInfosReceiver& info){this->setObjectScale(info);}}
  })
{
}

indie::module::GameInfos::~GameInfos() {

}

indie::module::GameClient&    indie::module::GameInfos::getGameClient() {
  return this->_gameClient;
}

indie::module::GameServerInfos &  indie::module::GameInfos::getServerInfos(){
  return this->_serverInfos;
}

std::unordered_map<size_t, indie::module::GameObject> &indie::module::GameInfos::getObjects()
{
  return (this->_objects);
}
std::queue<bwsg::socketInfosReceiver> &indie::module::GameInfos::getUpdateQueue()
{
  return (this->_updateQueue);
}

/************/
/* RECEIVER */
/************/
void          indie::module::GameInfos::update(const bwsg::socketInfosReceiver& info){
  if (this->_commands.find(info.command) != this->_commands.end()){
    this->_updateQueue.push(info);
  }
  else
    std::cerr << "Error: Command unknown (" << info.command << ")" << std::endl;
}

void          indie::module::GameInfos::loadObjects(){
  while (!this->_updateQueue.empty()){
    if (this->_commands.find(this->_updateQueue.front().command) != this->_commands.end())
      this->_commands[this->_updateQueue.front().command](this->_updateQueue.front());
    this->_updateQueue.pop();
  }
}

void          indie::module::GameInfos::popExplosions(){
  for (size_t i = 0; i < this->_explosions.size();){
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-this->_explosions.at(i)._startTime).count() > 250){
      this->_explosions.at(i)._mesh->setEmitter(0);
      this->_explosions.erase(this->_explosions.begin() + i);
      i = 0;
    }
    else
      i++;
  }
}

/************/
/* COMMANDS */
/************/
void          indie::module::GameInfos::createExplosion(const bwsg::socketInfosReceiver& info){
  if (this->_objects.find(info.objId) == this->_objects.end())
    {
      auto ps = this->_kirrlicht.addParticleSystem("./Client/Assets/Textures/Sprites/fire.bmp", kirr::vector3df(info.data[1], 15, info.data[2]), kirr::vector3df(2.5, 2.5, 2.5));
      if (ps){
        this->_kirrlicht.addParticleEmitter(ps, info.data[0] * 2.5, kirr::vector3df(info.data[3], 0, info.data[4]));
        this->_explosions.push_back(Explosion(ps, std::chrono::system_clock::now()));
      }
    }
}

void          indie::module::GameInfos::setObjectVisibility(const bwsg::socketInfosReceiver& info){
  if (this->_objects.find(info.objId) != this->_objects.end())
    this->_objects.at(info.objId).getMesh()->setVisible(static_cast<bool>(info.data[0]));
}

void          indie::module::GameInfos::setObjectAnimation(const bwsg::socketInfosReceiver& info){
  if (this->_objects.find(info.objId) != this->_objects.end())
    this->_objects.at(info.objId).setAnimation(info.data[0]);
}

void          indie::module::GameInfos::createObject(const bwsg::socketInfosReceiver& info){
  if (this->_objects.find(info.objId) == this->_objects.end() && this->_objectCreation.find(info.data[0]) != this->_objectCreation.end()){
    this->_objectCreation[info.data[0]](info.playerId, info.objId, kirr::Pos<float>(info.data[1], info.data[2], info.data[3]), kirr::Pos<float>());
    this->_objects.at(info.objId).getMesh()->setVisible(false);
  }
}

void          indie::module::GameInfos::removeObject(const bwsg::socketInfosReceiver& info){
  if (this->_objects.find(info.objId) != this->_objects.end()) {
    this->_kirrlicht.getSceneManager()->addToDeletionQueue(this->_objects[info.objId].getMesh());
    if (this->_objects.at(info.objId).getMesh() == this->_gameClient.getPlayerOne()->getObjectBinded()){
      this->_gameClient.getPlayerOne()->setObjectBinded(nullptr);
      this->_gameClient.getPlayerOne()->getCamera()->setPosition(specPos);
      this->_gameClient.getPlayerOne()->getCamera()->setTarget(specTarget);
    }
    else if (this->_objects.at(info.objId).getMesh() == this->_gameClient.getPlayerTwo()->getObjectBinded()){
      this->_gameClient.getPlayerTwo()->setObjectBinded(nullptr);
      this->_gameClient.getPlayerTwo()->getCamera()->setPosition(specPos);
      this->_gameClient.getPlayerTwo()->getCamera()->setTarget(specTarget);
    }
    this->_objects.erase(info.objId);
  }
}

void          indie::module::GameInfos::setObjectPosition(const bwsg::socketInfosReceiver& info){
  if (this->_objects.find(info.objId) != this->_objects.end()){
    this->_objects.at(info.objId).getMesh()->setPosition(kirr::vector3df(info.data[0], info.data[1], info.data[2]));
  }
}

void          indie::module::GameInfos::setObjectRotation(const bwsg::socketInfosReceiver& info){
  if (this->_objects.find(info.objId) != this->_objects.end()){
    if (this->_objects.at(info.objId).getMesh() != this->_gameClient.getPlayerOne()->getObjectBinded() && this->_objects.at(info.objId).getMesh() != this->_gameClient.getPlayerTwo()->getObjectBinded())
      this->_objects.at(info.objId).getMesh()->setRotation(kirr::vector3df(info.data[0], info.data[1], info.data[2]));
  }
}

void          indie::module::GameInfos::setObjectScale(const bwsg::socketInfosReceiver& info){
  if (this->_objects.find(info.objId) != this->_objects.end()){
    kirr::vector3df scale;
    scale.X = info.data[0];
    scale.Y = info.data[1];
    scale.Z = info.data[2];
    this->_objects.at(info.objId).setScale(info.data[3], scale);
  }
}

/*********************/
/* Create ObjectType */
/*********************/
void          indie::module::GameInfos::createPlayer(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){
  int         skin = 0;

  if (this->_gameClient.getPlayerOne()->getId() != 1 && this->_gameClient.getPlayerOne()->getId() != 2)
    skin = this->_gameClient.getModuleLoader().getNexusAPI().getPlayerColor(playerId);
  if (playerId == this->_gameClient.getPlayerOne()->getId()){
    if (this->_gameClient.getPlayerOne().get()->getObjectBinded() != nullptr){
      return ;
    }
    auto player = this->_kirrlicht.addAnimatedModel(pos, "./Client/Assets/Objects/Soldier_final.ms3d", skins.at(skin));
    player->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
    auto tmp = indie::module::GameObject(player, static_cast<int>(bwsg::ObjectType::PLAYER));
    this->_objects.insert(std::pair<size_t, GameObject> (objId, tmp));
    this->_gameClient.getPlayerOne().get()->setObjectBinded(player);
  }
  else if (playerId == this->_gameClient.getPlayerTwo()->getId()){
    if (this->_gameClient.getPlayerTwo().get()->getObjectBinded() != nullptr){
      return ;
    }
    auto player = this->_kirrlicht.addAnimatedModel(pos, "./Client/Assets/Objects/Soldier_final.ms3d", skins.at(skin));
    player->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
    auto tmp = indie::module::GameObject(player, static_cast<int>(bwsg::ObjectType::PLAYER));
    this->_objects.insert(std::pair<size_t, GameObject> (objId, tmp));
    this->_gameClient.getPlayerTwo().get()->setObjectBinded(player);
  }
  else{
    auto player = this->_kirrlicht.addAnimatedModel(pos, "./Client/Assets/Objects/Soldier_final.ms3d", skins.at(skin));
    player->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
    auto tmp = indie::module::GameObject(player, static_cast<int>(bwsg::ObjectType::PLAYER));
    this->_objects.insert(std::pair<size_t, GameObject> (objId, tmp));
  }
}

void          indie::module::GameInfos::createDCube(int , size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){
  auto cube = this->_kirrlicht.addModel(pos, "./Client/Assets/Objects/D_Cube.obj", "");
  auto tmp = indie::module::GameObject(cube, static_cast<int>(bwsg::ObjectType::D_CUBE));
  cube->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
  this->_objects.insert(std::pair<size_t, GameObject> (objId, tmp));
}

void          indie::module::GameInfos::createNDCube(int , size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){
  auto cube = this->_kirrlicht.addModel(pos, "./Client/Assets/Objects/ND_Cube.obj", "");
  auto tmp = indie::module::GameObject(cube, static_cast<int>(bwsg::ObjectType::ND_CUBE));
  cube->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
  this->_objects.insert(std::pair<size_t, GameObject> (objId, tmp));
}

void          indie::module::GameInfos::createPUPower(int , size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){
  auto pu = this->_kirrlicht.addModel(pos, "./Client/Assets/Objects/PU_Power.obj", "");
  auto tmp = indie::module::GameObject(pu, static_cast<int>(bwsg::ObjectType::PU_POWER));
  pu->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
  this->_objects.insert(std::pair<size_t, GameObject> (objId, tmp));
}

void          indie::module::GameInfos::createPUAmount(int , size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){
  auto pu = this->_kirrlicht.addModel(pos, "./Client/Assets/Objects/PU_Amount.obj", "");
  pu->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
  auto tmp = indie::module::GameObject(pu, static_cast<int>(bwsg::ObjectType::PU_AMOUNT));
  this->_objects.insert(std::pair<size_t, GameObject>(objId, tmp));
}

void          indie::module::GameInfos::createPUGhost(int , size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){
  auto cube = this->_kirrlicht.addModel(pos, "./Client/Assets/Objects/PU_Ghost.obj", "");
  cube->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
  auto tmp = indie::module::GameObject(cube, static_cast<int>(bwsg::ObjectType::PU_GHOST));
  this->_objects.insert(std::pair<size_t, GameObject>(objId, tmp));
}

void          indie::module::GameInfos::createPUPenetration(int , size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){
  auto pu = this->_kirrlicht.addModel(pos, "./Client/Assets/Objects/PU_Penetration.obj", "");
  pu->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
  auto tmp = indie::module::GameObject(pu, static_cast<int>(bwsg::ObjectType::PU_PENETRATION));
  this->_objects.insert(std::pair<size_t, GameObject>(objId, tmp));

}

void          indie::module::GameInfos::createBomb(int , size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation){
  auto bomb = this->_kirrlicht.addModel(pos, "./Client/Assets/Objects/bomb.3DS", "./Client/Assets/Textures/Colors/gold.jpg");
  bomb->setRotation(kirr::vector3df(rotation.x, rotation.y, rotation.z));
  auto tmp = indie::module::GameObject(bomb, static_cast<int>(bwsg::ObjectType::BOMB));
  this->_objects.insert(std::pair<size_t, GameObject>(objId, tmp));
}

/*
 * ISCONNECT
 */

bool indie::module::GameInfos::getIsConnect()
{
  return this->_isConnect.load();
}

void indie::module::GameInfos::setIsConnect(bool value)
{
  this->_isConnect.store(value);
}
