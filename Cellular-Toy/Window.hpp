
#pragma once

#include <Rk/string_ref.hpp>

#include "Input.hpp"

namespace Ce
{
  struct WindowUpdate
  {
    WindowUpdate (bool closed, v2i size, Input input) :
      closed (closed),
      size   (size),
      input  (input)
    { }

    bool  closed;
    v2i   size;
    Input input;

  };

  class Window
  {
    struct Impl;
    Impl* impl;

  public:
    Window (Rk::cstring_ref title);
    ~Window ();

    uptr handle () const;

    WindowUpdate pump ();

    void show ();

  };

}
