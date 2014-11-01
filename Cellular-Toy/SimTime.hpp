
#pragma once

#include <cstdint>

namespace Ce
{
  class SimTime
  {
  public:
    uint64_t real_time;
    float    sim_time,
             remaining;
  };

  static inline bool operator == (SimTime a, SimTime b)
  {
    return a.real_time == b.real_time
        && a.sim_time  == b.sim_time
        && a.remaining == b.remaining;
  }

  static inline bool operator != (SimTime a, SimTime b)
  {
    return !(a == b);
  }

}
