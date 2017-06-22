//
// Connection.cpp for Connection in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/Connection/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Tue May  9 20:11:38 2017 JSX
// Last update Sun Jun 18 22:11:31 2017 Maxime Cauvin
//

#include "Connection.hpp"
#include "Profile.hpp"

indie::module::Connection::Connection(indie::module::ModuleLoader & ml)
:
  AModule(ml),
  _ebrima(ml.getFontEbrima()),
  _oldStateConnect(false)
{
  this->_scopes = {};
}

indie::module::Connection::~Connection() {}

bool            indie::module::Connection::start()
{
  this->_state = true;
  kirr::GlobalEvent mevent = this->getModuleLoader().getKirrlicht().getEventReceiver().getEvent();
  while (this->_state) {
    if (!this->_kirrlicht.getDevice()->run() || mevent.keyTab[kirr::ALL_KEY_CODE::KEY_ESCAPE])
    {
      this->stop();
      this->clear();
      return (false);
    };
    this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(0,200,200,200));
    this->_kirrlicht.getDriver()->draw2DImage(this->_background, kirr::Core::position2d<kirr::s32>(0, 0));
    this->_components["Login"]->draw();
    this->_components["Passwd"]->draw();
    this->_components["PlayOffline"]->draw();
    this->_components["Connect"]->draw();
    this->_components["Title"]->draw();
    this->_components["LoginTxt"]->draw();
    this->_components["PasswdTxt"]->draw();
    this->_components["ErrorTxt"]->draw();
    this->_kirrlicht.getDriver()->endScene();
    if (this->checkLocalConnection() || this->checkConnection())
      continue;
    this->_oldStateConnect = reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Connect"])->isPressed();
    mevent = this->getModuleLoader().getKirrlicht().getEventReceiver().getEvent();
  }
  return (true);
}

bool            indie::module::Connection::checkLocalConnection()
{
  if (reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["PlayOffline"])->isPressed())
  {
    dynamic_cast<AModule *>(this->_moduleLoader.getModules()["Menu"].get())->getScopes()["Profile"].get()->disable();
    dynamic_cast<AModule *>(this->_moduleLoader.getModules()["Menu"].get())->getScopes()["Multiplayer"].get()->disable();
    this->_moduleLoader.switcher("Menu");
    return (true);
  }
  return (false);
}

bool            indie::module::Connection::checkConnection()
{
  if (reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Connect"])->isPressed() && this->_oldStateConnect != reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Connect"])->isPressed())
  {
    std::wstring wsps(this->_components["Login"]->getText());
    std::wstring wspa(this->_components["Passwd"]->getText());
    std::string pseudo(wsps.begin(), wsps.end());
    std::string passwd(wspa.begin(), wspa.end());
    if (!this->connect(pseudo, passwd)) {
      if (!this->_moduleLoader.getNexusAPI().playerExist(pseudo))
        this->_components["ErrorTxt"]->setText(L"This account doesn't exist");
      else
        this->_components["ErrorTxt"]->setText(L"Wrong password");
    } else {
      auto profile = dynamic_cast<indie::module::Profile*>(dynamic_cast<AModule *>(this->_moduleLoader.getModules()["Menu"].get())->getScopes()["Profile"].get());
      if (!profile) {
        return (false);
      }
      auto profileMap = this->_moduleLoader.getNexusAPI().getProfile(pseudo);
      profile->getProfileInfos().setPlayerId(std::stoi(profileMap["id"]));
      profile->getProfileInfos().setPseudo(profileMap["pseudo"]);
      profile->getProfileInfos().setLevel(std::stoi(profileMap["level"]));
      profile->getProfileInfos().setTimePlayed(std::stoi(profileMap["time_played"]));
      profile->getProfileInfos().setRegistrationDate(utils::split(profileMap["registration_date"], ' ').at(0));
      dynamic_cast<AModule *>(this->_moduleLoader.getModules()["Menu"].get())->getScopes()["Profile"].get()->enable();
      dynamic_cast<AModule *>(this->_moduleLoader.getModules()["Menu"].get())->getScopes()["Multiplayer"].get()->enable();
      this->_moduleLoader.switcher("Menu");
      return (true);
    }
  }
  return (false);
}

bool            indie::module::Connection::connect(const std::string & pseudo, const std::string & passwd)
{
  return (this->_moduleLoader.getNexusAPI().checkCredentials(pseudo, passwd));
}

bool            indie::module::Connection::load()
{
  if (!(this->_env = this->_kirrlicht.getGUIEnvironment()) ||
      !(this->_background = this->_kirrlicht.getTexture("./Client/Assets/Textures/Backgrounds/connection.jpg")) ||
      !(this->_skin = this->_env->getSkin()) ||
      !(this->_components["Title"] = this->_kirrlicht.putText(this->_ebrima[48], L"BOMBERWATCH", kirr::Core::rect<kirr::s32>(492, 50, 892, 100), kirr::Color(255, 255, 255, 255))) ||
      !(this->_components["LoginTxt"] = this->_kirrlicht.putText(this->_ebrima[20], L"Login", kirr::Core::rect<kirr::s32>(433, 292, 433 + 100, 292 + 40), kirr::Color(255, 255, 255, 255))) ||
      !(this->_components["PasswdTxt"] = this->_kirrlicht.putText(this->_ebrima[20], L"Password", kirr::Core::rect<kirr::s32>(433, 395, 433 + 100, 395 + 40), kirr::Color(255, 255, 255, 255))) ||
      !(this->_components["ErrorTxt"] = this->_kirrlicht.putText(this->_ebrima[32], L"", kirr::Core::rect<kirr::s32>(430, 200, 430 + 600, 200 + 40), kirr::Color(255, 255, 0, 0))) ||
      !(this->_components["Login"] = this->_env->addEditBox(L"", kirr::Core::rect<kirr::s32>(430, 330, 430 + 400, 330 + 28))) ||
      !(this->_components["Passwd"] = this->_env->addEditBox(L"", kirr::Core::rect<kirr::s32>(430, 430, 430 + 400, 430 + 28))) ||
      !(this->_components["PlayOffline"] = this->_env->addButton(kirr::Core::rect<kirr::s32>(444, 530, 444 + 150, 530 + 26), 0, 0,
                                                   L"Play offline", L"Play offline without internet connection")) ||
      !(this->_components["Connect"] = this->_env->addButton(kirr::Core::rect<kirr::s32>(670, 530, 670 + 150, 530 + 26), 0, 0,
                                               L"Connect", L"Attempt a connection to the server")))
    return (false);
  this->_skin->setFont(this->_ebrima[16]);
  this->_skin->setColor(kirr::Gui::EGDC_BUTTON_TEXT, kirr::Color(255, 0, 0, 0));
  this->_skin->setColor(kirr::Gui::EGDC_TOOLTIP, kirr::Color(255, 0, 0, 0));
  reinterpret_cast<kirr::Gui::IGUIEditBox *>(this->_components["Passwd"])->setPasswordBox(true);
  return (true);
}

bool            indie::module::Connection::clear()
{
  this->_env->clear();
  return (true);
}

bool            indie::module::Connection::stop()
{
  this->_state = false;
  return (true);
}
