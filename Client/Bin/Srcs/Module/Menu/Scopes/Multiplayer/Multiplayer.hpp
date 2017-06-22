/*
** Multiplayer.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Multiplayer
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:58:35 2017 Quentin Metge
** Last update Sun Jun 18 17:13:26 2017 Maxime Cauvin
*/

#ifndef MULTIPLAYER_HPP_
# define MULTIPLAYER_HPP_

#include "Menu.hpp"
#include "GameClient.hpp"
#include "Profile.hpp"
#include "AScope.hpp"
#include "UTILS/manip.hpp"

namespace indie{
  namespace module{

    class Multiplayer : public AScope
    {
      kirr::Gui::IGUIEnvironment                                  *_env;
      kirr::Gui::IGUISkin                                         *_skin;
      std::unordered_map<int, kirr::Gui::IGUIFont *>              &_ebrima;
      std::unordered_map<std::string, kirr::Gui::IGUIElement *>   _components;
      bool                                                        _localMp;
      bool                                                        _oldStateScrSplit;
      bool                                                        _oldStateRefresh;
      std::vector<int>                                            _serverListId;
      std::unordered_map<std::string, kirr::klang::ISound *>      &_sounds;
      kirr::klang::ISound                                         *_bgMusic;
      std::string                                                 _sAddrip;
      std::string                                                 _sPort;

    public:
      Multiplayer(Menu& menu);
      virtual ~Multiplayer(){}

      bool  checkEvent(kirr::GlobalEvent const&, const kirr::Pos<float> &, const kirr::Pos<float> &, bool);
      void  refreshServerList();

      virtual bool load();
      virtual bool loop();

    private:
      Menu&     _menu;
    };

  } /* module */
} /* indie */

#endif /* end of include guard: MULTIPLAYER_HPP_ */
