//
// Splashscreen.cpp for  in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Splashscreen/
//
// Made by Maxime Cauvin
// Login   <maxime.cauvin@epitech.eu>
//
// Started on  Wed May 24 17:34:22 2017 Maxime Cauvin
// Last update Sat Jun 17 17:57:23 2017 Maxime Cauvin
//

#include "Splashscreen.hpp"

indie::module::Splashscreen::Splashscreen(indie::module::ModuleLoader & ml) :
  AModule(ml),
  _state(true),
  _currentStep("Step 1")
{
  this->_scopes = {};
}

indie::module::Splashscreen::~Splashscreen() {}

bool            indie::module::Splashscreen::pollEvents(kirr::GlobalEvent const& mevent)
{
  for (auto it = mevent.pressTab.begin(); it != mevent.pressTab.end(); ++it)
  {
    if (it->second)
      this->_state = false;
  }
  return (true);
}

bool            indie::module::Splashscreen::_animationStep1()
{
  static double rot = 0.5f;

  if (this->_currentStep == "Step 1")
  {
    this->_sfx->setPlaybackSpeed(this->_sfx->getPlaybackSpeed() + 0.002f);
    this->_meshs["Logo"]->setRotation(kirr::Core::vector3df(this->_meshs["Logo"]->getRotation().X, this->_meshs["Logo"]->getRotation().Y, this->_meshs["Logo"]->getRotation().Z + rot));
    rot += 0.05f;
    if (rot >= 15.0f)
      this->_currentStep = "Step 2";
  }
  return (true);
}

bool            indie::module::Splashscreen::_animationStep2()
{
  if (this->_currentStep == "Step 2")
  {
    this->_meshs["Logo"]->setRotation(kirr::Core::vector3df(this->_meshs["Logo"]->getRotation().X, this->_meshs["Logo"]->getRotation().Y, this->_meshs["Logo"]->getRotation().Z + 15));
    this->_meshs["Logo"]->setPosition(kirr::Core::vector3df(this->_meshs["Logo"]->getAbsolutePosition().X, this->_meshs["Logo"]->getAbsolutePosition().Y, this->_meshs["Logo"]->getAbsolutePosition().Z + 0.10f));
    if (this->_meshs["Logo"]->getAbsolutePosition().Z > 12.0f)
      this->_currentStep = "Step 3";
  }
  return (true);
}

bool            indie::module::Splashscreen::_animationStep3()
{
  static double rot = 15.0f;

  if (this->_currentStep == "Step 3")
  {
    this->_meshs["N"]->setVisible(true);
    this->_meshs["E"]->setVisible(true);
    this->_meshs["U"]->setVisible(true);
    this->_meshs["S"]->setVisible(true);
    this->_meshs["Logo"]->setRotation(kirr::Core::vector3df(this->_meshs["Logo"]->getRotation().X, this->_meshs["Logo"]->getRotation().Y, this->_meshs["Logo"]->getRotation().Z - rot));
    this->_meshs["Logo"]->setPosition(kirr::Core::vector3df(this->_meshs["Logo"]->getAbsolutePosition().X, this->_meshs["Logo"]->getAbsolutePosition().Y, this->_meshs["Logo"]->getAbsolutePosition().Z - 0.05f));
    this->_kirrlicht.moveObjectToPos(this->_meshs["N"], kirr::Core::vector3df(4.3, -0.7, 1.6), "N", 216);
    this->_kirrlicht.moveObjectToPos(this->_meshs["E"], kirr::Core::vector3df(2.5, -0.7, 1.6), "E", 216);
    this->_kirrlicht.moveObjectToPos(this->_meshs["U"], kirr::Core::vector3df(-1.3, -0.7, 1.6), "U", 216);
    this->_kirrlicht.moveObjectToPos(this->_meshs["S"], kirr::Core::vector3df(-2.8, -0.7, 1.6), "S", 216);
    this->_sfx->setPlaybackSpeed(this->_sfx->getPlaybackSpeed() - 0.006f);
    rot -= 0.0695f;
    if (rot <= 0.0f)
    {
      this->_sfx->setIsPaused(true);
      this->_nexusSample->setIsPaused(false);
      this->_currentStep = "Step 4";
    }
  }
  return (true);
}

