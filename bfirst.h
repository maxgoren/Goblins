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

struct hashkeyBF {
  std::size_t operator()(const Point pt) const {
      std::size_t x = std::hash<int>()(pt.x);
      std::size_t y = std::hash<int>()(pt.y >> 4);
    return x^y;
  }
};

class bFirst {
  std::array<Point,4> cdir;
  std::queue<Point> que;
  std::unordered_map<Point, Point, hashkeyBF> camefrom;
public:
  World* map;
  void addNeighbors(Point current);
  void bFS(Point origin, Point target);
  bool inBounds(Point p);
  std::vector<Point> getPath(Point, Point);
  void reset();
  bFirst(World* map);
};

bFirst::bFirst(World* map)
{
   this->map = map;
   Point N({0,-1,'^'});
   Point S({0,1,'v'});
   Point E({1,0,'>'});
   Point W({-1,0,'<'});
   cdir[0]=E; cdir[1]=N; cdir[2]=W; cdir[3]=S;
}

bool bFirst::inBounds(Point p)
{
     return 0 <= p.x && p.x < map->mapW && 0 <= p.y && p.y < map->mapH;
}

void bFirst::addNeighbors(Point current)
{
  bool beenchecked = false;
  for (auto dir : cdir)
  {
   Point next;
   next = new Point({current.x + dir.x, current.y + dir.y, dir.s});
   if (inBounds(next) && map->layout[next.x][next.y].blocks == false)
   {
     for (auto all : camefrom)
     {
       if (all.first.x == next.x && all.first.y == next.y)
         beenchecked = true;
      }
      if (beenchecked == false) {
         que.push(next);
       camefrom[next] = current;
    }
      beenchecked = false;
   }
  }
}

void bFirst::bFS(Point origin, Point target)
{
   Point start;
   Point current;
   Point previous;
   start = origin;
   que.push(start);
   camefrom[start] = start;
   while (!que.empty())
   {
      previous = current;
      current = que.front();
      que.pop();
      if (current == previous)
      {
         break;
      }
      if (current == target)
          break;
      addNeighbors(current);
   }
}

std::vector<Point> bFirst::getPath(Point start, Point target)
{
   std::vector<Point> path;
   reset();
   bFS(start, target);
   Point current = target;
   while (current != start) {
      path.push_back(current);
      current = camefrom[current];
      map->layout[current.x][current.y].s = '*';
   }
   std::reverse(path.begin(),path.end());
   path.push_back(start);
   return path;
}

void bFirst::reset()
{
 while(!que.empty())
 {
   que.pop();
 }
 camefrom.clear();
}
