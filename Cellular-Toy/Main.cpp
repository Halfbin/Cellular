
#include "Renderer.hpp"
#include "Kernel.hpp"
#include "Window.hpp"

namespace Ce
{
  void true_main ()
  {
    Window   win ("Cellular");
    Renderer renderer;
    Kernel   kernel (win, renderer);

    kernel.run ();
  }

}