/*
** ClientGame.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ClientGame.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Wed May 10 22:48:19 2017 Enguerrand Allamel
** Last update Mon May 29 20:30:47 2017 JSX
*/

#ifndef CPP_INDIE_STUDIO_CLIENTGAME_HPP
#define CPP_INDIE_STUDIO_CLIENTGAME_HPP

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "TcpTunnelClient.hpp"

namespace indie{
  namespace module{
    class GameInfos;
  }
}

namespace bwsg
{
  class ClientGame
  {
   private:
    TcpTunnelClient::pointer  _tunnel;
    indie::module::GameInfos& _gameInfos;

   public:
    ClientGame(indie::module::GameInfos& gameInfos);
    virtual ~ClientGame();

    void commandWrite(const bwsg::socketInfosEmitter & dataEmitter);
    void setTcpTunnel(TcpTunnelClient::pointer pointer);
    void waitTcpTunnelIsSet() const;
    void commandRead(const bwsg::socketInfosReceiver & dataReceiver);

    void clientIsDisconnect();

    indie::module::GameInfos& getGameInfos();
  };
}

#endif //CPP_INDIE_STUDIO_TCPCLIENTTESTING_HPP
