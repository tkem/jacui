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

#include "detail.h"

#include <SDL/SDL_ttf.h>

#include <algorithm>

namespace {
    enum { uc_user, uc_timeout, uc_interval };

    inline SDL_Event make_user_event(int code, void* p1 = 0, void* p2 = 0) {
        SDL_Event event;
        event.type = SDL_USEREVENT;
        event.user.type = SDL_USEREVENT;
        event.user.code = code;
        event.user.data1 = p1;
        event.user.data2 = p2;
        return event;
    }

    extern "C" Uint32 jacui_timeout_callback(Uint32 /*interval*/, void* param)
    {
        SDL_Event event = make_user_event(uc_timeout, param);
        SDL_PushEvent(&event); // no throw from extern "C"
        return 0;
    }

    extern "C" Uint32 jacui_interval_callback(Uint32 interval, void* param)
    {
        SDL_Event event = make_user_event(uc_interval, param);
        SDL_PushEvent(&event); // no throw from extern "C"
        return interval;
    }

    jacui::size2d get_screen_size()
    {
        SDL_Surface* s = SDL_GetVideoSurface();
        if (!s)
            jacui::detail::throw_error("error getting screen size");
        return jacui::size2d(s->w, s->h);
    }

    void set_screen_size(jacui::size2d size)
    {
        SDL_Surface* s = SDL_GetVideoSurface();
        if (!s)
            jacui::detail::throw_error("error resizing screen");
        if (!SDL_SetVideoMode(size.width, size.height, s->format->BitsPerPixel, s->flags))
            jacui::detail::throw_error("error resizing screen");

        SDL_Event event;
        event.type = SDL_VIDEOEXPOSE;
        event.expose.type = SDL_VIDEOEXPOSE;
        if (SDL_PushEvent(&event) < 0)
            jacui::detail::throw_error("error pushing event");
    }
}

namespace jacui {
    namespace detail {
        event_queue::event_queue() : ntimer(0)
        {
            std::fill(&timers[0], &timers[max_timers], SDL_TimerID(0));
            event_.type = SDL_NOEVENT;
        }

        event* event_queue::wait()
        {
            if (type() == event::quit)
                return 0;
            if (type() == event::resize)
                set_screen_size(size());
            if (type() == event::timer && is_timeout())
                clear_timer(timer());
            if (!SDL_WaitEvent(&event_))
                return 0;
            return is_user() ? user() : this;
        }

        event* event_queue::poll()
        {
            if (type() == event::quit)
                return 0;
            if (type() == event::resize)
                set_screen_size(size());
            if (type() == event::timer && is_timeout())
                clear_timer(timer());
            if (!SDL_PollEvent(&event_))
                return 0;
            return is_user() ? user() : this;
        }

        void event_queue::push(event* pe)
        {
            SDL_Event event = make_user_event(uc_user, pe);
            if (SDL_PushEvent(&event) < 0)
                throw_error("error pushing event");
        }

        timer_event::timer_type event_queue::set_timeout(unsigned long ms)
        {
            timer_type timer = make_timer();
            if (!(timers[timer] = SDL_AddTimer(ms, jacui_timeout_callback, &timers[timer])))
                throw_error("error setting timeout");
            return timer;
        }

        timer_event::timer_type event_queue::set_interval(unsigned long ms)
        {
            timer_type timer = make_timer();
            if (!(timers[timer] = SDL_AddTimer(ms, jacui_interval_callback, &timers[timer])))
                throw_error("error setting interval");
            return timer;
        }

        bool event_queue::clear_timer(timer_event::timer_type timer)
        {
            if (timer >= max_timers || !timers[timer])
                return false;
            SDL_RemoveTimer(timers[timer]);
            timers[timer] = 0;
            return true;
        }

        void event_queue::quit()
        {
            event_.type = SDL_QUIT;
        }

        event::event_type event_queue::type() const 
        {
            switch (event_.type) {
            case SDL_ACTIVEEVENT:
                return event::noevent; // TODO: handle active
            case SDL_VIDEORESIZE:
                return event::resize;
            case SDL_VIDEOEXPOSE:
                return event::redraw;
            case SDL_MOUSEMOTION:
                return event::mousemove;
            case SDL_MOUSEBUTTONDOWN:
                return event::mousedown;
            case SDL_MOUSEBUTTONUP:
                return event::mouseup;
            case SDL_KEYDOWN:
                return event::keydown;
            case SDL_KEYUP:
                return event::keyup;
            case SDL_QUIT:
                return event::quit;
            case SDL_USEREVENT:
                switch (event_.user.code) {
                case uc_user:
                    return event::user;
                case uc_timeout:
                case uc_interval:
                    return event::timer;
                default:
                    return event::noevent;
                }
            default:
                return event::noevent;
            }
        }

