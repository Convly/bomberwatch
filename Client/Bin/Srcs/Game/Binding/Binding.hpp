/*
** KeyBinding.hpp for cpp_indie_studio in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Game/Player
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Wed May 10 13:39:02 2017 Quentin Metge
** Last update Mon May 29 23:46:29 2017 Quentin Metge
*/

#ifndef BINDING_HPP_
#define BINDING_HPP_

#include "IScope.hpp"
#include "StructServer.hpp"

namespace indie {
  namespace module {
    class GameClient;
  }
  namespace game {
    enum class ControlType : int{
      UNKNOWN = -1,
      CONTROLLER = 0,
      KEYBOARD = 1
    };

    class Binding{
    public:
      Binding(module::GameClient& gameClient, ControlType const controlType) : _gameClient(gameClient){controlType == ControlType::KEYBOARD ? this->bindToKeyboard() : this->bindToController();}
      virtual ~Binding(){}

    public:
      void          setMovement(kirr::ALL_KEY_CODE const foreward, kirr::ALL_KEY_CODE const back,
                                kirr::ALL_KEY_CODE const left, kirr::ALL_KEY_CODE const right);
      void          setActions(kirr::ALL_KEY_CODE const action1, kirr::ALL_KEY_CODE const action2,
                               kirr::ALL_KEY_CODE const action3, kirr::ALL_KEY_CODE const action4);
      bool          setKey(bwsg::ActionType const action, kirr::ALL_KEY_CODE const key);
      void          setControlType(const ControlType controlType){this->_controlType = controlType;}

    public:
      ControlType   getControlType() const{return this->_controlType;}
      std::unordered_map<bwsg::ActionType, kirr::ALL_KEY_CODE, kirr::EnumClassHash>  getActionBinding();

    public:
      void          bindToKeyboard();
      void          bindToController();

    private:
      module::GameClient& _gameClient;
      ControlType         _controlType;
      std::unordered_map<bwsg::ActionType, kirr::ALL_KEY_CODE, kirr::EnumClassHash> _actionBinding;
    };
  } /* game */
} /* indie */

#endif /* end of include guard: Player_INDIE_STUDIO_HPP_ */
