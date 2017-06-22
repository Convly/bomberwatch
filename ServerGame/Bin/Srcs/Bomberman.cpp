/*
** Game.cpp for cpp_indie_studio in /Users/metge_q/rendu/cpp_indie_studio/ServerGame/Bin/Srcs
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Fri Jun  26  21:13:57  2017 Quentin Metge
** Last update Sun Jun 18 18:33:10 2017 Quentin Metge
*/

#include "Referee.hpp"
#include "Bomberman.hpp"

using namespace bwsg;

Bomberman::Bomberman(Referee& referee)
:
_referee(referee){
  this->generateMap();
  this->resolvePowerUpsInfos();
}

Bomberman::~Bomberman(){

}

void            Bomberman::lap(){
  this->checkPowerUpTimer();
  this->checkBombExplosion();
  this->getPowerUps();
}

Player&         Bomberman::getPlayerById(int id){
  for (auto it = this->_players.begin(); it != this->_players.end(); it++){
    if (id == it->second._ownerId)
      return it->second;
  }
  return this->_players.begin()->second;
}

Bomb&         Bomberman::getBombById(int id){
  for (auto it = this->_bombs.begin(); it != this->_bombs.end(); it++){
    if (id == it->second._id)
      return it->second;
  }
  return this->_bombs.begin()->second;
}

void            Bomberman::resolvePowerUpsInfos() {
  this->_powerUpsInfos = {
    {bwsg::ObjectType::PU_AMOUNT,       std::make_pair(0, 2)},
    {bwsg::ObjectType::PU_POWER,        std::make_pair(3, 5)},
    {bwsg::ObjectType::PU_GHOST,        std::make_pair(6, 6)},
    {bwsg::ObjectType::PU_PENETRATION,  std::make_pair(7, 7)},
  };
}

void            Bomberman::getPowerUps(){
  for (auto it2 = this->_players.begin(); it2 != this->_players.end(); it2++){
    for (auto it1 = this->_powerUps.begin(); it1 != this->_powerUps.end(); it1++){
      auto pos = findCenterOfCase(this->_referee.getObjById(it2->second._id).getPosition());
      if (it1->second._pos.at(0) == pos.at(0)
        && it1->second._pos.at(2) == pos.at(2)){
        switch (static_cast<int>(this->_referee.getObjById(it1->second._id).getType())) {
          case static_cast<int>(ObjectType::PU_AMOUNT):
            it2->second._nbBombs++;
            break;
          case static_cast<int>(ObjectType::PU_POWER):
            it2->second._power++;
            break;
          case static_cast<int>(ObjectType::PU_GHOST):
            it2->second._ghost = true;
            it2->second._ghostStartTime = std::chrono::system_clock::now();
            this->_referee.setVisibility(
              -1,
              this->_referee.getPlayerObjByPlayerId(it2->second._ownerId),
              false,
              TriggerType::ALL_USERS
            );
            break;
          case static_cast<int>(ObjectType::PU_PENETRATION):
            it2->second._penetration = true;
            it2->second._penetrationStartTime = std::chrono::system_clock::now();
            break;
        }
        this->_referee.deleteObject(-1, this->_referee.getObjById(it1->second._id), bwsg::TriggerType::ALL_USERS);
        this->_powerUps.erase(it1->second._id);
        break;
      }
    }
  }
}

