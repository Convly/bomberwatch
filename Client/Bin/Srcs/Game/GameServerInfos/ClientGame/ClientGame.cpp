/*
** ClientGame.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ClientGame.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Wed May 10 22:48:19 2017 Enguerrand Allamel
** Last update Fri Jun 16 17:11:32 2017 JSX
*/

#include <thread>
#include "GameInfos.hpp"
#include "ClientGame.hpp"

bwsg::ClientGame::ClientGame(indie::module::GameInfos& gameInfos)
: _gameInfos(gameInfos)
{
}

bwsg::ClientGame::~ClientGame()
{
}

void bwsg::ClientGame::commandWrite(const bwsg::socketInfosEmitter & dataEmitter)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  if (this->_tunnel)
    this->_tunnel->writeEmitter(dataEmitter);
}

void bwsg::ClientGame::setTcpTunnel(TcpTunnelClient::pointer pointer)
{
  this->_tunnel = pointer;
}

void bwsg::ClientGame::waitTcpTunnelIsSet() const
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  end = std::chrono::system_clock::now();
  while (std::chrono::duration_cast<std::chrono::seconds>(end-start).count() < 5 && !this->_tunnel)
    end = std::chrono::system_clock::now();
}

void bwsg::ClientGame::commandRead(const bwsg::socketInfosReceiver & dataReceiver)
{
  this->_gameInfos.update(dataReceiver);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void bwsg::ClientGame::clientIsDisconnect()
{
  std::cout << "Client is disconnect" << std::endl;
  exit(0);
}

indie::module::GameInfos& bwsg::ClientGame::getGameInfos()
{
  return this->_gameInfos;
}