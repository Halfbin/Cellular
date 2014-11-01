
#pragma once

#include <Rk/vector.hpp>

namespace Ce
{
  class RenderItem
  {
  public:
    v2f position;

    explicit RenderItem (v2f pos) :
      position (pos)
    { }

  };

}
