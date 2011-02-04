// -*-c++-*-
//
//   $Id$
//

#ifndef JACUI_SCREEN_H
#define JACUI_SCREEN_H

#include "surface.h"
#include "event.h"
#include "cursor.h"
#include "xpmicon.h"

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

        window(const std::string& title, const xpmicon& icon, flags_type f = 0);

        window(const std::string& title, const xpmicon& icon, size2d size, flags_type f = 0);

        window(const std::string& title, const xpmicon& icon, std::size_t width, std::size_t height, flags_type f = 0);

        ~window();

        size2d size() const;

        std::size_t width() const;

        std::size_t height() const;

        std::string title() const;

        std::string title(const std::string& s);
        
        jacui::surface& surface();

        const jacui::surface& surface() const;

        void cursor(bool enable);

        void cursor(const jacui::cursor& c);

        void resize(size2d size);

        void resize(std::size_t width, std::size_t height);

        void update();

        timer_type set_timeout(unsigned long ms);

        bool clear_timeout(timer_type timer);

        timer_type set_interval(unsigned long ms);

        bool clear_interval(timer_type timer);

        void push(event* pe);

        event* poll();

        event* wait();

        void quit();

    private:
        window(const window&);
        window& operator=(const window&);

    private:
        struct impl;
        impl* pimpl_;
    };
}

#endif
