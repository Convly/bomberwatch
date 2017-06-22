##
## Makefile for Makefile in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/
##
## Made by jsx
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Mon May  1 01:13:42 2017 jsx
## Last update Fri Jun 16 14:20:53 2017 JSX
##

CLIENT 			= client
SERVER 			= server

PWD					=			pwd

CC      		=    	g++

RM      		=  		rm -rf

CP      		=  		cp -rf

OBJ     		= 		$(SRC:.cpp=.o)																	\

XXXCMPL:
	make -C ./ServerGame
	make -C ./Client/
	@printf "\033[0;32mIndie Studio compiled successfully !\n\033[0m"

cleanbasis:
	$(RM) $(OBJ)

fclean: cleanSrcs

cleanSrcs:
	make fclean -C ./ServerGame
	make fclean -C ./Client

uninstall: cleanSrcs
	$(RM) $(NAME)
	$(RM) ./Client/Bin/Dependencies/Includes/Irrlicht/*.h
	$(RM) ./Client/Bin/Dependencies/Includes/Lua-5.3.0/*.h
	$(RM) ./Client/Bin/Dependencies/Includes/Curl/*.h
	$(RM) ./Client/Bin/Dependencies/Includes/irrklang/*.h
	$(RM) ./Client/Bin/Dependencies/Libs/*.a
	$(RM) ./Client/Bin/Dependencies/Libs/*.so
	$(RM) ./Client/Assets/
	$(RM) ./tmp
	$(RM) ./install
	$(RM)	./elevatormusic.wav

re: cleanSrcs XXXCMPL

install:
	@printf "\033[0;32mWelcome to the bomberwatch's installer !\n\033[0m"
	@printf "\033[0;32mInstaling prerequisite...\n\033[0m"
	wget storage.bomberwatch.eu/elevatormusic.wav ; aplay elevatormusic.wav &
	mkdir ./install && mkdir ./tmp
	@printf "\033[0;32mGettting irrklang from Aurore server...\n\033[0m"
	wget storage.bomberwatch.eu/libs/audio/irrklang.zip ; mv irrklang.zip ./install/ && unzip ./install/irrklang.zip -d ./install && $(RM) ./install/irrklang.zip
	@printf "\033[0;Installing...\n\033[0m"
	$(CP) ./install/irrklang/include/* ./Client/Bin/Dependencies/Includes/irrklang
	$(CP) ./install/irrklang/libIrrKlang.so ./Client/Bin/Dependencies/Libs/
	@printf "\033[0;32mDone!\n\033[0m"
	mkdir ./tmp/curl/
	@printf "\033[0;32mCURL!\n\033[0m"
	@printf "\033[0;32mGettting curl from Aurore server...\n\033[0m"
	wget storage.bomberwatch.eu/libs/scripts/curl.zip ; mv curl.zip ./install/ && unzip ./install/curl.zip -d ./install && $(RM) ./install/curl.zip
	@printf "\033[0;32mDone!\n\033[0m"
	@printf "\033[0;32mBuilding curl...\n\033[0m"
	cd install/curl/ && ./buildconf
	cd install/curl/ && ./configure --without-ssl --prefix=$$PWD/../../tmp/curl/ && make && make install
	@printf "\033[0;32mDone!\n\033[0m"
	$(CP) ./tmp/curl/include/curl/*.h ./Client/Bin/Dependencies/Includes/curl/
	$(CP) ./tmp/curl/lib/libcurl.a ./Client/Bin/Dependencies/Libs/ 2>/dev/null || echo "Passing invalid scope"
	$(CP) ./tmp/curl/lib64/libcurl.a ./Client/Bin/Dependencies/Libs/ 2>/dev/null || echo "Passing invalid scope"
	@printf "\033[0;32mThe Curl installation is finished\n\033[0m"
	@printf "\033[0;32mGettting ChaiScript from Aurore server...\n\033[0m"
	wget 149.202.42.41/libs/scripts/ChaiScript-6.0.0.zip ; mv ChaiScript-6.0.0.zip ./install/ && unzip ./install/ChaiScript-6.0.0.zip -d ./install && $(RM) ./install/ChaiScript-6.0.0.zip
	$(CP) ./install/ChaiScript-6.0.0/include/* ./Client/Bin/Dependencies/Includes/ChaiScript/
	@printf "\033[0;32mThe ChaiScript installation is finished\n\033[0m"
	@printf "\033[0;32mGettting Assets from Aurore server...\n\033[0m"
	wget 149.202.42.41/libs/assets/assets.zip ; mv assets.zip ./install/ && unzip ./install/assets.zip -d ./install && $(RM) ./install/assets.zip
	$(CP) ./install/Assets/ ./Client/
	@printf "\033[0;32mDone...\n\033[0m"
	@printf "\033[0;32mGettting irrlicht from Aurore server...\n\033[0m"
	wget storage.bomberwatch.eu/libs/graphics/irrlicht-1.8.2.zip ; mv irrlicht-1.8.2.zip ./install/ && unzip ./install/irrlicht-1.8.2.zip -d ./install && $(RM) ./install/irrlicht-1.8.2.zip
	$(CP) ./install/irrlicht-1.8.2/include/* ./Client/Bin/Dependencies/Includes/Irrlicht
	@printf "\033[0;32mDone!\n\033[0m"
	@printf "\033[0;32mBuilding irrlicht...\n\033[0m"
	make -C ./install/irrlicht-1.8.2/source/Irrlicht/
	@printf "\033[0;32mDone!\n\033[0m"
	$(CP) ./install/irrlicht-1.8.2/source/Irrlicht/libIrrlicht.a ./Client/Bin/Dependencies/Libs/
	@printf "\033[0;32mThe Irrlicht installation is finished\n\033[0m"
	$(RM) ./install
	$(RM) ./tmp

	make -C ServerGame/
	make -C Client/

	killall -q aplay || echo "" > /dev/null
	$(RM)	./elevatormusic.wav
	@printf "\033[0;32mInstallation finished !\n\033[0m"

%.o : %.c
	$(CC) $(CXXFLAGS) -c $< -o $@
