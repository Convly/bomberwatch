/*
** Kirrlicht.hpp for Rendu in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Srcs/Commons/Kirrlicht
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Fri May 05 18:20:34 2017 cauvin-m
** Last update Sat Jun 17 16:58:21 2017 Maxime Cauvin
*/

#ifndef KIRRLICHT_HPP_
# define KIRRLICHT_HPP_

# include <string>
# include <unordered_map>
# include <iostream>
# include <chrono>
# include <cstdlib>
# include <cmath>
# include "UTILS/all.hpp"
# include "irrlicht.h"
# include "KeyCodeEnum.hpp"
# include "irrKlang.h"

#define LIGHT false

namespace kirr
{
  enum OBJ_ACTION
    {
      STAND,
      PUT,
      MOVE_1,
      MOVE_2,
      MOVE_BACK,
      SHOOT_1,
      SHOOT_2,
      DEATH_1,
      DEATH_2,
      DEAD_1,
      DEAD_2,
      DEFAULT,
    };

  template <typename T>
  struct Pos
    {
      T x;
      T y;
      T z;

      Pos(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) {}
    };

  struct      EnumClassHash
    {
      template <typename T>
      std::size_t operator()(T t) const
        {
          return static_cast<std::size_t>(t);
        }
    };

  namespace Core = irr::core;
  namespace Video = irr::video;
  namespace Scene = irr::scene;
  namespace Gui = irr::gui;
  namespace Io = irr::io;

  namespace klang = irrklang;

  typedef irr::s16                                                  s16;
  typedef irr::s32                                                  s32;
  typedef irr::s64                                                  s64;
  typedef irr::s8                                                   s8;
  typedef irr::u16                                                  u16;
  typedef irr::u32                                                  u32;
  typedef irr::u64                                                  u64;
  typedef irr::u8                                                   u8;
  typedef irr::c8                                                   c8;
  typedef irr::f32                                                  f32;
  typedef irr::f64                                                  f64;

  typedef irr::core::vector3df                                      vector3df;
  typedef irr::core::position2d<int>                                vector2di;
  typedef irr::core::position2d<float>                              vector2df;
  typedef irr::video::SColor                                        Color;

  typedef irr::EKEY_CODE                                            KEY_CODE;
  typedef irr::IrrlichtDevice                                       Device;
  typedef irr::video::IVideoDriver                                  VideoDriver;
  typedef irr::scene::ISceneManager                                 SceneManager;
  typedef irr::gui::ICursorControl                                  Cursor;

  typedef irr::scene::IAnimatedMeshSceneNode                        AnimatedModele;
  typedef irr::scene::IAnimatedMesh                                 AnimatedMesh;
  typedef irr::scene::ICameraSceneNode                              Camera;

  typedef kirr::Core::array<irr::SJoystickInfo>                     JoystickList;

  typedef std::unordered_map<OBJ_ACTION, Pos<float>, EnumClassHash> ObjActionMap;

  struct                                                      GlobalEvent
    {
      irr::SEvent::SJoystickEvent                             joystickState;
      std::unordered_map<ALL_KEY_CODE, bool, EnumClassHash>   keyTab;
      std::unordered_map<ALL_KEY_CODE, bool, EnumClassHash>   pressTab;
      class Kirrlicht                                         &kirrlicht;

      GlobalEvent(class Kirrlicht &k) : kirrlicht(k)
        {
          joystickState.Joystick = 42;
          for (int i = 0; i <= static_cast<int>(ALL_KEY_CODE::KEY_KEY_CODES_COUNT); i++)
            this->keyTab[static_cast<ALL_KEY_CODE>(i)] = false;
          for (int i = 0; i <= static_cast<int>(ALL_KEY_CODE::KEY_KEY_CODES_COUNT); i++)
            this->pressTab[static_cast<ALL_KEY_CODE>(i)] = false;
        }
      GlobalEvent &operator=(const GlobalEvent &obj)
        {
          this->joystickState = obj.joystickState;
          this->keyTab.clear();
          this->keyTab = obj.keyTab;
          this->pressTab.clear();
          this->pressTab = obj.pressTab;
          return (*this);
        }
      Pos<int>      getCursorPosition() const;
      Pos<float>    getRCursorPosition();
      Pos<float>    getRJoystickPosition1() const;
      Pos<float>    getRJoystickPosition2() const;
      int           getJoystickComputer() const;
    };

  class                   EventReceiver : public irr::IEventReceiver
    {
      GlobalEvent         _event;
      class Kirrlicht     &_kirrlicht;

    public:
      EventReceiver(Kirrlicht&);
      virtual ~EventReceiver();

      virtual bool        OnEvent(irr::SEvent const& event);
      GlobalEvent &       getEvent();
      void                resetEvent();
      bool                isKeyDown(kirr::ALL_KEY_CODE) const;
      bool                isKey(kirr::ALL_KEY_CODE) const;
    };

  class                   AnimatedObject
    {
      private:
        ObjActionMap                                                _action;
        AnimatedModele                                              *_obj;
        OBJ_ACTION                                                  _objAction;

      public:
        AnimatedObject(ObjActionMap action, AnimatedModele *obj) : _action(action), _obj(obj)
          {
        	   if (this->_obj)
             this->_obj->setFrameLoop(0, 1);
             this->_objAction = STAND;
           }
        virtual           ~AnimatedObject (){}
          AnimatedModele *getObj()
          {
            return (this->_obj);
          }

