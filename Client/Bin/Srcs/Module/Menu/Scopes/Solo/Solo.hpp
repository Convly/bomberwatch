/*
** Solo.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Solo
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 15:01:59 2017 Quentin Metge
** Last update Sat Jun 17 05:04:18 2017 Maxime Cauvin
*/

#ifndef SOLO_HPP_
# define SOLO_HPP_

#include "Menu.hpp"
#include "AScope.hpp"

namespace indie{
  namespace module{

    class Solo : public AScope
    {
      kirr::Gui::IGUIEnvironment                                  *_env;
      kirr::Gui::IGUISkin                                         *_skin;
      std::unordered_map<int, kirr::Gui::IGUIFont *>              &_ebrima;
      std::unordered_map<std::string, kirr::Gui::IGUIElement *>   _components;
      bool                                                        _localMp;
      bool                                                        _oldStateScrSplit;
      std::unordered_map<std::string, kirr::klang::ISound *>      &_sounds;
      Menu                                                        &_menu;
      kirr::klang::ISound                                         *_bgMusic;

    public:
      Solo(Menu& menu);
      virtual ~Solo(){}

      void constructEventBoxesKeys();
      void constructEventBoxesFcts();

      bool  checkEvent(kirr::GlobalEvent const&, const kirr::Pos<float> &, const kirr::Pos<float> &, bool);
      virtual bool load();
      virtual bool loop();
    };

  } /* module */
} /* indie */

#endif /* end of include guard: SOLO_HPP_ */
