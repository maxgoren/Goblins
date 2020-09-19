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
class AI {
public:
std::array<Point, 8> cd; //compass
int mapW;
int mapH;
std::vector<Actor*> goblins;
Actor* goblin;
std::random_device rd;
void render(int adjx, int adjy);
void dmap_move(field& layout, Actor* gbln);
void take_turn(field& layout);
void spawn(field& layout);
void config(field& layout, int mapW, int mapH);
AI();
};