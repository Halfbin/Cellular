
#include "Renderer.hpp"

#include <GL/glew.h>

#include "GLError.hpp"

namespace Ce
{
  void Renderer::render_frame (v2i size, RenderRange range)
  {
    glViewport (0, 0, size.x, size.y);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto item : range)
    {
      // ... render item
    }
  }

}
