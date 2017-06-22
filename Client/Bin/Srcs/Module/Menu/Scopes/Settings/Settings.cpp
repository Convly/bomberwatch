/*
** Settings.cpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Settings
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 15:00:59 2017 Quentin Metge
** Last update Sun Jun 18 20:55:29 2017 Maxime Cauvin
*/

#include "Settings.hpp"

indie::module::Settings::Settings(Menu& menu) :
  AScope("Settings"),
  _sounds(menu.getSoundsMap()),
  _menu(menu),
  _ebrima(menu.getModuleLoader().getFontEbrima()),
  _buttonNames({
    std::make_pair("Move forward", bwsg::ActionType::MOVE_FORWARD),
    std::make_pair("Move backward", bwsg::ActionType::MOVE_BACK),
    std::make_pair("Move left", bwsg::ActionType::MOVE_LEFT),
    std::make_pair("Move right", bwsg::ActionType::MOVE_RIGHT),
    std::make_pair("Action 1", bwsg::ActionType::ACTION1),
    std::make_pair("Action 2", bwsg::ActionType::ACTION2),
    std::make_pair("Action 3", bwsg::ActionType::ACTION3),
    std::make_pair("Action 4", bwsg::ActionType::ACTION4),
    std::make_pair("Pause", bwsg::ActionType::PAUSE),
  }),
  _buttonToAPI({
    {"Move forward", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsForward(playerId, key));
    }},
    {"Move backward", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsBackward(playerId, key));
    }},
    {"Move left", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsLeft(playerId, key));
    }},
    {"Move right", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsRight(playerId, key));
    }},
    {"Action 1", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsAction1(playerId, key));
    }},
    {"Action 2", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsAction2(playerId, key));
    }},
    {"Action 3", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsAction3(playerId, key));
    }},
    {"Action 4", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsAction4(playerId, key));
    }},
    {"Pause", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsPause(playerId, key));
    }},
    {"Control", [&] (int const& playerId, int const& key) {
      return (this->_menu.getModuleLoader().getNexusAPI().setSettingsControl(playerId, key));
    }}
  }),
  _namesAliases({
    {"forward", "Move forward"},
    {"backward", "Move backward"},
    {"left", "Move left"},
    {"right", "Move right"},
    {"action1", "Action 1"},
    {"action2", "Action 2"},
    {"action3", "Action 3"},
    {"action4", "Action 4"},
    {"pause", "Pause"},
    {"control", "Control"}
  }),
  _keysAliases({
    {kirr::ALL_KEY_CODE::KEY_LBUTTON, L"LMouse"},
    {kirr::ALL_KEY_CODE::KEY_RBUTTON, L"RMouse"},
    {kirr::ALL_KEY_CODE::KEY_CANCEL, L"Cancel"},
    {kirr::ALL_KEY_CODE::KEY_MBUTTON, L"MMouse"},
    {kirr::ALL_KEY_CODE::KEY_XBUTTON1, L"X1"},
    {kirr::ALL_KEY_CODE::KEY_XBUTTON2, L"X2"},
    {kirr::ALL_KEY_CODE::KEY_BACK, L"Backspace"},
    {kirr::ALL_KEY_CODE::KEY_TAB, L"Tab"},
    {kirr::ALL_KEY_CODE::KEY_CLEAR, L"Clear"},
    {kirr::ALL_KEY_CODE::KEY_RETURN, L"Enter"},
    {kirr::ALL_KEY_CODE::KEY_SHIFT, L"Shift"},
    {kirr::ALL_KEY_CODE::KEY_CONTROL, L"Ctrl"},
    {kirr::ALL_KEY_CODE::KEY_MENU, L"Alt"},
    {kirr::ALL_KEY_CODE::KEY_PAUSE, L"Pause"},
    {kirr::ALL_KEY_CODE::KEY_CAPITAL, L"Capslock"},
    {kirr::ALL_KEY_CODE::KEY_KANA, L"Kana"},
    {kirr::ALL_KEY_CODE::KEY_HANGUEL, L"Hanguel"},
    {kirr::ALL_KEY_CODE::KEY_HANGUL, L"Hangul"},
    {kirr::ALL_KEY_CODE::KEY_JUNJA, L"Junja"},
    {kirr::ALL_KEY_CODE::KEY_FINAL, L"Final"},
    {kirr::ALL_KEY_CODE::KEY_HANJA, L"Hanja"},
    {kirr::ALL_KEY_CODE::KEY_KANJI, L"Kanji"},
    {kirr::ALL_KEY_CODE::KEY_ESCAPE, L"Escape"},
    {kirr::ALL_KEY_CODE::KEY_CONVERT, L"Convert"},
    {kirr::ALL_KEY_CODE::KEY_NONCONVERT, L"Nonconvert"},
    {kirr::ALL_KEY_CODE::KEY_ACCEPT, L"Accept"},
    {kirr::ALL_KEY_CODE::KEY_MODECHANGE, L"Modechange"},
    {kirr::ALL_KEY_CODE::KEY_SPACE, L"Spacebar"},
    {kirr::ALL_KEY_CODE::KEY_PRIOR, L"PageUp"},
    {kirr::ALL_KEY_CODE::KEY_NEXT, L"PageDown"},
    {kirr::ALL_KEY_CODE::KEY_END, L"End"},
    {kirr::ALL_KEY_CODE::KEY_HOME, L"Home"},
    {kirr::ALL_KEY_CODE::KEY_LEFT, L"Left"},
    {kirr::ALL_KEY_CODE::KEY_UP, L"Up"},
    {kirr::ALL_KEY_CODE::KEY_RIGHT, L"Right"},
    {kirr::ALL_KEY_CODE::KEY_DOWN, L"Down"},
    {kirr::ALL_KEY_CODE::KEY_SELECT, L"Select"},
    {kirr::ALL_KEY_CODE::KEY_PRINT, L"Print"},
    {kirr::ALL_KEY_CODE::KEY_EXECUT, L"Execute"},
    {kirr::ALL_KEY_CODE::KEY_SNAPSHOT, L"PrintScreen"},
    {kirr::ALL_KEY_CODE::KEY_INSERT, L"Insert"},
    {kirr::ALL_KEY_CODE::KEY_DELETE, L"Delete"},
    {kirr::ALL_KEY_CODE::KEY_HELP, L"Help"},
    {kirr::ALL_KEY_CODE::KEY_KEY_0, L"0"},
    {kirr::ALL_KEY_CODE::KEY_KEY_1, L"1"},
    {kirr::ALL_KEY_CODE::KEY_KEY_2, L"2"},
    {kirr::ALL_KEY_CODE::KEY_KEY_3, L"3"},
    {kirr::ALL_KEY_CODE::KEY_KEY_4, L"4"},
    {kirr::ALL_KEY_CODE::KEY_KEY_5, L"5"},
    {kirr::ALL_KEY_CODE::KEY_KEY_6, L"6"},
    {kirr::ALL_KEY_CODE::KEY_KEY_7, L"7"},
    {kirr::ALL_KEY_CODE::KEY_KEY_8, L"8"},
    {kirr::ALL_KEY_CODE::KEY_KEY_9, L"9"},
    {kirr::ALL_KEY_CODE::KEY_KEY_A, L"A"},
    {kirr::ALL_KEY_CODE::KEY_KEY_B, L"B"},
    {kirr::ALL_KEY_CODE::KEY_KEY_C, L"C"},
    {kirr::ALL_KEY_CODE::KEY_KEY_D, L"D"},
    {kirr::ALL_KEY_CODE::KEY_KEY_E, L"E"},
    {kirr::ALL_KEY_CODE::KEY_KEY_F, L"F"},
    {kirr::ALL_KEY_CODE::KEY_KEY_G, L"G"},
    {kirr::ALL_KEY_CODE::KEY_KEY_H, L"H"},
    {kirr::ALL_KEY_CODE::KEY_KEY_I, L"I"},
    {kirr::ALL_KEY_CODE::KEY_KEY_J, L"J"},
    {kirr::ALL_KEY_CODE::KEY_KEY_K, L"K"},
    {kirr::ALL_KEY_CODE::KEY_KEY_L, L"L"},
    {kirr::ALL_KEY_CODE::KEY_KEY_M, L"M"},
    {kirr::ALL_KEY_CODE::KEY_KEY_N, L"N"},
    {kirr::ALL_KEY_CODE::KEY_KEY_O, L"O"},
    {kirr::ALL_KEY_CODE::KEY_KEY_P, L"P"},
    {kirr::ALL_KEY_CODE::KEY_KEY_Q, L"Q"},
    {kirr::ALL_KEY_CODE::KEY_KEY_R, L"R"},
    {kirr::ALL_KEY_CODE::KEY_KEY_S, L"S"},
    {kirr::ALL_KEY_CODE::KEY_KEY_T, L"T"},
    {kirr::ALL_KEY_CODE::KEY_KEY_U, L"U"},
    {kirr::ALL_KEY_CODE::KEY_KEY_V, L"V"},
    {kirr::ALL_KEY_CODE::KEY_KEY_W, L"W"},
    {kirr::ALL_KEY_CODE::KEY_KEY_X, L"X"},
    {kirr::ALL_KEY_CODE::KEY_KEY_Y, L"Y"},
    {kirr::ALL_KEY_CODE::KEY_KEY_Z, L"Z"},
    {kirr::ALL_KEY_CODE::KEY_LWIN, L"LWin"},
    {kirr::ALL_KEY_CODE::KEY_RWIN, L"RWin"},
    {kirr::ALL_KEY_CODE::KEY_APPS, L"ApplicationsKey"},
    {kirr::ALL_KEY_CODE::KEY_SLEEP, L"Sleep"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD0, L"Numpad0"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD1, L"Numpad1"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD2, L"Numpad2"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD3, L"Numpad3"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD4, L"Numpad4"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD5, L"Numpad5"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD6, L"Numpad6"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD7, L"Numpad7"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD8, L"Numpad8"},
    {kirr::ALL_KEY_CODE::KEY_NUMPAD9, L"Numpad9"},
    {kirr::ALL_KEY_CODE::KEY_MULTIPLY, L"*"},
    {kirr::ALL_KEY_CODE::KEY_ADD, L"+"},
    {kirr::ALL_KEY_CODE::KEY_SEPARATOR, L"Separator"},
    {kirr::ALL_KEY_CODE::KEY_SUBTRACT, L"-"},
    {kirr::ALL_KEY_CODE::KEY_DECIMAL, L"."},
    {kirr::ALL_KEY_CODE::KEY_DIVIDE, L"/"},
    {kirr::ALL_KEY_CODE::KEY_F1, L"F1"},
    {kirr::ALL_KEY_CODE::KEY_F2, L"F2"},
    {kirr::ALL_KEY_CODE::KEY_F3, L"F3"},
    {kirr::ALL_KEY_CODE::KEY_F4, L"F4"},
    {kirr::ALL_KEY_CODE::KEY_F5, L"F5"},
    {kirr::ALL_KEY_CODE::KEY_F6, L"F6"},
    {kirr::ALL_KEY_CODE::KEY_F7, L"F7"},
    {kirr::ALL_KEY_CODE::KEY_F8, L"F8"},
    {kirr::ALL_KEY_CODE::KEY_F9, L"F9"},
    {kirr::ALL_KEY_CODE::KEY_F10, L"F10"},
    {kirr::ALL_KEY_CODE::KEY_F11, L"F11"},
    {kirr::ALL_KEY_CODE::KEY_F12, L"F12"},
    {kirr::ALL_KEY_CODE::KEY_F13, L"F13"},
    {kirr::ALL_KEY_CODE::KEY_F14, L"F14"},
    {kirr::ALL_KEY_CODE::KEY_F15, L"F15"},
    {kirr::ALL_KEY_CODE::KEY_F16, L"F16"},
    {kirr::ALL_KEY_CODE::KEY_F17, L"F17"},
    {kirr::ALL_KEY_CODE::KEY_F18, L"F18"},
    {kirr::ALL_KEY_CODE::KEY_F19, L"F19"},
    {kirr::ALL_KEY_CODE::KEY_F20, L"F20"},
    {kirr::ALL_KEY_CODE::KEY_F21, L"F21"},
    {kirr::ALL_KEY_CODE::KEY_F22, L"F22"},
    {kirr::ALL_KEY_CODE::KEY_F23, L"F23"},
    {kirr::ALL_KEY_CODE::KEY_F24, L"F24"},
    {kirr::ALL_KEY_CODE::KEY_NUMLOCK, L"NumLock"},
    {kirr::ALL_KEY_CODE::KEY_SCROLL, L"ScrollLock"},
    {kirr::ALL_KEY_CODE::KEY_LSHIFT, L"LShift"},
    {kirr::ALL_KEY_CODE::KEY_RSHIFT, L"RShift"},
    {kirr::ALL_KEY_CODE::KEY_LCONTROL, L"LCtrl"},
    {kirr::ALL_KEY_CODE::KEY_RCONTROL, L"RCtrl"},
    {kirr::ALL_KEY_CODE::KEY_LMENU, L"LMenu"},
    {kirr::ALL_KEY_CODE::KEY_RMENU, L"RMenu"},
    {kirr::ALL_KEY_CODE::KEY_OEM_1, L";:"},
    {kirr::ALL_KEY_CODE::KEY_PLUS, L"+"},
    {kirr::ALL_KEY_CODE::KEY_COMMA, L","},
    {kirr::ALL_KEY_CODE::KEY_MINUS, L"-"},
    {kirr::ALL_KEY_CODE::KEY_PERIOD, L"."},
    {kirr::ALL_KEY_CODE::KEY_OEM_2, L"/?"},
    {kirr::ALL_KEY_CODE::KEY_OEM_3, L"`~"},
    {kirr::ALL_KEY_CODE::KEY_OEM_4, L"[{"},
    {kirr::ALL_KEY_CODE::KEY_OEM_5, L"\\|"},
    {kirr::ALL_KEY_CODE::KEY_OEM_6, L"]}"},
    {kirr::ALL_KEY_CODE::KEY_OEM_7, L"'\""},
    {kirr::ALL_KEY_CODE::KEY_OEM_8, L""},
    {kirr::ALL_KEY_CODE::KEY_OEM_AX, L"AX"},
    {kirr::ALL_KEY_CODE::KEY_OEM_102, L"<>"},
    {kirr::ALL_KEY_CODE::KEY_ATTN, L"Attn"},
    {kirr::ALL_KEY_CODE::KEY_CRSEL, L"Crsel"},
    {kirr::ALL_KEY_CODE::KEY_EXSEL, L"Exsel"},
    {kirr::ALL_KEY_CODE::KEY_EREOF, L"ErEof"},
    {kirr::ALL_KEY_CODE::KEY_PLAY, L"Play"},
    {kirr::ALL_KEY_CODE::KEY_ZOOM, L"Zoom"},
    {kirr::ALL_KEY_CODE::KEY_PA1, L"PA1"},
    {kirr::ALL_KEY_CODE::KEY_OEM_CLEAR, L"Clear"},
    {kirr::ALL_KEY_CODE::KEY_SCROLL_UP, L"WheelUp"},
    {kirr::ALL_KEY_CODE::KEY_SCROLL_DOWN, L"WheelDown"},
    {kirr::ALL_KEY_CODE::KEY_LCONTROLLER_UP, L"LStickUp"},
    {kirr::ALL_KEY_CODE::KEY_LCONTROLLER_DOWN, L"LStickDown"},
    {kirr::ALL_KEY_CODE::KEY_LCONTROLLER_RIGHT, L"LStickRight"},
    {kirr::ALL_KEY_CODE::KEY_LCONTROLLER_LEFT, L"LStickLeft"},
    {kirr::ALL_KEY_CODE::KEY_RCONTROLLER_UP, L"RStickUp"},
    {kirr::ALL_KEY_CODE::KEY_RCONTROLLER_DOWN, L"RStickDown"},
    {kirr::ALL_KEY_CODE::KEY_RCONTROLLER_RIGHT, L"RStickRight"},
    {kirr::ALL_KEY_CODE::KEY_RCONTROLLER_LEFT, L"RStickLeft"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_UP, L"CrossUp"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_DOWN, L"CrossDown"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_LEFT, L"CrossLeft"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_RIGHT, L"CrossRight"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_L1, L"L1"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_L2, L"L2"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_R1, L"R1"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_R2, L"R2"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_START, L"Start"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_SELECT, L"Select"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_ROUND, L"Round"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_SQUARE, L"Square"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_X, L"Cross"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_TRIANGLE, L"Triangle"},
    {kirr::ALL_KEY_CODE::KEY_CONTROLLER_LOG, L"Home"},
    {kirr::ALL_KEY_CODE::KEY_KEY_CODES_COUNT, L""}
  }),
  _controllerSelected(false),
  _idxTextures(indie::SkinColorEnum::GOLD),
  _oldStateComp({
    {"Prev", false},
    {"Next", false},
    {"Kb", false},
    {"Ct", false}})
{
  this->_posCamera = kirr::Pos<float>(-200 - 1500, 0, -230);

  // EVENT BOX KEYS
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false);});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return (!this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), false));});
  this->_eventBoxesKey.push_back([&] (const kirr::GlobalEvent & gEvent) {return this->checkEvent(gEvent, kirr::Pos<float>(573, 630, 0), kirr::Pos<float>(704, 675, 0), true);});
  // EVENT BOX FCTS
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("SEBACK", "./Client/Assets/Sounds/select.wav");
    this->_menu.zoomInString(this->getStringMesh("BACK"));
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.removeIntoSoundMapExceptOne("");
    this->_menu.zoomOutString(this->getStringMesh("BACK"));
  });
  this->_eventBoxesFct.push_back([&](){
    this->_menu.addSelectSound("SEBACK", "./Client/Assets/Sounds/select.wav");
    this->_components["WinKeyBinding"]->setVisible(false);
    this->_components["WinControlMode"]->setVisible(false);
    this->_components["WinPopupKey"]->setVisible(false);
    this->_components["Prev"]->setVisible(false);
    this->_components["Next"]->setVisible(false);
    this->pollScope(this->_menu, this->_menu.getCamera(), "Default", this->_menu.getPrevScope());
  });
}

