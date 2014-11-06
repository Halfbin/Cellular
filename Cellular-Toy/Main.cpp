
#include "GLContext.hpp"
#include "Renderer.hpp"
#include "Kernel.hpp"
#include "Window.hpp"

namespace Ce
{
  void true_main ()
  {
    Window   win ("Cellular");
    GLContext gl (win.handle ());
    Renderer renderer;
    Kernel   kernel (win, gl, renderer);

    kernel.run ();
  }

}