        const char* event_queue::name() const 
        {
            switch (event_.type) {
            case SDL_ACTIVEEVENT:
                return "active"; // TODO: handle active
            case SDL_VIDEORESIZE:
                return "resize";
            case SDL_VIDEOEXPOSE:
                return "redraw";
            case SDL_MOUSEMOTION:
                return "mousemove";
            case SDL_MOUSEBUTTONDOWN:
                return "mousedown";
            case SDL_MOUSEBUTTONUP:
                return "mouseup";
            case SDL_KEYDOWN:
                return "keydown";
            case SDL_KEYUP:
                return "keyup";
            case SDL_QUIT:
                return "quit";
            case SDL_USEREVENT:
                switch (event_.user.code) {
                case uc_user:
                    return "user";
                case uc_timeout:
                case uc_interval:
                    return "timer";
                default:
                    return "noevent";
                }
            default:
                return "noevent";
            }
        }

        void event_queue::cancel() 
        {
            if (is_timeout() || is_interval())
                clear_timer(timer());
            event_.type = SDL_NOEVENT;
        }

        size2d event_queue::size() const 
        {
            switch (event_.type) {
            case SDL_VIDEORESIZE:
                return size2d(event_.resize.w, event_.resize.h);
            default:
                return size2d();
            }
        }

        rect2d event_queue::rect() const 
        {
            switch (event_.type) {
            case SDL_VIDEOEXPOSE:
                return get_screen_size();
            default:
                return rect2d();
            }
        }

        input_event::modmask_type event_queue::modifiers() const 
        {
            switch (event_.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                return event_.key.keysym.mod;
            default:
                return SDL_GetModState();
            }
        }

        mouse_event::button_type event_queue::button() const 
        {
            switch (event_.type) {
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                return event_.button.button;
            case SDL_MOUSEMOTION:
                return 0; // TODO: SDL_BUTTON(event.motion.state)
            default:
                return 0;
            }
        }

        point2d event_queue::point() const 
        {
            switch (event_.type) {
            case SDL_MOUSEMOTION:
                return point2d(event_.motion.x, event_.motion.y);
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                return point2d(event_.button.x, event_.button.y);
            default:
                return point2d();
            }
        }

        keyboard_event::key_type event_queue::key() const 
        {
            switch (event_.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                // report uppercase characters for aesthetic reasons
                if (std::islower(event_.key.keysym.sym))
                    return std::toupper(event_.key.keysym.sym);
                else
                    return event_.key.keysym.sym;
            default:
                return 0;
            }
        }

        wchar_t event_queue::wchar() const 
        {
            // assume wchar_t is (widened) UTF-16
            switch (event_.type) {
            case SDL_KEYDOWN:
                return event_.key.keysym.unicode;
            case SDL_KEYUP:
                return event_.key.keysym.unicode;
            default:
                return 0;
            }
        }

        timer_event::timer_type event_queue::timer() const 
        {
            if (is_timeout() || is_interval())
                return static_cast<SDL_TimerID*>(event_.user.data1) - timers;
            else
                return 0;
        }

        event* event_queue::user() const 
        {
            return is_user() ? static_cast<event*>(event_.user.data1) : 0;
        }

        bool event_queue::is_user() const
        {
            return event_.type == SDL_USEREVENT && event_.user.code == uc_user;
        }

        bool event_queue::is_timeout() const
        {
            return event_.type == SDL_USEREVENT && event_.user.code == uc_timeout;
        }

        bool event_queue::is_interval() const
        {
            return event_.type == SDL_USEREVENT && event_.user.code == uc_interval;
        }

        timer_event::timer_type event_queue::make_timer()
        {
            // round robin to avoid reusing "active" timers
            for (timer_type i = 1; i != max_timers; ++i) {
                timer_type n = (ntimer + i) % max_timers;
                if (n != 0 && !timers[n]) {
                    ntimer = n;
                    return n;
                }
            }

            throw error("maximum number of timers exceeded");
        }

        init::init()
        {
            if (count++ == 0) {
                if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE) < 0)
                    throw_error("unable to initialize sdl");
                if (TTF_Init() < 0)
                    throw_error("unable to initialize ttf library");
                SDL_EnableUNICODE(true);
            }
        }

        init::~init()
        {
            if (--count == 0) {
                TTF_Quit();
                SDL_Quit();
            }
        }

        int init::count = 0;
    }
}