indie::module::Settings::~Settings() {}

bool  indie::module::Settings::checkEvent(kirr::GlobalEvent const& gEvent,
                                      const kirr::Pos<float> & topLeft,
                                      const kirr::Pos<float> & bottomRight,
                                      bool flag) {
  return this->_menu.getKirrlicht().mouseEventInZone(gEvent, topLeft, bottomRight, flag);
}

bool  indie::module::Settings::load()
{
  this->_wordsMesh.clear();
  if (!this->_loadComponents() ||
      !this->_loadButtons() ||
      !this->_loadBindingsFromServer() ||
      !this->_loadTextures() ||
      !this->_loadSkinFromServer() ||
      !this->_loadAudioFromServer())
    return (false);
  this->_oldStateComp["Kb"] = this->_buttonMode[0].second->isPressed();
  this->_oldStateComp["Ct"] = this->_buttonMode[1].second->isPressed();
  return (true);
}

bool indie::module::Settings::loop()
{
  indie::module::ProfileInfos &profileInfos = dynamic_cast<indie::module::Profile*>(this->_menu.getScopes()["Profile"].get())->getProfileInfos();

  this->_components["WinKeyBinding"]->setVisible(true);
  this->_components["WinControlMode"]->setVisible(true);
  this->_components["WinAudioConf"]->setVisible(true);
  this->_components["ScrollMusic"]->setVisible(true);
  this->_components["ScrollSFX"]->setVisible(true);
  this->_components["Prev"]->setVisible(true);
  this->_components["Next"]->setVisible(true);
  this->_components["WinKeyBinding"]->draw();
  this->_components["WinControlMode"]->draw();
  this->_components["WinPopupKey"]->draw();
  this->_components["WinAudioConf"]->draw();
  this->_components["ScrollMusic"]->draw();
  this->_components["ScrollSFX"]->draw();
  this->_components["Prev"]->draw();
  this->_components["Next"]->draw();
  this->_playerMesh->setRotation(kirr::Core::vector3df(this->_playerMesh->getRotation().X, this->_playerMesh->getRotation().Y + 1, this->_playerMesh->getRotation().Z));

  this->_eventChangingKeyBinding(profileInfos);
  this->_setControlType(profileInfos);
  this->_eventChangingSkin();

  this->_oldStateComp["Prev"] = reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Prev"])->isPressed();
  this->_oldStateComp["Next"] = reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Next"])->isPressed();
  this->_oldStateComp["Kb"] = this->_buttonMode[0].second->isPressed();
  this->_oldStateComp["Ct"] = this->_buttonMode[1].second->isPressed();

  this->_menu.setMusicVolume(reinterpret_cast<kirr::Gui::IGUIScrollBar *>(this->_components["ScrollMusic"])->getPos());
  this->_menu.setSFXVolume(reinterpret_cast<kirr::Gui::IGUIScrollBar *>(this->_components["ScrollSFX"])->getPos());
  return (true);
}