void            Bomberman::generateMap(){
  this->_map = {
    {2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
    {2, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1,  2},
    {2, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  2},
    {2, -1, -1,  1,  1,  1,  1,  1,  1,  1, -1, -1,  2, -1, -1,  1,  1,  1,  1,  1,  1,  1, -1, -1,  2},
    {2, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2},
    {2, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  2},
    {2, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1,  2},
    {2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
  };
}

std::vector<float>      Bomberman::findCenterOfCase(std::vector<float>& pos){
  std::vector<float>    res = {pos.at(0), pos.at(1), pos.at(2)};

  for (int i = pos.at(0) + 375; i < 750; i++){
    if (i % 30 == 0){
      res.at(0) = i - 390;
      break;
    }
  }
  for (int i = pos.at(2) + 375; i < 750; i++){
    if (i % 30 == 0){
      res.at(2) = i - 390;
      break;
    }
  }
  return res;
}

void              Bomberman::reset(){
  this->_players.clear();
  this->_bombs.clear();
  this->_powerUps.clear();
}

void              Bomberman::bombExplosion(Bomb& bomb){
  std::vector<std::vector<int>>   dir = {{-1, 0, 0}, {1, 0, 0}, {0, 0, -1}, {0, 0, 1}};
  bomb._explosed = true;
  for (size_t iDir = 0; iDir < dir.size(); iDir++){
    bool check = false;
    int iPower = 0;
    for (iPower = 0; !check && iPower <= this->getPlayerById(bomb._ownerId)._power; iPower++){
      std::vector<float> currentPos = {bomb._pos.at(0) + dir.at(iDir).at(0) * iPower * 30 , 0, bomb._pos.at(2) + dir.at(iDir).at(2) * iPower * 30};
      for (size_t i = 0; !check && i < this->_referee.getEnv()._entities.size();){
        std::vector<float> posEntity = findCenterOfCase(this->_referee.getEnv()._entities.at(i).getPosition());
        if (currentPos.at(0) == posEntity.at(0) && currentPos.at(2) == posEntity.at(2)){
          if (this->_referee.getEnv()._entities.at(i).getType() == ObjectType::ND_CUBE){
            check = true;
            iPower--;
            break;
          }
          else if (this->_referee.getEnv()._entities.at(i).getType() == ObjectType::D_CUBE
            || this->_referee.getEnv()._entities.at(i).getType() == ObjectType::PLAYER){
            if (this->_referee.getEnv()._entities.at(i).getType() == ObjectType::PLAYER)
              this->_players.erase(this->_referee.getEnv()._entities.at(i).getOwner());
            else{
              this->generatePowerUps(this->_referee.getEnv()._entities.at(i));
              check = true && !(this->getPlayerById(bomb._ownerId)._penetration);
            }
            this->_referee.deleteObject(-1, this->_referee.getEnv()._entities.at(i), bwsg::TriggerType::ALL_USERS);
            break;
          }
          else if (this->_referee.getEnv()._entities.at(i).getType() == ObjectType::BOMB
            && !this->getBombById(this->_referee.getEnv()._entities.at(i).getID())._explosed){
            bombExplosion(this->getBombById(this->_referee.getEnv()._entities.at(i).getID()));
          }
          else
            i++;
        }
        else
          i++;
      }
    }
    if (iPower - 1 > 0)
      this->_referee.createExplosion(-1, static_cast<float>(iPower - 1), bomb._pos, {static_cast<float>(dir.at(iDir).at(0)), static_cast<float>(dir.at(iDir).at(1)), static_cast<float>(dir.at(iDir).at(2))}, bwsg::TriggerType::ALL_USERS);
  }
  this->_referee.deleteObject(-1, this->_referee.getObjById(bomb._id), bwsg::TriggerType::ALL_USERS);
  this->_bombs.erase(bomb._id);
}

void                  Bomberman::checkBombExplosion(){
  for (auto it = this->_bombs.begin(); it != this->_bombs.end();){
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-it->second._startTime).count() > 3){
      this->bombExplosion(it->second);
      it = this->_bombs.begin();
    }
    else
      it++;
  }
}

bool                  Bomberman::canPutBomb(int id, std::vector<int> pos){
  int                 count = 0;

  for (size_t i = 0; i < this->_referee.getEnv()._entities.size(); i++){
    if (id == this->_referee.getEnv()._entities.at(i).getOwner()
      && this->_referee.getEnv()._entities.at(i).getType() == ObjectType::BOMB)
      count++;
  }
  if (count >= this->getPlayerById(id)._nbBombs)
    return false;
  for (auto it = this->_bombs.begin(); it != this->_bombs.end(); it++){
    if (it->second._pos.at(0) == pos.at(0)
      && it->second._pos.at(2) == pos.at(2))
      return false;
  }
  return true;
}

bool                  Bomberman::generatePowerUps(bwsg::ServerEntity& target) {
  int rd = static_cast<int>(std::rand() % 20);

  for (auto i = this->_powerUpsInfos.begin(); i != this->_powerUpsInfos.end(); i++) {
    if (rd >= i->_randRange.first && rd <= i->_randRange.second) {
      bwsg::ServerEntity& pu = this->_referee.addObject(i->_type, target.getPosition(), {0, 0, 0}, {10, 10, 10}, false, bwsg::OBJ_ACTION::DEFAULT, -1);
      this->_powerUps.insert(std::pair<int, bwsg::PowerUp>(pu.getID(), bwsg::PowerUp(pu.getID(), pu.getPosition())));
      this->_referee.dispObj(pu, bwsg::TriggerType::ALL_USERS, -1);
      return true;
    }
  }
  return false;
}

void              Bomberman::checkPowerUpTimer() {
  for (auto it = this->_players.begin(); it != this->_players.end(); it++) {
    bwsg::Player& pl = it->second;
    if (pl._ghost && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - pl._ghostStartTime).count() > 15) {
      pl._ghost = false;
      this->_referee.setVisibility(
        -1,
        this->_referee.getPlayerObjByPlayerId(pl._ownerId),
        true,
        TriggerType::ALL_USERS
      );
    }
    if (pl._penetration && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - pl._penetrationStartTime).count() > 15) {
      pl._penetration = false;
    }
  }
}
