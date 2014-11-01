

#include "Syncer.hpp"

#include <catch.hpp>

namespace Ce
{
  Syncer::Syncer () { }

  SimTime Syncer::initial (uint64_t real_time)
  {
    return SimTime { real_time, 0.0f, 0.0f };
  }

  SimTime Syncer::update (SimTime old_time, uint64_t real_time, uint64_t frequency, float max_lag)
  {
    float elapsed = float (real_time - old_time.real_time) / float (frequency);

    auto new_time = old_time;
    new_time.real_time = real_time;
    new_time.remaining += elapsed;
    if (new_time.remaining > max_lag)
      new_time.remaining = max_lag;
    return new_time;
  }

  SimTime Syncer::tick (SimTime old_time, float tick_length)
  {
    auto new_time = old_time;
    if (new_time.remaining >= tick_length)
      new_time.remaining -= tick_length;
    return new_time;
  }

  TEST_CASE ("Syncer") {
    Syncer syncer;
    auto initial = syncer.initial (1000);

    SECTION ("provides a correct initial time") {
      REQUIRE (initial.real_time == 1000);
      REQUIRE (initial.sim_time == 0.0f);
      REQUIRE (initial.remaining == 0.0f);
    }

    SECTION ("accumulates remaining time") {
      auto prev = initial;
      prev.remaining = 0.03f;
      auto updated = syncer.update (prev, 1020, 200, 0.25f);

      REQUIRE (updated.real_time == 1020);
      REQUIRE (updated.sim_time == 0.0f);
      REQUIRE (abs (updated.remaining - 0.13f) < 0.00001f);
    }

    SECTION ("will not accumulate too much time") {
      auto updated = syncer.update (initial, 1200, 200, 0.25f);

      REQUIRE (updated.remaining <= 0.25f);
    }

    SECTION ("consumes remaining time") {
      auto updated = syncer.update (initial, 1200, 200, 0.25f);
      auto ticked = syncer.tick (updated, 0.05f);

      REQUIRE ((updated.remaining - ticked.remaining - 0.05f) < 0.00001f);
    }

    SECTION ("won't consume less than one tick") {
      auto updated = initial;
      updated.remaining = 0.01f;
      auto ticked = syncer.tick (updated, 0.05f);

      REQUIRE (ticked == updated);
    }
  }

}
