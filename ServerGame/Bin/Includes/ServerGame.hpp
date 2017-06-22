/*
** ServerGame.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ServerGame.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 08 14:01:50 2017 Enguerrand Allamel
** Last update Tue May 30 20:52:28 2017 JSX
*/

#ifndef CPP_INDIE_STUDIO_SERVERGAME_HPP
#define CPP_INDIE_STUDIO_SERVERGAME_HPP

#include <unordered_map>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "TcpTunnelServer.hpp"
#include "StructServer.hpp"
#include "ServerCLI.hpp"
#include "ErrorServerGame.hpp"

namespace bwsg
{
  struct ServerPlayer
  {
    int				_ID;
    int				_tcpTunnelKey;
  };

  class IndieDedicated;
  class ServerGame
  {
   private:
    IndieDedicated &	                        	_indie;
    ServerCLI		                      		_serverCLI;
    std::thread						_serverCLIThread;
    std::vector<TcpTunnelServer::pointer>		_listTcpTunnel;
    std::unordered_map<int, struct ServerPlayer>	_listClient;
    size_t 						_maxSlots;
   public:
    ServerGame(IndieDedicated & indie);
    virtual ~ServerGame();

    void commandRead(int playerID, socketInfosEmitter dataEmitter);

    void addTcpTunnel(TcpTunnelServer::pointer pointer);
    void addServerPlayer(int playerID, int tcpTunnelKey);

    void closeTcpTunnel(int slotID);
    void closeClient(int playerID);

    void disconnectClient(int playerID);
    void clientIsDisconnect(int playerID);

    void commandWrite(int playerID, socketInfosReceiver dataEmitter);
    void commandWriteAll(socketInfosReceiver dataEmitter);
    void commandWriteOthers(int playerID, socketInfosReceiver);

    const std::unordered_map<int, struct ServerPlayer> &getListClient() const;
    const std::vector<TcpTunnelServer::pointer> &getListTcpTunnel() const;
    TcpTunnelServer::pointer getTcpTunnelByKey(int tcpTunnelKey);

    const size_t &getMaxSolts(void) const;

    void stop();
  };
}

#endif //CPP_INDIE_STUDIO_SERVERGAME_HPP
