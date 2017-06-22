/*
** TcpClient.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/TcpClient.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 08 16:00:33 2017 Enguerrand Allamel
** Last update Tue May 23 23:00:53 2017 JSX
*/

#include "GameInfos.hpp"
#include "TcpClient.hpp"

bwsg::TcpClient::TcpClient(boost::asio::io_service &ioService, boost::asio::ip::tcp::endpoint &endpoint, ClientGame &testing) :
	_ioService(ioService),
	_testing(testing)
{
  this->connect(endpoint);
}

bwsg::TcpClient::~TcpClient()
{
}

void bwsg::TcpClient::connect(boost::asio::ip::tcp::endpoint &endpoint)
{
  TcpTunnelClient::pointer newConnection = TcpTunnelClient::create(this->_ioService, this->_testing);
  boost::asio::ip::tcp::socket& socket = newConnection->socket();
  socket.async_connect(endpoint,
		       boost::bind(&TcpClient::handleConnect, this, newConnection, boost::asio::placeholders::error)
  );
}

void bwsg::TcpClient::handleConnect(TcpTunnelClient::pointer newConnection, const boost::system::error_code &error)
{
  if (!error)
    {
      this->_testing.setTcpTunnel(newConnection);
      this->_testing.getGameInfos().setIsConnect(true);
      newConnection->readReceiver(false);
    }
  else
    {
      std::cout << "[TCP Client] Fail connect" << std::endl;
      this->_testing.getGameInfos().setIsConnect(false);
    }
}
