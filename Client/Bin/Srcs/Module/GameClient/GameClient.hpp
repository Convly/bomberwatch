//
// GameClient.hpp for GameClient in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 19:25:46 2017 jsx
// Last update Sun Jun 18 02:17:15 2017 Maxime Cauvin
//

#ifndef GAMECLIENT_HPP_
# define GAMECLIENT_HPP_

#include <thread>
#include <chrono>
#include "AModule.hpp"
#include "Player.hpp"
#include "GameInfos.hpp"
#include "IndieDedicated.hpp"

namespace indie
{
  namespace module
  {
    class ProfileInfos;
    class GameClient : public AModule
    {
    private:
      std::shared_ptr<std::thread>            _dedicated;
      indie::module::GameInfos                _gameInfos;
      std::shared_ptr<game::Player>           _playerOne;
      std::shared_ptr<game::Player>           _playerTwo;
      kirr::Camera*                           _camera;
      kirr::Scene::ISceneNode*                _skybox;
      kirr::Scene::ISceneNode*                _map;
      kirr::klang::ISound                     *_bgMusic;
      std::vector<std::pair<std::string const, std::vector<kirr::Scene::IMeshSceneNode *>>>  _wordsMesh;

    public:
      GameClient(indie::module::ModuleLoader &);
      virtual ~GameClient();

    public:
      virtual bool                    load();
      virtual bool                    start();
      virtual bool                    stop();
      virtual bool                    clear();
      virtual void                    toggleSkybox(bool const key);
      virtual bool                    tryEscapeGame(bool const key);
      virtual void                    changeFpsMode0(bool const key);
      virtual void                    changeFpsMode1(bool const key);



    public:
      bool      createLocalServer();

    public:
      void              updatePlayers(kirr::GlobalEvent& globalEvent);
      void              sendInfo();

    public:
      indie::module::GameInfos        &getGameInfos(){return this->_gameInfos;}
      kirr::Camera                    *getCamera(){return this->_camera;}
      std::shared_ptr<game::Player>    getPlayerOne(){return this->_playerOne;}
      std::shared_ptr<game::Player>    getPlayerTwo(){return this->_playerTwo;}
      indie::module::GameInfos&        getGameInfo(){return this->_gameInfos;}
      indie::module::ProfileInfos&     getProfileInfos();
    };

  } /* module */
} /* indie */

#endif
