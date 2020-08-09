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
#include <array>
#include <unordered_map>
#include <string>
#include <queue>
#include "BearLibTerminal.h"
#include "helpers.h"
#include "basic_objects.h"
#include "basic_ent.h"
#include "dijk.h"
#include "bfirst.h"
#include <benchmark/benchmark.h>

//For demonstarposes only
//dont be like me, dont use global anything.
int stepstaken = 0;
bool showpath = false;
bool showfield = true;
bool bf = true;
bool ast = true;
std::vector<Point> path;
std::vector<Point> bpath;
std::vector<Point> aspath;
void drawAll(World* map)
{
 int x, y;
 int level;
 for (x = 0; x < 80; x++)
 {
  for (y = 0; y < 40; y++)
  {
    level = map->layout[x][y].level;
    terminal_color(map->layout[x][y].color);
    terminal_printf(x,y,"%c", map->layout[x][y].s);
    if (bf == true && map->layout[x][y].s == '*')
    {
      terminal_color("magenta");
      terminal_printf(x,y,"%c", map->layout[x][y].s);
    }
    }
  }
  for (auto p : path)
  {
    terminal_layer(3);
    terminal_color("blue");
    terminal_print(p.x,p.y,"*");
  }
  for (auto a : aspath)
  {
    terminal_layer(3);
    terminal_color("yellow");
    terminal_print(a.x,a.y, "*");
  }
}




int main()
{
 int k;
 bool turn=true;
 terminal_open();
 terminal_set("window: title='dj', size=80x28;");
 World* Map;
 ent* me;
 Point Goal(66,3,'$');
 Map = new World(80, 40);
 me = new ent(10,10,666,'@');
 Map->sampleMap(Goal);
 dijk dk(Map);
 bFirst bf(Map);
 
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
    case TK_1: path.clear();path = dk.getPath(me->pos, Goal, false); 
    showpath = true;
               break;
    case TK_2: aspath.clear(); aspath = dk.getPath(me->pos, Goal, true); 
    showpath = true;
               break;
    case TK_3: bpath.clear(); bpath = bf.getPath(me->pos, Goal); break;
    case TK_4: showfield = !showfield; showpath = !showpath; break;
    case TK_Q: terminal_close(); exit(0); break;
    default: break;
   }
    turn = false;
    }
  }
  if (turn == false)
  {
    turn = true;
  }
  drawAll(dk.map);
  me->render();
  terminal_refresh();
 }
 terminal_close();
 return 0;
}
