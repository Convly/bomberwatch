//
// IndieDedicated.cpp for indiededicated in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/ServerGame/Bin/Srcs/IndieDedicated/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May 12 21:33:00 2017 JSX
// Last update Tue May 30 21:19:43 2017 JSX
//

#include "IndieDedicated.hpp"
#include "ServerManager.hpp"

bwsg::IndieDedicated::IndieDedicated(size_t port, const std::string & referee)
:
  _serverManager(port, *this),
  _referee(referee, *this)
{
  std::cout << "[BW - IndieDedicated] Start." << std::endl;
}

bwsg::IndieDedicated::~IndieDedicated() {
  std::cout << "[BW - IndieDedicated] Halt." << std::endl;
}

bwsg::ServerManager & bwsg::IndieDedicated::getServerManager() {return this->_serverManager;}
bwsg::Referee       & bwsg::IndieDedicated::getReferee() {return this->_referee;}
