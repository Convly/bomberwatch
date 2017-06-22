//
// Indie.cpp for Indie in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Indie/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:30:09 2017 jsx
// Last update Thu Jun 15 05:09:23 2017 Maxime Cauvin
//

#include "Indie.hpp"

indie::core::Indie::Indie()
:
  _nexusAPI(),
  _moduleLoader(*this, "Splashscreen", this->_nexusAPI)
{
}

indie::core::Indie::Indie(const std::string & entryModuleName)
:
  _nexusAPI(),
  _moduleLoader(*this, entryModuleName, this->_nexusAPI)
{
}

indie::core::Indie::~Indie() {
}

indie::module::ModuleLoader & indie::core::Indie::getModuleLoader() {
  return this->_moduleLoader;
}

const utils::APIClient &      indie::core::Indie::getNexusAPI() const{
  return this->_nexusAPI;
}

bool  indie::core::Indie::start() {
  std::cout << "Go to module loader entry point" << std::endl;
  bool ret = this->_moduleLoader.entryPoint();
  std::cout << "Exit module loader entry point at value (" << ret << ")" << std::endl;
  return ret;
}