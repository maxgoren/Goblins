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


//How it works:  automaton()->prep_fields()->place_seeds()->four_five()->flood_fill()->automaton() -> done.
//                                                            v   ^ 
//                                                      count_neighbors()
//How its used: Cave myCave(160, 40);
//              myCave.automaton();
//
//The completed cave is then available as myCave.layout;
#include "cave.h"

//need this hash to be able to use Point with std::unordered_map.
//which is used during the flood_fill stage.
struct hashkey {
  std::size_t operator()(const Point pt) const {
      std::size_t x = std::hash<int>()(pt.x);
      std::size_t y = std::hash<int>()(pt.y >> 4);
    return x^y;
  }
};


Cave::Cave()
{
    
}

void Cave::setup(int mw, int mh)
{
    int x,y;
    this->mapW = mw;
    this->mapH = mh;
  cdir[0] = {0,-1}; cdir[1] = {0,1};
  cdir[2] ={-1,1}; cdir[3] = {1,-1};
  cdir[4] = {1,0}; cdir[5] = {-1,0};
  cdir[6] = {-1,-1}; cdir[7] = {1,1};
}

void Cave::place_seed(field& layout)
{
    int x, y;
    std::random_device rd;
    pnrg rn(rd());
    for (x = 0; x < mapW; x++)
    {
        for (y = 0; y < mapH; y++)
        {
            if (rn.getrand(1,100)<43)
            layout[x][y].blocks = true;
        }
    }
}

void Cave::four_five(field& layout)
{
   int p;
   color_t dirt;
   color_t stone;
  int x, y, t;
  Point current;
  std::unordered_map<Point, bool, hashkey> wall;
  terminal_layer(0);
  terminal_bkcolor("black");
  for (x = 1; x < mapW-1; x++)
  {
      for (y = 1; y < mapH-1; y++)
      {
          t = count_neightbors(layout[x][y], layout);
          if (layout[x][y].blocks && t >= 4)
          {
              wall[layout[x][y]] = true;
              layout[x][y].symbol = '#';
              terminal_print(x,y, "#");
          } else if (!layout[x][y].blocks && t >= 5) {
              wall[layout[x][y]] = true;
              layout[x][y].symbol = '#';

              terminal_print(x,y, "#");
          } else {
              wall[layout[x][y]] = false;
              layout[x][y].symbol = '%';

                terminal_print(x,y, " ");
          }
      }
  }
  for (auto cell : wall)
  {
      if (cell.second == true)
      {
          
          layout[cell.first.x][cell.first.y].blocks = true;

      } else {
          
          layout[cell.first.x][cell.first.y].blocks = false;
      }
  }
  terminal_refresh();
}

//This function returns the number of cells which
//are blocking, for use in the four_five() function 
int Cave::count_neightbors(Point p, field& layout)
{
    int neighbors = 0;
    Point test;
    for (auto d : cdir)
    {
        test = {p.x + d.x, p.y + d.y};
        if (layout[test.x][test.y].blocks)
        {
            neighbors++;
        }
    }
    return neighbors;
}

//this isnt neccessary, it just makes a nice border
//around the caves.
void Cave::prep_fields(field& layout)
{
    int x, y, i;
    
    for (x = 0; x < mapW; x++)
    {
        for (y = 0; y < mapH; y++)
        {
            
            layout[x][y].blocks = true;
            layout[x][y].populated = false;
            layout[x][y].x = x;
            layout[x][y].y = y;
            layout[x][y].color=0xAACECECE;
        }
    }
    for (x = 1; x < mapW-1; x++)
    {
        for (y = 1; y < mapH - 1; y++)
        {
            layout[x][y].blocks = false;
            layout[x][y].x = x;
            layout[x][y].y = y;
        }
    }
    
}

//This function controls the whole show

field Cave::automaton(field& layout)
{
    int i, x, y, p;
    color_t stone;
    color_t dirt;
    prep_fields(layout);
    place_seed(layout);
    
    for (i = 0; i < 5; i++)
    {
        std::cout<<i<<" ";
        four_five(layout);
    }
    flood_fill(layout);
    put_colors(layout);
    std::cout<<"Map Ready.\n";
    return layout;
}


//This a a Basic Beadth first search flood fill
//which starts from multiple points. This ensures
//that there are no unreachable areas of the Cave.
void Cave::flood_fill(field& layout)
{
  Point current, next, visiting;
  std::queue<Point> frontier;
  std::vector<std::vector<bool>> seen;
  std::random_device rd;
  pnrg rn(rd());
  seen.resize(mapW, std::vector<bool>(mapH));
  for (auto sb : seen)
    for (auto bs : sb)
      bs = false;
  for (auto i = 0; i <5 ; i++)
  {
  do
  {
    current = {rn.getrand(3,mapW-3), rn.getrand(4,mapH-4)};
  } while (layout[current.x][current.y].blocks);
  frontier.push(current);
  seen[current.x][current.y] = true;
  }
  while (!frontier.empty())
  {
      visiting = frontier.front();
      frontier.pop();
      for (auto d : cdir)
      {
          next = {d.x + visiting.x, d.y + visiting.y};
          if (seen[next.x][next.y] == false && layout[next.x][next.y].blocks == false)
          {
            frontier.push(next);
            seen[next.x][next.y] = true;
          }
      }
  }
  int x,y;
  for (x = 0; x < mapW; x++)
  {
      for (y = 0; y < mapH; y++)
      {
          if (!seen[x][y] && !layout[x][y].blocks)
             layout[x][y].blocks = true;
      }
  }
}

void Cave::put_colors(field& layout)
{
    int x, y;
    int p;
    std::random_device rd;
    color_t dirt;
    color_t stone;
    pnrg rn(rd());
    for (x = 0; x < mapW; x++)
    {
        for (y = 0; y < mapH; y++)
        {
          
          if (layout[x][y].blocks)
          {
            p = rn.getrand(1,4);
            switch (p)
            {
                case 1: stone = 0xFF60676b; break;
                case 2: stone = 0xFF888CAD; break;
                case 3: stone = 0xFFA9A9A9; break;
                case 4: stone = 0xFFAC7954; break;
            }
            layout[x][y].blocks = stone;
          } else {
             p = rn.getrand(1,4);
             switch (p)
             {
                case 1: dirt = 0xFFDEB887; break;
                case 2: dirt = 0xFFF4A460; break;
                case 3: dirt = 0xFFA0522D; break;
                case 4: dirt = 0xFFF4A460; break;
             }
             layout[x][y].color = dirt;
          }

        }
    }
}