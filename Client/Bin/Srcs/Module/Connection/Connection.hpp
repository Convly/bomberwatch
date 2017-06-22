//
// GameClient.hpp for GameClient in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 19:25:46 2017 jsx
// Last update Fri Jun 16 17:22:52 2017 Maxime Cauvin
//

#ifndef CONNECTION_HPP_
# define CONNECTION_HPP_

#include "AModule.hpp"
#include "Player.hpp"

namespace indie
{
  namespace module
  {
    class Connection : public AModule
    {
      kirr::Gui::IGUIEnvironment                                *_env;
      kirr::Video::ITexture                                     *_background;
      kirr::Gui::IGUISkin                                       *_skin;
      std::unordered_map<std::string, kirr::Gui::IGUIElement *> _components;
      std::unordered_map<int, kirr::Gui::IGUIFont *>            &_ebrima;
      bool                                                      _oldStateConnect;

    public:
      Connection(indie::module::ModuleLoader &);
      virtual ~Connection();

      virtual bool  load();
      virtual bool  start();
      virtual bool  stop();
      virtual bool  clear();

    public:
      bool    connect(const std::string &, const std::string &);
      bool    checkConnection();
      bool    checkLocalConnection();
    };

  } /* module */
} /* indie */

#endif
