
#pragma once

#include "SimTime.hpp"

namespace Ce
{
  class Syncer
  {
  public:
    Syncer ();

    SimTime initial (uint64_t real_time);
    SimTime update  (SimTime, uint64_t real_time, uint64_t frequency, float max_lag);
    SimTime tick    (SimTime, float tick_length);

  };

}
