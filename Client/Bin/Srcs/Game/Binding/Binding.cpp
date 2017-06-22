/*
** Binding.cpp for cpp_indie_studio in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Game/Binding
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Wed May 10 18:18:53 2017 Quentin Metge
** Last update Wed Jun 14 17:32:37 2017 Quentin Metge
*/

#include "GameClient.hpp"
#include "Binding.hpp"

void          indie::game::Binding::setMovement(kirr::ALL_KEY_CODE const foreward, kirr::ALL_KEY_CODE const back,
                                                kirr::ALL_KEY_CODE const left, kirr::ALL_KEY_CODE const right){
  this->_actionBinding[bwsg::ActionType::MOVE_FORWARD] = foreward;
  this->_actionBinding[bwsg::ActionType::MOVE_BACK] = back;
  this->_actionBinding[bwsg::ActionType::MOVE_LEFT] = left;
  this->_actionBinding[bwsg::ActionType::MOVE_RIGHT] = right;
}

void          indie::game::Binding::setActions(kirr::ALL_KEY_CODE const action1, kirr::ALL_KEY_CODE const action2,
                                               kirr::ALL_KEY_CODE const action3, kirr::ALL_KEY_CODE const action4){
  this->_actionBinding[bwsg::ActionType::ACTION1] = action1;
  this->_actionBinding[bwsg::ActionType::ACTION2] = action2;
  this->_actionBinding[bwsg::ActionType::ACTION3] = action3;
  this->_actionBinding[bwsg::ActionType::ACTION4] = action4;
}

bool          indie::game::Binding::setKey(bwsg::ActionType const action, kirr::ALL_KEY_CODE const key){
  for (auto it = this->_actionBinding.begin(); it != this->_actionBinding.end(); it++){
    if (it->second == key)
      return (false);
  }
  this->_actionBinding[action] = key;
  return (true);
}

void          indie::game::Binding::bindToKeyboard(){
  this->_controlType = ControlType::KEYBOARD;
  this->_actionBinding = {{bwsg::ActionType::MOVE_FORWARD, kirr::ALL_KEY_CODE::KEY_KEY_Z},
                         {bwsg::ActionType::MOVE_BACK, kirr::ALL_KEY_CODE::KEY_KEY_S},
                         {bwsg::ActionType::MOVE_LEFT, kirr::ALL_KEY_CODE::KEY_KEY_Q},
                         {bwsg::ActionType::MOVE_RIGHT, kirr::ALL_KEY_CODE::KEY_KEY_D},
                         {bwsg::ActionType::ACTION1, kirr::ALL_KEY_CODE::KEY_SPACE},
                         {bwsg::ActionType::ACTION2, kirr::ALL_KEY_CODE::KEY_SHIFT},
                         {bwsg::ActionType::ACTION3, kirr::ALL_KEY_CODE::KEY_LBUTTON},
                         {bwsg::ActionType::ACTION4, kirr::ALL_KEY_CODE::KEY_RBUTTON},
                         {bwsg::ActionType::PAUSE, kirr::ALL_KEY_CODE::KEY_KEY_P}};
}
void          indie::game::Binding::bindToController(){
  this->_controlType = ControlType::CONTROLLER;
  this->_actionBinding = {{bwsg::ActionType::MOVE_FORWARD, kirr::ALL_KEY_CODE::KEY_LCONTROLLER_UP},
                         {bwsg::ActionType::MOVE_BACK, kirr::ALL_KEY_CODE::KEY_LCONTROLLER_DOWN},
                         {bwsg::ActionType::MOVE_LEFT, kirr::ALL_KEY_CODE::KEY_LCONTROLLER_LEFT},
                         {bwsg::ActionType::MOVE_RIGHT, kirr::ALL_KEY_CODE::KEY_LCONTROLLER_RIGHT},
                         {bwsg::ActionType::ACTION1, kirr::ALL_KEY_CODE::KEY_CONTROLLER_X},
                         {bwsg::ActionType::ACTION2, kirr::ALL_KEY_CODE::KEY_CONTROLLER_SQUARE},
                         {bwsg::ActionType::ACTION3, kirr::ALL_KEY_CODE::KEY_CONTROLLER_TRIANGLE},
                         {bwsg::ActionType::ACTION4, kirr::ALL_KEY_CODE::KEY_CONTROLLER_ROUND},
                         {bwsg::ActionType::PAUSE, kirr::ALL_KEY_CODE::KEY_CONTROLLER_START}};
}

std::unordered_map<bwsg::ActionType, kirr::ALL_KEY_CODE, kirr::EnumClassHash>  indie::game::Binding::getActionBinding()
{
  return (this->_actionBinding);
}
