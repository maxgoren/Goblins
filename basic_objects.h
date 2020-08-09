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
    int t_cost;
    int level;
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
    bool operator >(const Point& other) const{
       return std::tie(x,y) > std::tie(other.x,other.y);
    }
    
    Point(int x, int y, char s, int cost) : x(x), y(y), s(s), t_cost(cost) { }
    Point(int x, int y, int cost) : x(x), y(y), t_cost(cost) { }
    Point(int x, int y, char s) : x(x), y(y), s(s), t_cost(1) { }
    Point()
    {

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
Point layout[90][45];
std::vector<Rect> zone;
void setShape(Point pos, int w, int h);
void sampleMap(Point Goal);
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
     this->layout[x][y].t_cost = 100; //impossible
     this->layout[x][y].color = color_from_name("white");
     this->layout[x][y].s = '#';
   }
  }
 }

};

void World::setShape(Point pos, int w, int h)
{
 int cost = 1;
 int x, y;
 for (x = pos.x; x < pos.x+w; x++)
 for (y = pos.y; y < pos.y+h; y++)
 {
 {
  this->layout[x][y].blocks = false;
  this->layout[x][y].t_cost = cost;
  this->layout[x][y].s = ' ';
  this->layout[x][y].color = color_from_name("red");
  }
 }
}

void World::sampleMap(Point Goal)
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
  setShape(Point(65,2,0), 6, 1);
  setShape(Point(70,3,1), 2,23);
  setShape(Point(13,24,1),60,2);
  setShape(Point(13,17, 1), 2, 20);
  
   int x,y;
   for (x = 49; x < 71; x++)
   {
     for (y =5; y < 7; y++)
     {
       this->layout[x][y].blocks = false;
       this->layout[x][y].t_cost = 3;
       this->layout[x][y].s = '&';
       this->layout[x][y].color = color_from_name("green");
     }
   }
   for (x = 69; x< 73; x++)
   {
     for (y = 5; y < 7; y++)
     {
       this->layout[x][y].blocks = true;
       this->layout[x][y].s = '#';
       this->layout[x][y].t_cost = 100;
       this->layout[x][y].color = 0xffFFFFFF;
     }
   }
   for (x = 21; x < 35; x+=4)
   {
      this->layout[x][15].s = '^';
      this->layout[x][15].color=color_from_name("cyan");
      this->layout[x][15].t_cost = 4;
      this->layout[x+2][14].s = 'v';
      this->layout[x+2][14].t_cost = 4;
      this->layout[x+2][14].color=color_from_name("cyan");
      this->layout[x+3][14].t_cost = 1;
    }
    this->layout[36][15].s = '^';
    this->layout[36][15].color=color_from_name("cyan");
    this->layout[36][15].t_cost = 4;

    this->layout[36][14].s = 'v';
    this->layout[36][14].t_cost = 4;
    this->layout[36][14].color=color_from_name("cyan");

    this->layout[37][15].s = '^';
    this->layout[37][15].color=color_from_name("cyan");
    this->layout[37][15].t_cost = 4;

    this->layout[37][14].s = 'v';
    this->layout[37][14].t_cost = 4;
    this->layout[37][14].color=color_from_name("cyan");

    for (x = 40; x < 65;x++)
    {
      for (y = 7; y < 8; y++)
      {
          this->layout[x][y].color=color_from_name("yellow");
          this->layout[x][y].s = '|';
          this->layout[x][y].t_cost = 4;

          this->layout[x+7][y+2].color=color_from_name("yellow");
          this->layout[x+7][y+2].s = '|';
          this->layout[x+7][y+2].t_cost = 4;
      }
    }
  this->layout[Goal.x][Goal.y].s = Goal.s;
  this->layout[Goal.x][Goal.y].t_cost = 666; //take THAT bellman ford!
}
