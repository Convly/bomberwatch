/*
** Settings.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs/Post
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Tue Jun 13 14:18:35 2017 Antoine Dury
** Last update Tue Jun 13 14:44:39 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

void 				   ServerCloud::postUpdateSettingsForward(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/forward/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET forward = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, forward) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsBackward(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/backward/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET backward = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, backward) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsLeft(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/left/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET _left = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, _left) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsRight(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/right/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET _right = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, _right) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsAction1(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/action1/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET action1 = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, action1) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsAction2(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/action2/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET action2 = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, action2) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsAction3(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/action3/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET action3 = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, action3) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsAction4(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/action4/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET action4 = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, action4) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsPause(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/pause/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET pause = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, pause) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}

void 				   ServerCloud::postUpdateSettingsControl(const Rest::Request& req, Http::ResponseWriter res)
{
	std::string   id = req.param(":id").as<std::string>();
	std::string   key = req.param(":key").as<std::string>();
  pqxx::result  result;

	/* Beautiful log message */
	this->printMsg("POST /settings/control/" + id + "/" + key);

	/* Update settings in database */
  result = this->dbQuery(Operation::SELECT, "SELECT * FROM settings WHERE player = " + id + ";");
  if (!result.empty())
    this->dbQuery(Operation::UPDATE, "UPDATE settings SET control = " + key + " WHERE player = " + id + ";");
  else
    this->dbQuery(Operation::INSERT, "INSERT INTO settings(player, control) VALUES(" + id + ", " + key + ");");
  res.send(Http::Code::Ok, "settings successfully updated");
}
