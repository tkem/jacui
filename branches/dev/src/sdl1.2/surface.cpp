/**
 * JACUI - Just Another C++ User Interface Library
 *
 * Copyright (C) 2011 The JACUI Project <perlkoenig@gmail.com>
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

#include "jacui/surface.h"
#include "detail.h"
#include "jacui/error.h"

#include <cassert>

using namespace jacui::detail;

namespace {
    inline jacui::color get_pixel(SDL_Surface* s, int x, int y)
    {
        int bpp = s->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        Uint8 *p = static_cast<Uint8*>(s->pixels) + y * s->pitch + x * bpp;

        switch (bpp) {
        case 1:
            return map_pixel(s->format, *p);

        case 2:
            return map_pixel(s->format, *reinterpret_cast<Uint16*>(p));

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return map_pixel(s->format, p[0] << 16 | p[1] << 8 | p[2]);
            else
                return map_pixel(s->format, p[0] | p[1] << 8 | p[2] << 16);

        case 4:
            return map_pixel(s->format, *reinterpret_cast<Uint32*>(p));

        default:
            return jacui::color();
        }
    }

    inline void set_pixel(SDL_Surface* s, int x, int y, const jacui::color& c)
    {
        int bpp = s->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to set */
        Uint8 *p = static_cast<Uint8*>(s->pixels) + y * s->pitch + x * bpp;

        Uint32 pixel = map_color(s->format, c);

        switch(bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *reinterpret_cast<Uint16*>(p) = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *reinterpret_cast<Uint32*>(p) = pixel;
            break;
        }
    }

    void warp(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) {
        assert(srcrect->x >= 0 && srcrect->y >= 0);
        assert(srcrect->x + srcrect->w <= src->w);
        assert(srcrect->y + srcrect->h <= src->h);

        assert(dstrect->x >= 0 && dstrect->y >= 0);
        assert(dstrect->x + dstrect->w <= dst->w);
        assert(dstrect->y + dstrect->h <= dst->h);

        for (int y = 0; y != dstrect->h; ++y) {
            for (int x = 0; x != dstrect->w; ++x) {
                int srcx = srcrect->x + x * srcrect->w / dstrect->w;
                int srcy = srcrect->y + y * srcrect->h / dstrect->h;
                int dstx = dstrect->x + x;
                int dsty = dstrect->y + y;

                set_pixel(dst, dstx, dsty, get_pixel(src, srcx, srcy));
            }
        }
    }
}

namespace jacui {
    surface::~surface()
    {
    }

    bool surface::empty() const 
    {
        SDL_Surface* s = detail();
        return !s || !s->w || !s->h;
    }

    size2d surface::size() const 
    {
        SDL_Surface* s = detail();
        return s ? size2d(s->w, s->h) : size2d(0, 0);
    }

    std::size_t surface::width() const 
    { 
        SDL_Surface* s = detail();
        return s ? s->w : 0;
    }

    std::size_t surface::height() const 
    { 
        SDL_Surface* s = detail();
        return s ? s->h : 0;
    }

    rect2d surface::clip() const
    {
        SDL_Surface* s = detail();

        if (s) {
            SDL_Rect rect;
            SDL_GetClipRect(s, &rect);
            return rect2d(rect.x, rect.y, rect.w, rect.h);
        } else {
            return rect2d();
        }
    }

    rect2d surface::clip(rect2d r)
    {
        SDL_Surface* s = detail();

        if (s) {
            SDL_Rect rect;
            SDL_GetClipRect(s, &rect);
            rect2d res(rect.x, rect.y, rect.w, rect.h);
            rect = make_rect(r);
            SDL_SetClipRect(s, &rect);
            return res;
        } else {
            return rect2d();
        }
    }

    void surface::fill(color c, rect2d r)
    {
        SDL_Surface* s = detail();

        if (s) {
            SDL_Rect rect = make_rect(r);
            if (SDL_FillRect(s, &rect, map_color(s->format, c)) < 0) {
                throw_error("error filling surface");
            }
        }
    }

    void surface::blit(const surface& s, rect2d src, rect2d dst)
    {
        SDL_Surface* psrc = s.detail();
        SDL_Surface* pdst = detail();

        if (psrc && pdst) {
            SDL_Rect srcrect = make_rect(src);
            SDL_Rect dstrect = make_rect(dst);
            
            if (srcrect.w == dstrect.w && srcrect.h == dstrect.h) {
                if (SDL_BlitSurface(psrc, &srcrect, pdst, &dstrect) < 0) {
                    throw_error("error blitting surface");
                }
            } else {
                surface_lock srclock(psrc);
                surface_lock dstlock(pdst);

                warp(psrc, &srcrect, pdst, &dstrect);
            }
        }
    }

    void surface::blit(const surface& s, rect2d src, point2d dst)
    {
        SDL_Surface* psrc = s.detail();
        SDL_Surface* pdst = detail();

        if (psrc && pdst) {
            SDL_Rect srcrect = make_rect(src);
            SDL_Rect dstrect = make_rect(dst);

            if (SDL_BlitSurface(psrc, &srcrect, pdst, &dstrect) < 0) {
                throw_error("error blitting surface");
            }
        }
    }

    void surface::blit(const surface& s, rect2d src, int x, int y)
    {
        SDL_Surface* psrc = s.detail();
        SDL_Surface* pdst = detail();

        if (psrc && pdst) {
            SDL_Rect srcrect = make_rect(src);
            SDL_Rect dstrect = { x, y, 0, 0 };

            if (SDL_BlitSurface(psrc, &srcrect, pdst, &dstrect) < 0) {
                throw_error("error blitting surface");
            }
        }
    }
}
