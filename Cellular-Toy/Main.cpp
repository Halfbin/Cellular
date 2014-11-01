
#include "Syncer.hpp"
#include "Clock.hpp"

#include <iostream>

namespace Ce
{
  void true_main ()
  {
    Syncer syncer;
    Clock  clock;

    auto sim_time = syncer.initial (clock.read ());

    for (;;)
    {
      // ...

      sim_time = syncer.update (sim_time, clock.read (), clock.frequency (), 4.00f);

      for (;;)
      {
        auto next_time = syncer.tick (sim_time, 1.00f);
        if (next_time == sim_time)
          break;

        std::cout << "tick\n";

        sim_time = next_time;
      }
    }
  }

}