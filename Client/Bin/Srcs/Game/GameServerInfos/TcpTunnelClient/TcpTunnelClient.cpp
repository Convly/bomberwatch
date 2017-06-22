/*
** TcpTunnelClient.cpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/TcpTunnelClient.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Tue May 09 18:16:12 2017 Enguerrand Allamel
** Last update Tue May 23 18:39:28 2017 JSX
*/

#include "ClientGame.hpp"
#include "TcpTunnelClient.hpp"

bwsg::TcpTunnelClient::TcpTunnelClient(boost::asio::io_service &ioService, ClientGame &testing) :
	_socket(ioService),
	_timer(ioService, boost::posix_time::seconds(5)),
	_timerNb(0),
	_client(testing)
{
}

bwsg::TcpTunnelClient::~TcpTunnelClient()
{
}

/*
 * READ
 */

void bwsg::TcpTunnelClient::readReceiver(bool isTimeout)
{
  boost::asio::async_read(this->_socket,
			  boost::asio::buffer(&this->_receivedBufferReceiver, sizeof(bwsg::socketInfosReceiver)),
			  boost::asio::transfer_at_least(sizeof(bwsg::socketInfosReceiver)),
			  boost::bind(&TcpTunnelClient::handleReadReceiver, shared_from_this(), boost::asio::placeholders::error, isTimeout)
  );
  if (isTimeout)
    {
      this->_timerNb++;
      this->_timer.expires_from_now(boost::posix_time::seconds(5));
      this->_timer.async_wait(boost::bind(&TcpTunnelClient::closeTimeout, shared_from_this()));
    }
}

/*
 * Handle READ
 */

void bwsg::TcpTunnelClient::handleReadReceiver(const boost::system::error_code& error, bool isTimeout)
{
  bwsg::socketInfosReceiver receivedBufferReceiver;
  if (!error)
    {
      receivedBufferReceiver = this->_receivedBufferReceiver;
      this->readReceiver(isTimeout);
      this->_client.commandRead(receivedBufferReceiver);
    }
  else
    {
      std::cout << "[ERROR TCP TUNNEL] Read : " << error.message() << std::endl;
      this->close();
      this->_client.clientIsDisconnect();
    }
}

/*
 * WRITE
 */
void bwsg::TcpTunnelClient::writeEmitter(bwsg::socketInfosEmitter sendBuffer)
{
  boost::asio::async_write(this->_socket,
			   boost::asio::buffer(&sendBuffer, sizeof(bwsg::socketInfosEmitter)),
			   boost::bind(&TcpTunnelClient::handleWriteEmitter, shared_from_this(), boost::asio::placeholders::error));
}

/*
 * Handle WRITE
 */
void bwsg::TcpTunnelClient::handleWriteEmitter(const boost::system::error_code &error)
{
  if (error)
    {
      std::cout << "[ERROR TCP TUNNEL] Write : " << error.message() << std::endl;
      this->close();
      this->_client.clientIsDisconnect();
    }

}

/*
 * Utils
 */
void bwsg::TcpTunnelClient::closeTimeout()
{
  this->_timerNb--;
  if (this->_timerNb.load(std::memory_order_relaxed) == 0)
    {
      this->close();
      this->_client.clientIsDisconnect();
    }
}

void bwsg::TcpTunnelClient::close()
{
  this->_socket.close();
}
