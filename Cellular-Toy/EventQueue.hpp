
#pragma once

#include "Event.hpp"

#include <Rk/types.hpp>

namespace Ce
{
  class EventQueue
  {
    const Event*  evs_;
    const Event*  evs_end_;

  public:
    EventQueue (const Event* events, const Event* end) :
      evs_     (events),
      evs_end_ (end)
    { }

    EventQueue (const Event* events, size_t event_count) :
      evs_     (events),
      evs_end_ (events + event_count)
    { }

    EventQueue pop_event (Event&) const;

    size_t count () const
    {
      return evs_end_ - evs_;
    }

  };

}
