//
// ModuleLoader.cpp for ModuleLoader in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/ModuleLoader/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:38:05 2017 jsx
// Last update Sun Jun 18 02:48:33 2017 Maxime Cauvin
//

#include "ModuleLoader.hpp"
#include "Splashscreen.hpp"
#include "Intro.hpp"
#include "GameClient.hpp"
#include "Menu.hpp"
#include "Connection.hpp"
#include "Indie.hpp"

indie::module::ModuleLoader::ModuleLoader(indie::core::Indie& indie, const std::string & moduleName, utils::APIClient & nexusAPI)
:
  _indie(indie),
  _status(true),
  _nexusAPI(nexusAPI),
  _modules({
    {"Splashscreen", std::make_shared<indie::module::Splashscreen>(*this)},
    {"Intro", std::make_shared<indie::module::Intro>(*this)},
    {"Menu", std::make_shared<indie::module::Menu>(*this)},
    {"GameClient", std::make_shared<indie::module::GameClient>(*this)},
    {"Connection", std::make_shared<indie::module::Connection>(*this)}
  }),
  _current(this->_modules[moduleName])
{
  if (this->_current.get() == nullptr) {
    throw indie::Error("Invalid module constructor for module loader");
  }
}


indie::module::ModuleLoader::~ModuleLoader()
{
  this->_kirrlicht.drop();
  // this->_progressBar->drop();
}

////////////////////////////////////
//_____________TOOLS _____________//
////////////////////////////////////

bool    indie::module::ModuleLoader::entryPoint()
{
  if (!this->_current.get())
    return (false);
  bool ret = (this->_kirrlicht.start("Bomberwatch", kirr::Pos<int>(1280, 720))
          && (this->_progressBar = new ProgressBar(this->_kirrlicht.getGUIEnvironment(), kirr::Core::rect<kirr::s32>(80, 650, 1280 - 80, 650 + 30)))
          && this->_progressBar->addBorder(2, kirr::Video::SColor(255, 255, 255, 255))
          && this->_progressBar->setColors(kirr::Video::SColor(255, 0, 255, 0), kirr::Video::SColor(255, 0, 0, 0))
          && this->loadFonts()
          && this->loadMeshs()
          && this->loadTextures()
          && this->_current.get()->load()
          && this->_current.get()->start());
  return this->_status && ret;
}

bool    indie::module::ModuleLoader::moduleExist(const std::string & moduleName) {
  return this->_modules.find(moduleName) != this->_modules.end() && this->_modules[moduleName].get() != nullptr;
}

bool    indie::module::ModuleLoader::isAvailable(const std::string & moduleName) {
  return this->moduleExist(moduleName) && this->_modules[moduleName].get()->getAccess();
}

bool    indie::module::ModuleLoader::switcher(const std::string & moduleName) {
  if (moduleName == "EXIT_SESSION") {
    this->setStatus(true);
    return true;
  }
  if (!(this->isAvailable(moduleName))) {
    std::cerr << "\"" << moduleName << "\" is not a valid module name and/or is not loaded in the module loader"<< std::endl;
    return false;
  } else if (this->_modules[moduleName].get() == this->_current.get()) {
    std::cerr << "\"" << moduleName << "\" is already the current module loaded, take a peeck at the indie::module::moduleLoader::reload method"<< std::endl;
    return false;
  }

  auto target = this->_modules[moduleName];
  if (this->_current.get()->stop() && this->_current.get()->clear()) {
    if (target.get()->load()) {
      this->_current = target;
      this->_current.get()->start();
    } else {
      target.get()->clear();
      this->_current.get()->load();
      this->_current.get()->start();
    }
  } else {
    throw indie::Error("Can't stenchon the melanchon");
  }
  return true;
}

bool   indie::module::ModuleLoader::reload() {
  return this->_current.get() && this->_current.get()->reset();
}

////////////////////////////////////
//_____________GETTERS____________//
////////////////////////////////////

bool indie::module::ModuleLoader::getStatus() const {
  return this->_status;
}

void indie::module::ModuleLoader::setStatus(bool status) {
  this->_status = status;
}

