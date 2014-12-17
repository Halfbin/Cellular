
#include "Kernel.hpp"

#include <Rk/transform.hpp>

namespace Ce
{
  Kernel::Kernel (Window& window, GLContext& gl, Renderer& renderer) :
    window   (window),
    gl       (gl),
    renderer (renderer)
  {
    auto fig = new NullFigure;
    Entity ent (fig, v2f { 12, 24 });
    ents.push_back (ent);
  }

  void Kernel::run ()
  {
    std::vector <RenderItem> render_items;

    window.show ();
    auto sim_time = syncer.initial (clock.read ());

    for (;;)
    {
      auto win_state = window.pump ();

      if (win_state.closed)
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

      render_items.clear ();
      for (const auto& ent : ents)
      {
        auto item = ent.render ();
        render_items.push_back (item);
      }

      float fov = 75.0f,
            aspect = float (win_state.size.x) / float (win_state.size.y);

      FrameParams frame_params {
        win_state.size,
        m4f::identity (),
        Rk::eye_to_clip (fov, aspect, 0.1f, 100.0f)
      };

      auto render_range = RenderRange (render_items.data (), render_items.size ());
      renderer.render_frame (frame_params, render_range);
      gl.flip ();
    }

  }

}
