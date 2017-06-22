/*
** Player.cpp for cpp_indie_studio in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Game
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 29 23:25:49 2017 Quentin Metge
** Last update Wed Jun 14 19:02:22 2017 Quentin Metge
*/

#include "Player.hpp"
#include "GameClient.hpp"

using namespace indie;
using namespace game;

Player::Player(module::GameClient& gameClient, bool const activate, ControlType const controlType) : _gameClient(gameClient), _activate(activate), _binding(this->_gameClient, controlType), _view(), _actions(bwsg::NB_ACTION, false){
}

Player::~Player(){
}

void                Player::updateRotation(){
  if (this->_objectBinded == nullptr)
    return ;
  this->_view.X = -MM_PI * ((this->_objectBinded->getRotation().Y + 90) / 180);
}

void              Player::updateRotationPlayer(kirr::Pos<float> const& curs){
  if (this->_objectBinded == nullptr || (curs.x == 0 && curs.y == 0))
    return ;
  this->_objectBinded->setRotation(kirr::vector3df(0, this->_objectBinded->getRotation().Y - curs.x * 30, 0));
  float tmp = this->_view.Y;
  this->_view.Y += curs.y / 2 * MM_PI / 6;
  if (this->_view.Y < -1.05 || this->_view.Y > 1)
    this->_view.Y = tmp;
}

void              Player::updateCamera(){
  if (this->_objectBinded == nullptr)
    return ;
  kirr::vector3df camera;
  kirr::vector3df target;
  kirr::vector3df * edges = new kirr::vector3df[8];
  irr::core::aabbox3df boundingbox = this->_objectBinded->getTransformedBoundingBox();

  boundingbox.getEdges(edges);
  float y = (edges[1].Y - edges[0].Y) * 0.914634;
  this->updateRotation();
  target.X = this->_objectBinded->getPosition().X + 30 * std::cos(this->_view.X);
  target.Y = this->_objectBinded->getPosition().Y + 30 * std::tan(this->_view.Y) + y;
  target.Z = this->_objectBinded->getPosition().Z + 30 * std::sin(this->_view.X);
  camera.X = this->_objectBinded->getPosition().X + this->_render * std::cos(this->_view.X);
  camera.Y = this->_objectBinded->getPosition().Y + this->_render * std::tan(this->_view.Y) + y;
  camera.Z = this->_objectBinded->getPosition().Z + this->_render * std::sin(this->_view.X);
  this->_camera->setTarget(target);
  this->_camera->setPosition(camera);
}

void                Player::updateActions(kirr::GlobalEvent& globalEvent){
  std::vector<bool> data = {globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::MOVE_FORWARD]],
                    globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::MOVE_BACK]],
                    globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::MOVE_LEFT]],
                    globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::MOVE_RIGHT]],
                    globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::ACTION1]],
                    globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::ACTION2]],
                    globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::ACTION3]],
                    globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::ACTION4]],
                    globalEvent.pressTab[this->getBinding().getActionBinding()[bwsg::ActionType::PAUSE]]};

  if (!equal(data.begin(), data.end(), this->_actions.begin())){
    this->_actions = data;
    this->_actionsChange = true;
  }
}

void                  Player::sendInfo(){
  if (this->_objectBinded == nullptr)
    return ;
  static float Y = this->_objectBinded->getRotation().Y;
  bwsg::socketInfosEmitter  sIE;

  sIE.angleY = this->_objectBinded->getRotation().Y;
  sIE.playerId = this->getId();
  sIE.commandType = static_cast<int>(bwsg::CommandType::ACTION_PLAYER);
  for (size_t i = 0; i < this->_actions.size(); i++){
    sIE.data[i] = this->_actions[i];
  }
  if (this->_actionsChange == true){
    this->_actionsChange = false;
    this->_gameClient.getGameInfos().getServerInfos().getServer().get()->getClientGame().commandWrite(sIE);
  }
  else if (this->_objectBinded->getRotation().Y != Y){
    Y = _objectBinded->getRotation().Y;
    this->_gameClient.getGameInfos().getServerInfos().getServer().get()->getClientGame().commandWrite(sIE);
  }
}
