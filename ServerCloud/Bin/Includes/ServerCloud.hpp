/*
** ServerCloud.hpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon May 08 15:04:01 2017 Antoine Dury
** Last update Sun Jun 18 17:04:31 2017 Antoine Dury
*/

#ifndef SERVERCLOUD_HPP
#define SERVERCLOUD_HPP

#include <iostream>
#include <csignal>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pqxx/pqxx>

const std::string NOT_FOUND = "404 Not Found";

namespace bwsc
{
  class ServerCloud
  {
    public:
      /* Ctor & Dtor */
      ServerCloud(const std::string&, const size_t&, const std::string&);
      virtual ~ServerCloud(void);

      /* Server controls */
      int   start(void);
      void  stop(void) const;

    private:
      /* Routes */
      void  setupRoutes(void);

      /* Get */
      void  getAccountById(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getAccountByPseudo(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getAccountIdByPseudo(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getCredentials(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getPlayerColor(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getPlayerMusic(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getPlayerSFX(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getLeaderboard(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getLeaderboardId(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getLeaderboardPlayers(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getLeaderboardScores(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getServerById(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getServerByName(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getServerList(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  getSettings(const Net::Rest::Request&, Net::Http::ResponseWriter);

      /* Post */
      void  postCreateAccount(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateLevel(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateTimePlayed(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdatePlayerColor(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdatePlayerMusic(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdatePlayerSFX(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postCreateLeaderboard(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateLeaderboardPlayer(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateLeaderboardScore(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postDeleteLeaderboardPlayer(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postCreateServer(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateServerNbPlayers(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postDeleteServer(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsForward(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsBackward(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsLeft(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsRight(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsAction1(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsAction2(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsAction3(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsAction4(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsPause(const Net::Rest::Request&, Net::Http::ResponseWriter);
      void  postUpdateSettingsControl(const Net::Rest::Request&, Net::Http::ResponseWriter);

      /* Database */
      enum  Operation
      {
        UNDEFINED = -1,
        SELECT = 0,
        INSERT = 1,
        UPDATE,
        DELETE
      };
      int           setupDatabase(void);
      pqxx::result  dbQuery(const Operation&, const std::string&);

      /* Utils */
      void  printMsg(const std::string&) const;
      int   printError(const std::string&) const;

    private:
      const std::string                     _address;
      const size_t                          _port;
      std::shared_ptr<Net::Http::Endpoint>  _server;
      Net::Rest::Router                     _router;
      pqxx::connection                      _db;
  };
}

#endif //CPP_INDIE_STUDIO_SERVERCLOUD_HPP
