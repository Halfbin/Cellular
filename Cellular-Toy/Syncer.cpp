

#include "Syncer.hpp"

#include "Test.hpp"

namespace Ce
{
  Syncer::Syncer () { }

  int Syncer::add (int x, int y)
  {
    return x + y;
  }

  Rk::Test::Test syncer_test = []
  {
    Syncer syncer;

    using namespace Rk::Test;

    it ("adds integers", [&] {
      auto x = syncer.add (4, 8);
      if (x != 12) throw TestFailure ();
    });
  };

}
