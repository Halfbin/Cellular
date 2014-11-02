
#include "Kernel.hpp"
#include "Renderer.hpp"

namespace Ce
{
  void true_main ()
  {
    Renderer renderer;
    Kernel   kernel (renderer);

    kernel.run ();
  }

}