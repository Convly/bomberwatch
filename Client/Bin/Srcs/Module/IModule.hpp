//
// IModule.hpp for IMODULE in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Modules/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:23:00 2017 jsx
// Last update Sat May  6 01:03:26 2017 jsx
//

#ifndef IMODULE_INDIE_STUDIO_HPP_
#define IMODULE_INDIE_STUDIO_HPP_

#include <iostream>
#include <string>
#include "IScope.hpp"

namespace indie {
  namespace module {
    class IModule {
    public:
      virtual ~IModule () {};

    public:
      virtual bool      load() = 0;
      virtual bool      start() = 0;
      virtual bool      stop() = 0;
      virtual bool      clear() = 0;
      virtual bool      reset() = 0;

    public:
      virtual void      disable() = 0;
      virtual void      enable() = 0;
      virtual bool      toogleAccess() = 0;

    public:
      virtual bool      getAccess() const = 0;

    public:
      virtual void      setAccess(bool) = 0;
    };
  } /* module */
} /* indie */

#endif /* end of include guard: IMODULE_INDIE_STUDIO_HPP_ */
