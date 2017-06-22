/*
** Multiplayer.cpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Multiplayer
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 14:58:07 2017 Quentin Metge
** Last update Sun Jun 18 17:19:33 2017 Maxime Cauvin
*/

#include "Multiplayer.hpp"

indie::module::Multiplayer::Multiplayer(Menu& menu) :
  AScope("Multiplayer"),
  _ebrima(menu.getModuleLoader().getFontEbrima()),
  _localMp(false),
  _oldStateScrSplit(false),
  _sounds(menu.getSoundsMap()),
  _menu(menu)
{
  this->_posCamera = kirr::Pos<float>(-200 + 1500, 0 - 1500, -230);
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {
    return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), true);
  });
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {
    return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false);
  });
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {
    return (!this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false));
  });
  this->_eventBoxesFct.push_back([&](){
    this->_components["ScreenSplit"]->setVisible(false);
    this->_components["IpAddress"]->setVisible(false);
    this->_components["Port"]->setVisible(false);
    this->_components["Connect"]->setVisible(false);
    this->_components["Refresh"]->setVisible(false);
    this->_components["WinServerList"]->setVisible(false);
    this->_components["ListBox"]->setVisible(false);
    this->_menu.addSelectSound("MPBACK", "./Client/Assets/Sounds/select.wav");
    this->pollScope(this->_menu, this->_menu.getCamera(), "Default", "Play");
  });
  this->_eventBoxesFct.push_back([&](){
  this->_menu.addSelectSound("MPBACK", "./Client/Assets/Sounds/select.wav");
    this->_menu.zoomInString(this->getStringMesh("BACK"));
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.removeIntoSoundMapExceptOne("");
    this->_menu.zoomOutString(this->getStringMesh("BACK"));
  });
}

bool  indie::module::Multiplayer::checkEvent(kirr::GlobalEvent const& gEvent,
                                             const kirr::Pos<float> & topLeft,
                                             const kirr::Pos<float> & bottomRight,
                                             bool flag) {
  return this->_menu.getKirrlicht().mouseEventInZone(gEvent, topLeft, bottomRight, flag);
}

void indie::module::Multiplayer::refreshServerList()
{
  if (dynamic_cast<indie::module::Profile*>(this->_menu.getScopes()["Profile"].get())->getProfileInfos().getPlayerId() != 1)
  {
    reinterpret_cast<kirr::Gui::IGUIListBox *>(this->_components["ListBox"])->clear();
    this->_serverListId = this->_menu.getModuleLoader().getNexusAPI().getServerList();
    for (size_t i = 0; i < this->_serverListId.size(); i++)
    {
      std::unordered_map<std::string, std::string> infos = this->_menu.getModuleLoader().getNexusAPI().getServerInfos(this->_serverListId[i]);
      reinterpret_cast<kirr::Gui::IGUIListBox *>(this->_components["ListBox"])->addItem(utils::getWStrFromStr(infos["ip"] + " - " + infos["name"]).c_str());
    }
  }
}

