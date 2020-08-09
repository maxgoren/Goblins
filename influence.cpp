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
#include <tuple>
#include <string>
#include "BearLibTerminal.h"
#include "helpers.h"
#include "basic_objects.h"
#include "basic_ent.h"
#include "bfMapper.h"
#include "colors.h"
bool showvals = false;


void drawAll(World* map, ent* me, MaxCode::list<ent*> gobs)
{
  struct colors red = {255 , 0, 0};
  struct colors yellow = {255, 160, 0};
  struct colors blue = {0, 0, 255};
  struct colors pizza;
  int level;
  float mix;
 std::string dist = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*+?";
 int x, y;

 for (x = 0; x < 80; x++)
 {
  for (y = 0; y < 40; y++)
  {
      level = map->layout[x][y].level;
      terminal_layer(1);
      if (showvals == true)
      {
        mix = level /2 ;
        pizza = fadeColors(red,blue,mix/10);
        if (level > 20)
        { pizza = {0,0,255}; }
        terminal_color(color_from_argb(255, pizza.r, pizza.g, pizza.b));
        if (map->layout[x][y].level < 72)
        {
          terminal_printf(x,y,"%c", dist.at(level));
        } else {
          terminal_print(x,y,".");
        }
    	} else {
    	   terminal_print(x,y,"0");
      }
	
	  if (map->layout[x][y].blocks == true && map->layout[x][y].populated == false)
	  {
	    terminal_layer(1);
	    terminal_color("white");
	    terminal_print(x, y, "#");
	  }
  }
 }

  me->render();
  ent* g;
  for (int p = 1; p <= gobs.size(); p++)
  {
    gobs.at(p)->render();
  }
}

int main()
{
 int k;
 terminal_open();
 terminal_set("window: title='MaxCodes.info Influence Map', size=80x28;");
 bool turn = true;
 World* Map;
 ent* me;
 ent *g;
 MaxCode::list<ent*> gobs;
 Point Goal({51,6,'$'});
 Map = new World(80, 40);
 me = new ent(10,10,666,'@');
 g = new ent(56,5,999,'G');
 gobs.push(g);
 Map->sampleMap();
 bfMapper bf(Map);
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
    case TK_1:
     showvals = !showvals; break;
    case TK_Q: terminal_close(); exit(0); break;
    default: break;
   }
   bf.bFS(me->pos);
   turn = false;
  }
 }
   if (turn==false)
   { 
      bf.moveEnt(gobs.at(1));
     turn = true; 
  }
  drawAll(bf.map, me, gobs);
  terminal_refresh();
 }
 terminal_close();
 return 0;
}
