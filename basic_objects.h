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

struct Point {
    int x;
     int y;
     char s;
     bool blocks;
    color_t color;
    bool operator==(const Point& other) const {
     return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
      return x != other.x || y != other.y;
    }
    Point operator=(Point other) {
      x = other.x;
     y = other.y;
      s = other.s;
      return other;
    }
    Point operator=(Point* other) {
      x = other->x;
     y = other->y;
      s = other->s;
      return *other;
    }

    bool operator < (const Point& other) const
    {
        return std::tie(x,y) < std::tie(other.x,other.y);
    }
};

class Rect {
public:
 Point uL;
 Point lR;
 int id;
 Rect(int x, int y, int w, int h)
 {
  this->uL.x = x;
  this->uL.y = y;
  this->lR.x = x + w;
  this->lR.y = y + h;
 }
};

class World {
public:
int mapW;
int mapH;
Point layout[160][80];
std::vector<Rect> zone;
void setShape(Point pos, int w, int h);
void sampleMap();
 World(int w, int h)
 {
  int x, y;
  this->mapW = w;
  this->mapH = h;
  for (x = 0; x < w; x++)
  {
   for (y = 0; y < h; y++)
   {
     this->layout[x][y].blocks = true;
   }
  }
 }

};

void World::setShape(Point pos, int w, int h)
{
 int x, y;
 for (x = pos.x; x < pos.x+w; x++)
 for (y = pos.y; y < pos.y+h; y++)
 {
 {
  this->layout[x][y].blocks = false;
  }
 }
}

void World::sampleMap()
{
  Point rm1;
  Point rm2;
  Point rm3;
  Point rm4;
  Point rm5;
  Point rm6;
  Point rm7;
  rm1.x = 5; rm1.y = 5;
  rm2.x = 12; rm2.y = 11;
  rm3.x = 19; rm3.y = 14;
  rm4.x = 44; rm4.y = 16;
  rm5.x = 46; rm5.y = 20;
  rm6.x = 59; rm6.y = 7;
  rm7.x = 42; rm7.y = 3;
  setShape(rm1, 13, 8);
  setShape(rm2, 8, 6);
  setShape(rm3, 27,2);
  setShape(rm4, 2, 6);
  setShape(rm5, 15,2);
  setShape(rm6, 2, 15);
  setShape(rm7, 30, 8);

}
