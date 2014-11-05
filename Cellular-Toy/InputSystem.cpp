
#include "InputSystem.hpp"

#include <Rk/exception.hpp>

namespace Ce
{
  void InputSystem::on_raw_input (LPARAM lp)
  {
    RAWINPUT raw = { };
    uint raw_len = sizeof (raw);
    auto result = GetRawInputData ((HRAWINPUT) lp, RID_INPUT, &raw, &raw_len, sizeof (RAWINPUTHEADER));
    if (result == -1)
      return;

    // Shouldn't get anything we didn't subscribe to anyway
    if (raw.header.dwType == RIM_TYPEMOUSE)
    {
      auto mouse_events = decode_raw_mouse (raw.data.mouse, mouse.pointer);
      for (auto ev : mouse_events)
        mouse = mouse.react (ev); // integrate the events into the mouse state
      events.insert (events.end (), mouse_events.begin (), mouse_events.end ());
    }
    else if (raw.header.dwType == RIM_TYPEKEYBOARD)
    {
      auto key_event = decode_raw_key (raw.data.keyboard);
      keyboard = keyboard.react (key_event);
      events.push_back (key_event);
    }
  }

  void InputSystem::enter_mouse_look (HWND target)
  {
    if (mouse_looking)
      return;

    // Register for raw mouse input, pre-empting WM_* mouse messages
    RAWINPUTDEVICE mouse { 0x01, 0x02, RIDEV_NOLEGACY, target };
    auto ok = RegisterRawInputDevices (&mouse, 1, sizeof (mouse));
    if (!ok)
      throw Rk::win_error ("RegisterRawInputDevices failed");

    // Make sure the cursor really is hidden
    while (ShowCursor (false) >= 0);

    // Constrain the pointer to the client area
    RECT area;
    GetClientRect ((HWND) target, &area);
    ClipCursor (&area);

    mouse_looking = true;
  }

  void InputSystem::leave_mouse_look (HWND target)
  {
    if (!mouse_looking)
      return;

    // Deregister from raw mouse input; WM_* mouse messages will resume
    RAWINPUTDEVICE mouse { 0x01, 0x02, RIDEV_REMOVE, nullptr };
    RegisterRawInputDevices (&mouse, 1, sizeof (mouse));

    // Make sure the cursor really is visible
    while (ShowCursor (true) < 0);

    // Stop constraining the pointer
    ClipCursor (nullptr);

    mouse_looking = false;
  }

  void InputSystem::get_focus (HWND target)
  {
    RAWINPUTDEVICE keyboard { 0x01, 0x06, RIDEV_APPKEYS | RIDEV_NOLEGACY, target };
    auto ok = RegisterRawInputDevices (&keyboard, 1, sizeof (keyboard));
    if (!ok)
      throw Rk::win_error ("RegisterRawInputDevices failed");

    focus = true;
  }

  void InputSystem::lose_focus (HWND target)
  {
    // If we lose focus, we shouldn't hang on to the mouse
    leave_mouse_look (target);

    RAWINPUTDEVICE keyboard { 0x01, 0x06, RIDEV_REMOVE, nullptr };
    RegisterRawInputDevices (&keyboard, 1, sizeof (keyboard));

    focus = false;
  }

  LRESULT InputSystem::handle_input (HWND src, UINT msg, WPARAM wp, LPARAM lp)
  {
    switch (msg)
    {
      case WM_SIZE:
        if (mouse_looking)
        {
          POINT area [2] { { 0, 0 }, { } };
          ClientToScreen ((HWND) src, area);
          area [1].x = area [0].x + LOWORD (lp);
          area [1].y = area [0].y + HIWORD (lp);
          ClipCursor ((const RECT*) area);
        }
      return 0;

      case WM_SETFOCUS:  get_focus  (src); return 0;
      case WM_KILLFOCUS: lose_focus (src); return 0;

      case WM_LBUTTONDOWN:
        mouse = mouse.react (ButtonEvent (Button::left, true));
      return 0;

      case WM_LBUTTONUP:
        mouse = mouse.react (ButtonEvent (Button::left, false));
      return 0;

      case WM_MBUTTONDOWN:
        mouse = mouse.react (ButtonEvent (Button::middle, true ));
      return 0;

      case WM_MBUTTONUP:
        mouse = mouse.react (ButtonEvent (Button::middle, false));
      return 0;

      case WM_RBUTTONDOWN:
        mouse = mouse.react (ButtonEvent (Button::right, true ));
      return 0;

      case WM_RBUTTONUP:
        mouse = mouse.react (ButtonEvent (Button::right, false));
      return 0;

      case WM_MOUSEWHEEL:
        mouse = mouse.react (WheelEvent (1.0f * (i16) HIWORD (wp)));
      return 0;

      case WM_INPUT:
        if (!focus || wp == RIM_INPUTSINK)
          break;

        on_raw_input (lp);
      return 0;

      default:;
    }

    return DefWindowProcW ((HWND) src, msg, wp, lp);
  }

  void InputSystem::begin_pump ()
  {
    events.clear ();
  }

  Input InputSystem::end_pump ()
  {
    auto queue = EventQueue (events.data (), events.size ());
    return Input (queue, keyboard, mouse);
  }

  InputSystem::InputSystem () :
    focus         (false),
    mouse_looking (false)
  { }

}
