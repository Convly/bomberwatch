##
## Makefile for makefile in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Thu May  4 12:00:12 2017 jsx
## Last update Sun Jun 18 16:13:16 2017 Maxime Cauvin
##

NAME    		=     ../bomberwatch

CC      		=    	g++

RM      		=  		rm -f

CXXFLAGS  	=   	-W -Wall -Wextra -Werror -std=c++14 -pipe 							\

CXXFLAGS    +=  	-I./Bin/Libs/																						\
									-I../ServerGame/Bin/Includes														\
									-I./Bin/Dependencies/Includes/Irrlicht									\
									-I./Bin/Dependencies/Includes/curl											\
									-I./Bin/Dependencies/Includes/ChaiScript								\
									-I./Bin/Dependencies/Includes/irrklang/									\
									-I./Bin/Srcs/Errors/																		\
									-I./Bin/Srcs/Commons/Kirrlicht													\
									-I./Bin/Srcs/Commons/ProgressBar												\
									-I./Bin/Srcs/Indie/																			\
									-I./Bin/Srcs/Module/																		\
									-I./Bin/Srcs/Module/ModuleLoader/												\
									-I./Bin/Srcs/Module/Menu																\
									-I./Bin/Srcs/Module/Intro/															\
									-I./Bin/Srcs/Module/Menu/Scopes													\
									-I./Bin/Srcs/Module/Menu/Scopes/Home										\
									-I./Bin/Srcs/Module/Menu/Scopes/Multiplayer							\
									-I./Bin/Srcs/Module/Menu/Scopes/Play										\
									-I./Bin/Srcs/Module/Menu/Scopes/Profile									\
									-I./Bin/Srcs/Module/Menu/Scopes/Profile/ProfileInfos		\
									-I./Bin/Srcs/Module/Menu/Scopes/Settings								\
									-I./Bin/Srcs/Module/Menu/Scopes/Solo										\
									-I./Bin/Srcs/Module/Connection													\
									-I./Bin/Srcs/Module/Splashscreen												\
									-I./Bin/Srcs/Module/GameClient													\
									-I./Bin/Srcs/Game/																			\
									-I./Bin/Srcs/Game/GameInfos/														\
									-I./Bin/Srcs/Game/GameServerInfos/											\
									-I./Bin/Srcs/Game/Binding/ 															\
									-I./Bin/Srcs/Game/GameServerInfos/ClientGame/						\
									-I./Bin/Srcs/Game/GameServerInfos/ClientManager/				\
									-I./Bin/Srcs/Game/GameServerInfos/TcpClient/						\
									-I./Bin/Srcs/Game/GameServerInfos/TcpTunnelClient/			\


LDFLAGS			=		 	-L/usr/lib 																									\
									-L./Bin/Libs/ -lutils																				\
									-L./Bin/Dependencies/Libs/																	\
									-L./Bin/Dependencies/Libs/irrklang/													\
									-L../ServerGame/																						\
									-lIrrlicht																									\
									-lGL 																												\
									-lXxf86vm																										\
									-lXext																											\
									-lX11																												\
									-ldl																												\
									-lcurl																											\
									-lboost_system																							\
									-lboost_serialization																	 			\
									-lboost_thread 																							\
									-lboost_filesystem																					\
									-lpthread																										\
									-lbbwserver																									\
									-lIrrKlang -Wl,-rpath=$(CURDIR)/Bin/Dependencies/Libs/ 			\

SRC					= 		./Bin/Srcs/main.cpp																										\
									./Bin/Srcs/Indie/Indie.cpp																						\
									./Bin/Srcs/Module/ModuleLoader/ModuleLoader.cpp												\
									./Bin/Srcs/Module/Intro/Intro.cpp																			\
									./Bin/Srcs/Module/Menu/Menu.cpp																				\
									./Bin/Srcs/Commons/Kirrlicht/Kirrlicht.cpp														\
									./Bin/Srcs/Commons/ProgressBar/ProgressBar.cpp												\
									./Bin/Srcs/Module/Menu/Scopes/Home/Home.cpp														\
									./Bin/Srcs/Module/Menu/Scopes/Multiplayer/Multiplayer.cpp							\
									./Bin/Srcs/Module/Menu/Scopes/Play/Play.cpp														\
									./Bin/Srcs/Module/Menu/Scopes/Profile/Profile.cpp											\
									./Bin/Srcs/Module/Menu/Scopes/Profile/ProfileInfos/ProfileInfos.cpp		\
									./Bin/Srcs/Module/Menu/Scopes/Settings/Settings.cpp										\
									./Bin/Srcs/Module/Menu/Scopes/Solo/Solo.cpp														\
									./Bin/Srcs/Module/Connection/Connection.cpp														\
									./Bin/Srcs/Module/Splashscreen/Splashscreen.cpp												\
									./Bin/Srcs/Module/GameClient/GameClient.cpp														\
									./Bin/Srcs/Game/GameInfos/GameInfos.cpp																\
									./Bin/Srcs/Game/GameInfos/GameObject.cpp															\
									./Bin/Srcs/Game/GameServerInfos/ClientGame/ClientGame.cpp							\
									./Bin/Srcs/Game/GameServerInfos/ClientManager/ClientManager.cpp				\
									./Bin/Srcs/Game/GameServerInfos/TcpClient/TcpClient.cpp								\
									./Bin/Srcs/Game/GameServerInfos/TcpTunnelClient/TcpTunnelClient.cpp		\
									./Bin/Srcs/Game/GameServerInfos/GameServerInfos.cpp										\
									./Bin/Srcs/Game/Binding/Binding.cpp																		\
									./Bin/Srcs/Game/Player.cpp																						\
									./Bin/Srcs/Commons/EventReceiver/EventReceiver.cpp										\

OBJ     		= 		$(SRC:.cpp=.o)

all: basis $(NAME)

basis:
	make -C ./Bin/Libs/Bin/Utils/

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CXXFLAGS) -o $(NAME) $(LDFLAGS)
	@printf "\033[0;32mClient compiled successfully !\n\033[0m"

cleanbasis:
	$(RM) $(OBJ)

clean: cleanbasis
	make clean -C ./Bin/Libs/Bin/Utils/

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./Bin/Libs/Bin/Utils/

re: fclean all

%.o : %.c
	$(CC) $(CXXFLAGS) -c $< -o $@
