/*
** Solo.cpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Solo
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 15:01:44 2017 Quentin Metge
** Last update Sun Jun 18 02:04:09 2017 Maxime Cauvin
*/

#include "GameClient.hpp"
#include "Solo.hpp"

indie::module::Solo::Solo(Menu& menu) :
  AScope("Solo"),
  _ebrima(menu.getModuleLoader().getFontEbrima()),
  _localMp(false),
  _oldStateScrSplit(false),
  _sounds(menu.getSoundsMap()),
  _menu(menu)
{
  this->_posCamera = kirr::Pos<float>(-200 + 1500, 0 + 1500, -230);

  this->constructEventBoxesKeys();
  this->constructEventBoxesFcts();
}

bool  indie::module::Solo::checkEvent(kirr::GlobalEvent const& gEvent,
                                      const kirr::Pos<float> & topLeft,
                                      const kirr::Pos<float> & bottomRight,
                                      bool flag) {
  return this->_menu.getKirrlicht().mouseEventInZone(gEvent, topLeft, bottomRight, flag);
}

bool indie::module::Solo::load() {
  this->_wordsMesh.clear();
  if (!this->_menu.getModuleLoader().getKirrlicht().displayString("SOLO", kirr::Pos<float>(-287 + 1500, 250 + 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("START", kirr::Pos<float>(-630 + 1500, 80 + 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("BACK", kirr::Pos<float>(-255 + 1500, -240 + 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.6, 0.6, 0.6), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !(this->_env = this->_menu.getModuleLoader().getKirrlicht().getGUIEnvironment()) ||
      !(this->_skin = this->_env->getSkin()) ||
      !(this->_components["ScreenSplit"] = this->_env->addButton(kirr::Core::rect<kirr::s32>(900, 250, 900 + 100, 250 + 26), 0, -1,
                                                   L"Off")) ||
      !(this->_components["ScreenSTxt"] = this->_menu.getModuleLoader().getKirrlicht().putText(this->_ebrima[16], L"Splited Screen",
                                                                                               kirr::Core::rect<kirr::s32>(904, 223, 904 + 220, 223 + 30),
                                                                                               kirr::Color(255, 0, 0, 0))) ||
      !(this->_bgMusic = this->_menu.getBgMusic()))
    return (false);
  this->_components["ScreenSplit"]->setVisible(false);
  return (true);
}

bool indie::module::Solo::loop()
{
  this->_components["ScreenSplit"]->setVisible(true);
  this->_components["ScreenSTxt"]->draw();
  this->_components["ScreenSplit"]->draw();
  if (reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["ScreenSplit"])->isPressed() && !this->_oldStateScrSplit)
  {
    if (!this->_localMp){
      this->_components["ScreenSplit"]->setText(L"On");
      this->_menu.getPlayerTwo()->setState(true);
    }
    else{
      this->_components["ScreenSplit"]->setText(L"Off");
      this->_menu.getPlayerTwo()->setState(false);
    }
    this->_localMp = !this->_localMp;
  }
  this->_oldStateScrSplit = reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["ScreenSplit"])->isPressed();
  return (true);
}

void indie::module::Solo::constructEventBoxesKeys() {
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return (!this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false) &&
                                                                                 !this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(385, 319, 0), false) &&
                                                                                 !this->checkEvent(gEvent, kirr::Pos<float>(130, 330, 0), kirr::Pos<float>(385, 389, 0), false));});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(385, 319, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(385, 319, 0), false);});
}

void indie::module::Solo::constructEventBoxesFcts() {
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("SOBACK", "./Client/Assets/Sounds/select.wav");
    this->_components["ScreenSplit"]->setVisible(false);
    this->pollScope(this->_menu, this->_menu.getCamera(), "Default", "Play");
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("SOBACK", "./Client/Assets/Sounds/select.wav");
    this->_menu.zoomInString(this->getStringMesh("BACK"));
    this->_menu.moveStringToLeft(this->getStringMesh("START"), -630 + 1500, 8);
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.removeIntoSoundMapExceptOne("");
    this->_menu.zoomOutString(this->getStringMesh("BACK"));
    this->_menu.moveStringToLeft(this->getStringMesh("START"), -630 + 1500, 8);
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.removeIntoSoundMapExceptOne("");
    auto gameClientPtr = dynamic_cast<indie::module::GameClient*>(this->_menu.getModuleLoader().getModules()["GameClient"].get());
    if (!gameClientPtr)
      return false;
    gameClientPtr->getGameInfos().getServerInfos().setMultiplayer(false);
    this->_bgMusic->stop();
    this->_menu.getModuleLoader().switcher("GameClient");
    return true;
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("SOSTART", "./Client/Assets/Sounds/select.wav");
    this->_menu.zoomOutString(this->getStringMesh("BACK"));
    this->_menu.moveStringToRight(this->getStringMesh("START"), -630 + 1500, 8, 40);
    return (true);
  });
}
