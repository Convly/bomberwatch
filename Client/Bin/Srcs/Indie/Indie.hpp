//
// Indie.hpp for Indie in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Indie/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:25:57 2017 jsx
// Last update Thu May 11 02:18:15 2017 JSX
//

#ifndef INDIE_STUDIO_CORE_HPP_
#define INDIE_STUDIO_CORE_HPP_

#include <iostream>
#include <string>
#include "UTILS/http.hpp"

#include "ModuleLoader.hpp"

namespace indie {

  namespace core {
    class Indie {
    private:
      utils::APIClient              _nexusAPI;
      indie::module::ModuleLoader   _moduleLoader;

    public:
      Indie ();
      Indie (const std::string &);
      ~Indie ();

    public:
      bool start();
      indie::module::ModuleLoader & getModuleLoader();
      const utils::APIClient &      getNexusAPI() const;
    };
  } /* core */
} /* indie */

#endif /* end of include guard: INDIE_STUDIO_CORE_HPP_ */
