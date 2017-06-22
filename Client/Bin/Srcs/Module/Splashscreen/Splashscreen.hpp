//
// Splashscreen.hpp for  in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Splashscreen/
//
// Made by Maxime Cauvin
// Login   <maxime.cauvin@epitech.eu>
//
// Started on  Wed May 24 17:34:34 2017 Maxime Cauvin
// Last update Sat Jun 17 17:03:13 2017 Maxime Cauvin
//

#ifndef SPLASHSCREEN_HPP_
#define  SPLASHSCREEN_HPP_

# include "AModule.hpp"

namespace indie
{
  namespace module
  {
    class Splashscreen : public AModule
    {
      kirr::klang::ISound *_sfx;
      kirr::klang::ISound *_nexusSample;
      std::unordered_map<std::string, kirr::Scene::IMeshSceneNode *>   _meshs;
      kirr::Camera    *_camera;
      bool _state;
      std::string _currentStep;
      kirr::Scene::IParticleSystemSceneNode     *_particleSystem;
      kirr::Scene::IParticleFadeOutAffector     *_affector;

    public:
      Splashscreen(indie::module::ModuleLoader &);
      virtual ~Splashscreen();

      virtual bool  load();
      virtual bool  start();
      virtual bool  stop();
      virtual bool  clear();

      bool          pollEvents(kirr::GlobalEvent const& mevent);
      bool          makeAnimation();

    private:
      bool          _animationStep1();
      bool          _animationStep2();
      bool          _animationStep3();
      bool          _animationStep4();
    };
  }
}

#endif
