/*
** Profile.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Profile
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:59:57 2017 Quentin Metge
** Last update Sat Jun 17 04:43:33 2017 Maxime Cauvin
*/

#ifndef PROFILE_HPP_
# define PROFILE_HPP_

#include <algorithm>
#include <string>
#include "Menu.hpp"
#include "AScope.hpp"
#include "ProfileInfos.hpp"

namespace indie{
  namespace module{

    class Profile : public AScope
    {
      std::unordered_map<std::string, kirr::klang::ISound *>      &_sounds;
      Menu&                         _menu;
      indie::module::ProfileInfos   _profileInfos;

    public:
      Profile(Menu& menu);
      virtual ~Profile(){}

      bool  checkEvent(kirr::GlobalEvent const&, const kirr::Pos<float> &, const kirr::Pos<float> &, bool);

      virtual bool load();

      indie::module::ProfileInfos & getProfileInfos();
      Menu& getMenu();

    private:
    };

  } /* module */
} /* indie */

#endif /* end of include guard: PROFILE_HPP_ */
