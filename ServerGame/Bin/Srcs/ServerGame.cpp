/*
** ServerGame.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ServerGame.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 08 14:01:50 2017 Enguerrand Allamel
** Last update Sat Jun 17 00:30:11 2017 Quentin Metge
*/

#include "IndieDedicated.hpp"
#include "ServerGame.hpp"

/**
 * CTOR
 * @param indie
 */
bwsg::ServerGame::ServerGame(bwsg::IndieDedicated & indie) :
	_indie(indie),
	_serverCLI(*this, "Bienvenue sur le CLI du Server pour BomberWatch !"),
	_maxSlots(8)
{
  std::cout << "[BW ServerGame] Start initialisation ..." << std::endl;

  this->_listTcpTunnel.resize(this->_maxSlots);
  for (auto tunnel : this->_listTcpTunnel)
    tunnel = nullptr;
}

/**
 * DTOR
 */
bwsg::ServerGame::~ServerGame()
{
  for (size_t i = 0; i < this->_listTcpTunnel.size(); i++) {
    try {
      this->closeTcpTunnel(i);
    } catch (const bwsg::ErrorServerGame& e) {
      std::cout << e.what() << std::endl;
    }
  }
  std::cout << "[BW ServerGame] Halt" << std::endl;
}

/**
 * Callback read command
 * @param playerID
 * @param dataEmitter
 */
void bwsg::ServerGame::commandRead(int playerID, socketInfosEmitter dataEmitter)
{
  this->_indie.getReferee().setEventEmitter(dataEmitter, playerID);
}

/**
 * Add new Tcp Tunnel
 * @param pointer
 */
void bwsg::ServerGame::addTcpTunnel(TcpTunnelServer::pointer pointer)
{
  size_t slotID;

  slotID = 0;
  for (auto tunnel : this->_listTcpTunnel)
    {
      if (!tunnel)
	break;
      slotID += 1;
    }
  if (slotID >= this->_listTcpTunnel.size())
    {
      pointer->close();
      std::cout << "[BW - TCP Server] : Max connection reach: " << slotID << ". Tunnel close." << std::endl;
      return ;
    }
  this->_listTcpTunnel.at(slotID) = pointer;
  pointer->setSlotID(slotID);
  std::cout << "[BW - TCP Server] : New TcpTunnel " << slotID << " connection." << std::endl;
}

/**
 * Add new ServerPlayer
 * @param playerID
 * @param pointer
 */
