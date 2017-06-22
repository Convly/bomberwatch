/*
** TcpTunnelServer.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/TcpTunnelServer.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Tue May 09 18:16:12 2017 Enguerrand Allamel
** Last update Wed May 24 17:14:01 2017 JSX
*/

#ifndef CPP_INDIE_STUDIO_TCPTUNNEL_HPP
#define CPP_INDIE_STUDIO_TCPTUNNEL_HPP

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "StructServer.hpp"

namespace bwsg
{

  class ServerGame;

  class TcpTunnelServer : public boost::enable_shared_from_this<bwsg::TcpTunnelServer>
  {
   public:
    typedef boost::shared_ptr <TcpTunnelServer> pointer;

    static pointer create(boost::asio::io_service &ios, ServerGame &serverGame)
    { return pointer(new TcpTunnelServer(ios, serverGame)); }

    boost::asio::ip::tcp::socket &socket()
    { return this->_socket; }

   private:
    boost::asio::ip::tcp::socket _socket;
    socketInfosEmitter _receivedBufferEmitter;
    boost::asio::deadline_timer _timer;
    std::atomic_long _timerNb;

    ServerGame 	&_servegame;
    size_t 	_slotID;

   public:
    TcpTunnelServer(boost::asio::io_service &ioService, ServerGame &servegame);

    virtual ~TcpTunnelServer();

    void readEmitter(bool isTimeout);

    void handleReadEmitter(const boost::system::error_code &error, bool isTimeout);

    void writeReceiver(socketInfosReceiver sendBuffer);

    void handleWriteReceiver(const boost::system::error_code &error);


    void closeTimeout();

    void close();

    void	setSlotID(size_t slotID);
  };
}


#endif //CPP_INDIE_STUDIO_TCPTUNNEL_HPP
