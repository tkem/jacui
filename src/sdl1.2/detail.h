// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_SDL_1_2_DETAIL_H
#define JACUI_SDL_1_2_DETAIL_H

#include "event.h"
#include "error.h"
#include "types.h"

#include <SDL/SDL.h>

#include <string>

namespace jacui {
    namespace detail {
        // convert SDL error to sdl exception
        inline void throw_error(const std::string& msg)
        {
            const char* err = SDL_GetError();
            error e(err ? msg + ": " + err : msg);
            SDL_ClearError();
            throw e;
        }

        struct surface_type: public SDL_Surface { };

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

        class event_queue:
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