std::unordered_map<std::string, std::shared_ptr<indie::module::IModule>> &indie::module::ModuleLoader::getModules() {
  return this->_modules;
}

std::shared_ptr<indie::module::IModule>  indie::module::ModuleLoader::getCurrent() const {
  return this->_current;
}

std::unordered_map<int, kirr::Gui::IGUIFont *> &indie::module::ModuleLoader::getFontEbrima() {
  return (this->_ebrima);
}

kirr::Kirrlicht & indie::module::ModuleLoader::getKirrlicht() {
  return this->_kirrlicht;
}

utils::APIClient &      indie::module::ModuleLoader::getNexusAPI() {
  return this->_nexusAPI;
}

indie::core::Indie&     indie::module::ModuleLoader::getIndie() {
  return this->_indie;
}

const indie::core::Indie&     indie::module::ModuleLoader::getIndie() const {
  return this->_indie;
}

////////////////////////////////////
//_____________LOADERS____________//
////////////////////////////////////

bool                    indie::module::ModuleLoader::loadMeshs()
{
  this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(0, 0, 0, 0));
  this->_progressBar->setProgress(33);
  this->_kirrlicht.putText(this->_ebrima[48], L"Loading...",
                           kirr::Core::rect<kirr::s32>(1280 / 2 - 80, 720 / 2 - 48, 1280, 720))->draw();
  this->_kirrlicht.putText(this->_ebrima[32], L"3D Alphabet",
                         kirr::Core::rect<kirr::s32>(80, 590, 1280 - 80, 590 + 45))->draw();
  this->_progressBar->draw();
  this->_kirrlicht.getDriver()->endScene();

  std::vector<std::string>  allMesh({
      "./Client/Assets/Objects/Soldier_final.ms3d",
      "./Client/Assets/Objects/PU_Amount.obj",
      "./Client/Assets/Objects/PU_Power.obj",
      "./Client/Assets/Objects/PU_Penetration.obj",
      "./Client/Assets/Objects/PU_Ghost.obj",
      "./Client/Assets/Objects/map.obj",
      "./Client/Assets/Objects/bomb.3DS",
      "./Client/Assets/Objects/ND_Cube.obj",
      "./Client/Assets/Objects/D_Cube.obj",
      "./Client/Assets/Objects/Splashscreen/Logo.obj",
      "./Client/Assets/Objects/Splashscreen/N.obj",
      "./Client/Assets/Objects/Splashscreen/E.obj",
      "./Client/Assets/Objects/Splashscreen/U.obj",
      "./Client/Assets/Objects/Splashscreen/S.obj"});

  if (!this->_kirrlicht.loadAlphabet("./Client/Assets/Objects/AlphaNumeric/"))
    return (false);
  this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(0, 0, 0, 0));
  this->_progressBar->setProgress(this->_progressBar->getProgress() + ((66 - 33) / (static_cast<double>(36.0f + allMesh.size()))) * 36);
  this->_kirrlicht.putText(this->_ebrima[48], L"Loading...",
                           kirr::Core::rect<kirr::s32>(1280 / 2 - 80, 720 / 2 - 48, 1280, 720))->draw();
  this->_kirrlicht.putText(this->_ebrima[32], L"3D Alphabet",
                         kirr::Core::rect<kirr::s32>(80, 590, 1280 - 80, 590 + 45))->draw();
  this->_progressBar->draw();
  this->_kirrlicht.getDriver()->endScene();
  for (size_t i = 0; i < allMesh.size(); i++)
    {
      this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(0, 0, 0, 0));
      this->_progressBar->setProgress(this->_progressBar->getProgress() + ((66 - 33) / (static_cast<double>(36.0f + allMesh.size()))));
      this->_kirrlicht.putText(this->_ebrima[48], L"Loading...",
                               kirr::Core::rect<kirr::s32>(1280 / 2 - 80, 720 / 2 - 48, 1280, 720))->draw();
      this->_kirrlicht.putText(this->_ebrima[32], utils::getWStrFromStr(allMesh.at(i)).c_str(),
                               kirr::Core::rect<kirr::s32>(80, 590, 1280 - 80, 590 + 45))->draw();
      this->_progressBar->draw();
      this->_kirrlicht.getDriver()->endScene();
      if (!this->_kirrlicht.loadStaticMesh(allMesh.at(i)))
        {
          std::cerr << "Error: Missing Mesh: " << allMesh.at(i) << '\n';
          return (false);
        }
    }
  return (true);
}

