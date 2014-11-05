
#include "WindowImpl.hpp"

#include <Rk/unicode_convert.hpp>
#include <Rk/exception.hpp>

namespace Ce
{
  LRESULT Window::Impl::handle_message (HWND src, UINT msg, WPARAM wp, LPARAM lp)
  {
    switch (msg)
    {
      case WM_CLOSE:
        closed = true;
      return 0;

      case WM_SIZE:
        width  = LOWORD (lp);
        height = HIWORD (lp);
      break; // in_sys needs to know

      default:;
    }

    return in_sys.handle_input (src, msg, wp, lp);
  }

  LRESULT __stdcall Window::Impl::dispatch_message (HWND window, UINT msg, WPARAM wp, LPARAM lp)
  {
    auto self = reinterpret_cast <Impl*> (GetWindowLongPtr (window, GWLP_USERDATA));

    // Retrieve this from fake menu
    if (!self)
    {
      auto menu = GetMenu (window);

      MENUITEMINFO info = { };
      info.cbSize = sizeof (info);
      info.fMask = MIIM_DATA;
      GetMenuItemInfo (menu, 1, false, &info);

      self = reinterpret_cast <Impl*> (info.dwItemData);
      self->window = window;

      SetWindowLongPtr (window, GWLP_USERDATA, reinterpret_cast <LONG_PTR> (self));
      SetMenu (window, nullptr);
    }

    return self->handle_message (window, msg, wp, lp);
  }

  Window::Impl::Impl (Rk::cstring_ref title) :
    closed (false)
  {
    // Real display window
    WNDCLASSEXW window_class = { };
    window_class.cbSize        = sizeof (window_class);
    window_class.hInstance     = GetModuleHandleW (nullptr);
    window_class.hCursor       = LoadCursorW (nullptr, IDC_ARROW);
    window_class.hIcon         = LoadIconW   (nullptr, IDI_APPLICATION);
    window_class.lpfnWndProc   = dispatch_message;
    window_class.lpszClassName = L"Ce::Window::Impl";
    RegisterClassExW (&window_class);

    // Neat way to get this ptr into first wndproc call
    auto fake_menu = CreateMenu ();
    AppendMenuW (fake_menu, MF_OWNERDRAW, 1, (LPCWSTR) this);

    auto w_title = Rk::string_utf8_to_16 (title);

    window = CreateWindowExW (
      0,
      window_class.lpszClassName,
      (LPCWSTR) w_title.c_str (),
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
      CW_USEDEFAULT, 0,
      1600, 900,
      0,
      fake_menu,
      window_class.hInstance,
      0
    );

    if (!window || iptr (window) == -1)
      throw Rk::win_error ("CreateWindowExW for display");
  }

  Window::Impl::~Impl ()
  {
    DestroyWindow (window);
  }

  WindowUpdate Window::Impl::pump ()
  {
    in_sys.begin_pump ();

    MSG msg;
    while (PeekMessageW (&msg, nullptr, 0, 0, PM_REMOVE))
      DispatchMessageW (&msg);

    auto input = in_sys.end_pump ();
    auto size = v2i (width, height);
    return WindowUpdate (closed, size, input);
  }

}
