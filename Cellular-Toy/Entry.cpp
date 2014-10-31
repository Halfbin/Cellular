
#include <exception>

extern "C" __declspec (dllimport) void __stdcall MessageBoxA (void*, const char*, const char*, unsigned);

namespace Ce
{
  void true_main ();

  extern "C" int main () try
  {
    true_main ();
    return 0;
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
