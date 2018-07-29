/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef _CURVE_H_
#define _CURVE_H_

#include "window.h"

class CurveWindow: public Window {
  public:
    CurveWindow(Window * parent, const rect_t & rect, std::function<int(int)> function, std::function<int()> position=nullptr):
      Window(parent, rect),
      function(std::move(function)),
      position(std::move(position))
    {
    }

    void setOnPressHandler(std::function<void()> handler)
    {
      onPress = handler;
    }

    void checkEvents() override
    {
      // will always force a full window refresh
      if (position) {
        invalidate();
      }
    }

    void addPoint(const point_t & point);

    void clearPoints();

    void paint(BitmapBuffer * dc) override;

    bool onTouchEnd(coord_t x, coord_t y) override;

  protected:
    std::function<int(int)> function;
    std::function<int()> position;
    std::function<void()> onPress;
    std::list<point_t> points;
    void drawBackground(BitmapBuffer * dc);
    void drawCurve(BitmapBuffer * dc);
    void drawPosition(BitmapBuffer * dc);
    void drawPoint(BitmapBuffer * dc, const point_t & point);
    coord_t getPointX(int x);
    coord_t getPointY(int y);
};

#endif // _CURVE_H_
