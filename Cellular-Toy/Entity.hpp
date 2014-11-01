
#pragma once

#include <Rk/vector.hpp>

namespace Ce
{
  class Entity
  {
  public:
    v2f position;

    explicit Entity (v2f pos) :
      position (pos)
    { }

  };

}