std::vector<std::pair<std::string, kirr::Gui::IGUIButton *>>  indie::module::Settings::getButtonList() const
{
  return (this->_buttonList);
}

std::vector<std::pair<std::string, kirr::Gui::IGUIButton *>>  indie::module::Settings::getButtonMode() const
{
  return (this->_buttonMode);
}

std::vector<std::pair<std::string, bwsg::ActionType>>  indie::module::Settings::getButtonNames() const
{
  return (this->_buttonNames);
}

kirr::Scene::IAnimatedMeshSceneNode                           *indie::module::Settings::getPlayerMesh()
{
  return (this->_playerMesh);
}

bool                                                  indie::module::Settings::_loadComponents()
{
  if (!this->_menu.getModuleLoader().getKirrlicht().displayString("SETTINGS", kirr::Pos<float>(-358 - 1500, 250, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(1, 1, 1), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !this->_menu.getModuleLoader().getKirrlicht().displayString("BACK", kirr::Pos<float>(-255 - 1500, -240, 200), kirr::Pos<float>(0, 180, 0), kirr::Core::vector3df(0.6, 0.6, 0.6), this->getWordsMesh(), "./Client/Assets/Textures/Colors/blue.png") ||
      !(this->_env = this->_menu.getModuleLoader().getKirrlicht().getGUIEnvironment()) ||
      !(this->_skin = this->_env->getSkin()) ||
      !(this->_components["WinControlMode"] = this->_env->addWindow(kirr::Core::rect<kirr::s32>(700, 180, 700 + 180, 180 + 120))) ||
      !(this->_components["WinKeyBinding"] = this->_env->addWindow(kirr::Core::rect<kirr::s32>(950, 180, 950 + 250, 180 + 390))) ||
      !(this->_components["WinPopupKey"] = this->_env->addWindow(kirr::Core::rect<kirr::s32>(1280 / 2 - 100, 720 / 2 - 55, 1280 / 2 + 100, 720 / 2 + 55))) ||
      !(this->_components["WinAudioConf"] = this->_env->addWindow(kirr::Core::rect<kirr::s32>(700, 450, 700 + 180, 450 + 120))) ||
      !(this->_components["ScrollMusic"] = this->_env->addScrollBar(true, kirr::Core::rect<kirr::s32>(15, 27, 15 + 150, 27 + 15), this->_components["WinAudioConf"])) ||
      !(this->_components["ScrollSFX"] = this->_env->addScrollBar(true, kirr::Core::rect<kirr::s32>(15, 78, 15 + 150, 78 + 15), this->_components["WinAudioConf"])) ||
      !(this->_components["Prev"] = this->_env->addButton(kirr::Core::rect<kirr::s32>(190, 200, 190 + 50, 200 + 25), 0, -1, L"Prev")) ||
      !(this->_components["Next"] = this->_env->addButton(kirr::Core::rect<kirr::s32>(360, 200, 360 + 50, 200 + 25), 0, -1, L"Next")) ||
      !(this->_playerMesh = this->_menu.getModuleLoader().getKirrlicht().addAnimatedModel(kirr::Pos<float>(-220 - 1500, -11, -200), "./Client/Assets/Objects/Soldier_final.ms3d", "./Client/Assets/Textures/Player/soldier_gold.jpg")) ||
      !this->_menu.getKirrlicht().putText(this->_ebrima[12], L"Music Volume",
                                          kirr::Core::rect<kirr::s32>(15, 47, 15 + 150, 47 + 15),
                                          kirr::Video::SColor(255, 0, 0, 0), false, true, this->_components["WinAudioConf"]) ||
      !this->_menu.getKirrlicht().putText(this->_ebrima[12], L"SFX Volume",
                                          kirr::Core::rect<kirr::s32>(15, 98, 15 + 150, 98 + 15),
                                          kirr::Video::SColor(255, 0, 0, 0), false, true, this->_components["WinAudioConf"]) ||
      !this->_menu.getKirrlicht().putText(this->_ebrima[12], L"Keyboard",
                                          kirr::Core::rect<kirr::s32>(20, 80, 20 + 80, 80 + 30),
                                          kirr::Video::SColor(255, 0, 0, 0), false, true, this->_components["WinControlMode"]) ||
      !this->_menu.getKirrlicht().putText(this->_ebrima[12], L"Controller",
                                          kirr::Core::rect<kirr::s32>(110, 80, 110 + 80, 80 + 30),
                                          kirr::Video::SColor(255, 0, 0, 0), false, true, this->_components["WinControlMode"]) ||
      !this->_menu.getKirrlicht().putText(this->_ebrima[14], L"Press a key to continue",
                                          kirr::Core::rect<kirr::s32>(30, 45, 30 + 180, 45 + 30),
                                          kirr::Video::SColor(255, 0, 0, 0), false, true, this->_components["WinPopupKey"]))
    return (false);

  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinKeyBinding"])->setDrawBackground(true);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinKeyBinding"])->getCloseButton()->setVisible(false);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinControlMode"])->setDrawBackground(true);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinControlMode"])->getCloseButton()->setVisible(false);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinAudioConf"])->setDrawBackground(true);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinAudioConf"])->getCloseButton()->setVisible(false);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinPopupKey"])->setDrawBackground(true);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinPopupKey"])->setDraggable(false);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinPopupKey"])->setDrawTitlebar(false);
  reinterpret_cast<kirr::Gui::IGUIWindow *>(this->_components["WinPopupKey"])->getCloseButton()->setVisible(false);

  reinterpret_cast<kirr::Gui::IGUIScrollBar *>(this->_components["ScrollMusic"])->setPos(this->_menu.getMusicVolume());
  reinterpret_cast<kirr::Gui::IGUIScrollBar *>(this->_components["ScrollSFX"])->setPos(this->_menu.getSFXVolume());

  this->_components["WinKeyBinding"]->setVisible(false);
  this->_components["WinControlMode"]->setVisible(false);
  this->_components["WinPopupKey"]->setVisible(false);
  this->_components["WinAudioConf"]->setVisible(false);
  this->_components["ScrollMusic"]->setVisible(false);
  this->_components["ScrollSFX"]->setVisible(false);
  this->_components["Prev"]->setVisible(false);
  this->_components["Next"]->setVisible(false);

  this->_skin->setFont(this->_ebrima[12]);
  return (true);
}

