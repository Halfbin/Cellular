
#pragma once

#include "Window.hpp"

#include "InputSystem.hpp"

#include <Ce/MinWin.hpp>

namespace Ce
{
  struct Window::Impl
  {
    InputSystem in_sys;

    HWND window;

    bool closed;
    uint width, height;

    LRESULT handle_message (HWND, UINT, WPARAM, LPARAM);
    static LRESULT __stdcall dispatch_message (HWND, UINT, WPARAM, LPARAM);

    Impl (Rk::cstring_ref title);
    ~Impl ();

    WindowUpdate pump ();

  };

}
