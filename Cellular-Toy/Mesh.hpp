
#pragma once

#include <Rk/types.hpp>

namespace Ce
{
  struct Geom
  {
    uint vao;
    uint index_type;
    uint prim_type;
  };

  struct Material
  {

  };

  struct Mesh
  {
    Geom*     geom;
    Material* material;
    uint      vertex_base;
    uint      vertex_max;
    uint      index_offset;
    uint      index_count;
  };

  struct MeshRange
  {
    Mesh* first;
    uint  count;
  };

}
