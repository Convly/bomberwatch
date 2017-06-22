/*
** EventReceiver.cpp for Rendu in /home/cauvin_m/Rendu/cpp_indie_studio/Client/Bin/Srcs/Commons/EventReceiver
**
** Made by cauvin-m
** Login   <cauvin_m@epitech.net>
**
** Started on  Sat May 06 01:27:59 2017 cauvin-m
** Last update Thu Jun 15 02:52:52 2017 Marco
*/

#include <iostream>
#include "Kirrlicht.hpp"

kirr::EventReceiver::EventReceiver(Kirrlicht &k) : _event(GlobalEvent(k)), _kirrlicht(k)
{
}

kirr::EventReceiver::~EventReceiver()
{
}

bool                          kirr::EventReceiver::OnEvent(irr::SEvent const& event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      this->_event.keyTab[static_cast<kirr::ALL_KEY_CODE>(event.KeyInput.Key)] = true;
      this->_event.pressTab[static_cast<kirr::ALL_KEY_CODE>(event.KeyInput.Key)] = event.KeyInput.PressedDown;
      if (event.KeyInput.Shift)
        this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_SHIFT] = event.KeyInput.PressedDown;
    }
  if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
      switch (event.MouseInput.Event)
        {
          case irr::EMIE_LMOUSE_PRESSED_DOWN:
            this->_event.keyTab[kirr::ALL_KEY_CODE::KEY_LBUTTON] = true;
            this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LBUTTON] = true;
            break;

          case irr::EMIE_LMOUSE_LEFT_UP:
            this->_event.keyTab[kirr::ALL_KEY_CODE::KEY_LBUTTON] = true;
            this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LBUTTON] = false;
            break;

          case irr::EMIE_RMOUSE_PRESSED_DOWN:
            this->_event.keyTab[kirr::ALL_KEY_CODE::KEY_RBUTTON] = true;
            this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RBUTTON] = true;
            break;

          case irr::EMIE_RMOUSE_LEFT_UP:
            this->_event.keyTab[kirr::ALL_KEY_CODE::KEY_RBUTTON] = true;
            this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RBUTTON] = false;
            break;

          case irr::EMIE_MOUSE_WHEEL:
            if (event.MouseInput.Wheel > 0)
              {
                this->_event.keyTab[kirr::ALL_KEY_CODE::KEY_SCROLL_UP] = true;
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_SCROLL_UP] = true;
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_SCROLL_DOWN] = false;
              }
            else
              {
                this->_event.keyTab[kirr::ALL_KEY_CODE::KEY_SCROLL_DOWN] = true;
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_SCROLL_DOWN] = true;
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_SCROLL_UP] = false;
              }
            break;
          default:
            break;
        }
    }
  if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT)
    {
      if (event.JoystickEvent.Joystick == this->_event.getJoystickComputer())
        {
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_UP] = false;
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_DOWN] = false;
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_LEFT] = false;
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_RIGHT] = false;
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_LEFT] = false;
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_UP] = false;
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_DOWN] = false;
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_LEFT] = false;
          this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_RIGHT] = false;

          const float DEAD_ZONE = 0.05f;

          float x = static_cast<float>(event.JoystickEvent.Axis[irr::SEvent::SJoystickEvent::AXIS_Z]) / 32767.f;
          if (fabs(x) < DEAD_ZONE || fabs(x) > 1)
            x = 0.f;
          float y = static_cast<float>(event.JoystickEvent.Axis[irr::SEvent::SJoystickEvent::AXIS_R]) / -32767.f;
          if (fabs(y) < DEAD_ZONE || fabs(y) > 1)
            y = 0.f;

          if (x > 0)
            {
              if (y > x)
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_UP] = true;
              else if (fabs(y) > x)
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_DOWN] = true;
              else
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_RIGHT] = true;
            }
          else if (x < 0)
            {
              if (y > fabs(x))
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_UP] = true;
              else if (fabs(y) > fabs(x))
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_DOWN] = true;
              else
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_RCONTROLLER_LEFT] = true;
            }

          x = static_cast<float>(event.JoystickEvent.Axis[irr::SEvent::SJoystickEvent::AXIS_X]) / 32767.f;
          if (fabs(x) < DEAD_ZONE || fabs(x) > 1)
            x = 0.f;
          y = static_cast<float>(event.JoystickEvent.Axis[irr::SEvent::SJoystickEvent::AXIS_Y]) / -32767.f;
          if (fabs(y) < DEAD_ZONE || fabs(y) > 1)
            y = 0.f;

          if (x > 0)
            {
              if (y > x)
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_UP] = true;
              else if (fabs(y) > x)
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_DOWN] = true;
              else
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_RIGHT] = true;
            }
          else if (x < 0)
            {
              if (y > fabs(x))
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_UP] = true;
              else if (fabs(y) > fabs(x))
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_DOWN] = true;
              else
                this->_event.pressTab[kirr::ALL_KEY_CODE::KEY_LCONTROLLER_LEFT] = true;
            }

            size_t value[] = {1, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
            ALL_KEY_CODE key[] = {ALL_KEY_CODE::KEY_CONTROLLER_SELECT,
              ALL_KEY_CODE::KEY_CONTROLLER_START,
              ALL_KEY_CODE::KEY_CONTROLLER_UP,
              ALL_KEY_CODE::KEY_CONTROLLER_RIGHT,
              ALL_KEY_CODE::KEY_CONTROLLER_DOWN,
              ALL_KEY_CODE::KEY_CONTROLLER_LEFT,
              ALL_KEY_CODE::KEY_CONTROLLER_L2,
              ALL_KEY_CODE::KEY_CONTROLLER_R2,
              ALL_KEY_CODE::KEY_CONTROLLER_L1,
              ALL_KEY_CODE::KEY_CONTROLLER_R1,
              ALL_KEY_CODE::KEY_CONTROLLER_TRIANGLE,
              ALL_KEY_CODE::KEY_CONTROLLER_ROUND,
              ALL_KEY_CODE::KEY_CONTROLLER_X,
              ALL_KEY_CODE::KEY_CONTROLLER_SQUARE,
              ALL_KEY_CODE::KEY_CONTROLLER_LOG
            };

            for (int i = 0; i < 15; i++)
              {
                this->_event.pressTab[key[i]] = false;
                if (value[i] == event.JoystickEvent.ButtonStates)
                  this->_event.pressTab[key[i]] = true;
              }
          this->_event.joystickState = event.JoystickEvent;
        }
    }
  return (false);
}

kirr::GlobalEvent &   kirr::EventReceiver::getEvent()
{
  return (this->_event);
}

void                          kirr::EventReceiver::resetEvent()
{
  this->_event = GlobalEvent(this->_kirrlicht);
}

bool                          kirr::EventReceiver::isKeyDown(kirr::ALL_KEY_CODE k) const
{
  return (this->_event.pressTab.at(k));
}

bool                          kirr::EventReceiver::isKey(kirr::ALL_KEY_CODE k) const
{
  return (this->_event.keyTab.at(k));
}
