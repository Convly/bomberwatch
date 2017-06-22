/*
** Settings.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs/Get
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 13 14:02:01 2017 Antoine Dury
** Last update Tue Jun 13 14:45:29 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

void            ServerCloud::getSettings(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string   id = req.param(":id").as<std::string>();
  pqxx::result  result;

  /* Beautiful log message */
  this->printMsg("GET /settings/" + id);

  /* Get settings from database with id */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    {
      auto        _r = result.begin();
      std::string response = _r[1].as<std::string>() + "," + _r[2].as<std::string>() +
                             "," + _r[3].as<std::string>() + "," + _r[4].as<std::string>() +
                             "," + _r[5].as<std::string>() + "," + _r[6].as<std::string>() +
                             "," + _r[7].as<std::string>() + "," + _r[8].as<std::string>() +
                             "," + _r[9].as<std::string>() + "," + _r[10].as<std::string>() +
                             "," + _r[11].as<std::string>();

      res.send(Http::Code::Ok, response);
    }
  else
    res.send(Http::Code::Not_Found, NOT_FOUND);
}
