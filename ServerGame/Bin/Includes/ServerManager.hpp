/*
** ServerManager.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ServerManager.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Thu May 11 20:19:36 2017 Enguerrand Allamel
** Last update Mon May 29 15:30:28 2017 JSX
*/

#ifndef CPP_INDIE_STUDIO_SERVERMANAGER_HPP
#define CPP_INDIE_STUDIO_SERVERMANAGER_HPP

#include "ServerGame.hpp"
#include "TcpServer.hpp"
#include <boost/thread.hpp>

namespace bwsg
{
  class IndieDedicated;

  class ServerManager
  {
   private:
    ServerGame					_serverGame;
    boost::asio::io_service 			_ioService;
    TcpServer 					_server;
    boost::shared_ptr<boost::thread>		_threadIoService;
   public:
    ServerManager(unsigned short port, IndieDedicated & indie);
    virtual ~ServerManager();

    ServerGame& getServerGame();
  };
}

#endif //CPP_INDIE_STUDIO_SERVERMANAGER_HPP
