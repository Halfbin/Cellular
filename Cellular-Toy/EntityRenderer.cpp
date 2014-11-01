
#include "EntityRenderer.hpp"

#include <catch.hpp>

namespace Ce
{
  RenderItem EntityRenderer::render_entity (const Entity& ent)
  {
    return RenderItem (ent.position);
  }

  TEST_CASE ("EntityRenderer") {
    EntityRenderer er;
    Entity ent ({12, 34});

    SECTION ("preserves entity position") {
      auto item = er.render_entity (ent);
      REQUIRE (item.position == ent.position);
    }
  }
}
