/*
** Kirrlicht.cpp for Rendu in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Srcs/Commons/Kirrlicht
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Fri May 05 18:19:55 2017 cauvin-m
** Last update Sun Jun 18 19:50:15 2017 Marco
*/

#include "Kirrlicht.hpp"

kirr::Kirrlicht::Kirrlicht() : _receiver(EventReceiver(*this))
{

}

kirr::Kirrlicht::~Kirrlicht()
{
}

bool                                  kirr::Kirrlicht::drop()
{
  if (this->_device)
    {
      this->_device->closeDevice();
      this->_device->run();
      this->_device->drop();
    }
  return (true);
}

bool                                  kirr::Kirrlicht::start(const std::string &name, const Pos<int> &screenSize)
{
  this->_device = irr::createDevice (Video::EDT_OPENGL, Core::dimension2d<irr::u32>(screenSize.x, screenSize.y), 32, false, true, false, &this->_receiver);

  this->_name = name;
  this->_screenSize = screenSize;

  if (this->_device)
      {
        if (!(this->_driver = this->_device->getVideoDriver())
          || !(this->_sceneManager = this->_device->getSceneManager())
          || !(this->_cursor = this->_device->getCursorControl())
          || !(this->_env = this->_device->getGUIEnvironment())
          || !(this->_skin = this->_env->getSkin())
          || !(this->_engine = irrklang::createIrrKlangDevice()))
          return (false);
        this->getDevice()->setResizable(false);
        this->_device->activateJoysticks(this->_joystickInfo);
        this->_cursor->setPosition(Core::position2d<int>(screenSize.x / 2, screenSize.y / 2));
        return (true);
    }
  return (false);
}

kirr::Scene::IMesh                     *kirr::Kirrlicht::loadStaticMesh(std::string const& path)
{
  kirr::Scene::IMesh                   *model;

  if (this->_mesh.find(path) == this->_mesh.end())
    {
      model = this->_sceneManager->getMesh(path.c_str());
      if (model)
        this->_mesh.insert({path, model});
      return (model);
    }
  return (this->_mesh.at(path));
}

kirr::Video::ITexture                  *kirr::Kirrlicht::loadTexture(std::string const& path)
{
  kirr::Video::ITexture                *texture;

  if (this->_texture.find(path) == this->_texture.end())
    {
      texture = this->_driver->getTexture(path.c_str());
      if (texture)
        this->_texture.insert({path, texture});
      return (texture);
    }
  return (this->_texture.at(path));
}

bool    kirr::Kirrlicht::displayString(std::string const& str,
                                       Pos<float> const& p,
                                       Pos<float> const& r,
                                       Core::vector3df const& scale,
                                       std::vector<std::pair<std::string const, std::vector<kirr::Scene::IMeshSceneNode *>>> & vectToFill,
                                       std::string const& texture)
{
  irr::f32                            pos = p.x;
  Scene::IMeshSceneNode               *model;
  Scene::IMeshManipulator             *manip = this->_sceneManager->getMeshManipulator();
  Scene::IMesh                        *mesh;
  std::vector<kirr::Scene::IMeshSceneNode *>   listMeshs;

  for (size_t i = 0; i < str.size(); i++)
    {
      if (str[i] == ' ' || str[i] == '\t' || this->_alphabet.find(str[i]) == this->_alphabet.end())
        pos += 38 * scale.X;
      else
        {
          if (!(mesh = manip->createMeshUniquePrimitives(this->_mesh.at(this->_alphabet[str[i]]))))
            return (false);
          manip->scale(mesh, scale);
          if (!(model = this->addInScene(mesh, Pos<float>(pos, p.y, p.z), Pos<float>(r.x, r.y, r.z), texture)))
            return (false);
          listMeshs.push_back(model);
          mesh->drop();
          pos += model->getBoundingBox().MinEdge.X * -1 + 2;
        }
    }
  vectToFill.push_back(std::pair<std::string const, std::vector<kirr::Scene::IMeshSceneNode *>>(str, listMeshs));
  return (true);
}

