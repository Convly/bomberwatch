/*
** Account.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs/Post
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon May 22 15:14:15 2017 Antoine Dury
** Last update Sun Jun 18 17:18:37 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

void 				   	ServerCloud::postCreateAccount(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string		pseudo = req.param(":pseudo").as<std::string>();
	std::string		password = req.param(":password").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /account/create/" + pseudo + "/********");

	/* Create account in database */
	this->dbQuery(Operation::INSERT, "INSERT INTO accounts(id, pseudo, password) VALUES((SELECT MAX(id) + 2 FROM accounts) ,'" + pseudo + "', '" + password + "');");
	res.send(Http::Code::Ok, pseudo + " successfully created");
}

void 				   ServerCloud::postUpdateLevel(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string  id = req.param(":id").as<std::string>();
	std::string  level = req.param(":level").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /account/level/" + id + "/" + level);

	/* Update account in database */
	this->dbQuery(Operation::UPDATE, "UPDATE accounts SET level = " + level + " WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "level successfully updated");
}

void           ServerCloud::postUpdateTimePlayed(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string  id = req.param(":id").as<std::string>();
	std::string  time = req.param(":time").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /account/time_played/" + id + "/" + time);

	/* Update account in database */
	this->dbQuery(Operation::UPDATE, "UPDATE accounts SET time_played = " + time + " WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "time played successfully updated");
}

void           ServerCloud::postUpdatePlayerColor(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string  id = req.param(":id").as<std::string>();
	std::string  color = req.param(":color").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /account/color/" + id + "/" + color);

	/* Update account in database */
	this->dbQuery(Operation::UPDATE, "UPDATE accounts SET color = " + color + " WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "player color successfully updated");
}

void           ServerCloud::postUpdatePlayerMusic(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string  id = req.param(":id").as<std::string>();
	std::string  music = req.param(":music").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /account/music/" + id + "/" + music);

	/* Update account in database */
	this->dbQuery(Operation::UPDATE, "UPDATE accounts SET music = " + music + " WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "player music successfully updated");
}

void           ServerCloud::postUpdatePlayerSFX(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string  id = req.param(":id").as<std::string>();
	std::string  sfx = req.param(":sfx").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /account/sfx/" + id + "/" + sfx);

	/* Update account in database */
	this->dbQuery(Operation::UPDATE, "UPDATE accounts SET sfx = " + sfx + " WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "player sfx successfully updated");
}
