
#pragma once

#include "Event.hpp"

#include <Rk/vector.hpp>

namespace Ce
{
  enum class Button : u8
  {
    left, middle, right, ex_4, ex_5,
    count
  };

  struct ButtonEvent : public EventBase <EventTag::button>
  {
    Button button; bool down;
    ButtonEvent (Button button, bool down) : button (button), down (down) { }
    ButtonEvent () = default;
  };

  struct PointerEvent : public EventBase <EventTag::pointer>
  {
    v2i motion;
    PointerEvent (v2i motion) : motion (motion) { }
    PointerEvent () = default;
  };

  struct WheelEvent : public EventBase <EventTag::wheel>
  {
    float motion;
    WheelEvent (float motion) : motion (motion) { }
    WheelEvent () = default;
  };

  struct Mouse
  {
    bool buttons [uint (Button::count)];
    v2i  pointer;
    Mouse ();
    Mouse react (Event) const;
  };

}
