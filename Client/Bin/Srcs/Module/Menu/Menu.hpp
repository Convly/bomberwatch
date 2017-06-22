/*
** Menu.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 13:56:26 2017 Quentin Metge
** Last update Sun Jun 18 01:57:25 2017 Maxime Cauvin
*/

#ifndef MENU_HPP_
# define MENU_HPP_

#include "AModule.hpp"
#include "Player.hpp"

namespace indie
{
  namespace module
  {
    class Menu : public AModule
    {
    private:
      kirr::Camera                                            *_camera;
      std::shared_ptr<indie::game::Player>                    _playerOne;
      std::shared_ptr<indie::game::Player>                    _playerTwo;
      kirr::Video::ITexture                                   *_sky;
      std::unordered_map<std::string, kirr::klang::ISound *>  _sounds;
      kirr::klang::ISound                                     *_bgMusic;
      std::unordered_map<std::string, int>                    _volume;

    public:
      Menu(indie::module::ModuleLoader &);
      virtual ~Menu();

      virtual bool    load();
      virtual bool    start();
      virtual bool    stop();
      virtual bool    clear();

      void            removeIntoSoundMapExceptOne(std::string const& key);

      bool                                                    addSelectSound(std::string const& key, std::string const& soundPath);

      void                                                    setMusicVolume(int const& musicVolume);
      void                                                    setSFXVolume(int const& sfxVolume);

      kirr::Camera                                            *getCamera();
      std::shared_ptr<indie::game::Player>                    getPlayerOne();
      std::shared_ptr<indie::game::Player>                    getPlayerTwo();

      std::unordered_map<std::string, kirr::klang::ISound *>  getSoundsMap() const;
      std::unordered_map<std::string, kirr::klang::ISound *>  &getSoundsMap();
      kirr::klang::ISound                                     *getBgMusic();

      int                                                     getMusicVolume();
      int                                                     getSFXVolume();
    };

  } /* module */
} /* indie */

#endif
