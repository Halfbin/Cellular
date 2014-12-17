
#pragma once

#include "RenderItem.hpp"

namespace Ce
{
  struct FigureParams
  {
    v2f pos;
  };

  struct EntityFigure
  {
    virtual RenderItem render (FigureParams) const = 0;

  };

  struct NullFigure :
    EntityFigure
  {
    RenderItem render (FigureParams) const;

  };

  struct MeshFigure :
    EntityFigure
  {
    MeshRange meshes;

    MeshFigure (MeshRange meshes) :
      meshes (meshes)
    { }

    RenderItem render (FigureParams) const;

  };

}
