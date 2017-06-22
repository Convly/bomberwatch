//
// IndieDedicated.hpp for indiededicated in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/ServerGame/Bin/Srcs/IndieDedicated/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May 12 21:33:19 2017 JSX
// Last update Tue May 30 21:19:37 2017 JSX
//

#ifndef INDIE_DEDICATED_HPP_
#define INDIE_DEDICATED_HPP_

#include "ServerManager.hpp"
#include "Referee.hpp"

namespace bwsg {
  class IndieDedicated {
    private:
      bwsg::ServerManager   _serverManager;
      bwsg::Referee         _referee;

    public:
      IndieDedicated (size_t, const std::string & referee = "");
      virtual ~IndieDedicated ();

    public:
      bwsg::ServerManager &getServerManager();
      bwsg::Referee &getReferee();
  };
} /* server */

#endif /* end of include guard: INDIE_DEDICATED_HPP_ */
