/*
** ClientManager.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ClientManager.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Thu May 11 23:27:01 2017 Enguerrand Allamel
** Last update Mon May 29 19:57:12 2017 JSX
*/

#include "ClientManager.hpp"
#include "StructServer.hpp"

bwsg::ClientManager::ClientManager(indie::module::GameInfos& gameInfos, std::string ip, unsigned short port) :
	_clientGame(gameInfos),
	_endpoint(boost::asio::ip::address::from_string(ip), port),
	_client(this->_ioService, this->_endpoint, this->_clientGame)
{
  std::cout << "[BW Client Manager] Starting..." << std::endl;
  try
    {
      this->_threadIoService = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&boost::asio::io_service::run, &this->_ioService)));

      this->_clientGame.waitTcpTunnelIsSet();
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
}

bwsg::ClientManager::~ClientManager()
{
  std::cout << "[BW Client Manager] Wait end of IO Service (~5 secondes)" << std::endl;
  this->_ioService.stop();
  std::cout << "[BW Client Manager] IO service is stop" << std::endl;
  this->_threadIoService.get()->join();
  std::cout << "[BW Client Manager] IO service thread is stop" << std::endl;
}

bwsg::ClientGame& bwsg::ClientManager::getClientGame()
{
  return this->_clientGame;
}
