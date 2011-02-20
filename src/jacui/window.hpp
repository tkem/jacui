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

#ifndef JACUI_WINDOW_HPP
#define JACUI_WINDOW_HPP

#include "surface.hpp"
#include "cursor.hpp"
#include "event.hpp"

#include <string>

namespace jacui {
    /**
       \brief jacui window class
    */
    class window {
    public:
        /**
           \brief window creation flags type
        */
        typedef unsigned int flags_type;

        /**
           \brief open window in fullscreen mode
        */
        static const flags_type fullscreen;

        /**
           \brief prevent resizing of window
        */
        static const flags_type noresize;

        /**
           \brief hide window frame
        */
        static const flags_type noframe;

    public:
        /**
           \brief create a window with a specified caption
        */
        explicit window(const std::string& caption, flags_type f = 0);

        /**
           \brief create a window with a specified caption and size
        */
        window(const std::string& caption, const size2d& size, flags_type f = 0);

        /**
           \brief create a window with a specified caption and size
        */
        window(const std::string& caption, std::size_t width, std::size_t height, flags_type f = 0);

        /**
           \brief destroy a window
        */
        ~window();

        /**
           \brief the window's size
        */
        size2d size() const;

        /**
           \brief the window's width
        */
        std::size_t width() const;

        /**
           \brief the window's height
        */
        std::size_t height() const;

        /**
           \brief the window's caption
        */
        std::string caption() const;

        /**
           \brief set the window's caption
        */
        void caption(const std::string& s);

        /**
           \brief the window's view port
        */
        surface& view();

        /**
           \brief the window's view port
        */
        const surface& view() const;

        /**
           \brief the window's event queue
        */
        event_queue& events();

        /**
           \brief the window's event queue
        */
        const event_queue& events() const;

        /**
           \brief enable or disable the window's mouse cursor
        */
        void cursor(bool enable);

        /**
           \brief set the window's mouse cursor
        */
        void cursor(const jacui::cursor& c);

        /**
           \brief resize a window
        */
        void resize(const size2d& size);

        /**
           \brief resize a window
        */
        void resize(std::size_t width, std::size_t height);

        /**
           \brief update a window
        */
        void update();

        /**
           \brief close a window
        */
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