bool                                                  indie::module::Settings::_loadButtons()
{
  this->_buttonList = {
    {std::make_pair(this->_buttonNames[0].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 50, 25 + 70, 50 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::MOVE_FORWARD]]))},
    {std::make_pair(this->_buttonNames[1].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 85, 25 + 70, 85 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::MOVE_BACK]]))},
    {std::make_pair(this->_buttonNames[2].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 120, 25 + 70, 120 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::MOVE_LEFT]]))},
    {std::make_pair(this->_buttonNames[3].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 155, 25 + 70, 155 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::MOVE_RIGHT]]))},
    {std::make_pair(this->_buttonNames[4].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 190, 25 + 70, 190 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::ACTION1]]))},
    {std::make_pair(this->_buttonNames[5].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 225, 25 + 70, 225 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::ACTION2]]))},
    {std::make_pair(this->_buttonNames[6].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 260, 25 + 70, 260 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::ACTION3]]))},
    {std::make_pair(this->_buttonNames[7].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 295, 25 + 70, 295 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::ACTION4]]))},
    {std::make_pair(this->_buttonNames[8].first, this->_env->addButton(kirr::Core::rect<kirr::s32>(25, 330, 25 + 70, 330 + 20), this->_components["WinKeyBinding"], -1, this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::PAUSE]]))}
  };
  this->_buttonMode = {
    {std::make_pair("Keyboard", this->_env->addButton(kirr::Core::rect<kirr::s32>(27, 35, 27 + 35, 35 + 35), this->_components["WinControlMode"]))},
    {std::make_pair("Controller", this->_env->addButton(kirr::Core::rect<kirr::s32>(118, 35, 118 + 35, 35 + 35), this->_components["WinControlMode"]))}
  };
  this->_buttonMode[0].second->setIsPushButton();
  this->_buttonMode[1].second->setIsPushButton();
  for (size_t i = 0; i < this->_buttonList.size(); i++)
  {
    if (!this->_menu.getKirrlicht().putText(this->_ebrima[12], kirr::Core::stringw(this->_buttonNames[i].first.c_str()).c_str(),
                                            kirr::Core::rect<kirr::s32>(110, 52 + 35 * i, 110 + 200, 52 + 35 * i + 20),
                                            kirr::Video::SColor(255, 0, 0, 0), false, true, this->_components["WinKeyBinding"]))
      return (false);
    this->_buttonList[i].second->setIsPushButton(true);
  }
  return (true);
}

