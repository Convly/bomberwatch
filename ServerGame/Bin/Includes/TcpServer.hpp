/*
** TcpServer.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/TcpServer.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 08 14:15:20 2017 Enguerrand Allamel
** Last update Mon May 08 14:15:20 2017 Enguerrand Allamel
*/

#ifndef CPP_INDIE_STUDIO_TCPSERVER_HPP
#define CPP_INDIE_STUDIO_TCPSERVER_HPP

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "ServerGame.hpp"
#include "TcpTunnelServer.hpp"

namespace bwsg
{
  class TcpServer
  {
   private:
    boost::asio::ip::tcp::acceptor 	_acceptor;
    ServerGame				&_servergame;

   public:
    TcpServer(boost::asio::io_service& ioService, size_t port, ServerGame &serverGame);
    virtual ~TcpServer();

    void start();
    void handleConnect(TcpTunnelServer::pointer newConnection, const boost::system::error_code& error);
  };
}

#endif //CPP_INDIE_STUDIO_TCPSERVER_HPP
