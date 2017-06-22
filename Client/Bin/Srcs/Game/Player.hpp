//
// Player.hpp for Player in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/Player/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 20:57:13 2017 jsx
// Last update Tue May 23 18:30:19 2017 Maxime Cauvin
//

#ifndef Player_INDIE_STUDIO_HPP_
#define Player_INDIE_STUDIO_HPP_

#include <cmath>
#include <algorithm>
#include "Binding.hpp"

namespace indie {
  namespace module {
    class GameClient;
  }
  namespace game {
    enum{
      RENDER_MAX = -30,
      RENDER_MIN = 2
    };

    class Player {
    public:
      Player(module::GameClient& gameClient, bool const activate, ControlType const controlType);
      virtual ~Player();

    public:
      void        setCamera(kirr::Camera* camera){this->_camera = camera;}
      void        setObjectBinded(kirr::Scene::ISceneNode* obj){this->_objectBinded = obj;}
      void        setId(const int id){_id = id;}
      void        setState(const bool state){this->_activate = state;}
      void        setRender(const float render){this->_render = render;}

    public:
      kirr::Scene::ISceneNode* getObjectBinded() const {return this->_objectBinded;}
      bool              getState() const{return this->_activate;}
      int               getId() const{return this->_id;}
      Binding&          getBinding() {return this->_binding;}
      kirr::Camera*     getCamera() const {return this->_camera;}
      std::vector<bool> getActions() const{return (this->_actions);}
      float             getRender() const{return this->_render;}

    public:
      void              updateRotation();
      void              updateActions(kirr::GlobalEvent& globalEvent);
      void              updateRotationPlayer(kirr::Pos<float> const& curs);
      void              updateCamera();

    public:
      void              sendInfo();

    private:
      module::GameClient&      _gameClient;

    private:
      bool                     _activate;
      int                      _id;
      Binding                  _binding;
	    kirr::Camera*            _camera = nullptr;
      kirr::Scene::ISceneNode* _objectBinded = nullptr;
      float                    _render = 1.5;
      kirr::vector3df          _view;
      std::vector<bool>        _actions;
      bool                     _actionsChange = true;
    };
  } /* game */
} /* indie */

#endif /* end of include guard: Player_INDIE_STUDIO_HPP_ */
