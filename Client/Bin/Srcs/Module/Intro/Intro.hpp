//
// Intro.hpp for intro in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Modules/Intro/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:21:29 2017 jsx
// Last update Sat May  6 01:51:52 2017 jsx
//

#ifndef INDIE_STUDIO_MODULE_INTRO_HPP_
#define INDIE_STUDIO_MODULE_INTRO_HPP_

#include "AModule.hpp"

namespace indie {
  namespace module {
    class Intro : public AModule {

    public:
      Intro (indie::module::ModuleLoader &);
      virtual ~Intro ();

    public:
      virtual bool      load();
      virtual bool      start();
      virtual bool      stop();
      virtual bool      clear();
    };
  } /* module */
} /* indie */

#endif /* end of include guard: INDIE_STUDIO_MODULE_INTRO_HPP_ */
