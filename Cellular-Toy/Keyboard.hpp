
#pragma once

#include "Event.hpp"

namespace Ce
{
  enum class Key : u8
  {
    invalid = 0,

    alpha_a, alpha_b, alpha_c, alpha_d, alpha_e, alpha_f, alpha_g, alpha_h,
    alpha_i, alpha_j, alpha_k, alpha_l, alpha_m, alpha_n, alpha_o, alpha_p,
    alpha_q, alpha_r, alpha_s, alpha_t, alpha_u, alpha_v, alpha_w, alpha_x,
    alpha_y, alpha_z,

    alpha_0, alpha_1, alpha_2, alpha_3, alpha_4, alpha_5, alpha_6, alpha_7,
    alpha_8, alpha_9,

    backtick, dash, equals, bk_space, tab, lt_brace, rt_brace, enter, capslock,
    semi_col, apos, hash, lt_shift, bk_slash, comma, period, slash, rt_shift,
    lt_ctrl, lt_alt, spacebar, rt_alt, rt_ctrl, escape,

    f1,  f2,  f3,  f4,  f5,  f6,  f7,  f8,  f9,  f10, f11, f12,
    f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24,

    prt_scrn, scr_lock, pause, insert, del, home, end, page_up, page_dn,
    up, down, left, right,

    num_lock,
    np_div, np_mul, np_minus, np_plus, np_point, np_enter,
    np_0, np_1, np_2, np_3, np_4, np_5, np_6, np_7, np_8, np_9,

    count
  };

  struct KeyEvent : public EventBase <EventTag::key>
  {
    Key key; bool down;
    KeyEvent (Key key, bool down) : key (key), down (down) { }
    KeyEvent () = default;
  };

  struct Keyboard
  {
    bool keys [uint (Key::count)];
    Keyboard ();
    Keyboard react (Event) const;
  };

}
