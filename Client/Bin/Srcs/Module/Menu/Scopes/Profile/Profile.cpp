/*
** Profile.cpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Profile
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:59:47 2017 Quentin Metge
** Last update Sun Jun 18 02:02:39 2017 Maxime Cauvin
*/

#include "Profile.hpp"

indie::module::Profile::Profile(Menu& menu) :
  AScope("Profile"),
  _sounds(menu.getSoundsMap()),
  _menu(menu),
  _profileInfos(1, *this)
{
  this->_posCamera = kirr::Pos<float>(-200, 0 - 1500, -230);
  // EVENT BOX KEYS
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return (!this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false));});
  // EVENT BOX FCTS
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("PRBACK", "./Client/Assets/Sounds/select.wav");
    this->pollScope(this->_menu, this->_menu.getCamera(), "Default", "Default");
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("PRBACK", "./Client/Assets/Sounds/select.wav");
    this->_menu.zoomInString(this->getStringMesh("BACK"));
  });
  this->_eventBoxesFct.push_back([&](){
  this->_menu.removeIntoSoundMapExceptOne("");
    this->_menu.zoomOutString(this->getStringMesh("BACK"));
  });
}

bool  indie::module::Profile::checkEvent(kirr::GlobalEvent const& gEvent,
                                      const kirr::Pos<float> & topLeft,
                                      const kirr::Pos<float> & bottomRight,
                                      bool flag) {
  return this->_menu.getKirrlicht().mouseEventInZone(gEvent, topLeft, bottomRight, flag);
}

indie::module::ProfileInfos &     indie::module::Profile::getProfileInfos() {
  return this->_profileInfos;
}

bool indie::module::Profile::load() {
  this->_wordsMesh.clear();
  if (this->_profileInfos.getPlayerId() != 1)
  {
    std::string nickname(this->_profileInfos.getPseudo() + " " + std::to_string(this->_profileInfos.getPlayerId()));

    std::transform(nickname.begin(), nickname.end(),nickname.begin(), ::toupper);
    if (!this->_menu.getModuleLoader().getKirrlicht().displayString("PROFILE", kirr::Pos<float>(-333, 250 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
        !this->_menu.getModuleLoader().getKirrlicht().displayString(nickname, kirr::Pos<float>(-600, -80 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.45, 0.45, 0.45), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
        !this->_menu.getModuleLoader().getKirrlicht().displayString("LEVEL " + std::to_string(this->_profileInfos.getLevel()), kirr::Pos<float>(-600, -115 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.45, 0.45, 0.45), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
        !this->_menu.getModuleLoader().getKirrlicht().displayString("PLAYED TIME " + std::to_string(this->_profileInfos.getTimePlayed()) + "MN", kirr::Pos<float>(-92, 100 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.45, 0.45, 0.45), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
        !this->_menu.getModuleLoader().getKirrlicht().displayString("ONLINE RANK NA", kirr::Pos<float>(-95, 65 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.45, 0.45, 0.45), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
        !this->_menu.getModuleLoader().getKirrlicht().displayString("REGISTRATION DATE " + this->_profileInfos.getRegistrationDate(), kirr::Pos<float>(-200, 30 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.45, 0.45, 0.45), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
        !this->_menu.getModuleLoader().getKirrlicht().displayString("BACK", kirr::Pos<float>(-255, -240 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.6, 0.6, 0.6), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png"))
      return (false);
  }
  return (true);
}


indie::module::Menu& indie::module::Profile::getMenu()
{
  return (this->_menu);
}
