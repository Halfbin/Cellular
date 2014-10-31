

namespace Rk
{
  namespace Test
  {
    struct TestFailure { };

    class Session
    {
    public:
      virtual void show_result (const char*, bool pass) = 0;

    };

    extern Session* session;

    class Test
    {
      void (*code) ();
      Test* next;
      static Test* head;
      friend void run_tests ();

    public:
      Test (void (*code) ()) :
        code (code),
        next (head)
      {
        head = this;
      }

      void run ()
      {
        code ();
      }

    };

    void run_tests ();

    template <typename code_t>
    void it (const char* what, code_t code)
    {
      auto pass = true;

      try { code (); }
      catch (TestFailure&)
      {
        pass = false;
      }

      session->show_result (what, pass);
    }

    //#define RKTEST(test_func) extern "C" int main () { test_func (); };

  }

}
