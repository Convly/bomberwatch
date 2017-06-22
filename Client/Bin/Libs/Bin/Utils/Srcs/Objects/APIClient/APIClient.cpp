/*
** APIClient.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/Client/Bin/Libs/Bin/Utils/Srcs/Objects/APIClient
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue May 09 18:59:53 2017 Antoine Dury
** Last update Sun Jun 18 19:38:54 2017 Antoine Dury
*/

#include "APIClient.hpp"

using namespace utils;

/******************************************************************************/
/*                                Ctor & Dtor                                 */
/******************************************************************************/
APIClient::APIClient(void)
  : _address("164.132.58.41"), _port(8022)
{
  this->_curl = curl_easy_init();
}

APIClient::APIClient(const std::string& address, const size_t& port)
  : _address(address), _port(port)
{
  this->_curl = curl_easy_init();
}

APIClient::~APIClient(void)
{
  curl_easy_cleanup(this->_curl);
}


/******************************************************************************/
/*                                  Requests                                  */
/******************************************************************************/
static std::string  data;

static void         writeData(const char *buf, const size_t size, const size_t nmemb)
{
  data.clear();
  for (size_t i = 0; i < size * nmemb; i++)
    data += buf[i];
}

std::string         APIClient::requestGET(const std::string& path)
{
  std::string       url = "http://" + this->_address + ":" + std::to_string(this->_port) + path;

  curl_easy_reset(this->_curl);
  curl_easy_setopt(this->_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, &writeData);
  curl_easy_perform(this->_curl);
  return (data);
}

std::string         APIClient::requestPOST(const std::string& path)
{
  std::string       url = "http://" + this->_address + ":" + std::to_string(this->_port) + path;

  curl_easy_reset(this->_curl);
  curl_easy_setopt(this->_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, &writeData);
  curl_easy_setopt(this->_curl, CURLOPT_POSTFIELDS, NULL);
  curl_easy_setopt(this->_curl, CURLOPT_POSTFIELDSIZE, 0);
  curl_easy_perform(this->_curl);
  return (data);
}


/******************************************************************************/
/*                            Complete getter API                             */
/******************************************************************************/
std::unordered_map<std::string, std::string>    APIClient::getProfile(const int& id)
{
  size_t                    i = 0;
  std::vector<std::string>  tmp;
  std::vector<std::string>  table = {"id", "pseudo", "level", "registration_date", "time_played"};
  std::string               result = this->requestGET("/account/id/" + std::to_string(id));
  std::unordered_map<std::string, std::string>  profile;

  if (result.empty())
    {
      this->errorMsg(1);
      return (profile);
    }
  else if (result == NOT_FOUND)
    {
      profile["id"] = NOT_FOUND;
      return (profile);
    }
  tmp = split(result, ',');
  for (auto it = table.begin(); it != table.end(); it++)
    profile[*it] = tmp.at(i++);
  return (profile);
}

std::unordered_map<std::string, std::string>    APIClient::getProfile(const std::string& pseudo)
{
  size_t                    i = 0;
  std::vector<std::string>  tmp;
  std::vector<std::string>  table = {"id", "pseudo", "level", "registration_date", "time_played"};
  std::string               result = this->requestGET("/account/pseudo/" + pseudo);
  std::unordered_map<std::string, std::string>  profile;

  if (result.empty())
    {
      this->errorMsg(1);
      return (profile);
    }
  else if (result == NOT_FOUND)
    {
      profile["id"] = NOT_FOUND;
      return (profile);
    }
  tmp = split(result, ',');
  for (auto it = table.begin(); it != table.end(); it++)
    profile[*it] = tmp.at(i++);
  return (profile);
}

