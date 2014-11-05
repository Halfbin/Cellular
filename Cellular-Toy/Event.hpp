
#pragma once

#include <Rk/types.hpp>
#include <Rk/memory.hpp>

namespace Ce
{
  enum EventTag
  {
    invalid = 0,
    key,
    mouse,
    button,
    pointer,
    wheel
  };

  class Event;

  namespace Detail
  {
    class EventModel
    {
      EventTag stored_tag;

    protected:
      friend class Ce::Event;
      explicit EventModel (EventTag tag) :
        stored_tag (tag)
      { }

    public:
      bool is (EventTag tag) const
      {
        return tag == stored_tag;
      }

      template <typename M>
      const M* ptr () const
      {
        if (is (M::tag)) return static_cast <const M*> (this);
        else return nullptr;
      }

      template <typename M>
      const M& as () const
      {
        auto p = ptr <M> ();
        if (!p) throw std::bad_cast ();
        else return *p;
      }

    };

  }

  template <EventTag tag_>
  class EventBase :
    public Detail::EventModel
  {
  protected:
    EventBase () : Detail::EventModel (tag_) { }
  public:
    static const EventTag tag = tag_;
  };

  class Event
  {
    Rk::raw_storage <Detail::EventModel, 64> storage;

  public:
    template <typename E>
    Event (E payload)
    {
      static_assert (std::is_convertible <E, Detail::EventModel>::value,
        "Not an event");
      static_assert (sizeof (E) <= storage.capacity, "Event too large");
      new (storage.raw ()) E (payload);
    }

    Event ()
    {
      new (storage.raw ()) Detail::EventModel (EventTag::invalid);
    }

    bool is (EventTag other) const
    {
      return storage.value ().is (other);
    }

    template <typename E>
    const E& as () const
    {
      return storage.value ().as <E> ();
    }

    template <typename E>
    const E* ptr () const
    {
      return storage.value ().ptr <E> ();
    }

  };

}
