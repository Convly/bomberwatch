/*
** ServerCLI.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ServerCLI.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 22 16:39:31 2017 Enguerrand Allamel
** Last update Mon May 22 16:39:31 2017 Enguerrand Allamel
*/

#include "ServerGame.hpp"
#include "ServerCLI.hpp"

bwsg::ServerCLI::ServerCLI(ServerGame &serverGame, const std::string motd) :
	_serverGame(serverGame),
	_motd(motd)
{
  std::cout << "[ServerCLI] Start initialization ..." << std::endl;
  std::function<void*(void*)> func = [&] (void*) {
    this->start();
    return nullptr;
  };

  this->_cmd.insert(std::pair<std::string, std::function<void(ServerCLI&, std::string&)>>("/list", &ServerCLI::printListClient));
  this->_cmd.insert(std::pair<std::string, std::function<void(ServerCLI&, std::string&)>>("/listAll", &ServerCLI::printAllTunnelState));
  this->_cmd.insert(std::pair<std::string, std::function<void(ServerCLI&, std::string&)>>("/kick", &ServerCLI::kick));
  this->_cmd.insert(std::pair<std::string, std::function<void(ServerCLI&, std::string&)>>("/stop", &ServerCLI::stop));

  this->_run = true;
  this->_consoleThread = boost::thread(func, nullptr);
}

bwsg::ServerCLI::~ServerCLI()
{
  this->_run = false;
  this->_consoleThread.interrupt();
  std::cout << "[ServerCLI] Goodbye" << std::endl;
}

void bwsg::ServerCLI::start()
{
  std::cout << "[ServerCLI] " << this->_motd << std::endl;
  for (std::string line; this->_run.load() && std::getline(std::cin, line, '\n');) {
      std::vector<std::string> args = this->split(line.c_str(), ' ');
      if (!args.empty())
	{
	  auto it = this->_cmd.find(*(args.begin()));
	  if (it != this->_cmd.end())
	    (*it).second(*this, line);
	}
    }
}

/* SPLIT */
template<typename Out>
void bwsg::ServerCLI::split(const std::string &s, char delim, Out result) {
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
      if (item != "")
	*(result++) = item;
    }
}

std::vector<std::string> bwsg::ServerCLI::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}
/* -------- */

/*
 * CMD Functions
 */

void bwsg::ServerCLI::printListClient(std::string&)
{
  auto listClient = this->_serverGame.getListClient();
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "Numbers of clients : " << listClient.size() << std::endl;
  for (auto it = listClient.begin() ; it != listClient.end() ; it++)
    std::cout << "\tPlayer ID: " <<  it->first << " - TCP Tunnel: " << it->second._tcpTunnelKey << std::endl;
  std::cout << "------------------------------------------------" << std::endl;
}

void bwsg::ServerCLI::printAllTunnelState(std::string&)
{
  auto listTunnel = this->_serverGame.getListTcpTunnel();
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "State of all tunnels (" << this->_serverGame.getMaxSolts() << ") : " << std::endl;
  size_t slotID;
  slotID = 0;
  for (auto tunnel : listTunnel)
    {
      if (!tunnel)
	break;
      slotID += 1;
    }
  std::cout << "Numbers of Tcp Tunnel possible : " << listTunnel.size() << std::endl;
  std::cout << "------------------------------------------------" << std::endl;
}

void bwsg::ServerCLI::kick(std::string& cmd)
{
  std::vector<std::string> args = this->split(cmd.c_str(), ' ');
  if (args.size() < 2)
    {
      std::cout << "Usage ./kick {playerID} ..." << std::endl;
      return ;
    }
  for (auto it = std::next(args.begin()) ; it != args.end() ; it++)
    {
     try
       {
	 this->_serverGame.disconnectClient(std::stoi(*it));
       }
     catch (...) {
	 std::cout << "Player not found." << std::endl;
	 return ;
       }
    }
}

void bwsg::ServerCLI::stop(std::string&)
{
  this->_serverGame.stop();
}