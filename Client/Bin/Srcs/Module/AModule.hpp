//
// AModule.hpp for AModule in /home/jsx/Epitech/tek2/C++2/indiestudio/cpp_indie_studio/Client/Bin/Srcs/Modules/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri May  5 15:23:13 2017 jsx
// Last update Thu May 11 13:44:24 2017 JSX
//

#ifndef AMODULE_INDIE_STUDIO_HPP_
#define AMODULE_INDIE_STUDIO_HPP_

#include "ModuleLoader.hpp"
#include "IModule.hpp"

namespace indie {
  namespace module {
    class AModule : public IModule {
    protected:
      bool                                                      _access;
      bool                                                      _state;
      indie::module::ModuleLoader &                             _moduleLoader;
      kirr::Kirrlicht &                                         _kirrlicht;
      std::string                                               _currentScope;
      std::string                                               _prevScope;
      std::unordered_map<std::string, std::shared_ptr<IScope>>  _scopes;

    public:
      AModule (indie::module::ModuleLoader & ml)
        :
          _access(true),
          _state(false),
          _moduleLoader(ml),
          _kirrlicht(ml.getKirrlicht()),
          _currentScope("Default"),
          _prevScope("Default"){

      }
      virtual ~AModule () {}

    public:
      virtual bool      load() {return false;}
      virtual bool      start() {return false;}
      virtual bool      stop() {return false;}
      virtual bool      clear() {return false;}
      virtual bool      reset() {return this->stop() && this->clear() && this->load() && this->start();}

    public:
      virtual void      disable()                     {this->_access = false;}
      virtual void      enable()                      {this->_access = true;}
      virtual bool      toogleAccess()                {return (this->_access = !(this->_access));}

    public:
      virtual indie::module::ModuleLoader & getModuleLoader() const {return this->_moduleLoader;}
      virtual kirr::Kirrlicht &             getKirrlicht()    const {return this->_kirrlicht;}
      virtual bool                          getAccess()       const {return (this->_access);}
      virtual std::string                   getCurrentScope() const {return (this->_currentScope);}
      virtual std::string                   getPrevScope()    const {return (this->_prevScope);}
      virtual std::unordered_map<std::string, std::shared_ptr<IScope>>   getScopes() const  {return (this->_scopes);}

    public:
      virtual void      setAccess(const bool access)              {this->_access = access;}
      virtual void      setCurrentScope(std::string const& str)   {this->_currentScope = str;}
      virtual void      setPrevScope(std::string const& str)   {this->_prevScope = str;}

    public:
      virtual void  moveStringToRight(std::vector<kirr::Scene::IMeshSceneNode *> const& meshes, float const& initial,
                                      float const& shift, float const& limit)
      {
        if (meshes.size() && meshes[0]->getPosition().X >= initial + limit)
          return ;
        for (size_t i = 0; i < meshes.size(); i++)
          meshes[i]->setPosition(kirr::Core::vector3df(meshes[i]->getPosition().X + shift, meshes[i]->getPosition().Y, meshes[i]->getPosition().Z));
      }
      virtual void  moveStringToLeft(std::vector<kirr::Scene::IMeshSceneNode *> const& meshes, float const& initial,
                                     float const& shift)
      {
        if (meshes.size() && meshes[0]->getPosition().X <= initial)
          return ;
        for (size_t i = 0; i < meshes.size(); i++)
          meshes[i]->setPosition(kirr::Core::vector3df(meshes[i]->getPosition().X - shift, meshes[i]->getPosition().Y, meshes[i]->getPosition().Z));
      }
      virtual void  zoomInString(std::vector<kirr::Scene::IMeshSceneNode *> const& meshes)
      {
        for (size_t i = 0; i < meshes.size(); i++)
        {
          if (meshes[i]->getScale() != kirr::Core::vector3df(1.1, 1.1, 1.1))
            meshes[i]->setScale(meshes[i]->getScale() + 0.02);
        }
      }
      virtual void  zoomOutString(std::vector<kirr::Scene::IMeshSceneNode *> const& meshes)
      {
        for (size_t i = 0; i < meshes.size(); i++)
        {
          if (meshes[i]->getScale() != kirr::Core::vector3df(1, 1, 1))
            meshes[i]->setScale(meshes[i]->getScale() - 0.02);
        }
      }
    };
  } /* module */
} /* indie */

#endif /* end of include guard: AMODULE_INDIE_STUDIO_HPP_ */
