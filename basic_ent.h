/*
Copyright (c) 2020 Max Goren
maxgoren@icloud.com
http://www.maxcodes.info

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

class ent {
public:
Point pos;
  char ch[2];
  int id;
  bool canMove(World* Map, int x, int y);
  void move(World*, int x, int y);
  void render();
  ent(int x, int y, int id, char ch);
};

ent::ent(int x, int y, int id, char ch)
{
 this->pos.x = x;
 this->pos.y = y;
 this->ch[0] = ch;
 this->ch[1] = '\0';
 this->id = id;
}

bool ent::canMove(World* Map, int x, int y)
{
 if (Map->layout[x][y].blocks == false) {
    return true;
 } else {
   return false;
 }
}

void ent::move(World* Map, int dx, int dy)
{
 if (canMove(Map, this->pos.x + dx,this->pos.y + dy))
 {
 this->pos.x += dx;
 this->pos.y += dy;
 }
}

void ent::render()
{
 terminal_layer(4);
 terminal_color("green");
 terminal_print(pos.x, pos.y, ch);
}
