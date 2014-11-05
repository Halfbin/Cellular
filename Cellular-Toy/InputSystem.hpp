
#pragma once

#include "MinWin.hpp"
#include "Input.hpp"

#include <vector>

namespace Ce
{
  typedef std::vector <Event> Events;

  class InputSystem
  {
    Keyboard keyboard;
    Mouse    mouse;
    bool     focus,
             mouse_looking;

    Events events;

    static Events decode_raw_mouse (RAWMOUSE, v2i prev_pointer);
    static Event  decode_raw_key   (RAWKEYBOARD);
    void on_raw_input (LPARAM);

    void enter_mouse_look (HWND);
    void leave_mouse_look (HWND);

    void get_focus  (HWND);
    void lose_focus (HWND);

  public:
    InputSystem ();

    void    begin_pump ();
    LRESULT handle_input (HWND, UINT, WPARAM, LPARAM);
    Input   end_pump ();

  };

}
