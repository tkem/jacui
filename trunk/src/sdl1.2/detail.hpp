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

#ifndef JACUI_SDL_1_2_DETAIL_HPP
#define JACUI_SDL_1_2_DETAIL_HPP

#include "../jacui/event.hpp"
#include "../jacui/error.hpp"
#include "../jacui/types.hpp"

#include <SDL/SDL.h>

#include <string>

namespace jacui {
    namespace detail {
        struct surface_type: public SDL_Surface { };

        struct cursor_type: public SDL_Cursor { };

        // convert SDL error to sdl exception
        inline void throw_error(const std::string& msg)
        {
            const char* err = SDL_GetError();
            error e(err ? msg + ": " + err : msg);
            SDL_ClearError();
            throw e;
        }

        class surface_lock {
        public:
            surface_lock(SDL_Surface* s) : surface_(s) {
                if (SDL_MUSTLOCK(surface_) && SDL_LockSurface(surface_) < 0) {
                    throw_error("error locking surface");
                }
            }

            ~surface_lock() {
                if (SDL_MUSTLOCK(surface_)) {
                    SDL_UnlockSurface(surface_);
                }
            }

            SDL_Surface* get() { return surface_; }

        private:
            surface_lock(const surface_lock&);
            surface_lock& operator=(const surface_lock&);
            
        private:
            SDL_Surface* surface_;
        };

        class event_queue: public jacui::event_queue,
            private resize_event, 
            private redraw_event, 
            private mouse_event, 
            private keyboard_event, 
            private timer_event 
        {
        public:
            event_queue();

            event* wait();

            event* poll();

            void push(event*);

            timer_event::timer_type set_timeout(unsigned long ms);

            timer_event::timer_type set_interval(unsigned long ms);

            bool clear_timer(timer_event::timer_type timer);

            void quit();

        private:
            event_type type() const;

            const char* name() const;

            void cancel();

            size2d size() const;

            rect2d rect() const;

            modmask_type modifiers() const;

            button_type button() const;

            point2d point() const;

            key_type key() const;

            wchar_t wchar() const;

            timer_type timer() const;

        private:
            event* user() const;

            bool is_user() const;

            bool is_timeout() const;

            bool is_interval() const;

            timer_type make_timer();

        private:
            event_queue(const event_queue&);
            event_queue& operator=(const event_queue&);

        private:
            SDL_Event event_;

            enum { max_timers = 128 };
            SDL_TimerID timers[max_timers];
            timer_type ntimer;
        };

        class init {
        public:
            init();
            ~init();

        private:
            static int count;

        private:
            init(const init&);
            init& operator=(const init&);
        };

        inline surface_type* make_surface(SDL_Surface* p) {
            if (!p)
                throw_error("error creating surface");
            return static_cast<surface_type*>(p);
        }

        inline surface_type* copy_surface(surface_type* p) {
            return p ? make_surface(SDL_ConvertSurface(p, p->format, p->flags)) : 0;
        }

        inline cursor_type* make_cursor(SDL_Cursor* p) {
            if (!p)
                throw_error("error creating cursor");
            return static_cast<cursor_type*>(p);
        }

        inline SDL_RWops* make_rwops(const void* s, std::size_t n) {
            SDL_RWops* p = SDL_RWFromConstMem(s, n);
            if (!p)
                jacui::detail::throw_error("error creating memory resource");
            return p;
        }

        inline SDL_RWops* make_rwops(const std::string& s) {
            return make_rwops(s.data(), s.size());
        }

        inline SDL_Rect make_rect(point2d p) {
            SDL_Rect rect = { p.x, p.y, 0, 0 };
            return rect;
        }

        inline SDL_Rect make_rect(size2d s) {
            SDL_Rect rect = { 0, 0, s.width, s.height };
            return rect;
        }

        inline SDL_Rect make_rect(rect2d r) {
            SDL_Rect rect = { r.x, r.y, r.width, r.height };
            return rect;
        }

        inline SDL_Color make_color(color c) {
            SDL_Color color = { c.r, c.g, c.b, 0 };
            return color;
        }

        inline Uint32 map_color(SDL_PixelFormat* fmt, const color& c) {
            return SDL_MapRGBA(fmt, c.r, c.g, c.b, c.a);
        }

        inline color map_pixel(SDL_PixelFormat* fmt, Uint32 pixel) {
            color c;
            SDL_GetRGBA(pixel, fmt, &c.r, &c.g, &c.b, &c.a);
            return c;
        }
    }
}

namespace {
    jacui::detail::init jacui_init_guard_;
}

#endif
