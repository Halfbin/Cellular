
#include "Kernel.hpp"

namespace Ce
{
  Kernel::Kernel (Window& window, Renderer& renderer) :
    window   (window),
    renderer (renderer)
  {
    ents.emplace_back (v2f {12, 34});
  }

  void Kernel::run ()
  {
    window.show ();

    auto sim_time = syncer.initial (clock.read ());

    for (;;)
    {
      auto update = window.pump ();

      if (update.closed)
        break;

      // handle input

      sim_time = syncer.update (sim_time, clock.read (), clock.frequency (), 0.25f);

      for (;;)
      {
        auto after_tick = syncer.tick (sim_time, 0.05f);
        if (after_tick == sim_time)
          break;

        // ...

        sim_time = after_tick;
      }

      renderer.begin_frame ();

      for (const auto& ent : ents)
      {
        auto item = ent_renderer.render_entity (ent);
        renderer.add_item (item);
      }

      renderer.end_frame ();
    }

  }

}
