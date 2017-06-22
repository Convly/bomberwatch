/*
** ServerCLI.hpp for cpp_indie_studio in /home/enguerrand/delivery/cpp_indie_studio/ServerCLI.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Mon May 22 16:39:31 2017 Enguerrand Allamel
** Last update Mon May 22 16:39:31 2017 Enguerrand Allamel
*/

#ifndef CPP_INDIE_STUDIO_SERVERCLI_HPP
#define CPP_INDIE_STUDIO_SERVERCLI_HPP

#include <map>
#include <thread>
#include <atomic>
#include <boost/thread.hpp>

namespace bwsg
{
  class ServerGame;
  class ServerCLI
  {
   private:
    std::map<std::string, std::function<void(ServerCLI&, std::string&)>>	_cmd;
   private:
    ServerGame		&_serverGame;
    const std::string	_motd;
    boost::thread	_consoleThread;
    std::atomic_bool 	_run;
   public:
    ServerCLI(ServerGame &serverGame, const std::string motd);
    ~ServerCLI();

    void	start();

    template<typename Out>
    void split(const std::string &s, char delim, Out result);
    std::vector<std::string> split(const std::string &s, char delim);

   public:
    void	printListClient(std::string&);
    void	printAllTunnelState(std::string&);
    void	kick(std::string&);
    void 	stop(std::string&);
  };
}


#endif //CPP_INDIE_STUDIO_SERVERCLI_HPP
