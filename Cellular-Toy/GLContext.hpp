
#pragma once

#include <Rk/types.hpp>

namespace Ce
{
  class GLContext
  {
    struct Impl;
    Impl* impl;

  public:
    GLContext (uptr target);
    ~GLContext ();

    void flip ();

  };

}
