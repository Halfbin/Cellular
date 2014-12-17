
#include "Renderer.hpp"

#include <GL/glew.h>

#include "GLError.hpp"

namespace Ce
{
  namespace
  {
    struct SharedUniforms
    {
      mat4f world_to_eye;
      mat4f eye_to_clip;

      SharedUniforms (const FrameParams& p) :
        world_to_eye (p.world_to_eye),
        eye_to_clip  (p.eye_to_clip)
      { }

    };

  }

  struct Renderer::Impl
  {
    uint shared_ubo;

    Impl ();
    ~Impl ();

  };

  Renderer::Impl::Impl ()
  {
    glGenBuffers (1, &shared_ubo);
    glBindBuffer (GL_UNIFORM_BUFFER, shared_ubo);
    glBufferData (GL_UNIFORM_BUFFER, sizeof (SharedUniforms), nullptr, GL_STREAM_DRAW);
  }

  Renderer::Impl::~Impl ()
  {
    glDeleteBuffers (1, &shared_ubo);
  }

  Renderer::Renderer () :
    impl (new Impl)
  { }

  Renderer::~Renderer ()
  {
    delete impl;
  }

  void Renderer::render_frame (FrameParams params, RenderRange range)
  {
    glViewport (0, 0, params.frame_size.x, params.frame_size.y);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // place matrices into shared ubo
    SharedUniforms shared_unis (params);
    glBindBuffer (GL_UNIFORM_BUFFER, impl->shared_ubo);
    glBufferData (GL_UNIFORM_BUFFER, sizeof (shared_unis), &shared_unis, GL_STREAM_DRAW);

    for (auto item : range)
    {
      glUseProgram (item.program);
      // ... render item
    }
  }

}
