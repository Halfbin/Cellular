
#pragma once

#include "Mesh.hpp"

#include <Rk/vector.hpp>

namespace Ce
{
  class RenderItem
  {
  public:
    MeshRange meshes;
    uint      program;
    v2f       position;

  };

}
