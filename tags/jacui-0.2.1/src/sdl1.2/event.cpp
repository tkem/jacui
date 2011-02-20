/*
 * JACUI - Just Another C++ User Interface Library
 *
 * Copyright (C) 2011 The JACUI Project
 *
 * http://code.google.com/p/jacui/
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "jacui/event.hpp"
#include "detail.hpp"

namespace jacui {
    event::~event()
    {
    }

    event_queue::~event_queue()
    {
    }

    const input_event::modmask_type input_event::shift_mask = KMOD_SHIFT;
    const input_event::modmask_type input_event::ctrl_mask = KMOD_CTRL;
    const input_event::modmask_type input_event::alt_mask = KMOD_ALT;

    const mouse_event::button_type mouse_event::lbutton = SDL_BUTTON_LEFT;
    const mouse_event::button_type mouse_event::mbutton = SDL_BUTTON_MIDDLE;
    const mouse_event::button_type mouse_event::rbutton = SDL_BUTTON_RIGHT;

    const keyboard_event::key_type keyboard_event::bs = '\b';
    const keyboard_event::key_type keyboard_event::ht = '\t';
    const keyboard_event::key_type keyboard_event::cr = '\r';
    const keyboard_event::key_type keyboard_event::esc = '\033';
    const keyboard_event::key_type keyboard_event::del = '\177';

    const keyboard_event::key_type keyboard_event::up = SDLK_UP;
    const keyboard_event::key_type keyboard_event::down = SDLK_DOWN;
    const keyboard_event::key_type keyboard_event::left = SDLK_LEFT;
    const keyboard_event::key_type keyboard_event::right = SDLK_RIGHT;
    const keyboard_event::key_type keyboard_event::pgup = SDLK_PAGEUP;
    const keyboard_event::key_type keyboard_event::pgdown = SDLK_PAGEDOWN;
    const keyboard_event::key_type keyboard_event::home = SDLK_HOME;
    const keyboard_event::key_type keyboard_event::end = SDLK_END;
    const keyboard_event::key_type keyboard_event::ins = SDLK_INSERT;

    const keyboard_event::key_type keyboard_event::lshift = SDLK_LSHIFT;
    const keyboard_event::key_type keyboard_event::rshift = SDLK_RSHIFT;
    const keyboard_event::key_type keyboard_event::lctrl = SDLK_LCTRL;
    const keyboard_event::key_type keyboard_event::rctrl = SDLK_RCTRL;
    const keyboard_event::key_type keyboard_event::lalt = SDLK_LALT;
    const keyboard_event::key_type keyboard_event::ralt = SDLK_RALT;

    const keyboard_event::key_type keyboard_event::f1 = SDLK_F1;
    const keyboard_event::key_type keyboard_event::f2 = SDLK_F2;
    const keyboard_event::key_type keyboard_event::f3 = SDLK_F3;
    const keyboard_event::key_type keyboard_event::f4 = SDLK_F4;
    const keyboard_event::key_type keyboard_event::f5 = SDLK_F5;
    const keyboard_event::key_type keyboard_event::f6 = SDLK_F6;
    const keyboard_event::key_type keyboard_event::f7 = SDLK_F7;
    const keyboard_event::key_type keyboard_event::f8 = SDLK_F8;
    const keyboard_event::key_type keyboard_event::f9 = SDLK_F9;
    const keyboard_event::key_type keyboard_event::f10 = SDLK_F10;
    const keyboard_event::key_type keyboard_event::f11 = SDLK_F11;
    const keyboard_event::key_type keyboard_event::f12 = SDLK_F12;
}
