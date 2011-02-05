/**
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

#ifndef JACUI_EVENT_HPP
#define JACUI_EVENT_HPP

#include "types.hpp"

namespace jacui {
    /**
       \brief Generic JACUI event class
    */
    class event {
    public:
        enum event_type {
            noevent, // also a cancelled event
            resize,
            redraw,
            mousemove,
            mousedown,
            mouseup,
            keydown,
            keyup,
            timer,
            quit,
            user
        };
        
        virtual ~event();

        virtual event_type type() const = 0;

        virtual const char* name() const = 0;

        virtual void cancel() = 0;
    };

    class resize_event: public virtual event {
    public:
        virtual size2d size() const = 0;
    };

    class redraw_event: public virtual event {
    public:
        virtual rect2d rect() const = 0;
    };

    class input_event: public virtual event {
    public:
        // modifier key masks
        typedef unsigned int modmask_type;
        static const modmask_type shift_mask;
        static const modmask_type ctrl_mask;
        static const modmask_type alt_mask;

        virtual modmask_type modifiers() const = 0;

        bool shift() const { return modifiers() & shift_mask; }

        bool ctrl() const { return modifiers() & ctrl_mask; }

        bool alt() const { return modifiers() & alt_mask; }
    };

    class mouse_event: public virtual input_event {
    public:
        typedef unsigned int button_type;
        static const button_type lbutton;
        static const button_type mbutton;
        static const button_type rbutton;

        virtual button_type button() const = 0;

        virtual point2d point() const = 0;
    };

    class keyboard_event: public virtual input_event {
    public:
        // key type extends ASCII characters
        typedef int key_type;

        // non-printable ASCII characters
        static const key_type bs; // '\b';
        static const key_type ht; // '\t';
        static const key_type cr; // '\r';
        static const key_type esc; // '\033';
        static const key_type del; // '\177';

        // keypad keys
        static const key_type up;
        static const key_type down;
        static const key_type left;
        static const key_type right;
        static const key_type pgup;
        static const key_type pgdown;
        static const key_type home;
        static const key_type end;
        static const key_type ins;

        // modifier keys
        static const key_type lshift;
        static const key_type rshift;
        static const key_type lctrl;
        static const key_type rctrl;
        static const key_type lalt;
        static const key_type ralt;

        // function keys
        static const key_type f1;
        static const key_type f2;
        static const key_type f3;
        static const key_type f4;
        static const key_type f5;
        static const key_type f6;
        static const key_type f7;
        static const key_type f8;
        static const key_type f9;
        static const key_type f10;
        static const key_type f11;
        static const key_type f12;

        virtual key_type key() const = 0;

        virtual wchar_t wchar() const = 0;
    };

    class timer_event: public virtual event {
    public:
        typedef unsigned int timer_type;

        virtual timer_type timer() const = 0;
    };

    class user_event: public virtual event {
    public:
        event_type type() const { return user; }
    };


    /**
       \brief JACUI event queue base class
    */
    class event_queue {
    public:
        virtual ~event_queue();

        virtual event* wait() = 0;

        virtual event* poll() = 0;

        virtual void push(event* e) = 0;

        virtual timer_event::timer_type set_timeout(unsigned long ms) = 0;

        virtual timer_event::timer_type set_interval(unsigned long ms) = 0;

        virtual bool clear_timer(timer_event::timer_type timer) = 0;
    };
}

#endif
