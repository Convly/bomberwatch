/*
** ServerCloud.cpp for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud/Bin/Srcs
**
** Made by Antoine Dury
** Login   <antoine.dury@epitech.eu>
**
** Started on  Mon May 08 15:04:06 2017 Antoine Dury
** Last update Sun Jun 18 17:16:33 2017 Antoine Dury
*/

#include "ServerCloud.hpp"

using namespace bwsc;
using namespace Net;

/******************************************************************************/
/*                                Ctor & Dtor                                 */
/******************************************************************************/
ServerCloud::ServerCloud(const std::string& address, const size_t& port, const std::string& db)
	: _address(address), _port(port), _db(db)
{
	Address	addr(address, Port(port));

	this->_server = std::make_shared<Http::Endpoint>(addr);
}

ServerCloud::~ServerCloud(void)
{
	this->_db.disconnect();
  this->printMsg("Stopped");
}


/******************************************************************************/
/*                              Server controls                               */
/******************************************************************************/
int 		ServerCloud::start(void)
{
	auto	opts = Http::Endpoint::options()
							 .threads(2)
							 .flags(Tcp::Options::InstallSignalHandler);

	/* Init server */
	this->printMsg("Starting on http://" + this->_address + ":" + std::to_string(this->_port) + "/");
	this->setupRoutes();
	this->_server->init(opts);
	this->_server->setHandler(this->_router.handler());

	/* Init database */
	if (this->setupDatabase() == 1)
		return (1);

	/* Start server */
	this->_server->serveThreaded();

	return (0);
}

void 		ServerCloud::stop(void) const
{
	/* Stop server */
	this->_server->shutdown();
}