kirr::Scene::IMeshSceneNode            *kirr::Kirrlicht::addInScene(Scene::IMesh *mesh,
                                                                    Pos<float> const& position,
                                                                    Pos<float> const& rotation,
                                                                    std::string const& texture)
{
  Scene::IMeshSceneNode          *model;

  if (this->_driver && this->_sceneManager && mesh)
    {
      if (!(model = this->_sceneManager->addMeshSceneNode(mesh)))
        return (nullptr);
      model->setPosition(irr::core::vector3df(position.x, position.y, position.z));
      model->setRotation(irr::core::vector3df(rotation.x, rotation.y, rotation.z));
      model->setMaterialFlag(Video::EMF_LIGHTING, false);
      if (texture != "" && this->_texture.find(texture) != this->_texture.end())
        model->setMaterialTexture(0, this->_texture.at(texture));
    }
  return (model);
}

kirr::Scene::IMeshSceneNode            *kirr::Kirrlicht::addModel(Pos<float> pos, const std::string &mesh, const std::string &texture)
{
  if (this->_mesh.find(mesh) == this->_mesh.end())
    return (nullptr);

  Scene::IMeshSceneNode                *model = 0;

  if (this->_driver && this->_sceneManager)
    {
      if (!(model = this->_sceneManager->addMeshSceneNode(this->_mesh.at(mesh))))
        return (nullptr);
      model->setPosition(irr::core::vector3df(pos.x, pos.y, pos.z));
      model->setMaterialFlag(Video::EMF_LIGHTING, false);
      if (texture != "" && this->_texture.find(texture) != this->_texture.end())
        model->setMaterialTexture(0, this->_texture.at(texture));
    }
  return (model);
}

irr::scene::IAnimatedMeshSceneNode    *kirr::Kirrlicht::addAnimatedModel(Pos<float> pos, const std::string &mesh, const std::string &texture)
{
  if (this->_mesh.find(mesh) == this->_mesh.end())
    return (NULL);
  irr::scene::IAnimatedMeshMD2*       model = static_cast<irr::scene::IAnimatedMeshMD2 *>(this->_mesh.at(mesh));

  if (model)
    {
      irr::scene::IAnimatedMeshSceneNode* Nmodel = this->_sceneManager->addAnimatedMeshSceneNode(model);

      if (Nmodel)
        {
          Nmodel->setPosition(irr::core::vector3df(pos.x, pos.y, pos.z));
          Nmodel->setFrameLoop(1, 0);
          Nmodel->setMaterialFlag(irr::video::EMF_LIGHTING, false);

          if (texture != "" && this->_texture.find(texture) != this->_texture.end())
            Nmodel->setMaterialTexture(0, this->_texture.at(texture));
          return (Nmodel);
        }
    }
  return (NULL);
}

bool                                  kirr::Kirrlicht::makeTransition(Camera *camera,
                                                                      Pos<float> const& posFinish)
{
  int tmpX = (posFinish.x - camera->getPosition().X) / 10;
  int tmpY = (posFinish.y - camera->getPosition().Y) / 10;
  for (int x = camera->getPosition().X, y = camera->getPosition().Y; x != posFinish.x || y != posFinish.y; x += tmpX, y += tmpY)
    {
      auto t1 = std::chrono::high_resolution_clock::now();
      camera->setPosition(irr::core::vector3df(x, y, camera->getPosition().Z));
      camera->setTarget(irr::core::vector3df(x, y, camera->getTarget().Z));
      this->getDriver()->beginScene(true, true, irr::video::SColor(255, 200, 200, 200));
      this->getSceneManager()->drawAll();
      this->getDriver()->endScene();
      std::chrono::duration<double, std::milli> fp_ms;
      while ((fp_ms = std::chrono::high_resolution_clock::now() - t1).count() < 2);
    }
  this->getEventReceiver().resetEvent();
  camera->setPosition(Core::vector3df(posFinish.x, posFinish.y, camera->getPosition().Z));
  camera->setTarget(Core::vector3df(posFinish.x, posFinish.y, camera->getTarget().Z));
  return (true);
}

