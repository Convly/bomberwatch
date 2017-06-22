//
// GameClient.cpp for GameClient in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/GameClient/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon May  8 19:25:39 2017 jsx
// Last update Sun Jun 18 20:27:38 2017 Maxime Cauvin
//

#include "GameClient.hpp"
#include "StructServer.hpp"
#include "Profile.hpp"

indie::module::GameClient::GameClient(indie::module::ModuleLoader & ml)
:
  AModule(ml),
  _dedicated(nullptr),
  _gameInfos(*this, this->_kirrlicht),
  _playerOne(std::make_shared<indie::game::Player>(*this, true, indie::game::ControlType::KEYBOARD)),
  _playerTwo(std::make_shared<indie::game::Player>(*this, false, indie::game::ControlType::CONTROLLER))
{
  this->_scopes = {};
}


indie::module::GameClient::~GameClient()
{
}

bool            indie::module::GameClient::start()
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
    this->_gameInfos.popExplosions();
    this->toggleSkybox(mevent.pressTab[kirr::ALL_KEY_CODE::KEY_F10]);
    if (this->_playerOne->getBinding().getControlType() == indie::game::ControlType::KEYBOARD)
      this->changeFpsMode0(mevent.pressTab[kirr::ALL_KEY_CODE::KEY_F9]);
    else
      this->changeFpsMode0(mevent.pressTab[kirr::ALL_KEY_CODE::KEY_CONTROLLER_SELECT]);
    if (this->_playerTwo->getBinding().getControlType() == indie::game::ControlType::KEYBOARD)
      this->changeFpsMode1(mevent.pressTab[kirr::ALL_KEY_CODE::KEY_F9]);
    else
      this->changeFpsMode1(mevent.pressTab[kirr::ALL_KEY_CODE::KEY_CONTROLLER_SELECT]);
    this->sendInfo();
    this->_gameInfos.loadObjects();
    this->updatePlayers(mevent);
    if (this->_kirrlicht.getDevice()->isWindowActive()){
      this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(255, 200, 200, 200));
      this->_kirrlicht.getSceneManager()->setActiveCamera(this->_playerOne->getCamera());
      if (this->_playerTwo->getState()){
        this->_kirrlicht.getDriver()->setViewPort(irr::core::rect<irr::s32>(0, 0, this->_kirrlicht.getScreenSize().x, this->_kirrlicht.getScreenSize().y / 2));
        this->_kirrlicht.getSceneManager()->drawAll();
        this->_kirrlicht.getSceneManager()->setActiveCamera(this->_playerTwo->getCamera());
        this->_kirrlicht.getDriver()->setViewPort(irr::core::rect<irr::s32>(0, this->_kirrlicht.getScreenSize().y / 2, this->_kirrlicht.getScreenSize().x, this->_kirrlicht.getScreenSize().y));
      }
      this->_kirrlicht.getSceneManager()->drawAll();
      this->_kirrlicht.adjustCursor();
      this->_kirrlicht.getDriver()->endScene();
    }
    else
      this->_kirrlicht.getDevice()->yield();
    if (this->tryEscapeGame(mevent.pressTab[kirr::ALL_KEY_CODE::KEY_ESCAPE])) {
      std::exit(0);
      return (true);
    }
  }
  return (true);
}

void                                indie::module::GameClient::changeFpsMode0(bool const key){
  static bool                       prevKey = false;
  float                             tmp;

  if (!key && prevKey){
    tmp = this->_playerOne->getRender() - 10;
    if (tmp < -30)
      tmp = 1.5;
    this->_playerOne->setRender(tmp);
  }
  prevKey = key;
}

void                                indie::module::GameClient::changeFpsMode1(bool const key){
  static bool                       prevKey = false;
  float                             tmp;

  if (!key && prevKey){
    tmp = this->_playerTwo->getRender() - 10;
    if (tmp < -30)
      tmp = 1.5;
    this->_playerTwo->setRender(tmp);
  }
  prevKey = key;
}