bool                                                  indie::module::Settings::_loadBindingsFromServer()
{
  indie::module::ProfileInfos &profileInfos = dynamic_cast<indie::module::Profile*>(this->_menu.getScopes()["Profile"].get())->getProfileInfos();

  if (profileInfos.getPlayerId() == 1)
  {
    this->_menu.getPlayerOne().get()->getBinding().bindToKeyboard();
    this->_menu.getPlayerTwo().get()->getBinding().bindToController();
    this->_buttonMode[0].second->setPressed();
  }
  else
  {
    this->_profileSettings = this->_menu.getModuleLoader().getNexusAPI().getSettings(profileInfos.getPlayerId());
    if (this->_profileSettings.find("control") != this->_profileSettings.end())
    {
      if (static_cast<indie::game::ControlType>(this->_profileSettings["control"]) == indie::game::ControlType::CONTROLLER)
      {
        this->_menu.getPlayerOne().get()->getBinding().bindToController();
        this->_menu.getPlayerTwo().get()->getBinding().bindToKeyboard();
        this->_buttonMode[1].second->setPressed();
      }
      else
      {
        this->_menu.getPlayerOne().get()->getBinding().bindToKeyboard();
        this->_menu.getPlayerTwo().get()->getBinding().bindToController();
        this->_buttonMode[0].second->setPressed();
      }
    }
    for (auto it = this->_profileSettings.begin(); it != this->_profileSettings.end() &&
                                                   this->_profileSettings["id"] != -1; ++it)
    {
      if (it->second != -1)
      {
        for (size_t i = 0; i < this->_buttonNames.size(); i++)
        {
          if (this->_buttonNames[i].first == this->_namesAliases[it->first])
          {
            this->_menu.getPlayerOne().get()->getBinding().setKey(this->_buttonNames[i].second, static_cast<kirr::ALL_KEY_CODE>(it->second));
            break;
          }
        }
      }
    }
    this->_buttonList[0].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::MOVE_FORWARD]]);
    this->_buttonList[1].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::MOVE_BACK]]);
    this->_buttonList[2].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::MOVE_LEFT]]);
    this->_buttonList[3].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::MOVE_RIGHT]]);
    this->_buttonList[4].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::ACTION1]]);
    this->_buttonList[5].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::ACTION2]]);
    this->_buttonList[6].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::ACTION3]]);
    this->_buttonList[7].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::ACTION4]]);
    this->_buttonList[8].second->setText(this->_keysAliases[this->_menu.getPlayerOne().get()->getBinding().getActionBinding()[bwsg::ActionType::PAUSE]]);
  }
  return (true);
}

