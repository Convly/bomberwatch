/*
** TcpTunnelClient.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/TcpTunnelClient.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Tue May 09 18:16:12 2017 Enguerrand Allamel
** Last update Mon May 29 20:31:13 2017 JSX
*/

#ifndef CPP_INDIE_STUDIO_TCPTUNNEL_SERVER_HPP
#define CPP_INDIE_STUDIO_TCPTUNNEL_SERVER_HPP

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "StructServer.hpp"

namespace bwsg
{
  class ClientGame;
  class TcpTunnelClient : public boost::enable_shared_from_this<bwsg::TcpTunnelClient>
  {
   public:
    typedef boost::shared_ptr<TcpTunnelClient> pointer;
    static pointer create(boost::asio::io_service& ios, ClientGame &testing) { return pointer(new TcpTunnelClient(ios, testing)); }
    boost::asio::ip::tcp::socket& socket() { return this->_socket; }

   private:
    boost::asio::ip::tcp::socket 	_socket;
    bwsg::socketInfosReceiver		_receivedBufferReceiver;
    boost::asio::deadline_timer 	_timer;
    std::atomic_long			_timerNb;

    ClientGame 			&_client;

   public:
    TcpTunnelClient(boost::asio::io_service& ioService, ClientGame &testing);
    virtual ~TcpTunnelClient();

    void readReceiver(bool isTimeout);

    void handleReadReceiver(const boost::system::error_code& error, bool isTimeout);

    void writeEmitter(bwsg::socketInfosEmitter sendBuffer);


    void handleWriteEmitter(const boost::system::error_code& error);

    void closeTimeout();
    void close();
  };
}


#endif //CPP_INDIE_STUDIO_TCPTUNNEL_HPP
