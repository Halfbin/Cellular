
#pragma once

//#include <Rk/tio/format.hpp>
#include <Rk/string_ref.hpp>

#include <stdexcept>

#include <GL/glew.h>

namespace Ce
{
  class GLError :
    public std::runtime_error
  {
  public:
    GLError (Rk::cstring_ref message, GLenum code = glGetError ()) :
    //std::runtime_error (Rk::tio::format ("%1: OpenGL error code %2", message, int (code)))
      std::runtime_error (Rk::to_string (message))
    { }

  };

  inline void check_gl (Rk::cstring_ref message, GLenum code = glGetError ())
  {
    if (code != GL_NO_ERROR)
      throw GLError (message, code);
  }

}
