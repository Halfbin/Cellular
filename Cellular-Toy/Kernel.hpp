
#pragma once

#include "Syncer.hpp"
#include "Clock.hpp"

namespace Ce
{
  class Kernel
  {
    // External
    Clock clock;

    // Other cells
    // ...

    // Internals
    Syncer syncer;

  public:
    Kernel ();

    void run ();

  };

}
