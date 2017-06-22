//
// ProfileInfos.cpp for profileinfos in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Profile/ProfileInfos/
//
// Made by JSX
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Thu May 11 04:02:31 2017 JSX
// Last update Thu Jun  1 02:20:58 2017 JSX
//

#include "ProfileInfos.hpp"
#include "Profile.hpp"

indie::module::ProfileInfos::ProfileInfos(const int playerId, indie::module::Profile & profile)
:
  _profile(profile),
  _playerId(playerId),
  _pseudo("Unknown Player"),
  _level(1),
  _playedTime(0),
  _registrationDate("NA")
{

}

indie::module::ProfileInfos::ProfileInfos(const int playerId, const std::string & pseudo, const int level, const int playedTime, const std::string & registrationDate, indie::module::Profile & profile)
:
  _profile(profile),
  _playerId(playerId),
  _pseudo(pseudo),
  _level(level),
  _playedTime(playedTime),
  _registrationDate(registrationDate)
{

}

indie::module::ProfileInfos::~ProfileInfos() {

}

indie::module::ProfileInfos &   indie::module::ProfileInfos::operator=(const indie::module::ProfileInfos & item) {
  if (this != &item) {
    this->_playerId = item.getPlayerId();
    this->_pseudo = item.getPseudo();
    this->_level = item.getLevel();
    this->_playedTime = item.getTimePlayed();
    this->_registrationDate = item.getRegistrationDate();
  }
  return *this;
}

// GETTERS

int                         indie::module::ProfileInfos::getPlayerId() const {
  return this->_playerId;
}

const std::string &         indie::module::ProfileInfos::getPseudo() const {
  return this->_pseudo;
}

int                         indie::module::ProfileInfos::getLevel() const {
  return this->_level;
}

int                         indie::module::ProfileInfos::getTimePlayed() const {
  return this->_playedTime;
}

const std::string &         indie::module::ProfileInfos::getRegistrationDate() const {
  return this->_registrationDate;
}

// SETTERS

void                        indie::module::ProfileInfos::setPlayerId(const int item) {
  this->_playerId = item;
}

void                        indie::module::ProfileInfos::setPseudo(const std::string & item) {
  this->_pseudo = item;
}

void                        indie::module::ProfileInfos::setLevel(const int item) {
  this->_level = item;
}

void                        indie::module::ProfileInfos::setTimePlayed(const int item) {
  this->_playedTime = item;
}

void                        indie::module::ProfileInfos::setRegistrationDate(const std::string & item) {
  this->_registrationDate = item;
}
