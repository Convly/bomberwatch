//
// GameServerInfos.hpp for GameServerInfos in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/GameServerInfos/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 23:19:57 2017 jsx
// Last update Tue May 23 01:07:29 2017 JSX
//

#ifndef GAME_SERVER_INFOS_HPP_
#define GAME_SERVER_INFOS_HPP_

#include <iostream>
#include <string>
#include "ClientManager.hpp"

namespace indie {
  namespace module {
    //class GameInfos;

    class GameServerInfos {
    private:
      std::string                            _ipaddr;
      size_t                                 _port;
      unsigned short                         _ping;
      std::shared_ptr<bwsg::ClientManager>   _server;
      bool                                   _multiplayer;
      indie::module::GameInfos&              _gameInfos;

    public:
      GameServerInfos (GameInfos& gameInfos);
      virtual ~GameServerInfos ();

    public:
      std::string                             getIpaddr()  const;
      unsigned short                          getPort()    const;
      size_t                                  getPing()    const;
      std::shared_ptr<bwsg::ClientManager>  & getServer();
      bool                                    isMultiplayer() const;

    public:
      void      setIpAddr(const std::string &);
      void      setPort(const unsigned short);
      void      setPing(const size_t);
      void      setMultiplayer(bool);

    public:
      bool      connect();
      bool      disconnect();
    };
  } /* module */
} /* indie */

#endif /* end of include guard: GAME_SERVER_INFOS_HPP_ */
