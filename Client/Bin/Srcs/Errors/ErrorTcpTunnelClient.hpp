/*
** ErrorTcpTunnelServer.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ErrorTcpTunnelServer.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Tue May 30 18:20:20 2017 Enguerrand Allamel
** Last update Tue May 30 18:20:20 2017 Enguerrand Allamel
*/

#ifndef CPP_INDIE_STUDIO_ERRORTCPTUNNELCLIENT_HPP
#define CPP_INDIE_STUDIO_ERRORTCPTUNNELCLIENT_HPP

namespace bwsg
{
  class ErrorTcpTunnelClient: public std::exception
  {
   public:
    ErrorTcpTunnelClient(const std::string& msg = "") throw() : _msg(msg) {}

    virtual const char* what() const throw() {
      return (std::string("Error SERVER GAME: " + _msg).c_str());
    }

    virtual ~ErrorTcpTunnelClient() throw(){}

   private:
    std::string _msg;
  };
}


#endif //CPP_INDIE_STUDIO_ERRORTCPTUNNELCLIENT_HPP
