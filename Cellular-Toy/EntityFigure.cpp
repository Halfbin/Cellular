
#include "EntityFigure.hpp"

#include <catch.hpp>

namespace Ce
{
  auto NullFigure::render (FigureParams) const
    -> RenderItem
  {
    MeshRange meshes { nullptr, 0 };
    return RenderItem { meshes, 0, v2f {0,0} };
  }

}
