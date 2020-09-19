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
#include "dijkstra_map.h"

dijkstra_map::dijkstra_map(int mapW, int mapH)
{
    this->mapW = mapW;
    this->mapH = mapH;
    cd[0] = {0, -1}; cd[4] = {1,-1};
    cd[1] = {0, 1};  cd[5] = {-1, 1};
    cd[2] = {1, 0};  cd[6] = {1,1};
    cd[3] ={-1, 0};  cd[7] ={-1,-1};
    visited.resize(mapW,std::vector<bool>(mapH));
}



bool dijkstra_map::onmap(Point curr)
{
  if ((curr.x > 0 && curr.x < mapW) && (curr.y > 0 && curr.y < mapH)) 
    return true;
  
  return false;
}

void dijkstra_map::dijk_map(field& layout, Point start)
{
    std::queue<Point> frontier;
    bool ee = false;
    Point current, next;
    start.level = 0;
    frontier.push(start);
    visited[start.x][start.y] = true;
    while (!frontier.empty())
    {
        current = frontier.front();
        frontier.pop();
        for (auto dir : cd)
        {
            next = {current.x + dir.x, current.y + dir.y};
            next.level = current.level + 1;
           // std::cout<<next.level<<"\n";
            if (onmap(next))             
            {
                if (visited[next.x][next.y] == false && layout[next.x][next.y].blocks == false)
                {
                    layout[next.x][next.y].level = next.level;
                    visited[next.x][next.y] = true;
                    frontier.push(next);
                }
            }
        }
    }
    int x,y;
    for (x = 0; x < mapW; x++)
    {
        for (y = 0; y < mapH; y++)
        {
            visited[x][y] = false;
        }
    }
}


std::stack<Point> dijkstra_map::bfs_Path(field& layout, Point start, Point t)
{
  bool found = false;
  Point v;
  Point next;
  std::unordered_map<Point, Point, hashkey> camefrom;
  std::queue<Point> frontier;
  visited[start.x][start.y] = true; 
  frontier.push(start);
  camefrom[start] = start;
  while (!frontier.empty())
  {
      v = frontier.front(); frontier.pop();
      if (v == t) 
      { 
          found = true;
          break;
      }
      for (auto d : cd)
      {
          next = {v.x + d.x, v.y + d.y};
          if (onmap(next) && visited[next.x][next.y] == false)
          {
              if (layout[next.x][next.y].blocks == false)
              {
                  visited[next.x][next.y] = true;
                  camefrom[next] = v;
                  frontier.push(next);
              }
          }
      }
  }
  std::stack<Point> path;
  if (found)
  {
  while (v != start)
  {
     path.push(v);
     v = camefrom[v];
  }
      path.push(start);
  } else {
      path.push(start);
  }
  return path;
}