bool                                indie::module::GameClient::tryEscapeGame(bool const key){
  static bool                       prevKey = false;
  bool                              pressed;

  pressed = !key && prevKey;
  prevKey = key;
  return pressed;
}

void                                indie::module::GameClient::toggleSkybox(bool const key){
  static bool                       state = true;
  static bool                       prevKey = false;

  if (!key && prevKey){
    state = !state;
    if (state){
      this->_skybox->setVisible(true);
      this->_map->setVisible(true);
    }
    else{
      this->_skybox->setVisible(false);
      this->_map->setVisible(false);
    }
  }
  prevKey = key;
}

bool            indie::module::GameClient::createLocalServer() {
  this->_gameInfos.getServerInfos().setIpAddr("127.0.0.1");
  this->_gameInfos.getServerInfos().setPort(7171);
  this->_dedicated = std::make_shared<std::thread>([&](void*){
    try {
      bwsg::IndieDedicated dedicated(7171);
      dedicated.getReferee().core();
    } catch (...) {
      return nullptr;
    }
    std::cout << "[BW - IndieDedicated] Halt." << std::endl;

    return nullptr;
  }, nullptr);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  return true;
}

bool         indie::module::GameClient::load()
{
  kirr::Camera* camera1;
  kirr::Camera* camera2;

  if (!(this->_bgMusic = this->_kirrlicht.add2dSound("./Client/Assets/Sounds/music_game1.wav", true)))
    return (false);
  this->_bgMusic->setVolume(dynamic_cast<indie::module::Menu *>(this->getModuleLoader().getModules()["Menu"].get())->getMusicVolume() / 100.0f);

  if (!(camera1 = this->_kirrlicht.getSceneManager()->addCameraSceneNode()))
    return (false);
  this->_map = this->_kirrlicht.addModel(kirr::Pos<float>(), "./Client/Assets/Objects/map.obj", "./Client/Assets/Textures/Colors/red.jpg");
  this->_map->setScale(kirr::vector3df(41, 41, 41));
  this->_map->setPosition(kirr::vector3df(0, 4, 0));
  this->_playerOne.get()->setCamera(camera1);
  this->_playerOne.get()->getCamera()->setPosition(specPos);
  this->_playerOne.get()->getCamera()->setTarget(specTarget);
  this->_kirrlicht.getSceneManager()->setActiveCamera(camera1);
  if (this->_playerTwo->getState()){
    this->_kirrlicht.getDriver()->setViewPort(irr::core::rect<irr::s32>(0, 0, this->_kirrlicht.getScreenSize().x, this->_kirrlicht.getScreenSize().y / 2));
    this->_kirrlicht.getSceneManager()->drawAll();
    if (!(camera2 = this->_kirrlicht.getSceneManager()->addCameraSceneNode()))
      return (false);
    this->_playerTwo.get()->setCamera(camera2);
    this->_playerTwo.get()->getCamera()->setPosition(specPos);
    this->_playerTwo.get()->getCamera()->setTarget(specTarget);
    this->_kirrlicht.getSceneManager()->setActiveCamera(camera2);
    this->_kirrlicht.getDriver()->setViewPort(irr::core::rect<irr::s32>(0, this->_kirrlicht.getScreenSize().y / 2, this->_kirrlicht.getScreenSize().x, this->_kirrlicht.getScreenSize().y));
  }
  this->_kirrlicht.getSceneManager()->drawAll();

  /*
  * Create a private server for solo mode
  */
  if (!(this->_gameInfos.getServerInfos().isMultiplayer()) && !(this->createLocalServer()))
    return false;

  /*
  * Attribute a PlayerID for each of the connected players
  */
  int pid = this->getProfileInfos().getPlayerId();
  this->_playerOne.get()->setId(pid);
  this->_playerTwo.get()->setId(pid + 1);

  /*
  * Try to create a connection to the server
  */
  this->_gameInfos.getServerInfos().connect();

  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  end = std::chrono::system_clock::now();
  while (std::chrono::duration_cast<std::chrono::seconds>(end-start).count() < 5 && !this->_gameInfos.getIsConnect())
    end = std::chrono::system_clock::now();
  if (!this->_gameInfos.getIsConnect())
    return false;

  /*
  *   Register player One (and player two if splitted screen is activated)
  */
  this->_gameInfos.getServerInfos().getServer().get()->getClientGame().commandWrite({this->_playerOne.get()->getId(), 2, 0, {}});
  if (this->_playerTwo->getState())
    this->_gameInfos.getServerInfos().getServer().get()->getClientGame().commandWrite({this->_playerTwo.get()->getId(), 2, 0, {}});

  /*
  * Get textures and kirrlicht stuff
  */
  this->_state = true;
  this->_kirrlicht.getCursor()->setVisible(false);
  this->_kirrlicht.centerCursor();
  this->_skybox = this->_kirrlicht.getSceneManager()->addSkyBoxSceneNode(
    this->_kirrlicht.getTexture("./Client/Assets/Textures/Skyboxes/sky_up.png"),
    this->_kirrlicht.getTexture("./Client/Assets/Textures/Skyboxes/sky_down.png"),
    this->_kirrlicht.getTexture("./Client/Assets/Textures/Skyboxes/sky_left.png"),
    this->_kirrlicht.getTexture("./Client/Assets/Textures/Skyboxes/sky_right.png"),
    this->_kirrlicht.getTexture("./Client/Assets/Textures/Skyboxes/sky_front.png"),
    this->_kirrlicht.getTexture("./Client/Assets/Textures/Skyboxes/sky_back.png")
  );
  return (true);
}

