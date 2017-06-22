/*
** Server.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs/Post
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon Jun 12 12:15:44 2017 Antoine Dury
** Last update Tue Jun 13 11:11:28 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

void            ServerCloud::postCreateServer(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string		name = req.param(":name").as<std::string>();
  std::string		ip = req.param(":ip").as<std::string>();
	std::string		gamemode = req.param(":gamemode").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /server/create/" + name + "/" + ip + "/" + gamemode);

	/* Create server in database */
	this->dbQuery(Operation::INSERT, "INSERT INTO servers(name, ip, gamemode) VALUES('" + name + "', '" + ip + "', '" + gamemode + "');");
	res.send(Http::Code::Ok, "server successfully created");
}

void            ServerCloud::postUpdateServerNbPlayers(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string		id = req.param(":id").as<std::string>();
  std::string		nbPlayers = req.param(":nb_players").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /server/player/" + id + "/" + nbPlayers);

	/* Update server players in database */
	this->dbQuery(Operation::UPDATE, "UPDATE servers SET players = " + nbPlayers + " WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "server players successfully updated");
}

void            ServerCloud::postDeleteServer(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string		id = req.param(":id").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /server/delete/" + id);

	/* Update server players in database */
	this->dbQuery(Operation::DELETE, "DELETE FROM servers WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "server successfully deleted");
}
