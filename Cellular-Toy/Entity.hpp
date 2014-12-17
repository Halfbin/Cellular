
#pragma once

#include <Rk/vector.hpp>
#include "EntityFigure.hpp"

namespace Ce
{
  class Entity
  {
    EntityFigure* figure;

    FigureParams figure_params () const
    {
      return FigureParams { position };
    }

  public:
    v2f position;

    Entity (EntityFigure* figure, v2f position) :
      figure   (figure),
      position (position)
    { }

    RenderItem render () const
    {
      return figure->render (figure_params ());
    }

  };

}
