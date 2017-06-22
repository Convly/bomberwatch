/*
** APIClient.hpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/Client/Bin/Libs/Bin/Utils/Srcs/Objects/APIClient
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue May 09 19:00:05 2017 Antoine Dury
** Last update Sun Jun 18 17:25:33 2017 Antoine Dury
*/

#ifndef APICLIENT_HPP
#define APICLIENT_HPP

#include <curl.h>
#include <iostream>
#include <unordered_map>
#include "split.hpp"

namespace utils
{
  const std::string NOT_FOUND = "404 Not Found";

  class APIClient
  {
    public:
      /* Ctor & Dtor */
      APIClient(void);
      APIClient(const std::string&, const size_t&);
      virtual ~APIClient(void);

    private:
      /* Requests */
      std::string requestGET(const std::string&);
      std::string requestPOST(const std::string&);

    public:
      /* Complete getter API */
      std::unordered_map<std::string, std::string>  getProfile(const int&);
      std::unordered_map<std::string, std::string>  getProfile(const std::string&);
      std::vector<std::pair<int, int>>              getLeaderboard(const int&);
      std::unordered_map<std::string, std::string>  getLeaderboardInfos(const int&);
      std::vector<int>                              getServerList(void);
      std::unordered_map<std::string, std::string>  getServerInfos(const int&);
      std::unordered_map<std::string, std::string>  getServerInfos(const std::string&);
      std::unordered_map<std::string, int>          getSettings(const int&);

      /* Simple getter API */
      int         getId(const std::string&);
      std::string getPseudo(const int&);
      int         getLevel(const int&);
      std::string getRegistrationDate(const int&);
      int         getTimePlayed(const int&);
      int         getPlayerColor(const int&);
      int         getPlayerMusic(const int&);
      int         getPlayerSFX(const int&);
      int         getGameId(const std::string&, const std::string&);
      int         getServerNbPlayers(const int&);

      /* Creator API */
      int registerPlayer(const std::string&, const std::string&);
      int createGame(const std::string&, const std::string&);
      int createServer(const std::string&, const std::string&, const std::string&);

      /* Setter API */
      bool  setLevel(const int&, const int&);
      bool  incLevel(const int&);
      bool  setTimePlayed(const int&, const int&);
      bool  setPlayerColor(const int&, const int&);
      bool  setPlayerMusic(const int&, const int&);
      bool  setPlayerSFX(const int&, const int&);
      bool  setLeaderboardPlayer(const int&, const int&);
      bool  setLeaderboardScore(const int&, const int&, const int&);
      bool  setServerNbPlayers(const int&, const int&);
      bool  setSettingsForward(const int&, const int&);
      bool  setSettingsBackward(const int&, const int&);
      bool  setSettingsLeft(const int&, const int&);
      bool  setSettingsRight(const int&, const int&);
      bool  setSettingsAction1(const int&, const int&);
      bool  setSettingsAction2(const int&, const int&);
      bool  setSettingsAction3(const int&, const int&);
      bool  setSettingsAction4(const int&, const int&);
      bool  setSettingsPause(const int&, const int&);
      bool  setSettingsControl(const int&, const int&);

      /* Unsetter API */
      bool  unsetLeaderboardPlayer(const int&, const int&);
      bool  deleteServer(const int&);

      /* Check API */
      bool  playerExist(const int&);
      bool  playerExist(const std::string&);
      bool  checkCredentials(const std::string&, const std::string&);

      /* Utils */
      void  errorMsg(const size_t&) const;

    private:
      const std::string     _address;
      const size_t          _port;
      CURL                  *_curl;
  };
}

#endif
