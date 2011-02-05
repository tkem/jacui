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

#ifndef JACUI_WINDOW_H
#define JACUI_WINDOW_H

#include "surface.h"
#include "event.h"

#include <string>

namespace jacui {
    /**
       \brief JACUI window class
    */
    class window {
    public:
        typedef unsigned int flags_type;
        static const flags_type fullscreen;
        static const flags_type noresize;
        static const flags_type noframe;

        typedef timer_event::timer_type timer_type;

    public:
        explicit window(const std::string& title, flags_type f = 0);

        window(const std::string& title, size2d size, flags_type f = 0);

        window(const std::string& title, std::size_t width, std::size_t height, flags_type f = 0);

        ~window();

        size2d size() const;

        std::size_t width() const;

        std::size_t height() const;

        std::string title() const;

        void title(const std::string& s);

        surface& view();

        const surface& view() const;

        event_queue& events();

        const event_queue& events() const;

        void cursor(bool enable);

        void resize(size2d size);

        void resize(std::size_t width, std::size_t height);

        void update();

        void close();

    private:
        window(const window&);
        window& operator=(const window&);

    private:
        struct impl;
        impl* pimpl_;
    };
}

#endif
