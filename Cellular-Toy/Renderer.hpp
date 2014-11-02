
#pragma once

#include "RenderItem.hpp"

#include <vector>

namespace Ce
{
  class Renderer
  {
    std::vector <RenderItem> items;

  public:
    void begin_frame ();
    void end_frame ();

    void add_item (RenderItem item);

  };

}
