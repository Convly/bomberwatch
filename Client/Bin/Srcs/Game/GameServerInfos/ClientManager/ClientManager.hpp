/*
** ClientManager.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ClientManager.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Thu May 11 23:27:01 2017 Enguerrand Allamel
** Last update Mon May 29 20:11:55 2017 JSX
*/

#ifndef CPP_INDIE_STUDIO_CLIENTMANAGER_HPP
#define CPP_INDIE_STUDIO_CLIENTMANAGER_HPP

#include <boost/thread.hpp>
#include "ClientGame.hpp"
#include "TcpClient.hpp"

namespace bwsg
{
  class ClientManager
  {
   private:
    ClientGame				                _clientGame;
    boost::shared_ptr<boost::thread>	_threadIoService;
    boost::asio::io_service 	 	      _ioService;
    boost::asio::ip::tcp::endpoint 	  _endpoint;
    TcpClient 				                _client;
   public:
    ClientManager(indie::module::GameInfos& gameInfos, std::string ip, unsigned short port);
    virtual ~ClientManager();

    ClientGame& getClientGame();
  };
}

#endif //CPP_INDIE_STUDIO_CLIENTMANAGER_HPP