void bwsg::ServerGame::addServerPlayer(int playerID, int slotID)
{
  if (this->_listClient.find(playerID) != this->_listClient.end())
    {
      std::cout << "PlayerID (" << playerID << ") is already use " << std::endl;
      this->closeTcpTunnel(slotID);
      return ;
    }
  else if (this->_listClient.size() >= this->_maxSlots)
    {
      std::cout << "Player max reach max reach !  (" << this->_maxSlots << ")." << std::endl;
      this->closeTcpTunnel(slotID);
      return ;
    }
  struct ServerPlayer serverPlayer = {playerID, slotID};
  this->_listClient.emplace(playerID, serverPlayer);
  std::cout << "[BW - TCP Server] : New Client register " << playerID << " connection. To Tunnel: " << slotID << std::endl;

  // Get objects already on the map
	if (playerID % 2) {
		std::cout << "[BW - TCP Server] : Sending entities to the client " << playerID << "]" << std::endl;
		for (auto it = this->_indie.getReferee().getEnv()._entities.begin(); it != this->_indie.getReferee().getEnv()._entities.end(); it++) {
			this->_indie.getReferee().dispObj(*it, TriggerType::U_ONLY, playerID);
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}

  std::cout << "[BW - TCP Server] : Creating new player for " << slotID << std::endl;
	this->_indie.getReferee().getLocks()[playerID] = false;
  // Creating player for the new client

	std::vector<std::vector<float>> startPlayer = {{-330, 2, -330}, {0, 2, -330}, {330, 2, -330}, {-330, 2, 0}, {330, 2, 0}, {-330, 2, 330}, {0, 2, 330}, {330, 2, 330}};
	size_t nbPlayer = this->getListClient().size();
	bwsg::ServerEntity pl = this->_indie.getReferee().addObject(bwsg::ObjectType::PLAYER, startPlayer[nbPlayer - 1], {0, 0, 0}, {16.4f, 16.8f, 3.4f}, false, bwsg::OBJ_ACTION::DEFAULT, playerID);
	this->_indie.getReferee().dispObj(pl, TriggerType::ALL_USERS, playerID);
}

/*
 * Close Tcp Tunnel (and Client use this)
 * @attention Do not use manualy
 * @param playerID
 */
void bwsg::ServerGame::closeTcpTunnel(int slotID)
{
  for (auto it = this->_listClient.begin() ; it != this->_listClient.end() ; it++)
    {
     if (it->second._tcpTunnelKey == slotID)
       {
	 this->closeClient(it->first);
	 if (this->_listClient.empty())
	   break;
	 it = this->_listClient.begin();
       }
    }
  try
    {
      if (this->getTcpTunnelByKey(slotID))
	this->getTcpTunnelByKey(slotID)->close();
      this->_listTcpTunnel.at(slotID) = nullptr;
      std::cout << "[BW - TCP Server] : Close TcpTunnel " << slotID << "." << std::endl;
    } catch (bwsg::ErrorServerGame  &error)
    {
      std::cerr << "Error:" << error.what() << std::endl;
    }
}

/**
 * Close Player ID (and not TCP Tunnel Link warn to this)
 * @attention Do not use manualy (Use disconnectClient(int playerID) for disconnected client
 * @param playerID
 */
void bwsg::ServerGame::closeClient(int playerID)
{
  if (this->_listClient.find(playerID) == this->_listClient.end())
    {
      std::cout << "[BW - TCP Server] : Close client fail, playerID not found ! (" << playerID << ")." << std::endl;
      return ;
    }
  this->_listClient.erase(playerID);
  std::cout << "[BW - TCP Server] : Close Client " << playerID << " connection." << std::endl;
  this->clientIsDisconnect(playerID);
}

/**
 * Function for disconnect client
 * @param playerID
 */
void bwsg::ServerGame::disconnectClient(int playerID)
{
  if (this->_listClient.find(playerID) == this->_listClient.end())
    throw ErrorServerGame("Disconnect Client fail, playerID not found !");
  this->closeTcpTunnel(this->_listClient.find(playerID)->second._tcpTunnelKey);
}

/**
 * Notify if client is disconnected
 * @param playerID
 */
void bwsg::ServerGame::clientIsDisconnect(int playerID)
{
  try {
    this->_indie.getReferee().deleteObject(playerID, this->_indie.getReferee().getPlayerObjByPlayerId(playerID), bwsg::TriggerType::ALL_USERS);
    std::cout << "[BW - TCP Server] : Disconnect for Client " << playerID << " connection is finish !" << std::endl;
  } catch (...) {
    std::cerr << "Client Is Disconnect symbol error" << std::endl;
  }
}

/**
 * Write command for one playerID
 * @param playerID
 * @param dataReceiver
 */
void bwsg::ServerGame::commandWrite(int playerID, socketInfosReceiver dataReceiver)
{
  if (this->_listClient.find(playerID) == this->_listClient.end())
    {
      std::cout << "PlayerID not found" << std::endl;
      return;
    }
    try {
      this->getTcpTunnelByKey(this->_listClient.at(playerID)._tcpTunnelKey)->writeReceiver(dataReceiver);
    } catch (...) {
      std::cerr << "Can't write on tunnel for player [" << playerID << "]" << std::endl;
    }
}

/**
 * Write command for all player
 * @param dataReceiver
 */
void bwsg::ServerGame::commandWriteAll(socketInfosReceiver dataReceiver)
{
  for (auto it = this->_listClient.begin() ; it != this->_listClient.end() ; it++)
    {
      if (it->first % 2 != 0)
	this->commandWrite(it->first, dataReceiver);
    }
}

/**
 * Write command for all player, expect this playerID
 * @param playerID
 * @param dataReceiver
 */
void 	bwsg::ServerGame::commandWriteOthers(int playerID, socketInfosReceiver dataReceiver)
{
  for (auto it = this->_listClient.begin() ; it != this->_listClient.end() ; it++)
    {
      if (it->first != playerID && it->first % 2 != 0)
	this->commandWrite(it->first, dataReceiver);
    }
}

/**
 * Return list of Client
 * @return
 */
const std::unordered_map<int, struct bwsg::ServerPlayer> & bwsg::ServerGame::getListClient() const
{
  return this->_listClient;
}

/**
 * Return list Tcp Tunnel
 * @return
 */
const std::vector<bwsg::TcpTunnelServer::pointer>& bwsg::ServerGame::getListTcpTunnel() const
{
  return this->_listTcpTunnel;
};

/**
 * Return Tcp Tunnel by Key
 * @param tcpTunnelKey
 * @return
 */
bwsg::TcpTunnelServer::pointer bwsg::ServerGame::getTcpTunnelByKey(int tcpTunnelKey)
{
  if (!this->_listTcpTunnel.at(tcpTunnelKey))
    throw ErrorServerGame("TcpTunnelKey not found.");
  return (this->_listTcpTunnel.at(tcpTunnelKey));
}

/**
 * Return maxSlots for server
 * @return
 */
const size_t& bwsg::ServerGame::getMaxSolts() const
{
  return (this->_maxSlots);
}

/**
 * Stop server
 */
void bwsg::ServerGame::stop()
{
  std::cout << "[BW - ServerGame] Stop server receive." << std::endl;
  this->_indie.getReferee().kill();
}