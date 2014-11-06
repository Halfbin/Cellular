
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

  uptr Window::handle () const
  {
    return (uptr) impl->window;
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