/******************************************************************************/
/*                                   Routes                                   */
/******************************************************************************/
void 							ServerCloud::setupRoutes(void)
{
	using namespace	Rest::Routes;

	/* GET account */
	Get(this->_router, "/account/id/:id", bind(&ServerCloud::getAccountById, this));
	Get(this->_router, "/account/pseudo/:pseudo", bind(&ServerCloud::getAccountByPseudo, this));
	Get(this->_router, "/account_id/:pseudo", bind(&ServerCloud::getAccountIdByPseudo, this));
	Get(this->_router, "/account/credentials/:pseudo/:password", bind(&ServerCloud::getCredentials, this));
	Get(this->_router, "/account/color/:id", bind(&ServerCloud::getPlayerColor, this));
	Get(this->_router, "/account/music/:id", bind(&ServerCloud::getPlayerMusic, this));
	Get(this->_router, "/account/sfx/:id", bind(&ServerCloud::getPlayerSFX, this));

	/* GET leaderboard */
	Get(this->_router, "/leaderboard/:id", bind(&ServerCloud::getLeaderboard, this));
	Get(this->_router, "/leaderboard/id/:server/:gamemode", bind(&ServerCloud::getLeaderboardId, this));
	Get(this->_router, "/leaderboard/players/:id", bind(&ServerCloud::getLeaderboardPlayers, this));
	Get(this->_router, "/leaderboard/scores/:id", bind(&ServerCloud::getLeaderboardScores, this));

	/* GET servers */
	Get(this->_router, "/server/id/:id", bind(&ServerCloud::getServerById, this));
	Get(this->_router, "/server/name/:name", bind(&ServerCloud::getServerByName, this));
	Get(this->_router, "/server/list", bind(&ServerCloud::getServerList, this));

	/* GET settings */
	Get(this->_router, "/settings/:id", bind(&ServerCloud::getSettings, this));

	/* POST account */
	Post(this->_router, "/account/create/:pseudo/:password", bind(&ServerCloud::postCreateAccount, this));
	Post(this->_router, "/account/level/:id/:level", bind(&ServerCloud::postUpdateLevel, this));
	Post(this->_router, "/account/time_played/:id/:time", bind(&ServerCloud::postUpdateTimePlayed, this));
	Post(this->_router, "/account/color/:id/:color", bind(&ServerCloud::postUpdatePlayerColor, this));
	Post(this->_router, "/account/music/:id/:music", bind(&ServerCloud::postUpdatePlayerMusic, this));
	Post(this->_router, "/account/sfx/:id/:sfx", bind(&ServerCloud::postUpdatePlayerSFX, this));

	/* POST leaderboard */
	Post(this->_router, "/leaderboard/create/:server/:gamemode", bind(&ServerCloud::postCreateLeaderboard, this));
	Post(this->_router, "/leaderboard/player/:id/:player_id", bind(&ServerCloud::postUpdateLeaderboardPlayer, this));
	Post(this->_router, "/leaderboard/score/:id/:player_id/:score", bind(&ServerCloud::postUpdateLeaderboardScore, this));
	Post(this->_router, "/leaderboard/delete_player/:id/:player_id", bind(&ServerCloud::postDeleteLeaderboardPlayer, this));

	/* POST servers */
	Post(this->_router, "/server/create/:name/:ip/:gamemode", bind(&ServerCloud::postCreateServer, this));
	Post(this->_router, "/server/player/:id/:nb_players", bind(&ServerCloud::postUpdateServerNbPlayers, this));
	Post(this->_router, "/server/delete/:id", bind(&ServerCloud::postDeleteServer, this));

	/* POST settings */
	Post(this->_router, "/settings/forward/:id/:key", bind(&ServerCloud::postUpdateSettingsForward, this));
	Post(this->_router, "/settings/backward/:id/:key", bind(&ServerCloud::postUpdateSettingsBackward, this));
	Post(this->_router, "/settings/left/:id/:key", bind(&ServerCloud::postUpdateSettingsLeft, this));
	Post(this->_router, "/settings/right/:id/:key", bind(&ServerCloud::postUpdateSettingsRight, this));
	Post(this->_router, "/settings/action1/:id/:key", bind(&ServerCloud::postUpdateSettingsAction1, this));
	Post(this->_router, "/settings/action2/:id/:key", bind(&ServerCloud::postUpdateSettingsAction2, this));
	Post(this->_router, "/settings/action3/:id/:key", bind(&ServerCloud::postUpdateSettingsAction3, this));
	Post(this->_router, "/settings/action4/:id/:key", bind(&ServerCloud::postUpdateSettingsAction4, this));
	Post(this->_router, "/settings/pause/:id/:key", bind(&ServerCloud::postUpdateSettingsPause, this));
	Post(this->_router, "/settings/control/:id/:key", bind(&ServerCloud::postUpdateSettingsControl, this));
}

/******************************************************************************/
/*                                  Database                                  */
/******************************************************************************/
int 						ServerCloud::setupDatabase()
{
	if (this->_db.is_open())
		this->printMsg("Connected to " + std::string(this->_db.dbname()) + " database");
	else
		return (this->printError("Can't connect to database"));
	return (0);
}

pqxx::result		ServerCloud::dbQuery(const Operation& operation, const std::string& query)
{
	pqxx::result	result;

	if (operation == Operation::SELECT)
		{
			pqxx::nontransaction	nt(this->_db);
			pqxx::result 					tmp(nt.exec(query));

			result = tmp;
		}
	else if (operation == Operation::INSERT ||
					operation == Operation::UPDATE ||
					operation == Operation::DELETE)
		{
			pqxx::work	work(this->_db);

			work.exec(query);
			work.commit();
		}
	return (result);
}


/******************************************************************************/
/*                                   Utils                                    */
/******************************************************************************/
void 	ServerCloud::printMsg(const std::string& msg) const
{
  std::cout << "[Nexus] : " << msg << std::endl;
}

int		ServerCloud::printError(const std::string& err) const
{
  std::cerr << "[Nexus - Error] : " << err << std::endl;
	return (1);
}
