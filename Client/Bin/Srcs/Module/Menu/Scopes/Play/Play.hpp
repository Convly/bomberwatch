/*
** Play.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Play
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:59:23 2017 Quentin Metge
** Last update Sat Jun 17 04:42:18 2017 Maxime Cauvin
*/

#ifndef PLAY_HPP_
# define PLAY_HPP_

#include "Menu.hpp"
#include "AScope.hpp"

namespace indie{
  namespace module{

    class Play : public AScope
    {
      std::unordered_map<std::string, kirr::klang::ISound *>      &_sounds;
      Menu&     _menu;

    public:
      Play(Menu& menu);
      virtual ~Play(){}

      bool  checkEvent(kirr::GlobalEvent const&, const kirr::Pos<float> &, const kirr::Pos<float> &, bool);

      virtual bool load();

    private:
      void constructEventBoxesKeys();
      void constructEventBoxesFcts();

    private:
    };

  } /* module */
} /* indie */

#endif /* end of include guard: PLAY_HPP_ */
