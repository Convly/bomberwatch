/*
** Leaderboard.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs/Get
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon May 22 15:19:31 2017 Antoine Dury
** Last update Mon Jun 12 14:15:02 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

void            ServerCloud::getLeaderboard(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string   id = req.param(":id").as<std::string>();
  pqxx::result  result;

  /* Beautiful log message */
  this->printMsg("GET /leaderboard/" + id);

  /* Get leaderboard from database with id */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM leaderboards WHERE id = " + id + ";");
  if (!result.empty())
    {
      auto        _r = result.begin();
      std::string response = _r[0].as<std::string>() + "," + _r[1].as<std::string>() +
                             "," + _r[2].as<std::string>() + "," + _r[3].as<std::string>();

      res.send(Http::Code::Ok, response);
    }
  else
    res.send(Http::Code::Not_Found, NOT_FOUND);
}

void            ServerCloud::getLeaderboardId(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string   server = req.param(":server").as<std::string>();
  std::string   gamemode = req.param(":gamemode").as<std::string>();
  pqxx::result  result;

  /* Beautiful log message */
  this->printMsg("GET /leaderboard/id/" + server + "/" + gamemode);

  /* Get leaderboard from database with id */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM leaderboards WHERE server = '"+ server + "' AND gamemode = '" + gamemode + "' ORDER BY id DESC;");
  if (!result.empty())
    {
      auto        _r = result.begin();
      std::string response = _r[0].as<std::string>();

      res.send(Http::Code::Ok, response);
    }
  else
    res.send(Http::Code::Not_Found, NOT_FOUND);
}

void            ServerCloud::getLeaderboardPlayers(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string   id = req.param(":id").as<std::string>();
  pqxx::result  result;

  /* Beautiful log message */
  this->printMsg("GET /leaderboard/players/" + id);

  /* Get leaderboard players from database with id */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM leaderboards WHERE id = " + id + ";");
  if (!result.empty())
    {
      auto        _r = result.begin();
      std::string response = _r[4].as<std::string>();

      response.erase(0, 1);
      response.erase(response.size() - 1, 1);
      res.send(Http::Code::Ok, response);
    }
  else
    res.send(Http::Code::Not_Found, NOT_FOUND);
}

void  ServerCloud::getLeaderboardScores(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string   id = req.param(":id").as<std::string>();
  pqxx::result  result;

  /* Beautiful log message */
  this->printMsg("GET /leaderboard/scores/" + id);

  /* Get leaderboard scores from database with id */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM leaderboards WHERE id = " + id + ";");
  if (!result.empty())
    {
      auto        _r = result.begin();
      std::string response = _r[5].as<std::string>();

      response.erase(0, 1);
      response.erase(response.size() - 1, 1);
      res.send(Http::Code::Ok, response);
    }
  else
    res.send(Http::Code::Not_Found, NOT_FOUND);
}
