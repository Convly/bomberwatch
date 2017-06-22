##
## Makefile for Makfile in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Bin/Libs/Bin/Utils/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Mon May  1 01:40:17 2017 jsx
## Last update Sun Jun 18 17:17:21 2017 Maxime Cauvin
##

NAME    		=     libutils.a

INCNAME			=			UTILS

CC      		=    	g++

RM      		=  		rm -f

INCSRC			=			./Srcs/Functions/join/join.hpp 											\
									./Srcs/Functions/split/split.hpp 										\
									./Srcs/Functions/fileExist/fileExist.hpp 						\
									./Srcs/Functions/wchar/wchar.hpp 										\
									./Srcs/Functions/isANumber/isANumber.hpp 						\
									./Srcs/Functions/isAnIPAddress/isAnIPAddress.hpp		\
									./Srcs/Objects/APIClient/APIClient.hpp 			 				\

CXXFLAGS  	=   	-W -Wall -Wextra -Werror -std=c++14 -fPIC						\
									-lcurl 																							\

CXXFLAGS    +=  	-I./Srcs/Functions/join/ 														\
									-I./Srcs/Functions/split/ 			 										\
									-I./Srcs/Functions/fileExist/ 			 								\
									-I./Srcs/Functions/wchar/ 			 										\
									-I./Srcs/Functions/isANumber/ 			 								\
									-I./Srcs/Functions/isAnIPAddress/ 			 						\
									-I./Srcs/Objects/APIClient/ 			 									\
									-I../../../Dependencies/Includes/curl/							\


SRC					= 		./Srcs/Functions/join/join.cpp											\
									./Srcs/Functions/split/split.cpp										\
									./Srcs/Functions/fileExist/fileExist.cpp						\
									./Srcs/Functions/wchar/wchar.cpp										\
									./Srcs/Functions/isANumber/isANumber.cpp						\
									./Srcs/Functions/isAnIPAddress/isAnIPAddress.cpp		\
									./Srcs/Objects/APIClient/APIClient.cpp 			 				\


OBJ     		= 		$(SRC:.cpp=.o)																			\

all: $(NAME)

$(NAME): $(OBJ)
	$(RM) -r $(INCNAME)/Includes/
	mkdir $(INCNAME)/Includes/
	cp $(INCSRC) -t $(INCNAME)/Includes/
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	cp $(NAME) ../../
	cp -r $(INCNAME) ../../
	$(RM) -r $(INCNAME)/Includes/
	@printf "\033[0;32mUtils library compiled successfully !\n\033[0m"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) -r $(INCNAME)/Includes/
	$(RM) $(NAME)
	$(RM) ../../$(NAME)
	$(RM) -r ../../$(INCNAME)

re: fclean all

%.o : %.c
	$(CC) $(CXXFLAGS) -c $< -o $@
