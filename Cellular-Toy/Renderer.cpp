
#include "Renderer.hpp"

#include <iostream>

namespace Ce
{
  void Renderer::begin_frame ()
  {
    items.clear ();
  }
  
  void Renderer::end_frame ()
  {
    for (const auto& item : items)
      std::cout << "(" << item.position.x << ", " << item.position.y << ")\n";
  }

  void Renderer::add_item (RenderItem item)
  {
    items.push_back (item);
  }

}
