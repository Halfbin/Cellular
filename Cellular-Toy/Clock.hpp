
#pragma once

#include <cstdint>

namespace Ce
{
  namespace Detail
  {
    extern "C"
    {
      __declspec(dllimport) int32_t __stdcall QueryPerformanceFrequency (uint64_t*);
      __declspec(dllimport) int32_t __stdcall QueryPerformanceCounter   (uint64_t*);
    }
  }

  class Clock
  {
    uint64_t freq;

  public:
    Clock ()
    {
      Detail::QueryPerformanceFrequency (&freq);
    }

    uint64_t read () const
    {
      uint64_t reading = 0;
      Detail::QueryPerformanceCounter (&reading);
      return reading;
    }

    uint64_t frequency () const
    {
      return freq;
    }

  };

}