std::vector<std::pair<int, int>>    APIClient::getLeaderboard(const int& id)
{
  std::string                       resultPlayers = this->requestGET("/leaderboard/players/" + std::to_string(id));
  std::string                       resultScores = this->requestGET("/leaderboard/scores/" + std::to_string(id));
  std::vector<std::pair<int, int>>  leaderboard;
  std::vector<std::string>          tmp, tmp2;

  if (resultPlayers.empty() || resultScores.empty())
    {
      this->errorMsg(1);
      return (leaderboard);
    }
  else if (resultPlayers == NOT_FOUND || resultScores == NOT_FOUND)
    {
      leaderboard.push_back(std::make_pair(0, 0));
      return (leaderboard);
    }
  tmp = split(resultPlayers, ',');
  tmp2 = split(resultScores, ',');
  for (size_t i = 0; i != tmp.size(); i++)
    {
      if (tmp.at(i) != "NULL" && tmp2.at(i) != "NULL")
        {
          int player = std::stoi(tmp.at(i));
          int score = std::stoi(tmp2.at(i));

          if (player > 0 && score >= 0)
            leaderboard.push_back(std::make_pair(player, score));
        }
    }
  return (leaderboard);
}

std::unordered_map<std::string, std::string>    APIClient::getLeaderboardInfos(const int& id)
{
  size_t                    i = 0;
  std::vector<std::string>  tmp;
  std::vector<std::string>  table = {"id", "server", "gamemode", "begin_date"};
  std::string               result = this->requestGET("/leaderboard/" + std::to_string(id));
  std::unordered_map<std::string, std::string>  leaderboard;

  if (result.empty())
    {
      this->errorMsg(1);
      return (leaderboard);
    }
  else if (result == NOT_FOUND)
    {
      leaderboard["id"] = NOT_FOUND;
      return (leaderboard);
    }
  tmp = split(result, ',');
  for (auto it = table.begin(); it != table.end(); it++)
    leaderboard[*it] = tmp.at(i++);
  return (leaderboard);
}

std::vector<int>            APIClient::getServerList(void)
{
  std::vector<std::string>  tmp;
  std::string               result = this->requestGET("/server/list");
  std::vector<int>          serverList;

  if (result.empty())
    {
      this->errorMsg(1);
      return (serverList);
    }
  else if (result == NOT_FOUND)
    {
      serverList.push_back(-1);
      return (serverList);
    }
  tmp = split(result, ',');
  for (size_t i = 0; i != tmp.size(); i++)
    serverList.push_back(std::stoi(tmp.at(i)));
  return (serverList);
}

std::unordered_map<std::string, std::string>    APIClient::getServerInfos(const int& id)
{
  size_t                    i = 0;
  std::vector<std::string>  tmp;
  std::vector<std::string>  table = {"id", "name", "ip", "gamemode", "players"};
  std::string               result = this->requestGET("/server/id/" + std::to_string(id));
  std::unordered_map<std::string, std::string>  serverInfos;

  if (result.empty())
    {
      this->errorMsg(1);
      return (serverInfos);
    }
  else if (result == NOT_FOUND)
    {
      serverInfos["id"] = NOT_FOUND;
      return (serverInfos);
    }
  tmp = split(result, ',');
  for (auto it = table.begin(); it != table.end(); it++)
    serverInfos[*it] = tmp.at(i++);
  return (serverInfos);
}

std::unordered_map<std::string, std::string>    APIClient::getServerInfos(const std::string& name)
{
  size_t                    i = 0;
  std::vector<std::string>  tmp;
  std::vector<std::string>  table = {"id", "name", "ip", "gamemode", "players"};
  std::string               result = this->requestGET("/server/name/" + name);
  std::unordered_map<std::string, std::string>  serverInfos;

  if (result.empty())
    {
      this->errorMsg(1);
      return (serverInfos);
    }
  else if (result == NOT_FOUND)
    {
      serverInfos["id"] = NOT_FOUND;
      return (serverInfos);
    }
  tmp = split(result, ',');
  for (auto it = table.begin(); it != table.end(); it++)
    serverInfos[*it] = tmp.at(i++);
  return (serverInfos);
}