bool                                                  indie::module::Settings::_loadTextures()
{
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_gold.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_aqua.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_aqua_all.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_blue.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_blue_all.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_camo.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_dark_green.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_dark_green_red.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_fire.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_green.jpg"));
  this->_playerTextures.push_back(this->_menu.getModuleLoader().getKirrlicht().getTexture("./Client/Assets/Textures/Player/soldier_red.jpg"));
  return (true);
}

bool                                                  indie::module::Settings::_loadSkinFromServer()
{
  indie::module::ProfileInfos &profileInfos = dynamic_cast<indie::module::Profile*>(this->_menu.getScopes()["Profile"].get())->getProfileInfos();

  if (profileInfos.getPlayerId() != 1)
  {
    this->_idxTextures = static_cast<indie::SkinColorEnum>(this->_menu.getModuleLoader().getNexusAPI().getPlayerColor(profileInfos.getPlayerId()));
    this->_playerMesh->setMaterialTexture(0, this->_playerTextures[static_cast<int>(this->_idxTextures)]);
  }
  return (true);
}

bool                                                  indie::module::Settings::_loadAudioFromServer()
{
  indie::module::ProfileInfos &profileInfos = dynamic_cast<indie::module::Profile*>(this->_menu.getScopes()["Profile"].get())->getProfileInfos();

  if (profileInfos.getPlayerId() != 1)
  {
    this->_menu.setMusicVolume(this->_menu.getModuleLoader().getNexusAPI().getPlayerMusic(profileInfos.getPlayerId()));
    this->_menu.setSFXVolume(this->_menu.getModuleLoader().getNexusAPI().getPlayerSFX(profileInfos.getPlayerId()));

    reinterpret_cast<kirr::Gui::IGUIScrollBar *>(this->_components["ScrollMusic"])->setPos(this->_menu.getMusicVolume());
    reinterpret_cast<kirr::Gui::IGUIScrollBar *>(this->_components["ScrollSFX"])->setPos(this->_menu.getSFXVolume());
  }
  return (true);
}

