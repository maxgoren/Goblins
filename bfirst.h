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

namespace std {
template <> struct hash<Point> {
  typedef Point argument_type;
  typedef std::size_t result_type;
  std::size_t operator()(const Point Pt) const noexcept {
    return std::hash<int>()(Pt.x ^ (Pt.y << 4));
  }
};
}
class bFirst {
  std::array<Point,4> cdir;
  std::queue<Point> que;
  std::unordered_map<Point, Point> camefrom;
public:
  World* map;
  int addNeighbors(Point current, Point target);
  void bFS(Point origin, Point target);
  bool inBounds(Point p);
  std::vector<Point> getPath(Point, Point);
  bFirst(World* map);
};