bool                                  kirr::Kirrlicht::mouseEventInZone(GlobalEvent const& mevent,
                                                                        Pos<float> const& topLeft,
                                                                        Pos<float> const& bottomRight,
                                                                        bool isClicking) const
{
  return (mevent.getCursorPosition().x >= topLeft.x && mevent.getCursorPosition().x < bottomRight.x &&
          mevent.getCursorPosition().y >= topLeft.y && mevent.getCursorPosition().y < bottomRight.y &&
          ((isClicking) ? (mevent.pressTab.at(ALL_KEY_CODE::KEY_LBUTTON)) : (true)));
}

bool                                  kirr::Kirrlicht::loadAlphabet(const std::string &path)
{
  std::string                         my_path = "./Client/Assets/";

  if (path != "")
    my_path = path;

  std::string                         letter(my_path + "Letter_A.stl");

  for (int i = 0; i < 26; i++)
    {
      if (!this->loadStaticMesh(letter))
        return (false);
      this->_alphabet[letter[letter.size() - 5]] = letter;
      letter[letter.size() - 5] += 1;
    }
  letter = my_path + "0.stl";
  for (int i = 0; i < 10; i++)
    {
      if (!this->loadStaticMesh(letter))
      return (false);
      this->_alphabet[letter[letter.size() - 5]] = letter;
      letter[letter.size() - 5] += 1;
    }
  return (true);
}

bool                                  kirr::Kirrlicht::loadFonts(std::string const& filepath, std::string const& extension,
                                                                 std::vector<int> const& fontsizes, std::unordered_map<int, Gui::IGUIFont *> & mapToFill)
{
  Gui::IGUIFont *font;

  for (size_t i = 0; i < fontsizes.size(); i++)
  {
    if (utils::fileExist(filepath + std::to_string(fontsizes[i]) + extension) || this->_env)
    {
      if ((font = this->_env->getFont(std::string(filepath + std::to_string(fontsizes[i]) + extension).c_str())))
        mapToFill[fontsizes[i]] = font;
      else
        return (false);
    }
    else
      return (false);
  }
  return (true);
}

kirr::Gui::IGUIStaticText       *kirr::Kirrlicht::putText(kirr::Gui::IGUIFont *font, wchar_t const *str,
                                                          kirr::Core::rect<s32> const& pos, kirr::Video::SColor const& color,
                                                          bool border, bool wordWrap,
                                                          kirr::Gui::IGUIElement *parent, kirr::s32 id, bool fillBg)
{
  Gui::IGUIStaticText *text = this->_env->addStaticText(str, pos, border, wordWrap, parent, id, fillBg);

  if (!text)
    return (nullptr);
  text->setOverrideFont(font);
  text->setOverrideColor(color);
  return (text);
}

bool            kirr::Kirrlicht::moveObjectToPos(kirr::Scene::IMeshSceneNode *mesh, kirr::Core::vector3df const& toPos, std::string const& meshName, size_t const& turns)
{
  static std::unordered_map<std::string, std::pair<kirr::Core::vector3df, size_t>> movingMeshs;

  if (movingMeshs.find(meshName) == movingMeshs.end())
    movingMeshs[meshName] = std::make_pair(kirr::Core::vector3df((toPos.X - mesh->getPosition().X) / turns, (toPos.Y - mesh->getPosition().Y) / turns , (toPos.Z - mesh->getPosition().Z) / turns), turns);
  mesh->setPosition(mesh->getPosition() + movingMeshs[meshName].first);
  movingMeshs[meshName].second -= 1;
  if (!movingMeshs[meshName].second)
  {
    movingMeshs.erase(meshName);
    mesh->setPosition(toPos);
  }
  return (true);
}

