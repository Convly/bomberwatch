/*
** TcpTunnelServer.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/TcpTunnelServer.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Tue May 09 18:16:12 2017 Enguerrand Allamel
** Last update Tue May 09 18:16:12 2017 Enguerrand Allamel
*/

#include "ServerGame.hpp"
#include "TcpTunnelServer.hpp"

bwsg::TcpTunnelServer::TcpTunnelServer(boost::asio::io_service &ioService, ServerGame &servegame) :
	_socket(ioService),
	_timer(ioService, boost::posix_time::seconds(5)),
	_timerNb(0),
	_servegame(servegame)
{
}

bwsg::TcpTunnelServer::~TcpTunnelServer()
{
}

/*
 * READ
 */
void bwsg::TcpTunnelServer::readEmitter(bool isTimeout)
{
  boost::asio::async_read(this->_socket,
			  boost::asio::buffer(&this->_receivedBufferEmitter, sizeof(socketInfosEmitter)),
			  boost::asio::transfer_at_least(sizeof(socketInfosEmitter)),
			  boost::bind(&TcpTunnelServer::handleReadEmitter, shared_from_this(), boost::asio::placeholders::error, isTimeout)
  );
  if (isTimeout)
    {
      this->_timerNb++;
      this->_timer.expires_from_now(boost::posix_time::seconds(5));
      this->_timer.async_wait(boost::bind(&TcpTunnelServer::closeTimeout, shared_from_this()));
    }

}

/*
 * Handle READ
 */
void bwsg::TcpTunnelServer::handleReadEmitter(const boost::system::error_code& error, bool isTimeout)
{
  socketInfosEmitter receivedBufferEmitter;

  if (!error)
    {
      receivedBufferEmitter = this->_receivedBufferEmitter;
      this->readEmitter(isTimeout);
      if (receivedBufferEmitter.commandType == static_cast<int>(bwsg::CommandType::REGISTER))
	this->_servegame.addServerPlayer(receivedBufferEmitter.playerId, this->_slotID);
      this->_servegame.commandRead(receivedBufferEmitter.playerId, receivedBufferEmitter);
    }
  else
    {
      this->_servegame.closeTcpTunnel(this->_slotID);
    }
}

/*
 * WRITE
 */
void bwsg::TcpTunnelServer::writeReceiver(socketInfosReceiver sendBuffer)
{
  boost::asio::async_write(this->_socket,
			   boost::asio::buffer(&sendBuffer, sizeof(socketInfosReceiver)),
			   boost::bind(&TcpTunnelServer::handleWriteReceiver, shared_from_this(), boost::asio::placeholders::error));
}

/*
 * Handle WRITE
 */
void bwsg::TcpTunnelServer::handleWriteReceiver(const boost::system::error_code &error)
{
  if (error)
    {
      this->_servegame.closeTcpTunnel(this->_slotID);
    }
}

/*
 * Utils
 */
void bwsg::TcpTunnelServer::closeTimeout()
{
  this->_timerNb--;
  if (this->_timerNb.load(std::memory_order_relaxed) == 0)
    this->_servegame.closeTcpTunnel(this->_slotID);
}

void bwsg::TcpTunnelServer::close()
{
  std::cout << "[BW - TCP Server] : Close socket." << std::endl;
  this->_socket.close();
}

void bwsg::TcpTunnelServer::setSlotID(size_t slotID)
{
  this->_slotID = slotID;
}
