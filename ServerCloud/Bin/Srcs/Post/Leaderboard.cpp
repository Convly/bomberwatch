/*
** Leaderboard.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs/Post
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon May 22 15:21:42 2017 Antoine Dury
** Last update Tue May 23 16:05:26 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

void            ServerCloud::postCreateLeaderboard(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string		server = req.param(":server").as<std::string>();
	std::string		gamemode = req.param(":gamemode").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /leaderboard/create/" + server + "/" + gamemode);

	/* Create leaderboard in database */
	this->dbQuery(Operation::INSERT, "INSERT INTO leaderboards(server, gamemode) VALUES('" + server + "', '" + gamemode + "');");
	res.send(Http::Code::Ok, "leaderboard successfully created");
}

void            ServerCloud::postUpdateLeaderboardPlayer(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string		id = req.param(":id").as<std::string>();
  std::string		playerId = req.param(":player_id").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /leaderboard/player/" + id + "/" + playerId);

	/* Update leaderboard players in database */
	this->dbQuery(Operation::UPDATE, "UPDATE leaderboards SET players[" + playerId + "] = " + playerId + ", scores[" + playerId + "] = 0 WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "leaderboard players successfully updated");
}

void            ServerCloud::postUpdateLeaderboardScore(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string		id = req.param(":id").as<std::string>();
  std::string		playerId = req.param(":player_id").as<std::string>();
  std::string		score = req.param(":score").as<std::string>();

	/* Beautiful log message */
	this->printMsg("POST /leaderboard/score/" + id + "/" + playerId + "/" + score);

	/* Update leaderboard players in database */
	this->dbQuery(Operation::UPDATE, "UPDATE leaderboards SET scores[" + playerId + "] = " + score + " WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "leaderboard scores successfully updated");
}

void            ServerCloud::postDeleteLeaderboardPlayer(const Rest::Request& req, Http::ResponseWriter res)
{
  std::string		id = req.param(":id").as<std::string>();
  std::string		playerId = req.param(":player_id").as<std::string>();
  std::string   newPlayerId = std::to_string(std::stoi(playerId) * -1);

	/* Beautiful log message */
	this->printMsg("POST /leaderboard/delete_player/" + id + "/" + playerId);

	/* Delete leaderboard player in database */
	this->dbQuery(Operation::UPDATE, "UPDATE leaderboards SET players[" + playerId + "] = " + newPlayerId + ", scores[" + playerId + "] = -1 WHERE id = " + id + ";");
	res.send(Http::Code::Ok, "leaderboard player successfully deleted");
}
