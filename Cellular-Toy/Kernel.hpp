
#pragma once

#include <vector>

#include "EntityRenderer.hpp"
#include "GLContext.hpp"
#include "Renderer.hpp"
#include "Syncer.hpp"
#include "Window.hpp"
#include "Clock.hpp"

namespace Ce
{
  class Kernel
  {
    // Other cells
    Window&    window;
    GLContext& gl;
    Renderer&  renderer;

    // External
    Clock clock;

    // Internals
    Syncer         syncer;
    EntityRenderer ent_renderer;

    // State
    std::vector <Entity> ents;

  public:
    Kernel (Window&, GLContext&, Renderer&);

    void run ();

  };

}
