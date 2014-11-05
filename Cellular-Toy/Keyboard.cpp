
#include "InputSystem.hpp"

#include <catch.hpp>

namespace Ce
{
  namespace
  {
    const Key inv = Key::invalid;

    const Key keytab [256] = {
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::bk_space, Key::tab,      Key::invalid,  Key::invalid,
      Key::invalid,  Key::enter,    Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::pause,
      Key::capslock, Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::escape,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::spacebar, Key::page_up,  Key::page_dn,  Key::end,
      Key::home,     Key::left,     Key::up,       Key::right,
      Key::down,     Key::invalid,  Key::invalid,  Key::invalid,
      Key::prt_scrn, Key::insert,   Key::del,      Key::invalid,
      Key::alpha_0,  Key::alpha_1,  Key::alpha_2,  Key::alpha_3,
      Key::alpha_4,  Key::alpha_5,  Key::alpha_6,  Key::alpha_7,
      Key::alpha_8,  Key::alpha_9,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::alpha_a,  Key::alpha_b,  Key::alpha_c,
      Key::alpha_d,  Key::alpha_e,  Key::alpha_f,  Key::alpha_g,
      Key::alpha_h,  Key::alpha_i,  Key::alpha_j,  Key::alpha_k,
      Key::alpha_l,  Key::alpha_m,  Key::alpha_n,  Key::alpha_o,
      Key::alpha_p,  Key::alpha_q,  Key::alpha_r,  Key::alpha_s,
      Key::alpha_t,  Key::alpha_u,  Key::alpha_v,  Key::alpha_w,
      Key::alpha_x,  Key::alpha_y,  Key::alpha_z,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::np_0,     Key::np_1,     Key::np_2,     Key::np_3,
      Key::np_4,     Key::np_5,     Key::np_6,     Key::np_7,
      Key::np_8,     Key::np_9,     Key::np_mul,   Key::np_plus,
      Key::np_enter, Key::np_minus, Key::np_point, Key::np_div,
      Key::f1,       Key::f2,       Key::f3,       Key::f4,
      Key::f5,       Key::f6,       Key::f7,       Key::f8,
      Key::f9,       Key::f10,      Key::f11,      Key::f12,
      Key::f13,      Key::f14,      Key::f15,      Key::f16,
      Key::f17,      Key::f18,      Key::f19,      Key::f20,
      Key::f21,      Key::f22,      Key::f23,      Key::f24,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::num_lock, Key::scr_lock, Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::lt_shift, Key::rt_shift, Key::lt_ctrl,  Key::rt_ctrl,
      Key::lt_alt,   Key::rt_alt,   Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::semi_col, Key::equals,
      Key::comma,    Key::dash,     Key::period,   Key::slash,
      Key::backtick, Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::lt_brace,
      Key::bk_slash, Key::rt_brace, Key::apos,     Key::hash,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid,
      Key::invalid,  Key::invalid,  Key::invalid,  Key::invalid
    };

    Key vk_to_key (u8 vkey)
    {
      return keytab [vkey];
    }

  }

  Event InputSystem::decode_raw_key (RAWKEYBOARD raw)
  {
    auto vk = raw.VKey;
    auto scan_code = raw.MakeCode;

    if (vk == 255) // Escape sequence non-key; ignore
      return { };

    if (vk == VK_SHIFT) // Left/Right differntiation
      vk = MapVirtualKey (scan_code, MAPVK_VSC_TO_VK_EX);
    else if (vk == VK_NUMLOCK) // Pause/NumLock silliness
      scan_code = MapVirtualKey (vk, MAPVK_VK_TO_VSC) | 0x100;

    auto e0 = (raw.Flags & RI_KEY_E0) != 0,
         e1 = (raw.Flags & RI_KEY_E1) != 0;

    if (e1)
    {
      if (vk == VK_PAUSE) // Work around MapVirtualKey bug
        scan_code = 0x45;
      else
        scan_code = MapVirtualKey (vk, MAPVK_VK_TO_VSC);
    }

    switch (vk)
    {
      case VK_CONTROL:
        if (e0) vk = VK_RCONTROL;
        else    vk = VK_LCONTROL;
      break;

      case VK_MENU:
        if (e0) vk = VK_RMENU;
        else    vk = VK_LMENU;
      break;

      case VK_RETURN: if ( e0) vk = VK_SEPARATOR; break;
      case VK_DELETE: if (!e0) vk = VK_DECIMAL; break;
      case VK_INSERT: if (!e0) vk = VK_NUMPAD0; break;
      case VK_END:    if (!e0) vk = VK_NUMPAD1; break;
      case VK_DOWN:   if (!e0) vk = VK_NUMPAD2; break;
      case VK_NEXT:   if (!e0) vk = VK_NUMPAD3; break;
      case VK_LEFT:   if (!e0) vk = VK_NUMPAD4; break;
      case VK_CLEAR:  if (!e0) vk = VK_NUMPAD5; break;
      case VK_RIGHT:  if (!e0) vk = VK_NUMPAD6; break;
      case VK_HOME:   if (!e0) vk = VK_NUMPAD7; break;
      case VK_UP:     if (!e0) vk = VK_NUMPAD8; break;
      case VK_PRIOR:  if (!e0) vk = VK_NUMPAD9; break;

      default:;
    }

    auto down = (raw.Flags & RI_KEY_BREAK) == 0;
    auto key = vk_to_key (vk & 0xff);

    return KeyEvent (key, down);
  }

  Keyboard::Keyboard ()
  {
    for (auto& k : keys)
      k = false;
  }

  Keyboard Keyboard::react (Event ev) const
  {
    Keyboard new_keyboard (*this);
    if (auto kev = ev.ptr<KeyEvent> ())
      new_keyboard.keys [uint (kev->key)] = kev->down;
    return new_keyboard;
  }

  TEST_CASE ("Keyboard") {
    Keyboard kb;

    SECTION ("reacts to keystrokes") {
      auto new_kb = kb.react (KeyEvent (Key::prt_scrn, true));
      REQUIRE (new_kb.keys [uint (Key::prt_scrn)]);
    }
  }

}
