/*
** Server.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs/Get
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon Jun 12 14:13:25 2017 Antoine Dury
** Last update Mon Jun 12 14:53:27 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

void            ServerCloud::getServerById(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string   id = req.param(":id").as<std::string>();
  pqxx::result  result;

  /* Beautiful log message */
  this->printMsg("GET /server/id/" + id);

  /* Get server from database with id */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM servers WHERE id = " + id + ";");
  if (!result.empty())
    {
      auto        _r = result.begin();
      std::string response = _r[0].as<std::string>() + "," + _r[1].as<std::string>() +
                             "," + _r[2].as<std::string>() + "," + _r[3].as<std::string>() +
                             "," + _r[4].as<std::string>();

      res.send(Http::Code::Ok, response);
    }
  else
    res.send(Http::Code::Not_Found, NOT_FOUND);
}

void            ServerCloud::getServerByName(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string   name = req.param(":name").as<std::string>();
  pqxx::result  result;

  /* Beautiful log message */
  this->printMsg("GET /server/name/" + name);

  /* Get server from database with name */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM servers WHERE name = '" + name + "';");
  if (!result.empty())
    {
      auto        _r = result.begin();
      std::string response = _r[0].as<std::string>() + "," + _r[1].as<std::string>() +
                             "," + _r[2].as<std::string>() + "," + _r[3].as<std::string>() +
                             "," + _r[4].as<std::string>();

      res.send(Http::Code::Ok, response);
    }
  else
    res.send(Http::Code::Not_Found, NOT_FOUND);
}

void            ServerCloud::getServerList(const Rest::Request& req, Http::ResponseWriter res)
{
  pqxx::result  result;

  static_cast<void>(req);
  /* Beautiful log message */
  this->printMsg("GET /server/list");

  /* Get server from database with id */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM servers ORDER BY id;");
  if (!result.empty())
    {
      std::string response = "";

      for (auto it = result.begin(); it != result.end(); it++)
        {
          if (it != result.begin())
            response += ",";
          response += it[0].as<std::string>();
        }

      res.send(Http::Code::Ok, response);
    }
  else
    res.send(Http::Code::Not_Found, NOT_FOUND);
}
