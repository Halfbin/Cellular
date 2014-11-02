
#pragma once

#include <vector>

#include "EntityRenderer.hpp"
#include "Renderer.hpp"
#include "Syncer.hpp"
#include "Clock.hpp"

namespace Ce
{
  class Kernel
  {
    // Other cells
    Renderer& renderer;

    // External
    Clock clock;

    // Internals
    Syncer         syncer;
    EntityRenderer ent_renderer;

    // State
    std::vector <Entity> ents;

  public:
    Kernel (Renderer&);

    void run ();

  };

}