void                             kirr::Kirrlicht::centerCursor()
{
  this->_cursor->setPosition(irr::core::position2d<int>(this->_screenSize.x / 2, this->_screenSize.y / 2));
}

void                            kirr::Kirrlicht::adjustCursor() {
  static int counter = 0;

  counter++;
  if (counter >= 5) {
    this->centerCursor();
    counter = 0;
  }
}

kirr::Pos<int>                   kirr::Kirrlicht::getScreenSize() const
{
  return (this->_screenSize);
}

kirr::Device                     *kirr::Kirrlicht::getDevice()
{
  return (this->_device);
}

kirr::VideoDriver                *kirr::Kirrlicht::getDriver()
{
  return (this->_driver);
}

kirr::SceneManager               *kirr::Kirrlicht::getSceneManager()
{
  return (this->_sceneManager);
}

kirr::Cursor                     *kirr::Kirrlicht::getCursor()
{
  return (this->_cursor);
}

kirr::EventReceiver              &kirr::Kirrlicht::getEventReceiver()
{
  return (this->_receiver);
}

kirr::Gui::IGUIEnvironment       *kirr::Kirrlicht::getGUIEnvironment()
{
  return (this->_env);
}

kirr::Gui::IGUISkin              *kirr::Kirrlicht::getSkin()
{
  return (this->_skin);
}

kirr::JoystickList               kirr::Kirrlicht::getJoystickInfo()
{
  return (this->_joystickInfo);
}

kirr::Pos<int>    kirr::GlobalEvent::getCursorPosition() const
{
  Pos<int> back(this->kirrlicht.getCursor()->getPosition().X, this->kirrlicht.getCursor()->getPosition().Y, 0);
  return (back);
}

kirr::Pos<float>    kirr::GlobalEvent::getRCursorPosition()
{
  Pos<float>  pos(this->getCursorPosition().x, this->getCursorPosition().y, 0);
  Pos<float>  size(this->kirrlicht.getScreenSize().x, this->kirrlicht.getScreenSize().y, 0);
  Pos<float>  back((pos.x - (size.x / 2)) / (size.x / 2) * -1, (pos.y - (size.y / 2)) / (size.y / 2) * -1, 0);
  return (back);
}

kirr::Pos<float>      kirr::GlobalEvent::getRJoystickPosition1() const
{
  if (this->joystickState.Joystick == 42)
    return (0);
  const irr::SEvent::SJoystickEvent &joystickState = this->joystickState;
  const float DEAD_ZONE = 0.05f;

  float x = static_cast<float>(joystickState.Axis[irr::SEvent::SJoystickEvent::AXIS_X]) / 32767.f;
  if (std::fabs(x) < DEAD_ZONE || std::fabs(x) > 1)
    x = 0.f;
  float y = static_cast<float>(joystickState.Axis[irr::SEvent::SJoystickEvent::AXIS_Y]) / -32767.f;
  if (std::fabs(y) < DEAD_ZONE || std::fabs(y) > 1)
    y = 0.f;
  return (Pos<float>(x * -0.05, y * 0.05, 0));
}

kirr::Pos<float>      kirr::GlobalEvent::getRJoystickPosition2() const
{
  if (this->joystickState.Joystick == 42)
    return (0);
  const irr::SEvent::SJoystickEvent &joystickState = this->joystickState;
  const float DEAD_ZONE = 0.05f;

  float x = static_cast<float>(joystickState.Axis[irr::SEvent::SJoystickEvent::AXIS_Z]) / 32767.f;
  if (std::fabs(x) < DEAD_ZONE)
    x = 0.f;
  float y = static_cast<float>(joystickState.Axis[irr::SEvent::SJoystickEvent::AXIS_R]) / -32767.f;
  if (std::fabs(y) < DEAD_ZONE)
    y = 0.f;
  return Pos<float>(x * -0.15, y * 0.15, 0);
}

