
#include "Test.hpp"

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

namespace Rk
{
  namespace Test
  {
    class SessionImpl :
      public Session
    {
      HANDLE out;
      bool   is_console;

    public:
      void show_result (const char*, bool pass);

      SessionImpl ();

    };

    static SessionImpl impl;
    Session* session = &impl;

    SessionImpl::SessionImpl ()
    {
      out = GetStdHandle (STD_OUTPUT_HANDLE);
      DWORD dummy = 0;
      is_console = (GetConsoleMode (out, &dummy) != 0);
    }

    void SessionImpl::show_result (const char* what, bool pass)
    {
      CONSOLE_SCREEN_BUFFER_INFO info;

      if (is_console)
      {
        GetConsoleScreenBufferInfo (out, &info);

        auto colour_bit = pass ? FOREGROUND_GREEN : FOREGROUND_RED;
        SetConsoleTextAttribute (out, colour_bit);
      }

      DWORD written = 0;
      WriteFile (out, what, strlen (what), &written, nullptr);
      WriteFile (out, "\n", 1,             &written, nullptr);

      if (is_console)
        SetConsoleTextAttribute (out, info.wAttributes);
    }

    Test* Test::head = nullptr;

    void run_tests ()
    {
      for (auto test = Test::head; test; test = test->next)
        test->run ();

    }

  }

}
