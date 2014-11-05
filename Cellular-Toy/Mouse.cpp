
#include "InputSystem.hpp"

#include <catch.hpp>

namespace Ce
{
  Events InputSystem::decode_raw_mouse (RAWMOUSE raw, v2i prev_pointer)
  {
    Events events;

    // Decode button transitions
    ushort raw_buttons = raw.usButtonFlags;
    const ushort down_flag = 1, up_flag  = 2;

    for (int i = 0; i != 5; i++)
    {
      auto transition = (raw_buttons >> (2 * i)) & 3;
      bool down = (transition & down_flag) != 0;
      if (transition)
        events.push_back (ButtonEvent (Button (i), down));
    }

    // Decode wheel motion
    if (raw_buttons & 0x400)
    {
      auto motion = i16 (raw.usButtonData) * 1.0f;
      events.push_back (WheelEvent (motion));
    }

    // Decode pointer motion
    v2i pointer_motion = { raw.lLastX, raw.lLastY };

    if (raw.usFlags & MOUSE_MOVE_ABSOLUTE)
      pointer_motion -= prev_pointer;

    if (pointer_motion != v2i {0, 0})
      events.push_back (PointerEvent (pointer_motion));

    // Done
    return events;
  }

  Mouse::Mouse () :
    pointer {0, 0}
  {
    for (auto& b : buttons)
      b = false;
  }

  Mouse Mouse::react (Event ev) const
  {
    Mouse new_mouse (*this);
    if (auto bev = ev.ptr<ButtonEvent> ())
      new_mouse.buttons [uint (bev->button)] = bev->down;
    else if (auto pev = ev.ptr<PointerEvent> ())
      new_mouse.pointer += pev->motion;
    return new_mouse;
  }

  TEST_CASE ("Mouse") {
    Mouse mouse;

    SECTION ("reacts to button transitions") {
      auto new_mouse = mouse.react (ButtonEvent (Button::left, true));
      REQUIRE (new_mouse.buttons [uint (Button::left)] == true);
    }

    SECTION ("responds to pointer motion") {
      auto new_mouse = mouse.react (PointerEvent (v2i{-12, 30}));
      REQUIRE (new_mouse.pointer == v2i (-12, 30));
    }
  }

}