void                                                  indie::module::Settings::_eventChangingKeyBinding(indie::module::ProfileInfos const& profileInfos)
{
  kirr::GlobalEvent mevent = this->_menu.getModuleLoader().getKirrlicht().getEventReceiver().getEvent();

  for (size_t i = 0; i < this->_buttonList.size(); i++)
  {
    if (this->_buttonList[i].second->isPressed() && !this->_components["WinPopupKey"]->isVisible())
    {
      this->_components["WinPopupKey"]->setVisible(true);
      this->_components["WinPopupKey"]->draw();
      break;
    }
    else if (this->_buttonList[i].second->isPressed() && this->_components["WinPopupKey"]->isVisible())
    {
      while (this->_buttonList[i].second->isPressed())
      {
        if (!this->_menu.getModuleLoader().getKirrlicht().getDevice()->run())
        {
          this->_menu.stop();
          this->_menu.clear();
          continue;
        }
        mevent = this->_menu.getModuleLoader().getKirrlicht().getEventReceiver().getEvent();
        for (auto it = mevent.pressTab.begin(); it != mevent.pressTab.end(); ++it)
        {
          if (it->second)
          {
            this->_menu.getPlayerOne().get()->getBinding().setKey(this->_buttonNames[i].second, it->first);
            if (profileInfos.getPlayerId() != 1)
              this->_buttonToAPI[this->_buttonList[i].first](profileInfos.getPlayerId(), it->first);
            this->_buttonList[i].second->setText(this->_keysAliases[it->first]);
            this->_buttonList[i].second->setPressed(false);
            this->_components["WinPopupKey"]->setVisible(false);
            break;
          }
        }
      }
    }
  }
}