std::unordered_map<std::string, int>  APIClient::getSettings(const int& id)
{
  size_t                    i = 0;
  std::vector<std::string>  tmp;
  std::vector<std::string>  table = {"id", "forward", "backward", "left", "right", "action1",
                                    "action2", "action3", "action4", "pause", "control"};
  std::string               result = this->requestGET("/settings/" + std::to_string(id));
  std::unordered_map<std::string, int>  settings;

  if (result.empty())
    {
      this->errorMsg(1);
      return (settings);
    }
  else if (result == NOT_FOUND)
    {
      settings["id"] = -1;
      return (settings);
    }
  tmp = split(result, ',');
  for (auto it = table.begin(); it != table.end(); it++)
    settings[*it] = std::stoi(tmp.at(i++));
  return (settings);
}


/******************************************************************************/
/*                             Simple getter API                              */
/******************************************************************************/
int           APIClient::getId(const std::string& pseudo)
{
  std::string id = this->requestGET("/account_id/" + pseudo);

  if (id.empty())
    {
      this->errorMsg(1);
      return (-1);
    }
  else if (id == NOT_FOUND)
    return (-1);
  return (std::stoi(id));
}

std::string   APIClient::getPseudo(const int& id)
{
  auto        profile = this->getProfile(id);

  if (profile["id"] == NOT_FOUND)
    return (NOT_FOUND);
  return (profile["pseudo"]);
}

int           APIClient::getLevel(const int& id)
{
  auto        profile = this->getProfile(id);

  if (profile["id"] == NOT_FOUND)
    return (-1);
  return (std::stoi(profile["level"]));
}

std::string   APIClient::getRegistrationDate(const int& id)
{
  auto        profile = this->getProfile(id);

  if (profile["id"] == NOT_FOUND)
    return (NOT_FOUND);
  return (profile["registration_date"]);
}

int           APIClient::getTimePlayed(const int& id)
{
  auto        profile = this->getProfile(id);

  if (profile["id"] == NOT_FOUND)
    return (-1);
  return (std::stoi(profile["time_played"]));
}

int           APIClient::getPlayerColor(const int& id)
{
  std::string color = this->requestGET("/account/color/" + std::to_string(id));

  if (color.empty())
    {
      this->errorMsg(1);
      return (0);
    }
  else if (color == NOT_FOUND)
    return (0);
  return (std::stoi(color));
}

int           APIClient::getPlayerMusic(const int& id)
{
  std::string music = this->requestGET("/account/music/" + std::to_string(id));

  if (music.empty())
    {
      this->errorMsg(1);
      return (-1);
    }
  else if (music == NOT_FOUND)
    return (-1);
  return (std::stoi(music));
}

int           APIClient::getPlayerSFX(const int& id)
{
  std::string sfx = this->requestGET("/account/sfx/" + std::to_string(id));

  if (sfx.empty())
    {
      this->errorMsg(1);
      return (-1);
    }
  else if (sfx == NOT_FOUND)
    return (-1);
  return (std::stoi(sfx));
}


int           APIClient::getGameId(const std::string& server, const std::string& gamemode)
{
  std::string id = this->requestGET("/leaderboard/id/" + server + "/" + gamemode);

  if (id.empty())
    {
      this->errorMsg(1);
      return (-1);
    }
  else if (id == NOT_FOUND)
    return (-1);
  return (std::stoi(id));
}

int           APIClient::getServerNbPlayers(const int& id)
{
  auto        server = this->getServerInfos(id);

  if (server["id"] == NOT_FOUND)
    return (-1);
  return (std::stoi(server["players"]));
}


/******************************************************************************/
/*                                Creator API                                 */
/******************************************************************************/
int           APIClient::registerPlayer(const std::string& pseudo, const std::string& password)
{
  std::string res = this->requestPOST("/account/create/" + pseudo + "/" + password);
  if (res.empty())
    {
      this->errorMsg(1);
      return (-1);
    }
  return (std::stoi(this->requestGET("/account_id/" + pseudo)));
}

int           APIClient::createGame(const std::string& server, const std::string& gamemode)
{
  std::string res = this->requestPOST("/leaderboard/create/" + server + "/" + gamemode);
  if (res.empty())
    {
      this->errorMsg(1);
      return (-1);
    }
  return (this->getGameId(server, gamemode));
}

