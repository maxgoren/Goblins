/***********************************************************************************************************
(c) 2020 Max Goren http://www.maxcodes.info - max@maxcodes.info

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions 
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT 
SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
OR OTHER DEALINGS IN THE SOFTWARE.
***********************************************************************************************************/
#include "actor.h"
Actor::Actor(Point start, int id, char s) 
{
    this->pos = start;
    this->id = id;
    this->symbol = s;
}


bool Actor::can_walk(field& layout, Point p)
{
    if (layout[p.x][p.y].blocks == false)
    {
        if (layout[p.x][p.y].populated == false)
        {
            return true;
        }
    }
    return false;
}
Point Actor::getPos()
{
     return pos; 
}
void Actor::move(field& layout, int dx, int dy)
{
    Point check = {pos.x + dx, pos.y + dy};
    if (can_walk(layout, check))
    {
        layout[pos.x][pos.y].blocks = false;
        layout[pos.x][pos.y].populated = false;
        this->pos = check;
        layout[pos.x][pos.y].blocks = true;
        layout[pos.x][pos.y].populated = true;
    }
}

void Actor::render(int adjx, int adjy)
{
   if (adjx + adjy == 0)
   {
       terminal_color(0xFFFFFF00);
       terminal_put(pos.x,pos.y,symbol);
   } else {
    terminal_color("flame");
    terminal_put(adjx, adjy, symbol);
   }
}
