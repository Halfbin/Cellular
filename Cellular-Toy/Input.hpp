
#pragma once

#include "EventQueue.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace Ce
{
  struct Input
  {
    Input (EventQueue events, Keyboard keyboard, Mouse mouse) :
      events   (events),
      keyboard (keyboard),
      mouse    (mouse)
    { }

    EventQueue events;
    Keyboard   keyboard;
    Mouse      mouse;
  };

}
