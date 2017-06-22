/*
** Settings.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu/Scopes/Settings
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 15:01:13 2017 Quentin Metge
** Last update Sun Jun 18 20:51:20 2017 Maxime Cauvin
*/

#ifndef SETTINGS_HPP_
# define SETTINGS_HPP_

#include "Menu.hpp"
#include "AScope.hpp"
#include "GameClient.hpp"
#include "ProfileInfos.hpp"
#include "Profile.hpp"
#include "PlayerInfos.hpp"

namespace indie
{
  namespace module
  {
    class Settings : public AScope
    {
      std::unordered_map<std::string, kirr::klang::ISound *>                            &_sounds;
      Menu                                                                              &_menu;
      std::unordered_map<int, kirr::Gui::IGUIFont *>                                    &_ebrima;
      std::unordered_map<std::string, kirr::Gui::IGUIElement *>                         _components;
      kirr::Gui::IGUISkin                                                               *_skin;
      kirr::Gui::IGUIEnvironment                                                        *_env;
      std::vector<std::pair<std::string, kirr::Gui::IGUIButton *>>                      _buttonList;
      std::vector<std::pair<std::string, kirr::Gui::IGUIButton *>>                      _buttonMode;
      std::vector<std::pair<std::string, bwsg::ActionType>>                             _buttonNames;
      std::unordered_map<std::string, std::function<bool (int const&, int const&)>>     _buttonToAPI;
      std::unordered_map<std::string, int>                                              _profileSettings;
      std::unordered_map<std::string, std::string>                                      _namesAliases;
      std::unordered_map<kirr::ALL_KEY_CODE, wchar_t const*, kirr::EnumClassHash>       _keysAliases;
      bool                                                                              _controllerSelected;
      kirr::Scene::IAnimatedMeshSceneNode                                               *_playerMesh;
      std::vector<kirr::Video::ITexture *>                                              _playerTextures;
      SkinColorEnum                                                                     _idxTextures;
      std::unordered_map<std::string, bool>                                             _oldStateComp;

    public:
      Settings(Menu& menu);
      virtual ~Settings();

      bool  checkEvent(kirr::GlobalEvent const&, const kirr::Pos<float> &, const kirr::Pos<float> &, bool);
      std::vector<std::pair<std::string, kirr::Gui::IGUIButton *>>  getButtonList() const;
      std::vector<std::pair<std::string, kirr::Gui::IGUIButton *>>  getButtonMode() const;
      std::vector<std::pair<std::string, bwsg::ActionType>>        getButtonNames() const;
      kirr::Scene::IAnimatedMeshSceneNode                           *getPlayerMesh();

      virtual bool load();
      virtual bool loop();

    private:
      bool          _loadComponents();
      bool          _loadButtons();
      bool          _loadBindingsFromServer();
      bool          _loadTextures();
      bool          _loadSkinFromServer();
      bool          _loadAudioFromServer();

      void          _eventChangingKeyBinding(indie::module::ProfileInfos const& profileInfos);
      void          _setControlType(indie::module::ProfileInfos const& profileInfos);
      void          _eventChangingSkin();
    };

  } /* module */
} /* indie */

#endif /* end of include guard: SETTINGS_HPP_ */