void                                                  indie::module::Settings::_setControlType(indie::module::ProfileInfos const& profileInfos)
{
  if (this->_oldStateComp["Kb"] != this->_buttonMode[0].second->isPressed())
  {
    if (this->_buttonMode[0].second->isPressed())
    {
      this->_menu.getPlayerOne().get()->getBinding().bindToKeyboard();
      this->_buttonMode[1].second->setPressed(false);
      if (profileInfos.getPlayerId() != 1)
        this->_buttonToAPI["Control"](profileInfos.getPlayerId(), static_cast<int>(indie::game::ControlType::KEYBOARD));
      this->_menu.getPlayerTwo().get()->getBinding().bindToController();
    }
    else
    {
      this->_menu.getPlayerOne().get()->getBinding().bindToController();
      this->_buttonMode[0].second->setPressed(false);
      this->_buttonMode[1].second->setPressed();
      if (profileInfos.getPlayerId() != 1)
        this->_buttonToAPI["Control"](profileInfos.getPlayerId(), static_cast<int>(indie::game::ControlType::CONTROLLER));
      this->_menu.getPlayerTwo().get()->getBinding().bindToKeyboard();
    }
  }
  else if (this->_oldStateComp["Ct"] != this->_buttonMode[1].second->isPressed())
  {
    if (this->_buttonMode[1].second->isPressed())
    {
      this->_menu.getPlayerOne().get()->getBinding().bindToController();
      this->_buttonMode[0].second->setPressed(false);
      if (profileInfos.getPlayerId() != 1)
        this->_buttonToAPI["Control"](profileInfos.getPlayerId(), static_cast<int>(indie::game::ControlType::CONTROLLER));
      this->_menu.getPlayerTwo().get()->getBinding().bindToKeyboard();
    }
    else
    {
      this->_menu.getPlayerTwo().get()->getBinding().bindToKeyboard();
      this->_buttonMode[0].second->setPressed();
      this->_buttonMode[1].second->setPressed(false);
      if (profileInfos.getPlayerId() != 1)
        this->_buttonToAPI["Control"](profileInfos.getPlayerId(), static_cast<int>(indie::game::ControlType::KEYBOARD));
          this->_menu.getPlayerOne().get()->getBinding().bindToController();
    }
  }
}

void                                                  indie::module::Settings::_eventChangingSkin()
{
  indie::module::ProfileInfos &profileInfos = dynamic_cast<indie::module::Profile*>(this->_menu.getScopes()["Profile"].get())->getProfileInfos();

  if (!this->_oldStateComp["Prev"] && reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Prev"])->isPressed())
    {
      if (!static_cast<int>(this->_idxTextures))
        this->_idxTextures = static_cast<indie::SkinColorEnum>(this->_playerTextures.size() - 1);
      else
        this->_idxTextures = static_cast<indie::SkinColorEnum>(static_cast<int>(this->_idxTextures) - 1);
      if (profileInfos.getPlayerId() != 1)
        this->_menu.getModuleLoader().getNexusAPI().setPlayerColor(profileInfos.getPlayerId(), static_cast<int>(this->_idxTextures));
      this->_playerMesh->setMaterialTexture(0, this->_playerTextures[static_cast<int>(this->_idxTextures)]);
    }
  if (!this->_oldStateComp["Next"] && reinterpret_cast<kirr::Gui::IGUIButton *>(this->_components["Next"])->isPressed())
    {
      this->_idxTextures = static_cast<indie::SkinColorEnum>(static_cast<int>(this->_idxTextures) + 1);
      if (static_cast<size_t>(this->_idxTextures) == this->_playerTextures.size())
        this->_idxTextures = static_cast<indie::SkinColorEnum>(0);
      if (profileInfos.getPlayerId() != 1)
        this->_menu.getModuleLoader().getNexusAPI().setPlayerColor(profileInfos.getPlayerId(), static_cast<int>(this->_idxTextures));
      this->_playerMesh->setMaterialTexture(0, this->_playerTextures[static_cast<int>(this->_idxTextures)]);
    }
}