bool                    indie::module::ModuleLoader::loadTextures()
{
  this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(0, 0, 0, 0));
  this->_progressBar->setProgress(66);
  this->_kirrlicht.putText(this->_ebrima[48], L"Loading...",
                           kirr::Core::rect<kirr::s32>(1280 / 2 - 80, 720 / 2 - 48, 1280, 720))->draw();
  this->_progressBar->draw();
  this->_kirrlicht.getDriver()->endScene();

  std::vector<std::string>  allTexture({
    "./Client/Assets/Textures/Player/soldier_gold.jpg",
    "./Client/Assets/Textures/Player/soldier_aqua.jpg",
    "./Client/Assets/Textures/Player/soldier_aqua_all.jpg",
    "./Client/Assets/Textures/Player/soldier_blue.jpg",
    "./Client/Assets/Textures/Player/soldier_blue_all.jpg",
    "./Client/Assets/Textures/Player/soldier_camo.jpg",
    "./Client/Assets/Textures/Player/soldier_dark_green.jpg",
    "./Client/Assets/Textures/Player/soldier_dark_green_red.jpg",
    "./Client/Assets/Textures/Player/soldier_fire.jpg",
    "./Client/Assets/Textures/Player/soldier_green.jpg",
    "./Client/Assets/Textures/Sprites/fire.bmp",
    "./Client/Assets/Textures/Player/soldier_red.jpg",
    "./Client/Assets/Textures/Skyboxes/sky_menu.png",
    "./Client/Assets/Textures/Colors/blue.png",
    "./Client/Assets/Textures/Colors/red.jpg",
    "./Client/Assets/Textures/Colors/gold.jpg",
    "./Client/Assets/Textures/Skyboxes/sky_back.png",
    "./Client/Assets/Textures/Skyboxes/sky_down.png",
    "./Client/Assets/Textures/Skyboxes/sky_front.png",
    "./Client/Assets/Textures/Skyboxes/sky_left.png",
    "./Client/Assets/Textures/Skyboxes/sky_right.png",
    "./Client/Assets/Textures/Skyboxes/sky_up.png",
    "./Client/Assets/Textures/Backgrounds/connection.jpg",
    "./Client/Assets/Textures/Sprites/smoke.bmp"
  });

  for (size_t i = 0; i < allTexture.size(); i++)
    {
      this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(0, 0, 0, 0));
      this->_progressBar->setProgress(this->_progressBar->getProgress() + ((100 - 66) / static_cast<double>(allTexture.size())));
      this->_kirrlicht.putText(this->_ebrima[48], L"Loading...",
                               kirr::Core::rect<kirr::s32>(1280 / 2 - 80, 720 / 2 - 48, 1280, 720))->draw();
      this->_kirrlicht.putText(this->_ebrima[32], utils::getWStrFromStr(allTexture.at(i)).c_str(),
                               kirr::Core::rect<kirr::s32>(80, 590, 1280 - 80, 590 + 45))->draw();
      this->_progressBar->draw();
      this->_kirrlicht.getDriver()->endScene();
      if (!this->_kirrlicht.loadTexture(allTexture.at(i)))
        std::cerr << "Error: Missing Texture: " << allTexture.at(i) << std::endl;
    }
  this->_progressBar->setProgress(100);
  return (true);
}

bool                    indie::module::ModuleLoader::loadFonts()
{
  this->_kirrlicht.getDriver()->beginScene(true, true, kirr::Color(0, 0, 0, 0));
  this->_progressBar->setProgress(0);
  this->_progressBar->draw();
  this->_kirrlicht.getDriver()->endScene();
  return (this->_kirrlicht.loadFonts("./Client/Assets/Fonts/ebrima", ".xml", {10, 12, 14, 16, 18, 20, 26, 32, 36, 42, 48}, this->_ebrima));
}
