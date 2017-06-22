##
## Makefile for cpp_indie_studio in /home/antoine/rendu/cpp/cpp_indie_studio/ServerCloud
##
## Made by Antoine Dury
## Login   <antoine.dury@epitech.eu>
##
## Started on  Tue May 09 14:28:49 2017 Antoine Dury
## Last update Tue May 09 14:28:49 2017 Antoine Dury
##

NAME    	= 	serverCloud

CC      	= 	g++

RM      	=		rm -f

CPPFLAGS  =		-W -Wall -Wextra -Werror -std=c++14	\
							-I./Bin/Includes

LDFLAGS		=		-L/usr/local/lib/	\
							-lnet							\
							-lpqxx -lpq

SRCS 			=		./Bin/Srcs/Main.cpp 				\
							./Bin/Srcs/ServerCloud.cpp

SRCS			+=	./Bin/Srcs/Get/Account.cpp			\
							./Bin/Srcs/Get/Leaderboard.cpp	\
							./Bin/Srcs/Get/Server.cpp				\
							./Bin/Srcs/Get/Settings.cpp

SRCS			+=	./Bin/Srcs/Post/Account.cpp			\
							./Bin/Srcs/Post/Leaderboard.cpp	\
							./Bin/Srcs/Post/Server.cpp			\
							./Bin/Srcs/Post/Settings.cpp

OBJS			=		$(SRCS:.cpp=.o)


all:  $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CPPFLAGS) -o $(NAME) $(LDFLAGS)
	@printf "\033[0;32mServerCloud compiled successfully !\n\033[0m"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

%.o : %.c
	$(CC) $(CXXFLAGS) -c $< -o $@
