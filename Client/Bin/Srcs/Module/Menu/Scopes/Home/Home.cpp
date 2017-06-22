/*
** Home.cpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Home
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:55:18 2017 Quentin Metge
** Last update Sun Jun 18 02:00:43 2017 Maxime Cauvin
*/

#include "Home.hpp"

indie::module::Home::Home(Menu& menu) :
  AScope("Default"),
  _menu(menu),
  _sounds(menu.getSoundsMap())
{
  this->_posCamera = kirr::Pos<float>(-200, 0, -230);
  this->constructEventBoxesKeys();
  this->constructEventBoxesFcts();
}

indie::module::Home::~Home() {}

bool  indie::module::Home::checkEvent(kirr::GlobalEvent const& gEvent,
                                      const kirr::Pos<float> & topLeft,
                                      const kirr::Pos<float> & bottomRight,
                                      bool flag) {
  return this->_menu.getKirrlicht().mouseEventInZone(gEvent, topLeft, bottomRight, flag);
}

bool  indie::module::Home::load() {
  //Home
  this->_wordsMesh.clear();
  if (!this->_menu.getModuleLoader().getKirrlicht().displayString("BOMBERWATCH", kirr::Pos<float>(-430, 250, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("PLAY", kirr::Pos<float>(-630, 80, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("PROFILE", kirr::Pos<float>(-630, 10, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("SETTINGS", kirr::Pos<float>(-630, -60, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("EXIT", kirr::Pos<float>(-630, -130, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png"))
    return (false);
  return true;
}

void      indie::module::Home::constructEventBoxesKeys() {
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(335, 325, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 345, 0), kirr::Pos<float>(445, 405, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 425, 0), kirr::Pos<float>(490, 485, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 510, 0), kirr::Pos<float>(300, 570, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {
    return (!this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(335, 325, 0), false) &&
            !this->checkEvent(gEvent, kirr::Pos<float>(130, 345, 0), kirr::Pos<float>(445, 405, 0), false) &&
            !this->checkEvent(gEvent, kirr::Pos<float>(130, 425, 0), kirr::Pos<float>(490, 485, 0), false) &&
            !this->checkEvent(gEvent, kirr::Pos<float>(130, 510, 0), kirr::Pos<float>(300, 570, 0), false));
  });
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 260, 0), kirr::Pos<float>(335, 325, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 345, 0), kirr::Pos<float>(445, 405, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 425, 0), kirr::Pos<float>(490, 485, 0), true);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(130, 510, 0), kirr::Pos<float>(300, 570, 0), true);});
}

void      indie::module::Home::constructEventBoxesFcts() {
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("HPLAY", "./Client/Assets/Sounds/select.wav");
    this->_menu.moveStringToRight(this->getStringMesh("PLAY"), -630, 8, 40);
    this->_menu.moveStringToLeft(this->getStringMesh("PROFILE"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("SETTINGS"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("EXIT"), -630, 8);
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("HPROFILE", "./Client/Assets/Sounds/select.wav");
    this->_menu.moveStringToLeft(this->getStringMesh("PLAY"), -630, 8);
    this->_menu.moveStringToRight(this->getStringMesh("PROFILE"), -630, 8, 40);
    this->_menu.moveStringToLeft(this->getStringMesh("SETTINGS"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("EXIT"), -630, 8);
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("HSETTINGS", "./Client/Assets/Sounds/select.wav");
    this->_menu.moveStringToLeft(this->getStringMesh("PLAY"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("PROFILE"), -630, 8);
    this->_menu.moveStringToRight(this->getStringMesh("SETTINGS"), -630, 8, 40);
    this->_menu.moveStringToLeft(this->getStringMesh("EXIT"), -630, 8);
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("HEXIT", "./Client/Assets/Sounds/select.wav");
    this->_menu.moveStringToLeft(this->getStringMesh("PLAY"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("PROFILE"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("SETTINGS"), -630, 8);
    this->_menu.moveStringToRight(this->getStringMesh("EXIT"), -630, 8, 40);
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.removeIntoSoundMapExceptOne("");
    this->_menu.moveStringToLeft(this->getStringMesh("PLAY"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("PROFILE"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("SETTINGS"), -630, 8);
    this->_menu.moveStringToLeft(this->getStringMesh("EXIT"), -630, 8);
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("HPLAY", "./Client/Assets/Sounds/select.wav");
    this->pollScope(this->_menu, this->_menu.getCamera(), "Default", "Play");
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("HPROFILE", "./Client/Assets/Sounds/select.wav");
    this->pollScope(this->_menu, this->_menu.getCamera(), "Default", "Profile");
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("HSETTINGS", "./Client/Assets/Sounds/select.wav");
    this->pollScope(this->_menu, this->_menu.getCamera(), "Default", "Settings");
  });
  this->_eventBoxesFct.push_back([&]()
  {
    this->_menu.removeIntoSoundMapExceptOne("");
    this->_menu.stop();
  });
}
