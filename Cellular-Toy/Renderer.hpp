
#pragma once

#include "RenderItem.hpp"

namespace Ce
{
  class RenderRange
  {
    const RenderItem* begin_;
    const RenderItem* end_;

  public:
    RenderRange (const RenderItem* first, size_t count) :
      begin_ (first),
      end_   (first + count)
    { }

    const RenderItem* begin () const { return begin_; }
    const RenderItem* end   () const { return end_; }

  };

  class Renderer
  {
  public:
    void render_items (RenderRange);

  };

}
