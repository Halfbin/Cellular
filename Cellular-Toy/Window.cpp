
#include "WindowImpl.hpp"

namespace Ce
{
  Window::Window (Rk::cstring_ref title) :
    impl (new Impl (title))
  { }

  Window::~Window ()
  {
    delete impl;
  }

  WindowUpdate Window::pump ()
  {
    return impl->pump ();
  }

  void Window::show ()
  {
    ShowWindow (impl->window, SW_SHOWNORMAL);
  }

}
