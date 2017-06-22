//
// GameServerInfos.cpp for gameserverinfos in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/GameServerInfos/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 23:49:10 2017 jsx
// Last update Wed May 24 15:23:02 2017 JSX
//

#include "GameServerInfos.hpp"

indie::module::GameServerInfos::GameServerInfos(indie::module::GameInfos& gameInfos)
:
  _ipaddr("127.0.0.1"),
  _port(8442),
  _ping(0),
  _server(nullptr),
  _multiplayer(true),
  _gameInfos(gameInfos)
{

}

indie::module::GameServerInfos::~GameServerInfos() {
}

std::string    indie::module::GameServerInfos::getIpaddr()  const {return this->_ipaddr;}
unsigned short indie::module::GameServerInfos::getPort()    const {return this->_port;}
size_t         indie::module::GameServerInfos::getPing()    const {return this->_ping;}
std::shared_ptr<bwsg::ClientManager>  & indie::module::GameServerInfos::getServer() {return this->_server;}
bool           indie::module::GameServerInfos::isMultiplayer() const {return this->_multiplayer;}


void      indie::module::GameServerInfos::setIpAddr(const std::string & ip) {this->_ipaddr = ip;}
void      indie::module::GameServerInfos::setPort(const unsigned short port) {this->_port = port;}
void      indie::module::GameServerInfos::setPing(const size_t ping) {this->_ping = ping;}
void      indie::module::GameServerInfos::setMultiplayer(bool mt) {this->_multiplayer = mt;}

bool      indie::module::GameServerInfos::connect() {
  if (this->_server.get() != nullptr)
    this->disconnect();
  this->_server.reset();
  this->_server = std::make_shared<bwsg::ClientManager>(this->_gameInfos, this->_ipaddr, this->_port);
  return true;
}

bool      indie::module::GameServerInfos::disconnect() {
  this->_server.reset();
  return true;
}
