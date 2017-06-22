/*
** Home.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Home
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:51:13 2017 Quentin Metge
** Last update Sat Jun 17 03:58:49 2017 Maxime Cauvin
*/

#ifndef HOME_HPP_
# define HOME_HPP_

#include "Menu.hpp"
#include "AScope.hpp"

namespace indie
{
  namespace module
  {
    class Home : public AScope
    {
      Menu    &_menu;
      std::unordered_map<std::string, kirr::klang::ISound *> &_sounds;

    private:
      void constructEventBoxesKeys();
      void constructEventBoxesFcts();

    public:
      Home(Menu & menu);
      virtual ~Home();

    public:
      bool  checkEvent(kirr::GlobalEvent const&, const kirr::Pos<float> &, const kirr::Pos<float> &, bool);
      void  removeIntoSoundMapExceptOne(std::string const& key);

    public:
      virtual bool load();
    };
  }
}

#endif /* end of include guard: HOME_HPP_ */
