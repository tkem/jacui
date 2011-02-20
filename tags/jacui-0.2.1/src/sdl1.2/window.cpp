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

#include "jacui/window.hpp"
#include "detail.hpp"

namespace {
    class wmsurface: public jacui::surface {
    public:
        wmsurface() {
        }

        jacui::detail::surface_type* detail() const
        {
            return jacui::detail::make_surface(SDL_GetVideoSurface());
        }
    };

    inline Uint32 make_flags(jacui::window::flags_type f)
    {
        Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF | f;
        flags ^= SDL_RESIZABLE; // inverted!
        return flags;
    }
}

namespace jacui {
    struct window::impl {
        impl(const char* caption, std::size_t width, std::size_t height, flags_type f) 
        {
            if (caption)
                SDL_WM_SetCaption(caption, caption);
            if (!SDL_SetVideoMode(width, height, 24, make_flags(f)))
                detail::throw_error("error setting video mode");
        }

        wmsurface surface;
        detail::event_queue events;
    };

    const window::flags_type window::fullscreen = SDL_FULLSCREEN;

    const window::flags_type window::noresize = SDL_RESIZABLE; // inverted!

    const window::flags_type window::noframe = SDL_NOFRAME;

    window::window(const std::string& caption, flags_type f)
        : pimpl_(new impl(caption.c_str(), 0, 0, f))
    {
    }

    window::window(const std::string& caption, const size2d& s, flags_type f)
        : pimpl_(new impl(caption.c_str(), s.width, s.height, f))
    {
    }

    window::window(const std::string& caption, std::size_t width, std::size_t height, flags_type f)
        : pimpl_(new impl(caption.c_str(), width, height, f))
    {
    }

    window::~window()
    {
        delete pimpl_;
    }

    size2d window::size() const
    {
        return pimpl_->surface.size();
    }

    std::size_t window::width() const
    {
        return pimpl_->surface.width();
    }

    std::size_t window::height() const
    {
        return pimpl_->surface.height();
    }

    std::string window::caption() const
    {
        char* s;
        SDL_WM_GetCaption(&s, 0);
        return std::string(s ? s : "");
    }

    void window::caption(const std::string& s)
    {
        SDL_WM_SetCaption(s.c_str(), s.c_str());
    }

    surface& window::view()
    {
        return pimpl_->surface;
    }

    const surface& window::view() const
    {
        return pimpl_->surface;
    }

    event_queue& window::events()
    {
        return pimpl_->events;
    }

    const event_queue& window::events() const
    {
        return pimpl_->events;
    }

    void window::cursor(bool enable)
    {
        SDL_ShowCursor(enable ? SDL_ENABLE : SDL_DISABLE);
    }

    void window::cursor(const jacui::cursor& c)
    {
        SDL_SetCursor(c.detail());
    }

    void window::resize(const size2d& size)
    {
        return resize(size.width, size.height);
    }

    void window::resize(std::size_t width, std::size_t height)
    {
        SDL_Surface* s = SDL_GetVideoSurface();

        if (!s)
            detail::throw_error("error resizing window");
        if (!SDL_SetVideoMode(width, height, 0, s->flags))
            detail::throw_error("error resizing window");
    }

    void window::update()
    {
        SDL_Flip(SDL_GetVideoSurface());
    }

    void window::close()
    {
        pimpl_->events.quit();
    }

}
