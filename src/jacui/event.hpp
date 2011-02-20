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

#ifndef JACUI_EVENT_HPP
#define JACUI_EVENT_HPP

#include "types.hpp"

namespace jacui {
    /**
       \brief generic jacui event class
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

        /**
         * \brief destroy an event
         */
        virtual ~event();

        /**
         * \brief the type of the event
         */
        virtual event_type type() const = 0;

        /**
         * \brief the name of the event
         */
        virtual const char* name() const = 0;

        /**
         * \brief cancel an event
         */
        virtual void cancel() = 0;
    };

    /**
       \brief jacui resize event class
    */
    class resize_event: public virtual event {
    public:
        /**
         * \brief the new size of the window
         */
        virtual size2d size() const = 0;
    };

    /**
       \brief jacui redraw event class
    */
    class redraw_event: public virtual event {
    public:
        /**
         * \brief the region to be redrawn
         */
        virtual rect2d rect() const = 0;
    };

    /**
       \brief jacui input event class
    */
    class input_event: public virtual event {
    public:
        // modifier key masks
        typedef unsigned int modmask_type;

        static const modmask_type shift_mask;
        static const modmask_type ctrl_mask;
        static const modmask_type alt_mask;

        /**
         * \brief the modifier mask
         */
        virtual modmask_type modifiers() const = 0;

        /**
         * \brief whether the shift modifier was present
         */
        bool shift() const { return (modifiers() & shift_mask) != 0; }

        /**
         * \brief whether the ctrl modifier was present
         */
        bool ctrl() const { return (modifiers() & ctrl_mask) != 0; }

        /**
         * \brief whether the alt modifier was present
         */
        bool alt() const { return (modifiers() & alt_mask) != 0; }
    };

    /**
       \brief jacui mouse event class
    */
    class mouse_event: public virtual input_event {
    public:
        typedef unsigned int button_type;

        static const button_type lbutton;
        static const button_type mbutton;
        static const button_type rbutton;

        /**
         * \brief the mouse button for this event
         */
        virtual button_type button() const = 0;

        /**
         * \brief the position of the mouse cursor
         */
        virtual point2d point() const = 0;
    };

    /**
       \brief jacui keyboard event class
    */
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

        /**
           \brief the key code for this event
        */
        virtual key_type key() const = 0;

        /**
           \brief the wide character for this event
        */
        virtual wchar_t wchar() const = 0;
    };

    /**
       \brief jacui timer event class
    */
    class timer_event: public virtual event {
    public:
        typedef unsigned int timer_type;

        /**
           \brief the timer ID for this event
        */
        virtual timer_type timer() const = 0;
    };

    /**
       \brief jacui user event class
    */
    class user_event: public virtual event {
    public:
        /**
           \brief always set to user
        */
        event_type type() const { return user; }
    };


    /**
       \brief jacui event queue base class
    */
    class event_queue {
    public:
        /**
           \brief destroy an event queue
        */
        virtual ~event_queue();

        /**
           \brief wait for next event
        */
        virtual event* wait() = 0;

        /**
           \brief poll pending events
        */
        virtual event* poll() = 0;

        /**
           \brief add an event to the event queue
        */
        virtual void push(event* e) = 0;

        /**
           \brief create a timer with a given timeout
        */
        virtual timer_event::timer_type set_timeout(unsigned long ms) = 0;

        /**
           \brief create a recurring timer with a given time interval
        */
        virtual timer_event::timer_type set_interval(unsigned long ms) = 0;

        /**
           \brief clear an existing timer
        */
        virtual bool clear_timer(timer_event::timer_type timer) = 0;
    };
}

#endif