int           APIClient::createServer(const std::string& name, const std::string& ip, const std::string& gamemode)
{
  std::string res = this->requestPOST("/server/create/" + name + "/" + ip + "/" + gamemode);
  auto        server = this->getServerInfos(name);

  if (res.empty())
    {
      this->errorMsg(1);
      return (-1);
    }
  return (std::stoi(server["id"]));
}


/******************************************************************************/
/*                                 Setter API                                 */
/******************************************************************************/
bool          APIClient::setLevel(const int& id, const int& level)
{
  std::string res = this->requestPOST("/account/level/" + std::to_string(id) + "/" + std::to_string(level));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::incLevel(const int& id)
{
  return (this->setLevel(id, this->getLevel(id) + 1));
}

bool          APIClient::setTimePlayed(const int& id, const int& time)
{
  std::string res = this->requestPOST("/account/time_played/" + std::to_string(id) + "/" + std::to_string(time));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setLeaderboardPlayer(const int& id, const int& playerId)
{
  std::string res = this->requestPOST("/leaderboard/player/" + std::to_string(id) + "/" + std::to_string(playerId));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setLeaderboardScore(const int& id, const int& playerId, const int &score)
{
  std::string res = this->requestPOST("/leaderboard/score/" + std::to_string(id) + "/" + std::to_string(playerId) + "/" + std::to_string(score));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setPlayerColor(const int& id, const int& color)
{
  std::string res = this->requestPOST("/account/color/" + std::to_string(id) + "/" + std::to_string(color));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setPlayerMusic(const int& id, const int& music)
{
  std::string res = this->requestPOST("/account/music/" + std::to_string(id) + "/" + std::to_string(music));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setPlayerSFX(const int& id, const int& sfx)
{
  std::string res = this->requestPOST("/account/sfx/" + std::to_string(id) + "/" + std::to_string(sfx));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setServerNbPlayers(const int& id, const int& nbPlayers)
{
  std::string res = this->requestPOST("/server/player/" + std::to_string(id) + "/" + std::to_string(nbPlayers));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsForward(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/forward/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsBackward(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/backward/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsLeft(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/left/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsRight(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/right/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsAction1(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/action1/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsAction2(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/action2/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsAction3(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/action3/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsAction4(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/action4/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsPause(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/pause/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::setSettingsControl(const int& id, const int& key)
{
  std::string res = this->requestPOST("/settings/control/" + std::to_string(id) + "/" + std::to_string(key));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}


/******************************************************************************/
/*                                Unsetter API                                */
/******************************************************************************/
bool          APIClient::unsetLeaderboardPlayer(const int& id, const int& playerId)
{
  std::string res = this->requestPOST("/leaderboard/delete_player/" + std::to_string(id) + "/" + std::to_string(playerId));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}

bool          APIClient::deleteServer(const int& id)
{
  std::string res = this->requestPOST("/server/delete/" + std::to_string(id));
  if (res.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (true);
}


/******************************************************************************/
/*                                 Check API                                  */
/******************************************************************************/
bool          APIClient::playerExist(const int& id)
{
  std::string player = this->requestGET("/account/id/" + std::to_string(id));
  if (player.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (player != NOT_FOUND);
}

bool          APIClient::playerExist(const std::string& pseudo)
{
  std::string player = this->requestGET("/account/pseudo/" + pseudo);
  if (player.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (player != NOT_FOUND);
}

bool          APIClient::checkCredentials(const std::string& pseudo, const std::string& password)
{
  std::string credentials = this->requestGET("/account/credentials/" + pseudo + "/" + password);
  if (credentials.empty())
    {
      this->errorMsg(1);
      return (false);
    }
  return (credentials == "OK");
}


/******************************************************************************/
/*                                   Utils                                    */
/******************************************************************************/
void  APIClient::errorMsg(const size_t& errorCode) const
{
  switch (errorCode)
  {
    case 1: std::cerr << "Host is unreachable. Please contact your administrator or check your network connexion." << std::endl; break;
  }
}