int                   kirr::GlobalEvent::getJoystickComputer() const
{
  int                 back = -1;

  for (size_t x = 0; x < kirrlicht.getJoystickInfo().size(); x++)
    {
      back = x;
      if (kirrlicht.getJoystickInfo()[x].Name == "Sony PLAYSTATION(R)3 Controller")
        return (back);
    }
  return (-1);
}

kirr::Scene::IMesh    *kirr::Kirrlicht::getMesh(const std::string &mesh)
{
  if (this->_mesh.find(mesh) != this->_mesh.end())
    return (this->_mesh.at(mesh));
  return (nullptr);
}

kirr::Video::ITexture *kirr::Kirrlicht::getTexture(const std::string &texture)
{
  if (this->_texture.find(texture) != this->_texture.end())
    return (this->_texture.at(texture));
  return (nullptr);
}

kirr::klang::ISound   *kirr::Kirrlicht::add3dSound(Pos<float> pos, const std::string &path, bool loop)
{
  irrklang::ISound    *sound = this->_engine->play3D(path.c_str(), irrklang::vec3df(pos.x, pos.y, pos.z), loop, true, true);

  if (sound)
    return (sound);
  return (nullptr);
}

kirr::klang::ISound   *kirr::Kirrlicht::add2dSound(const std::string &path, bool loop)
{
  irrklang::ISound    *sound = this->_engine->play2D(path.c_str(), loop, true);

  if (sound)
    return (sound);
  return (nullptr);
}

void                  kirr::Kirrlicht::setListenerPos(Pos<float> pos, Pos<float> targ)
{
  irrklang::vec3df position(pos.x, pos.y, pos.z);
  irrklang::vec3df lookDirection(targ.x, targ.y, targ.z);
  irrklang::vec3df velPerSecond(0,0,0);
  irrklang::vec3df upVector(0,1,0);

  this->_engine->setListenerPosition(position, lookDirection, velPerSecond, upVector);
}

bool                                  kirr::Kirrlicht::addParticleEmitter(kirr::Scene::IParticleSystemSceneNode *ps,
                                                          float size,
                                                          kirr::vector3df const& rotation,
                                                          kirr::vector3df const& dimension,
                                                          kirr::vector3df const& Pps,
                                                          kirr::Core::aabbox3d<kirr::f32> const& box)
{
  kirr::Scene::IParticleEmitter       *em;

  if (ps == nullptr)
    return (false);

  em = ps->createBoxEmitter(
    box,
    rotation,
    Pps.X, Pps.Y,
    kirr::Video::SColor(0,255,255,255),
    kirr::Video::SColor(0,255,255,255),
    size * 10, size * 10, 0,
    kirr::Core::dimension2df(dimension.X, dimension.X),
    kirr::Core::dimension2df(dimension.Y, dimension.Y));
  if (em == nullptr)
    return (false);
  ps->setEmitter(em);
  em->drop();
  return (true);
}

kirr::Scene::IParticleSystemSceneNode *kirr::Kirrlicht::addParticleSystem(const std::string &texture, kirr::vector3df const& pos, kirr::vector3df const& scale)
{
  kirr::Scene::IParticleSystemSceneNode *ps = this->getSceneManager()->addParticleSystemSceneNode(false);
  if (ps)
    {
      ps->setPosition(pos);
      ps->setScale(scale);
      ps->setMaterialFlag(kirr::Video::EMF_LIGHTING, LIGHT);
      ps->setMaterialFlag(kirr::Video::EMF_ZWRITE_ENABLE, false);
      ps->setMaterialTexture(0, this->getTexture(texture));
      ps->setMaterialType(kirr::Video::EMT_TRANSPARENT_ADD_COLOR);
      return (ps);
    }
  return (nullptr);
}
