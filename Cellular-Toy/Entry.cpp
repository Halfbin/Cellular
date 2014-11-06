
#include "MinWin.hpp"

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <exception>

namespace Ce
{
  void true_main ();

  extern "C" int WINAPI WinMain (HINSTANCE, HINSTANCE, const char* cline, unsigned) try
  {
    /*if (arg_count > 1 && std::string (args [1]) == "test")
    {
      args [1] = "";
      Catch::Session session;
      session.applyCommandLine (arg_count, args);
      return session.run ();
    }
    else*/
    {
      true_main ();
      return 0;
    }
  }
  catch (std::exception& e)
  {
    MessageBoxA (0, "Exception", e.what (), 0);
    return 1;
  }
  catch (...)
  {
    MessageBoxA (0, "Exception", "?", 0);
    return 1;
  }

}