bool indie::module::Multiplayer::load() {
  this->_wordsMesh.clear();
  if (!this->_menu.getModuleLoader().getKirrlicht().displayString("MULTIPLAYER", kirr::Pos<float>(-430 + 1500, 250 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("BACK", kirr::Pos<float>(-255 + 1500, -240 - 1500, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.6, 0.6, 0.6), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !(this->_env = this->_menu.getModuleLoader().getKirrlicht().getGUIEnvironment()) ||
      !(this->_skin = this->_env->getSkin()) ||
      !(this->_components["IpAddress"] = this->_env->addEditBox(L"", kirr::Core::rect<kirr::s32>(80, 260, 80 + 160, 260 + 28))) ||
      !(this->_components["Port"] = this->_env->addEditBox(L"", kirr::Core::rect<kirr::s32>(270, 260, 270 + 74, 260 + 28))) ||
      !(this->_components["Connect"] = this->_env->addButton(kirr::Core::rect<kirr::s32>(81, 310, 81 + 100, 310 + 26), 0, 0,
                                                             L"Connect", L"Connect to the server")) ||
      !(this->_components["Refresh"] = this->_env->addButton(kirr::Core::rect<kirr::s32>(201, 310, 201 + 100, 310 + 26), 0, 0,
                                                             L"Refresh", L"Refresh the server list")) ||
      !(this->_components["WinServerList"] = this->_env->addWindow(kirr::Core::rect<kirr::s32>(600, 200, 600 + 570, 200 + 370))) ||
      !(this->_components["ListBox"] = this->_env->addListBox(kirr::Core::rect<kirr::s32>(0, 20, 0 + 570, 20 + 370), this->_components["WinServerList"])) ||
      !(this->_components["IpAddrTxt"] = this->_menu.getModuleLoader().getKirrlicht().putText(this->_ebrima[16], L"IP Address",
                                                                                              kirr::Core::rect<kirr::s32>(84, 233, 84 + 100, 233 + 30),
                                                                                              kirr::Color(255, 0, 0, 0))) ||
      !(this->_components["PortTxt"] = this->_menu.getModuleLoader().getKirrlicht().putText(this->_ebrima[16], L"Port",
                                                                                            kirr::Core::rect<kirr::s32>(274, 233, 274 + 100, 233 + 30),
                                                                                            kirr::Color(255, 0, 0, 0))) ||
      !(this->_components["ScreenSplit"] = this->_env->addButton(kirr::Core::rect<kirr::s32>(80, 390, 80 + 100, 390 + 26), 0, -1,
                                                   L"Off")) ||
      !(this->_components["ScreenSTxt"] = this->_menu.getModuleLoader().getKirrlicht().putText(this->_ebrima[16], L"Splited Screen",
                                                                                               kirr::Core::rect<kirr::s32>(84, 363, 84 + 220, 363 + 30),
                                                                                               kirr::Color(255, 0, 0, 0))) ||
      !(this->_bgMusic = this->_menu.getBgMusic()))
    return (false);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinServerList"])->setDrawBackground(true);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinServerList"])->getCloseButton()->setVisible(false);
  reinterpret_cast<kirr::Gui::IGUIEditBox *>(this->_components["IpAddress"])->setOverrideFont(this->_ebrima[16]);
  reinterpret_cast<kirr::Gui::IGUIEditBox *>(this->_components["Port"])->setOverrideFont(this->_ebrima[16]);
  reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Connect"])->setOverrideFont(this->_ebrima[16]);
  reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Refresh"])->setOverrideFont(this->_ebrima[16]);
  this->refreshServerList();
  this->_components["ScreenSplit"]->setVisible(false);
  this->_components["IpAddress"]->setVisible(false);
  this->_components["Port"]->setVisible(false);
  this->_components["Connect"]->setVisible(false);
  this->_components["Refresh"]->setVisible(false);
  this->_components["WinServerList"]->setVisible(false);
  this->_components["ListBox"]->setVisible(false);
  this->_components["Port"]->setText(L"7171");
  return (true);
}

bool indie::module::Multiplayer::loop()
{
  this->_components["ScreenSplit"]->setVisible(true);
  this->_components["IpAddress"]->setVisible(true);
  this->_components["Port"]->setVisible(true);
  this->_components["Connect"]->setVisible(true);
  this->_components["Refresh"]->setVisible(true);
  this->_components["WinServerList"]->setVisible(true);
  this->_components["ListBox"]->setVisible(true);
  this->_components["ScreenSplit"]->draw();
  this->_components["ScreenSTxt"]->draw();
  this->_components["IpAddress"]->draw();
  this->_components["Port"]->draw();
  this->_components["Connect"]->draw();
  this->_components["Refresh"]->draw();
  this->_components["IpAddrTxt"]->draw();
  this->_components["PortTxt"]->draw();
  this->_components["WinServerList"]->draw();
  if (reinterpret_cast<kirr::Gui::IGUIListBox *>(this->_components["ListBox"])->getSelected() != -1)
  {
    std::string str(utils::getStrFromWStr(reinterpret_cast<kirr::Gui::IGUIListBox *>(this->_components["ListBox"])->getListItem(reinterpret_cast<kirr::Gui::IGUIListBox *>(this->_components["ListBox"])->getSelected())));
    std::string str2(utils::getStrFromWStr(this->_components["IpAddress"]->getText()));
    std::string str3(utils::getStrFromWStr(this->_components["Port"]->getText()));
    std::string addip(str.substr(0, str.find(":")));
    std::string port(str.substr(str.find(":") + 1, str.find(" -") - str.find(":") - 1));
    if (addip != str2 || port != str3)
      reinterpret_cast<kirr::Gui::IGUIListBox *>(this->_components["ListBox"])->setSelected(-1);
    if (addip != str2)
      this->_components["IpAddress"]->setText(utils::getWStrFromStr(addip).c_str());
    if (port != str3)
      this->_components["Port"]->setText(utils::getWStrFromStr(port).c_str());
  }
  this->_sAddrip = utils::getStrFromWStr(this->_components["IpAddress"]->getText());
  this->_sPort = utils::getStrFromWStr(this->_components["Port"]->getText());
  if (reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Connect"])->isPressed() &&
      this->_sAddrip != "" && this->_sPort != "" &&
      (utils::isAnIPAddress(this->_sAddrip) || this->_sAddrip == "localhost") &&
      utils::isANumber(this->_sPort))
    {
      auto gameClientPtr = dynamic_cast<indie::module::GameClient*>(this->_menu.getModuleLoader().getModules()["GameClient"].get());

      if (!gameClientPtr)
        return false;
      gameClientPtr->getGameInfos().getServerInfos().setMultiplayer(true);
      if (this->_sAddrip == "localhost")
        gameClientPtr->getGameInfos().getServerInfos().setIpAddr("127.0.0.1");
      else
        gameClientPtr->getGameInfos().getServerInfos().setIpAddr(this->_sAddrip);
      gameClientPtr->getGameInfos().getServerInfos().setPort(std::stol(this->_sPort));
      this->_bgMusic->stop();
      this->_menu.getModuleLoader().switcher("GameClient");
    }
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
  if (reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Refresh"])->isPressed() && !this->_oldStateRefresh)
    this->refreshServerList();
  this->_oldStateScrSplit = reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["ScreenSplit"])->isPressed();
  this->_oldStateRefresh = reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Refresh"])->isPressed();
  return (true);
}
