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
#include <vector>
#include <array>
#include <queue>
#include "list.h"  //this is in the containers folders, the reason i use this is STL's poor implementation (imo) of find();

typedef std::vector<std::vector<Point>> field; //nicer looking code, less typing.

void dijkstra_walk(field layout, ent* g);  //an example of how to use the generated map for AI movement

class dijkstra_map {
private:
  std::array<Point,8> cdir;
  std::queue<Point> que;
  MaxCode::list<Point> visited;
  int mapW;
  int mapH;
public:
  void addNeighbors(Point current, int level);
  void make_map(Point origin); //created the Dijkstra Map
  inline bool inBounds(Point p);
  dijkstra_map(int mapW, int mapH);
};


dijkstra_map::dijkstra_map(int mapW, int mapH)
{
   this->mapW = mapW;
   this->mapH = mapH;
   cdir[0] = {0,-1};
   cdir[1] = {0,1};
   cdir[2] = {1,0};
   cdir[3] = {-1,0};
   cdir[4] = {-1,1};
   cdir[5] = {1,1};
   cdir[6] = {-1,-1};
   cdir[7] = {1,-1}; 
}

//checks that the point is within the boundaries of the map.
inline bool dijkstra_map::inBounds(Point p)
{
     return p.x > 0 && p.x < mapW && p.y > 0 && p.y < mapH;
}

//adds any unseen neighbors to the queue
field dijkstra_map::addNeighbors(field layout, Point current)
{
 Point next;
 for (auto dir : cdir)
 {
   next = {current.x + dir.x, current.y + dir.y};
   if (inBounds(next) && layout[next.x][next.y].blocks == false)
   {
      if (visited.find(next) == false)
      {
         que.push(next);
         visited.push(next);
	 layout[next.x][next.y].level = current.level + 1;
      }
    }
  }
  return layout;
}

//main search function to be called
field dijkstra_map::make_map(field layout, Point start)
{
   visited.clear();
   Point current;
   start.level = 1;
   que.push(start);
   visited.push(start);
   while (!que.empty())
   {
      current = que.front();
      que.pop();
      addNeighbors(layout, current);
   }
  return layout;
}

//This is one method of using dijkstra maps for AI movement
void dijkstra_move(field layout, ent* goblin)
{
  int bestValue = 1000;
  Point best;
  Point checking;
  for (auto dir : cdir)
  {
    checking.x = g->pos.x + dir.x;
    checking.y = g->pos.y + dir.y;
    checking.level = layout[checking.x][checking.y].level;
    if (checking.level < bestValue && layout[checking.x][checking.y].blocks == false && layout[checking.x][checking.y].populated == false)
    {
      bestValue = checking.level;
      best = checking;
    }
  }
  layout[goblin->pos.x][goblin->pos.y].blocks = false;
  layout[goblin->pos.x][goblin->pos.y].populated = false;
  
	goblin->pos = best;
  
  layout[goblin->pos.x][goblin->pos.y].blocks = true;
  layout[goblin->pos.x][goblin->pos.y].populated = true;
}

