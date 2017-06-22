//
// GameInfos.hpp for GameInfos in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/GameInfos/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 23:43:05 2017 jsx
// Last update Sat Jun 17 08:53:16 2017 Maxime Cauvin
//

#ifndef GAME_INFOS_INDIE_STUDIO_HPP_
#define GAME_INFOS_INDIE_STUDIO_HPP_

#include <iostream>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <thread>
#include "GameObject.hpp"

const kirr::vector3df specPos = {550, 700, 0};
const kirr::vector3df specTarget = {0, 0, 0};

namespace indie {
  namespace module {
    class GameClient;

    struct Explosion{
    public:
      Explosion(kirr::Scene::IParticleSystemSceneNode* mesh, std::chrono::time_point<std::chrono::system_clock> startTime) : _mesh(mesh), _startTime(startTime){}
      ~Explosion(){}

    public:
      kirr::Scene::IParticleSystemSceneNode* _mesh;
      std::chrono::time_point<std::chrono::system_clock> _startTime;
    };

    class GameInfos {
    public:
      GameInfos (GameClient& gameClient, kirr::Kirrlicht & kirrlicht);
      virtual ~GameInfos ();

    public:
      indie::module::GameClient&      getGameClient();
      indie::module::GameServerInfos& getServerInfos();
      std::unordered_map<size_t, GameObject> &getObjects();
      std::queue<bwsg::socketInfosReceiver> &getUpdateQueue();
      void                            update(const bwsg::socketInfosReceiver& info);
      void                            loadObjects();
      void                            popExplosions();

    public:
      void          createPlayer(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);
      void          createDCube(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);
      void          createNDCube(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);
      void          createPUSpeed(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);
      void          createPUPower(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);
      void          createPUAmount(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);
      void          createPUGhost(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);
      void          createBomb(int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);
      void          createPUPenetration(int , size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation);

    public:
      void          createObject(const bwsg::socketInfosReceiver& info);
      void          createExplosion(const bwsg::socketInfosReceiver& info);
      void          removeObject(const bwsg::socketInfosReceiver& info);
      void          setObjectPosition(const bwsg::socketInfosReceiver& info);
      void          setObjectRotation(const bwsg::socketInfosReceiver& info);
      void          setObjectScale(const bwsg::socketInfosReceiver& info);
      void          setObjectVisibility(const bwsg::socketInfosReceiver& info);
      void          setObjectAnimation(const bwsg::socketInfosReceiver& info);

      bool		getIsConnect();
      void 		setIsConnect(bool);

    private:
      GameClient&        _gameClient;
      GameServerInfos    _serverInfos;
      kirr::Kirrlicht &  _kirrlicht;
      // [id] = object;
      std::unordered_map<size_t, std::function<void (int playerId, size_t objId, kirr::Pos<float> pos, kirr::Pos<float> rotation)>> _objectCreation;
      std::unordered_map<size_t, GameObject>  _objects;
      std::queue<bwsg::socketInfosReceiver>   _updateQueue;
      std::atomic_bool			      _isConnect;

     private:
      std::unordered_map<int, std::function<void (const bwsg::socketInfosReceiver& info)>> _commands;
      std::vector<Explosion>  _explosions;
    };
  } /* module */
} /* indie */

#endif /* end of include guard: GAME_INFOS_INDIE_STUDIO_HPP_ */
