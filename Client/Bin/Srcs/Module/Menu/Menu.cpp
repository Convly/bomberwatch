/*
** Menu.cpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:11:06 2017 Quentin Metge
** Last update Sun Jun 18 20:45:39 2017 Maxime Cauvin
*/

#include "Menu.hpp"
#include "Home.hpp"
#include "Multiplayer.hpp"
#include "Profile.hpp"
#include "Settings.hpp"
#include "Solo.hpp"
#include "Play.hpp"

indie::module::Menu::Menu(indie::module::ModuleLoader & ml)
: AModule(ml),
  _volume({
    {"Music", 50},
    {"SFX", 100}
  }){
  this->_scopes = {
    {"Default", std::make_shared<indie::module::Home>(*this)},
    {"Play", std::make_shared<indie::module::Play>(*this)},
    {"Solo", std::make_shared<indie::module::Solo>(*this)},
    {"Multiplayer", std::make_shared<indie::module::Multiplayer>(*this)},
    {"Profile", std::make_shared<indie::module::Profile>(*this)},
    {"Settings", std::make_shared<indie::module::Settings>(*this)}
  };
}

indie::module::Menu::~Menu(){

}

bool            indie::module::Menu::start()
{
  this->_bgMusic->setIsPaused(false);
  while (this->_state)
  {
    kirr::GlobalEvent mevent = this->_kirrlicht.getEventReceiver().getEvent();
    if (!this->_kirrlicht.getDevice()->run())
    {
      this->stop();
      this->clear();
      continue;
    }
    this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(255, 200, 200, 200));
    this->_kirrlicht.getSceneManager()->drawAll();
    this->_scopes[this->_currentScope].get()->loop();
    this->_kirrlicht.getDriver()->endScene();
    this->_scopes[this->_currentScope]->pollEvent(mevent);
  }
  return (true);
}

bool            indie::module::Menu::load()
{
  // Create camera
  if (!(this->_camera = this->_kirrlicht.getSceneManager()->addCameraSceneNode(0, kirr::vector3df(0,0,0), kirr::vector3df(0,0,0))) ||
      !(this->_sky = this->_kirrlicht.getTexture("./Client/Assets/Textures/Skyboxes/sky_menu.png")) ||
      !this->_kirrlicht.getSceneManager()->addSkyBoxSceneNode(this->_sky, this->_sky, this->_sky, this->_sky, this->_sky, this->_sky) ||
      !(this->_bgMusic = this->_kirrlicht.add2dSound("./Client/Assets/Sounds/music_menu.wav", true)))
    return (false);

  this->_bgMusic->setVolume(this->_volume["Music"] / 100.0f);

  // Set camera
  this->_camera->setPosition(kirr::vector3df(-200, 0, -230));
  this->_camera->setTarget(kirr::vector3df(-200, 0, 0));

  // Load associated scopes
  if ((!(this->_playerOne = dynamic_cast<GameClient *>(this->getModuleLoader().getModules()["GameClient"].get())->getPlayerOne()) && std::fprintf(stderr, "Error: Loading player 1")) ||
      (!(this->_playerTwo = dynamic_cast<GameClient *>(this->getModuleLoader().getModules()["GameClient"].get())->getPlayerTwo()) && std::fprintf(stderr, "Error: Loading player 2")) ||
      !this->getScopes()["Default"].get()->load() ||
      !this->getScopes()["Play"].get()->load() ||
      !this->getScopes()["Solo"].get()->load() ||
      !this->getScopes()["Multiplayer"].get()->load() ||
      !this->getScopes()["Settings"].get()->load() ||
      !this->getScopes()["Profile"].get()->load())
    return (false);
  this->setCurrentScope("Default");
  this->_kirrlicht.getEventReceiver().resetEvent();
  this->_state = true;
  return (true);
}

bool            indie::module::Menu::clear()
{
  if (this->_bgMusic)
    this->_bgMusic->stop();
  this->_kirrlicht.getSceneManager()->clear();
  return (true);
}

bool            indie::module::Menu::stop()
{
  this->_state = false;
  this->_moduleLoader.setStatus(false);
  return (true);
}

void      indie::module::Menu::removeIntoSoundMapExceptOne(std::string const& key)
{
  for (auto it = this->_sounds.begin(); it != this->_sounds.end() && !this->_sounds.empty();)
  {
    if (it->second->isFinished() && it->first != key)
      it = this->_sounds.erase(it);
    else
      ++it;
  }
}

bool                                                    indie::module::Menu::addSelectSound(std::string const& key, std::string const& soundPath)
{
  if (this->_sounds.find(key) == this->_sounds.end())
  {
    this->_sounds[key] = this->_kirrlicht.add2dSound(soundPath, false);
    this->_sounds[key]->setVolume(this->_volume["SFX"] / 100.0f);
    this->_sounds[key]->setIsPaused(false);
  }
  this->removeIntoSoundMapExceptOne(key);
  return (true);
}

void                                                    indie::module::Menu::setMusicVolume(int const& musicVolume)
{
  if (musicVolume != this->_volume["Music"])
  {
    indie::module::ProfileInfos &profileInfos = dynamic_cast<indie::module::Profile *>(dynamic_cast<indie::module::Menu *>(this->getModuleLoader().getModules()["Menu"].get())->getScopes()["Profile"].get())->getProfileInfos();
    this->_volume["Music"] = musicVolume;
    this->_bgMusic->setVolume(musicVolume / 100.0f);
    this->getModuleLoader().getNexusAPI().setPlayerMusic(profileInfos.getPlayerId(), this->_volume["Music"]);
  }
}

void                                                    indie::module::Menu::setSFXVolume(int const& sfxVolume)
{
  if (sfxVolume != this->_volume["SFX"])
  {
    indie::module::ProfileInfos &profileInfos = dynamic_cast<indie::module::Profile *>(dynamic_cast<indie::module::Menu *>(this->getModuleLoader().getModules()["Menu"].get())->getScopes()["Profile"].get())->getProfileInfos();
    this->_volume["SFX"] = sfxVolume;
    this->getModuleLoader().getNexusAPI().setPlayerSFX(profileInfos.getPlayerId(), this->_volume["SFX"]);
  }
}

kirr::Camera    *indie::module::Menu::getCamera()
{
  return (this->_camera);
}

std::shared_ptr<indie::game::Player>    indie::module::Menu::getPlayerOne()
{
  return (this->_playerOne);
}

std::shared_ptr<indie::game::Player>    indie::module::Menu::getPlayerTwo()
{
  return (this->_playerTwo);
}

std::unordered_map<std::string, kirr::klang::ISound *> indie::module::Menu::getSoundsMap() const
{
  return (this->_sounds);
}
std::unordered_map<std::string, kirr::klang::ISound *> &indie::module::Menu::getSoundsMap()
{
  return (this->_sounds);
}

kirr::klang::ISound                                    *indie::module::Menu::getBgMusic()
{
  return (this->_bgMusic);
}

int                                                     indie::module::Menu::getMusicVolume()
{
  return (this->_volume["Music"]);
}

int                                                     indie::module::Menu::getSFXVolume()
{
  return (this->_volume["SFX"]);
}
