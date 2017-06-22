/*
** TcpClient.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/TcpClient.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 08 16:00:33 2017 Enguerrand Allamel
** Last update Mon May 22 19:47:44 2017 JSX
*/

#ifndef CPP_INDIE_STUDIO_TCPCLIENT_HPP
#define CPP_INDIE_STUDIO_TCPCLIENT_HPP

#include <atomic>
#include "ClientGame.hpp"
#include "TcpTunnelClient.hpp"
#include "ErrorTcpTunnelClient.hpp"
#include "UTILS/http.hpp"

namespace bwsg
{
  class TcpClient
  {
   private:
    boost::asio::io_service&	_ioService;
    ClientGame		&_testing;
   public:
    TcpClient(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint, ClientGame &testing);
    virtual ~TcpClient();

    void connect(boost::asio::ip::tcp::endpoint& endpoint);
    void handleConnect(TcpTunnelClient::pointer newConnection, const boost::system::error_code& error);
  };
}

#endif //CPP_INDIE_STUDIO_TCPCLIENTTESTING_HPP
