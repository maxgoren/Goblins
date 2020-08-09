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

struct hashkey {
  std::size_t operator()(const Point pt) const {
    std::size_t x = std::hash<int>()(pt.x);
    std::size_t y = std::hash<int>()(pt.y >> 4);
    return x^y;
  }
};

struct Element {
  int priority;
  Point value;
  bool operator > (Element other) const {
    return priority > other.priority;
  }
  Element(Point v, int p) : priority(p), value(v) { }
};

class dijk {
  std::array<Point,4> cdir;  
  std::priority_queue<Element, std::vector<Element>, std::greater<Element>> pque;
  std::unordered_map<Point, Point, hashkey> camefrom;
  std::unordered_map<Point, int, hashkey> effort;
public:
  World* map;
  int mapRep[90][45];
  int eucdist(Point A, Point B);
  void addNeighbors(Point current, Point target, bool astar);
  void dijkSearch(Point origin, Point target, bool astar);
  bool inBounds(Point p);
  int effort_now(Point A) const;
  int heuristic(Point A, Point B);
  std::vector<Point> getPath(Point, Point, bool astar);
  void reset();
  dijk(World* map);
};


dijk::dijk(World* map)
{
   this->map = map;
   Point N({0,-1,'^'});
   Point S({0,1,'v'});
   Point E({1,0,'>'});
   Point W({-1,0,'<'});
   cdir[0]=E; cdir[1]=N; cdir[2]=W; cdir[3]=S;
}
int dijk::heuristic(Point A, Point B)
{
   return std::abs(A.x - B.x) + std::abs(A.y - B.y);
}

bool dijk::inBounds(Point p)
{
     return 0 <= p.x && p.x < map->mapW && 0 <= p.y && p.y < map->mapH;
}

int dijk::effort_now(Point A) const
{
   return A.t_cost;
}

int dijk::eucdist(Point A, Point B)
{
  int dx = A.x - B.x;
  int dy = A.y - B.y;
  return sqrtf(pow(dx, 2) + pow(dy,2));
}


void dijk::addNeighbors(Point current, Point target, bool astar)
{

int thiscost = 0;
for (auto dir : cdir)
{
   Point next(current.x + dir.x, current.y + dir.y, dir.s );
   next.t_cost = map->layout[next.x][next.y].t_cost;
   if (inBounds(next) && map->layout[next.x][next.y].blocks == false)
   {
     for (auto all : effort)
     {
        thiscost = effort_now(next) + effort[current]; 
        if (effort.find(next) == effort.end() || thiscost < next.t_cost + effort[current]) 
        {
            effort[next] = thiscost;
            camefrom[next] = current;
            if (astar == true)
            {
                pque.emplace(next, thiscost + heuristic(next, target));
            } else {
                pque.emplace(next, thiscost);
            }
         }  
        }
      }
     }
}

void dijk::dijkSearch(Point origin, Point target, bool astar)
{
   Point start;
   Point current;
   int level = 0;
   start = origin;
   pque.emplace(start, start.t_cost);
   camefrom[start] = start;
   effort[start] = 0;
   while (!pque.empty())
   {
      current = pque.top().value;
      pque.pop();
      if (current == target)
          break;
      addNeighbors(current, target, astar);
   }
}

std::vector<Point> dijk::getPath(Point start, Point target, bool astar)
{
   this->reset();
   std::vector<Point> path;
   dijkSearch(start, target, astar);
   Point current = target;
   while (current != start) {
      path.push_back(current);
      current = camefrom[current];
      current.s = '*';
   }
   path.push_back(start);
   std::reverse(path.begin(),path.end());
   return path;
}

void dijk::reset()
{
 while (!pque.empty())
 {
  pque.pop();
 }
 camefrom.clear();
 effort.clear();
}