      public:
        bool              execAction(OBJ_ACTION act)
        {
          this->_objAction = act;
          if (this->_obj != NULL && (this->_action.find(act) != this->_action.end()))
            {
              this->_obj->setFrameLoop(this->_action[act].x, this->_action[act].y);
              return (true);
            }
          return (false);
        }
        AnimatedModele    *getMesh() const
        {
          return (this->_obj);
        }
        ObjActionMap      getAction() const
        {
          return (this->_action);
        }
        OBJ_ACTION        getObjAction() const
        {
          return (this->_objAction);
        }
        int               getRangeAction(OBJ_ACTION act) const
        {
          int             range = this->_action.at(act).y - this->_action.at(act).x;
          return (range);
        }
        void              setAction(ObjActionMap action)
        {
          this->_action.clear();
          this->_action = action;
        }
        void              setModele(AnimatedModele *obj)
        {
          this->_obj = obj;
        }
    };

  struct          Rect
    {
      Pos<float>  topLeft;
      Pos<float>  bottomRight;

      Rect() {};
      Rect(Pos<float> tL, Pos<float> bR) : topLeft(tL), bottomRight(bR) {};
      virtual ~Rect() {};
    };

  class Kirrlicht
    {
      private:
        Device                                            *_device;
        VideoDriver                                       *_driver;
        SceneManager                                      *_sceneManager;
        Cursor                                            *_cursor;
        EventReceiver                                     _receiver;
        Gui::IGUIEnvironment                              *_env;
        Gui::IGUISkin                                     *_skin;
        Core::array<irr::SJoystickInfo>                   _joystickInfo;
        irrklang::ISoundEngine*                           _engine;

      private:
        std::unordered_map<std::string, Scene::IMesh *>     _mesh;
        std::unordered_map<std::string, Video::ITexture *>  _texture;
        std::unordered_map<irr::c8, std::string>            _alphabet;

      private:
        std::string                                       _name;
        Pos<int>                                          _screenSize;

      public:
        Kirrlicht();
        virtual ~Kirrlicht();

      public:
        bool                                start(const std::string &, const Pos<int> &);
        bool                                drop();

      public:
        bool                                loadAlphabet(const std::string &path = "");
        Scene::IMesh                        *loadStaticMesh(std::string const&);
        Video::ITexture                     *loadTexture(std::string const&);
        Scene::IMeshSceneNode               *addInScene(Scene::IMesh *,
                                                        Pos<float> const&,
                                                        Pos<float> const&,
                                                        std::string const&);
        Scene::IMeshSceneNode               *addModel(Pos<float>,
                                                      const std::string &,
                                                      const std::string &texture = "");
        AnimatedModele                      *addAnimatedModel(Pos<float>,
                                                               const std::string &,
                                                               const std::string &texture = "");
        bool                                displayString(std::string const&,
                                                          Pos<float> const&,
                                                          Pos<float> const&,
                                                          Core::vector3df const&,
                                                          std::vector<std::pair<std::string const, std::vector<kirr::Scene::IMeshSceneNode *>>> & vectToFill,
                                                          std::string const& texture = "");
        bool                                mouseEventInZone(GlobalEvent const& mevent,
                                                             Pos<float> const& topLeft,
                                                             Pos<float> const& bottomRight,
                                                             bool isClicking) const;
        bool                                makeTransition(Camera *camera,
                                                           Pos<float> const& posFinish);
        bool                                loadFonts(std::string const& filepath, std::string const& extension,
                                                      std::vector<int> const& fontsizes, std::unordered_map<int, Gui::IGUIFont *> & mapToFill);
        kirr::Gui::IGUIStaticText           *putText(Gui::IGUIFont *font, wchar_t const *str,
                                                     Core::rect<s32> const& pos,
                                                     Video::SColor const& color = Video::SColor(255, 255, 255, 255),
                                                     bool border = false, bool wordWrap = true,
                                                     Gui::IGUIElement *parent = 0, s32 id = -1, bool fillBg = false);
        bool                                moveObjectToPos(Scene::IMeshSceneNode *mesh, Core::vector3df const& toPos, std::string const& meshName, size_t const& turns);
        void                                centerCursor();
        Scene::IMesh                        *getMesh(const std::string &);
        Video::ITexture                     *getTexture(const std::string &);
        void                                adjustCursor();
        klang::ISound                       *add3dSound(Pos<float>, const std::string &, bool = false);
        klang::ISound                       *add2dSound(const std::string &, bool = false);
        void                                setListenerPos(Pos<float>, Pos<float>);
        bool                                addParticleEmitter(kirr::Scene::IParticleSystemSceneNode *ps,
                                                              float size = 1,
                                                              kirr::vector3df const& rotation = kirr::vector3df(0, 0, 0),
                                                              kirr::vector3df const& dimension = kirr::vector3df(5, 15, 0),
                                                              kirr::vector3df const& Pps = kirr::vector3df(1000, 2000, 0),
                                                              Core::aabbox3d<kirr::f32> const& box = Core::aabbox3d<kirr::f32>(-7,0,-7,7,7,7));
      Scene::IParticleSystemSceneNode     *addParticleSystem(const std::string &texture,
                                                              kirr::vector3df const& pos = kirr::vector3df(0, 0, 0),
                                                              kirr::vector3df const& scale = kirr::vector3df(2, 2, 2));

      public:
        Pos<int>                            getScreenSize() const;
        Device                              *getDevice();
        VideoDriver                         *getDriver();
        SceneManager                        *getSceneManager();
        Cursor                              *getCursor();
        EventReceiver                       &getEventReceiver();
        Gui::IGUIEnvironment                *getGUIEnvironment();
        Gui::IGUISkin                       *getSkin();
        JoystickList                        getJoystickInfo();

    };
}

#endif /* KIRRLICHT_HPP_ */
