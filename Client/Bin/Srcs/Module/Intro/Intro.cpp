//
// Intro.cpp for intro in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/Intro/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 16:23:15 2017 jsx
// Last update Thu Jun 15 21:48:09 2017 Maxime Cauvin
//

#include "Intro.hpp"


indie::module::Intro::Intro(indie::module::ModuleLoader & ml)
:
  AModule(ml)
{
}

indie::module::Intro::~Intro() {
}

bool    indie::module::Intro::load() {
  return true;
}

bool    indie::module::Intro::start() {
  this->_moduleLoader.switcher("Connection");
  return true;
}

bool    indie::module::Intro::stop()
{
  this->_state = false;
  return true;
}

bool    indie::module::Intro::clear()
{
  this->_kirrlicht.getSceneManager()->clear();
  return true;
}
