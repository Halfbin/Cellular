
#include "Renderer.hpp"

#include <iostream>

namespace Ce
{
  void Renderer::render_items (RenderRange range)
  {
    for (auto item : range)
      std::cout << "(" << item.position.x << ", " << item.position.y << ")\n";
  }

}
