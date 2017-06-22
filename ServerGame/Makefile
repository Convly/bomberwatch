##
## Makefile for makefile in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Thu May  4 12:00:12 2017 jsx
## Last update Sun Jun 18 16:13:33 2017 Maxime Cauvin
##

NAME    =     libbbwserver.a

CC      =    	g++

RM      =  		rm -f

CXXFLAGS  =   	-W -Wall -Wextra -Werror -std=c++14

CXXFLAGS    +=  	-I./Bin/Includes 										\
					-I../Client/Bin/Dependencies/Includes/ChaiScript/		\

LDFLAGS = -lboost_system -lboost_serialization -lboost_thread -lpthread -ldl -pthread

SRCS = 		./Bin/Srcs/Bomberman.cpp							\
			./Bin/Srcs/Referee.cpp 								\
			./Bin/Srcs/ServerManager.cpp 						\
			./Bin/Srcs/ServerGame.cpp							\
			./Bin/Srcs/TcpServer.cpp							\
			./Bin/Srcs/TcpTunnelServer.cpp						\
			./Bin/Srcs/IndieDedicated.cpp						\
			./Bin/Srcs/ServerCLI.cpp 							\
			./Bin/Srcs/ServerEntity.cpp							\
			./Bin/Srcs/Chaidie.cpp 								\

OBJS     = 		$(SRCS:.cpp=.o)

all:  $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	@printf "\033[0;32mServerGame library compiled successfully !\n\033[0m"


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

%.o : %.c
	$(CC) $(CXXFLAGS) -c $< -o $@