bool            indie::module::Splashscreen::_animationStep4()
{
  if (this->_currentStep == "Step 4")
  {
    this->_particleSystem->setVisible(true);
    this->_camera->setPosition(kirr::Core::vector3df(this->_camera->getPosition().X, this->_camera->getPosition().Y, this->_camera->getPosition().Z - 0.0475f));
    if (this->_camera->getPosition().Z <= 2.5f)
      this->_meshs["Logo"]->setVisible(false);
    if (this->_camera->getPosition().Z <= 0.0f)
      this->_currentStep = "Step 5";
  }
  return (true);
}

bool            indie::module::Splashscreen::makeAnimation()
{
  if (!this->_animationStep1() ||
      !this->_animationStep2() ||
      !this->_animationStep3() ||
      !this->_animationStep4())
    return (false);
  return (true);
}

bool            indie::module::Splashscreen::start()
{
  this->_sfx->setIsPaused(false);
  while (this->_state)
  {
    kirr::GlobalEvent mevent = this->_kirrlicht.getEventReceiver().getEvent();
    if (!this->_kirrlicht.getDevice()->run())
    {
      this->stop();
      this->clear();
      continue;
    }
    this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(255, 0, 0, 0));
    this->_kirrlicht.getSceneManager()->drawAll();
    this->makeAnimation();
    this->_kirrlicht.getDriver()->endScene();
    this->pollEvents(mevent);
    if (this->_currentStep == "Step 5")
      break;
  }
  this->_sfx->stop();
  this->_nexusSample->stop();
  this->_moduleLoader.switcher("Intro");
  return (true);
}

bool            indie::module::Splashscreen::load()
{
  if (!(this->_sfx = this->_kirrlicht.add2dSound("./Client/Assets/Sounds/spin.wav", true)) ||
      !(this->_nexusSample = this->_kirrlicht.add2dSound("./Client/Assets/Sounds/nexus_sample.wav", false)) ||
      !(this->_camera = this->_kirrlicht.getSceneManager()->addCameraSceneNode(0, kirr::vector3df(0,0,0), kirr::vector3df(0,0,0))) ||
      !(this->_particleSystem = this->_kirrlicht.addParticleSystem("./Client/Assets/Textures/Sprites/smoke.bmp", kirr::vector3df(-1.5f, -1.5f, 2.0f),
                                                                 kirr::vector3df(3, 3, 3))) ||
      !this->_kirrlicht.addParticleEmitter(this->_particleSystem, 10, kirr::vector3df(0, 0, 0), kirr::vector3df(1, 1, 0),
                                           kirr::vector3df(300, 350, 0), kirr::Core::aabbox3d<kirr::f32>(-1, 0, -1, 2.2f, 1, 1)) ||
      !(this->_meshs["Logo"] = this->_kirrlicht.addModel({0, 0, 0}, "./Client/Assets/Objects/Splashscreen/Logo.obj", "")) ||
      !(this->_meshs["N"] = this->_kirrlicht.addModel({12.75f, 9.2f, 1.6f}, "./Client/Assets/Objects/Splashscreen/N.obj", "")) ||
      !(this->_meshs["E"] = this->_kirrlicht.addModel({7.25f, 9.2f, 1.6f}, "./Client/Assets/Objects/Splashscreen/E.obj", "")) ||
      !(this->_meshs["U"] = this->_kirrlicht.addModel({-7.25f, 9.2f, 1.6f}, "./Client/Assets/Objects/Splashscreen/U.obj", "")) ||
      !(this->_meshs["S"] = this->_kirrlicht.addModel({-12.75f, 9.2f, 1.6f}, "./Client/Assets/Objects/Splashscreen/S.obj", "")))
    return (false);

  this->_nexusSample->setVolume(0.5f);
  this->_camera->setPosition(kirr::vector3df(0, 0, 15));
  this->_camera->setTarget(kirr::vector3df(0, 0, 0));
  this->_meshs["N"]->setVisible(false);
  this->_meshs["E"]->setVisible(false);
  this->_meshs["U"]->setVisible(false);
  this->_meshs["S"]->setVisible(false);
  this->_particleSystem->setVisible(false);
  this->_kirrlicht.getEventReceiver().resetEvent();
  return (true);
}

bool            indie::module::Splashscreen::clear()
{
  this->_kirrlicht.getSceneManager()->clear();
  return (true);
}

bool            indie::module::Splashscreen::stop()
{
  this->_state = false;
  return (true);
}
