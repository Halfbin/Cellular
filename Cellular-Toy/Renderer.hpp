
#pragma once

#include <Rk/matrix.hpp>

#include "RenderItem.hpp"

namespace Ce
{
  struct FrameParams
  {
    v2i frame_size;
    m4f world_to_eye;
    m4f eye_to_clip;
  };

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
    struct Impl;
    Impl* impl;

  public:
    Renderer ();
    ~Renderer ();

    void render_frame (FrameParams, RenderRange);

  };

}
