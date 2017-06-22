/*
** ServerManager.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ServerManager.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Thu May 11 20:19:36 2017 Enguerrand Allamel
** Last update Mon May 29 15:30:36 2017 JSX
*/

#include "IndieDedicated.hpp"
#include "ServerManager.hpp"

bwsg::ServerManager::ServerManager(unsigned short port, bwsg::IndieDedicated  & indie) :
	_serverGame(indie),
	_server(this->_ioService, port, this->_serverGame)
{
  std::cout << "[BW ServerManager] Start TcpServer .." << std::endl;
  try
    {
      this->_threadIoService = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&boost::asio::io_service::run, &this->_ioService)));
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
}

bwsg::ServerManager::~ServerManager()
{
  std::cout << "[BW ServerManager] Stop io service." << std::endl;
  this->_ioService.stop();
  this->_threadIoService.get()->join();
  std::cout << "[BW ServerManager] Halt server ... clean all .." << std::endl;
}

bwsg::ServerGame& bwsg::ServerManager::getServerGame()
{
  return this->_serverGame;
}
