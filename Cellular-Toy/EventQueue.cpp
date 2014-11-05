
#include "EventQueue.hpp"

#include "Keyboard.hpp"
#include "Mouse.hpp"

#include <catch.hpp>

namespace Ce
{
  EventQueue EventQueue::pop_event (Event& event) const
  {
    if (evs_ != evs_end_)
    {
      event = *evs_;
      return { evs_ + 1, evs_end_ };
    }
    else
    {
      event = { };
      return *this;
    }
  }

  TEST_CASE ("InputQueue") {
    Event evs [3] = {
      KeyEvent (),
      ButtonEvent (),
      PointerEvent ()
    };

    EventQueue q (evs, 3);

    SECTION ("pops events from a queue") {
      Event ev;
      auto popped = q.pop_event (ev);

      REQUIRE (popped.count () == (q.count () - 1));
      REQUIRE (ev.is (EventTag::key));
    }

    SECTION ("will not pop from an empty queue") {
      EventQueue empty (evs, evs);
      Event ev;
      auto popped = empty.pop_event (ev);

      REQUIRE (popped.count () == 0);
      REQUIRE (ev.is (EventTag::invalid));
    }
  }

}
