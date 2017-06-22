//
// ModuleLoader.hpp for ModuleLoader in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Module/ModuleLoader/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:38:16 2017 jsx
// Last update Fri Jun 16 21:25:45 2017 Maxime Cauvin
//

#ifndef MODULE_LOADER_HPP_
#define MODULE_LOADER_HPP_

# include <iostream>
# include <unordered_map>
# include <memory>
# include "bwsg.hpp"
# include "Error.hpp"
# include "IModule.hpp"
# include "UTILS/http.hpp"
# include "ProgressBar.hpp"

namespace indie {

  namespace core {
    class Indie;
  }
  namespace module {
    class ModuleLoader {
    private:
      indie::core::Indie&                                                           _indie;
      bool                                                                          _status;
      utils::APIClient &                                                            _nexusAPI;
      kirr::Kirrlicht                                                               _kirrlicht;
      std::unordered_map<std::string, std::shared_ptr<indie::module::IModule>>      _modules;
      std::shared_ptr<indie::module::IModule>                                       _current;
      std::unordered_map<int, kirr::Gui::IGUIFont *>                                _ebrima;
      ProgressBar                                                                   *_progressBar;

    public:
      ModuleLoader (indie::core::Indie&, const std::string &, utils::APIClient&);
      ~ModuleLoader ();

    public:
      std::unordered_map<std::string, std::shared_ptr<indie::module::IModule>> &getModules();
      std::shared_ptr<indie::module::IModule>  getCurrent() const;
      std::unordered_map<int, kirr::Gui::IGUIFont *> &getFontEbrima();
      const indie::core::Indie&     getIndie() const;
      indie::core::Indie&           getIndie();
      bool                          getStatus() const;
      void                          setStatus(bool);

    public:
      bool  entryPoint();
      bool  moduleExist(const std::string &);
      bool  switcher(const std::string &);
      bool  reload();
      bool  isAvailable(const std::string &);
      kirr::Kirrlicht & getKirrlicht();
      utils::APIClient & getNexusAPI();

    public:
      bool  loadMeshs();
      bool  loadTextures();
      bool  loadFonts();
    };
  } /* module */
} /* indie */

#endif /* end of include guard: MODULE_LOADER_HPP_ */
