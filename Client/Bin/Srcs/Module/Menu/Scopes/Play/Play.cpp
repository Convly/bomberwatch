/*
** Play.cpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Play
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:59:07 2017 Quentin Metge
** Last update Sun Jun 18 02:02:15 2017 Maxime Cauvin
*/

#include "Play.hpp"

indie::module::Play::Play(Menu& menu) :
  AScope("Play"),
  _sounds(menu.getSoundsMap()),
  _menu(menu)
{
  this->_posCamera = kirr::Pos<float>(-200 + 1500, 0, -230);
  this->constructEventBoxesKeys();
  this->constructEventBoxesFcts();
}

bool  indie::module::Play::checkEvent(kirr::GlobalEvent const& gEvent,
                                      const kirr::Pos<float> & topLeft,
                                      const kirr::Pos<float> & bottomRight,
                                      bool flag) {
  return this->_menu.getKirrlicht().mouseEventInZone(gEvent, topLeft, bottomRight, flag);
}

bool indie::module::Play::load() {
  this->_wordsMesh.clear();
  if (!this->_menu.getModuleLoader().getKirrlicht().displayString("PLAY", kirr::Pos<float>(-280 + 1500, 250, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("SOLO", kirr::Pos<float>(-630 + 1500, 80, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("MULTIPLAYER", kirr::Pos<float>(-630 + 1500, 10, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("BACK", kirr::Pos<float>(-255 + 1500, -240, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.6, 0.6, 0.6), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png"))
    return (false);
  return true;
}

void indie::module::Play::constructEventBoxesKeys() {
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(337, 317, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 344, 0), kirr::Pos<float>(639, 401, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return (!this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false) &&
            !this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(337, 317, 0), false) &&
            !this->checkEvent(gEvent, kirr::Pos<float>(130, 344, 0), kirr::Pos<float>(639, 401, 0), false));
  });
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(337, 317, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 344, 0), kirr::Pos<float>(639, 401, 0), false);});
}

void indie::module::Play::constructEventBoxesFcts() {
  this->_eventBoxesFct.push_back([&]() {
    this->_menu.addSelectSound("PLBACK", "./Client/Assets/Sounds/select.wav");
    this->pollScope(this->_menu, this->_menu.getCamera(), "Default", this->_menu.getPrevScope());
  });
  this->_eventBoxesFct.push_back([&]() {
    this->_menu.addSelectSound("PLSOLO", "./Client/Assets/Sounds/select.wav");
    this->pollScope(this->_menu, this->_menu.getCamera(), "Play", "Solo");
  });
  this->_eventBoxesFct.push_back([&]() {
    this->_menu.addSelectSound("PLMULTI", "./Client/Assets/Sounds/select.wav");
    this->pollScope(this->_menu, this->_menu.getCamera(), "Play", "Multiplayer");
  });
  this->_eventBoxesFct.push_back([&]() {
    this->_menu.addSelectSound("PLBACK", "./Client/Assets/Sounds/select.wav");
    this->_menu.zoomInString(this->getStringMesh("BACK"));
    this->_menu.moveStringToLeft(this->getStringMesh("SOLO"), -630 + 1500, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("MULTIPLAYER"), -630 + 1500, 8);
  });
  this->_eventBoxesFct.push_back([&]() {
    this->_menu.removeIntoSoundMapExceptOne("");
    this->_menu.zoomOutString(this->getStringMesh("BACK"));
    this->_menu.moveStringToLeft(this->getStringMesh("SOLO"), -630 + 1500, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("MULTIPLAYER"), -630 + 1500, 8);
  });
  this->_eventBoxesFct.push_back([&]() {
    this->_menu.addSelectSound("PLSOLO", "./Client/Assets/Sounds/select.wav");
    this->_menu.zoomOutString(this->getStringMesh("BACK"));
    this->_menu.moveStringToRight(this->getStringMesh("SOLO"), -630 + 1500, 8, 40);
    this->_menu.moveStringToLeft(this->getStringMesh("MULTIPLAYER"), -630 + 1500, 8);
  });
  this->_eventBoxesFct.push_back([&]() {
    this->_menu.addSelectSound("PLMULTI", "./Client/Assets/Sounds/select.wav");
    this->_menu.zoomOutString(this->getStringMesh("BACK"));
    this->_menu.moveStringToLeft(this->getStringMesh("SOLO"), -630 + 1500, 8);
    this->_menu.moveStringToRight(this->getStringMesh("MULTIPLAYER"), -630 + 1500, 8, 40);
  });
}
