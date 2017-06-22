/*
** TcpServer.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/TcpServer.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 08 14:15:20 2017 Enguerrand Allamel
** Last update Tue May 23 23:00:35 2017 JSX
*/

#include "TcpServer.hpp"

bwsg::TcpServer::TcpServer(boost::asio::io_service& ioService, size_t port, ServerGame &serverGame) :
 	_acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	_servergame(serverGame)
{
  this->start();
}

bwsg::TcpServer::~TcpServer()
{

}

void bwsg::TcpServer::start()
{
  TcpTunnelServer::pointer newConnection = TcpTunnelServer::create(this->_acceptor.get_io_service(), this->_servergame);

  this->_acceptor.async_accept(newConnection->socket(),
			       boost::bind(&TcpServer::handleConnect, this, newConnection, boost::asio::placeholders::error));

}

void bwsg::TcpServer::handleConnect(TcpTunnelServer::pointer newConnection, const boost::system::error_code& error)
{
  this->start();
  if (!error)
    {
      this->_servergame.addTcpTunnel(newConnection);
      newConnection->readEmitter(false);
    }
}
