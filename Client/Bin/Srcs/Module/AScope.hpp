/*
** AScope.hpp for rendu in /Users/metge_q/rendu/cpp_indie_studio/Client/Bin/Srcs/Module/Menu
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 08 13:18:25 2017 Quentin Metge
** Last update Wed Jun 14 11:14:41 2017 Quentin Metge
*/

#ifndef ASCOPE_HPP_
# define ASCOPE_HPP_

#include "IScope.hpp"

namespace indie
{
  namespace module
  {
    class AScope : public IScope
    {
    public:
      AScope(std::string const& name) : _name(name), _access(true), _posCamera(kirr::Pos<float>(0, 0, -400)) {}
      virtual ~AScope(){}

    public:
      virtual bool  pollEvent(kirr::GlobalEvent const& gEvent){
        for (size_t i = 0; i < this->_eventBoxesKey.size(); i++){
          if (this->_eventBoxesKey[i](gEvent))
            this->_eventBoxesFct[i]();
        }
        return (true);
      }

    public:
      kirr::Pos<float>     getPosCamera() const {return (this->_posCamera);}
      bool                 pollScope(AModule & module, kirr::Camera *camera, const std::string & prevName, const std::string & curName){
        if (!dynamic_cast<indie::module::AScope*>(module.getScopes()[curName].get())->_access)
          return (true);
        module.setPrevScope(prevName);
        module.setCurrentScope(curName);
        module.getKirrlicht().makeTransition(camera, module.getScopes()[module.getCurrentScope()].get()->getPosCamera());
        return true;
      }

    public:
      virtual bool              load() {return (true);}
      virtual bool              loop() {return (true);}

      virtual void              disable(){this->_access = false;}
      virtual void              enable(){this->_access = true;}
      virtual bool              toogleAccess(){return (this->_access = !(this->_access));}

    public:
      virtual std::vector<std::pair<std::string const, std::vector<kirr::Scene::IMeshSceneNode *>>>&  getWordsMesh() {return (this->_wordsMesh);}
      virtual std::vector<kirr::Scene::IMeshSceneNode *>  getStringMesh(std::string const& word) const
      {
        for (size_t i = 0; i < this->_wordsMesh.size(); i++)
        {
          if (this->_wordsMesh[i].first == word)
            return (this->_wordsMesh[i].second);
        }
        return (std::vector<kirr::Scene::IMeshSceneNode *>());
      }
      virtual bool              getAccess() const
      {
        return (this->_access);
      }

    protected:
      std::string               _name;
      bool                      _access;
      kirr::Pos<float>          _posCamera;

    protected:
      std::vector<std::function<bool (kirr::GlobalEvent const&)>>       _eventBoxesKey;
      std::vector<std::function<void (void)>>                           _eventBoxesFct;

    protected:
      std::vector<std::pair<std::string const, std::vector<kirr::Scene::IMeshSceneNode *>>>  _wordsMesh;
    };
  } /* scope */
} /* indie */

#endif
