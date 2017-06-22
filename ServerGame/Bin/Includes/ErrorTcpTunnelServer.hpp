/*
** ErrorTcpTunnelServer.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ErrorTcpTunnelServer.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Tue May 30 18:20:20 2017 Enguerrand Allamel
** Last update Tue May 30 18:20:20 2017 Enguerrand Allamel
*/

#ifndef CPP_INDIE_STUDIO_ERRORTCPTUNNELSERVER_HPP
#define CPP_INDIE_STUDIO_ERRORTCPTUNNELSERVER_HPP

namespace bwsg
{
  class ErrorTcpTunnelServer: public std::exception
  {
   public:
    ErrorTcpTunnelServer(const std::string& msg = "") throw() : _msg(msg) {}

    virtual const char* what() const throw() {
      return ("Error TCP TUNNEL SERVER: " + _msg.c_str());
    }

    virtual ~ErrorTcpTunnelServer() throw(){}

   private:
    std::string _msg;
  };
}


#endif //CPP_INDIE_STUDIO_ERRORTCPTUNNELSERVER_HPP