bool            indie::module::GameClient::clear()
{
  this->_kirrlicht.getCursor()->setVisible(true);
  if (this->_dedicated) {
    this->getGameInfos().getServerInfos().getServer().get()->getClientGame().commandWrite({
      -1, static_cast<short>(bwsg::CommandType::AS), 0, {1}
    });
    this->_dedicated.get()->join();
  }
  this->_dedicated.reset();
  this->_kirrlicht.getSceneManager()->clear();
  this->_playerOne->setObjectBinded(nullptr);
  this->_gameInfos.getObjects().clear();
  return (true);
}

bool            indie::module::GameClient::stop()
{
  this->_state = false;
  return (true);
}

void                  indie::module::GameClient::updatePlayers(kirr::GlobalEvent& globalEvent){
  kirr::Pos<float>    p1 = globalEvent.getRCursorPosition();
  kirr::Pos<float>    p2 = p1;

  if (this->_playerOne.get()->getBinding().getControlType() == indie::game::ControlType::CONTROLLER)
    p1 = globalEvent.getRJoystickPosition2();
  if (this->_playerOne.get()->getObjectBinded() != nullptr){
    this->_playerOne.get()->updateRotationPlayer(p1);
    this->_playerOne.get()->updateCamera();
    this->_playerOne.get()->updateActions(globalEvent);
  }
  if (this->_playerTwo.get()->getState() && this->_playerTwo.get()->getObjectBinded() != nullptr){
    if (this->_playerTwo.get()->getBinding().getControlType() == indie::game::ControlType::CONTROLLER)
      p2 = globalEvent.getRJoystickPosition2();
    this->_playerTwo.get()->updateRotationPlayer(p2);
    this->_playerTwo.get()->updateCamera();
    this->_playerTwo.get()->updateActions(globalEvent);
  }
}

void                  indie::module::GameClient::sendInfo(){
  this->_playerOne.get()->sendInfo();
  if (this->_playerTwo.get()->getState())
    this->_playerTwo.get()->sendInfo();
}

indie::module::ProfileInfos&    indie::module::GameClient::getProfileInfos() {
  return dynamic_cast<indie::module::Profile *>(dynamic_cast<indie::module::Menu *>(this->getModuleLoader().getModules()["Menu"].get())->getScopes()["Profile"].get())->getProfileInfos();
}
