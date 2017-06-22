/*
** Account.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs/Get
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon May 22 15:12:56 2017 Antoine Dury
** Last update Sun Jun 18 17:10:36 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

void 						ServerCloud::getAccountById(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string		id = req.param(":id").as<std::string>();
	pqxx::result	result;

	/* Beautiful log message */
	this->printMsg("GET /account/id/" + id);

	/* Get account from database with id */
	result = this->dbQuery(Operation::SELECT, "SELECT * FROM accounts WHERE id = " + id + ";");
	if (!result.empty())
		{
			auto 				_r = result.begin();
			std::string	response = _r[0].as<std::string>() + "," + _r[1].as<std::string>() +
														 "," + _r[2].as<std::string>() + "," + _r[4].as<std::string>() +
														 "," + _r[5].as<std::string>();

			res.send(Http::Code::Ok, response);
		}
	else
		res.send(Http::Code::Not_Found, NOT_FOUND);
}

void 						ServerCloud::getAccountByPseudo(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string		pseudo = req.param(":pseudo").as<std::string>();
	pqxx::result	result;

	/* Beautiful log message */
	this->printMsg("GET /account/pseudo/" + pseudo);

	/* Get account from database with pseudo */
	result = this->dbQuery(Operation::SELECT, "SELECT * FROM accounts WHERE pseudo = '" + pseudo + "';");
	if (!result.empty())
		{
			auto 				_r = result.begin();
			std::string	response = _r[0].as<std::string>() + "," + _r[1].as<std::string>() +
														 "," + _r[2].as<std::string>() + "," + _r[4].as<std::string>() +
														 "," + _r[5].as<std::string>();

			res.send(Http::Code::Ok, response);
		}
	else
		res.send(Http::Code::Not_Found, NOT_FOUND);
}

void 						ServerCloud::getAccountIdByPseudo(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string		pseudo = req.param(":pseudo").as<std::string>();
	pqxx::result	result;

	/* Beautiful log message */
	this->printMsg("GET /account_id/" + pseudo);

	/* Get account id from database with pseudo */
	result = this->dbQuery(Operation::SELECT, "SELECT * FROM accounts WHERE pseudo = '" + pseudo + "';");
	if (!result.empty())
		{
			auto 				_r = result.begin();
			std::string	response = _r[0].as<std::string>();

			res.send(Http::Code::Ok, response);
		}
	else
		res.send(Http::Code::Not_Found, NOT_FOUND);
}

void 						ServerCloud::getCredentials(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string		pseudo = req.param(":pseudo").as<std::string>();
	std::string		password = req.param(":password").as<std::string>();
	pqxx::result	result;

	/* Beautiful log message */
	this->printMsg("GET /account/credentials/" + pseudo + "/********");

	/* Check credentials in database */
	result = this->dbQuery(Operation::SELECT, "SELECT * FROM accounts WHERE pseudo = '" + pseudo + "' AND password = '" + password + "';");
	if (!result.empty())
		res.send(Http::Code::Ok, "OK");
	else
		res.send(Http::Code::Not_Found, "KO");
}

void 						ServerCloud::getPlayerColor(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string		id = req.param(":id").as<std::string>();
	pqxx::result	result;

	/* Beautiful log message */
	this->printMsg("GET /account/color/" + id);

	/* Get player color from database with id */
	result = this->dbQuery(Operation::SELECT, "SELECT * FROM accounts WHERE id = " + id + ";");
	if (!result.empty())
		{
			auto 				_r = result.begin();
			std::string	response = _r[6].as<std::string>();

			res.send(Http::Code::Ok, response);
		}
	else
		res.send(Http::Code::Not_Found, NOT_FOUND);
}

void 						ServerCloud::getPlayerMusic(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string		id = req.param(":id").as<std::string>();
	pqxx::result	result;

	/* Beautiful log message */
	this->printMsg("GET /account/music/" + id);

	/* Get player music from database with id */
	result = this->dbQuery(Operation::SELECT, "SELECT * FROM accounts WHERE id = " + id + ";");
	if (!result.empty())
		{
			auto 				_r = result.begin();
			std::string	response = _r[7].as<std::string>();

			res.send(Http::Code::Ok, response);
		}
	else
		res.send(Http::Code::Not_Found, NOT_FOUND);
}

void 						ServerCloud::getPlayerSFX(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string		id = req.param(":id").as<std::string>();
	pqxx::result	result;

	/* Beautiful log message */
	this->printMsg("GET /account/sfx/" + id);

	/* Get player SFX from database with id */
	result = this->dbQuery(Operation::SELECT, "SELECT * FROM accounts WHERE id = " + id + ";");
	if (!result.empty())
		{
			auto 				_r = result.begin();
			std::string	response = _r[8].as<std::string>();

			res.send(Http::Code::Ok, response);
		}
	else
		res.send(Http::Code::Not_Found, NOT_FOUND);
}
