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
typedef unsigned int color_t;

typedef struct Point {
        int x, y;  //cardesian coordinates
        int cost;  //movement cost
        int level; //distance from [...] (Dijkstra Map)
        char symbol; //for rendering
        color_t color; //for rendering 0xAARRGGBB
        bool blocks;  //can be walked on, or is it a wall, etc
        bool populated; //is there already a character occupying this point?
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
        bool operator!=(const Point& other) const {
            return x != other.x || y != other.y;
        }
        bool operator<(const Point& other) const {
            return std::tie(x,y) < std::tie(other.x,other.y);
        }
        bool operator>(const Point& other) const {
            return std::tie(x,y) > std::tie(other.x,other.y);
        }
        Point operator=(Point other) {
            x = other.x;
            y = other.y;
            cost = other.cost;
            level = other.level;
            symbol = other.symbol;
            color = other.color;
            blocks = other.blocks;
            populated = other.blocks;
            return *this;
        }
        Point(int x, int y) : x(x), y(y) { }
        Point()
        {
        }

} Point;

typedef std::vector<std::vector<Point>> field;

field new_field(int width, int height)
{
    int x, y;
    field retfield;
    retfield.resize(width+2, std::vector<Point>(height+2));
    
    
    for (x = 0; x < width; x++)
    {
        for (y = 0; y < height; y++)
        {
          retfield[x][y].x = x;
          retfield[x][y].y = y;
          retfield[x][y].cost = 1;
          retfield[x][y].level = 1;
          retfield[x][y].symbol = '.';
          retfield[x][y].color = 0xFFff00ff;
          retfield[x][y].blocks = false;
          retfield[x][y].populated = false;
        }
    }
    return retfield;
}