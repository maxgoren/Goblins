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
#include "queue.h"
#include "list.h"

class bfMapper {
  Point cdir[8];
  MaxCode::Queue<Point> que;      //i implemented my own Queue and list templates
  MaxCode::list<Point>* visited;  //this can be switched to using the STL or Boost easily.
public:
  World* map;
  void addNeighbors(Point current, int level);
  void bFS(Point origin);
  bool inBounds(Point p);
  void moveEnt(ent* g);
  bfMapper(World* map);
};


bfMapper::bfMapper(World* map)
{
   this->map = map;
   Point N({0,-1,'^'});
   Point S({0,1,'v'});
   Point E({1,0,'>'});
   Point W({-1,0,'<'});
   Point NW({-1,1});
   Point NE({1,1});
   Point SW({-1,-1});
   Point SE({1,-1}); 
   cdir[0]=E; cdir[1]=N; cdir[2]=W; cdir[3]=S;
   cdir[4]=NW; cdir[5]=SE; cdir[6]=SW; cdir[7]=NE;
}

//checks that the point is within the boundaries of the map.
bool bfMapper::inBounds(Point p)
{
     return 0 <= p.x && p.x < map->mapW && 0 <= p.y && p.y < map->mapH;
}

//analyzes adjacency list and assigns level value;
void bfMapper::addNeighbors(Point current, int level)
{
 bool beenchecked = false;
 for (auto dir : cdir)
 {
   Point next;
   next = new Point({current.x + dir.x, current.y + dir.y, dir.s});
   if (inBounds(next) && map->layout[next.x][next.y].blocks == false)
   {
      if (visited->find(next) == false)
      {
         que.push(next);
         visited->push(next);
	      map->layout[next.x][next.y].level = level;
      }
    }
  }
}

//main search function to be called
void bfMapper::bFS(Point origin)
{
   Point start;
   Point current;
   int level = 1;
   start = origin;
   visited = new MaxCode::list<Point>;
   que.push(start);
   visited->push(start);
   que.push(Point({666,666}));
   while (!que.empty())
   {
      current = que.pop();
      if (current.x == 666) {
       level++;
       que.push(Point({666,666}));
       if (que.front().x == 666)
          break;
      }
      addNeighbors(current, level);
   }
   que.clear();
}

//for moving npc's around the map
void bfMapper::moveEnt(ent* g)
{
  int bestValue = 1000;
  Point best;
  Point checking;
  for (auto dir : cdir)
  {
    checking.x = g->pos.x + dir.x;
    checking.y = g->pos.y + dir.y;
    checking.level = map->layout[checking.x][checking.y].level;
    if (checking.level < bestValue && map->layout[checking.x][checking.y].blocks == false && map->layout[checking.x][checking.y].populated == false)
    {
      bestValue = checking.level;
      best = checking;
    }
  }
  map->layout[g->pos.x][g->pos.y].blocks = false;
  map->layout[g->pos.x][g->pos.y].populated = false;
  g->pos = best;
  map->layout[g->pos.x][g->pos.y].blocks = true;
  map->layout[g->pos.x][g->pos.y].populated = true;
}

