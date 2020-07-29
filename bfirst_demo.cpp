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

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <unordered_map>
#include <string>
#include "BearLibTerminal.h"
#include "helpers.h"
#include "basic_objects.h"
#include "basic_ent.h"
#include "bfirst.h"
#include "bfirst.cpp"

//For demonstartion purposes only
//dont be like me, dont use global anything.
int stepstaken = 0;
bool showpath = false;
std::vector<Point> path;
void eucdist(Point, Point);
void drawAll(World* map, ent* me, ent* notMe)
{
 int x, y;
 for (x = 0; x < 80; x++)
 {
  for (y = 0; y < 40; y++)
  {
  if (map->layout[x][y].blocks == true)
  {
   terminal_layer(1);
   terminal_color("white");
   terminal_print(x, y, "#");
  } else {
   terminal_print(x, y, " ");
  }
  if (showpath == true)
  {  //this shows the path BFS came up with
    if (map->layout[x][y].s == '*')
    {
      terminal_layer(2);
      terminal_color("orange");
      terminal_print(x,y,"*");
    }
    }
 }
}
  //this is our target point.
  terminal_print(51,7,"$");
  me->render();
  notMe->render();
  if (showpath == true)
  {
    eucdist(Point({7,7,'a'}), Point({51,7,'b'}));
  }
}

void moveNotMe(ent* notMe, Point target)
{
  std::vector<Point>::iterator it;
  it = path.begin();
  std::advance(it, stepstaken);
  notMe->pos = *it;
  stepstaken++;
}
void eucdist(Point a, Point b)
{
  int x,y, dx,dy;
  dx = a.x - b.x;
  dy = a.y - b.y;
  float dist = sqrtf(dx*dx+dy*dy);
  std::cout<<a.x<<"/"<<a.y<<" "<<b.x<<"/"<<b.y<<"\n";
  for (x = a.x; x <= b.x; x++)
  {
    for (y = a.y; y <= b.y; y++)
    {
      std::cout<<x<<"/"<<y<<"\n";
      terminal_layer(3);
      terminal_color("magenta");
      terminal_print(x,y,"o");
    }
  }
  terminal_printf(45,4, "Euclidean Distance: %f", dist);
  terminal_color("orange");
  terminal_printf(44,5, "Manhattan Distance: %d", path.size());
}

int main()
{
 int k;
 bool turn=true;
 terminal_open();
 terminal_set("window: title='dj', size=80x28;");
 World* Map;
 ent* me;
 ent* notMe;
 Point Goal({51,6,'$'});
 Map = new World(80, 40);
 me = new ent(10,10,666,'@');
 notMe = new ent(7,7,212,'G');
 Map->sampleMap();
 bFirst bf(Map);
 path = bf.getPath(notMe->pos, Goal);
 while(true)
 {
  terminal_clear();
  if (terminal_has_input())
  {
  if (turn == true)
  {
   k=terminal_read();
   switch (k)
   {
    case TK_UP: me->move(Map,0,-1); break;
    case TK_DOWN: me->move(Map,0,1); break;
    case TK_LEFT: me->move(Map,-1,0); break;
    case TK_RIGHT: me->move(Map,1,0); break;
    case TK_1: showpath = true; break;
    case TK_Q: terminal_close(); exit(0); break;
    default: break;
   }
    turn = false;
    }
  }
  if (turn == false)
  {
    moveNotMe(notMe, Goal);
    turn = true;
  }
  drawAll(bf.map, me, notMe);
  terminal_refresh();
 }
 terminal_close();
 return 0;
}
