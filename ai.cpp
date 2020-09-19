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
#include "ai.h"

AI::AI()
{

}
void AI::config(field& layout, int mw, int mh)
{
    mapW = mw;
    mapH = mh;
    cd[0] = {0, -1}; cd[4] = {1,-1};
    cd[1] = {0, 1};  cd[5] = {-1, 1};
    cd[2] = {1, 0};  cd[6] = {1,1};
    cd[3] ={-1, 0};  cd[7] ={-1,-1};
    spawn(layout);
}

void AI::spawn(field& layout)
{
    pnrg rn(rd());
    int rx,ry,rid;
    do
    {
        rx = rn.getrand(1,mapH-1);
        ry = rn.getrand(1, mapH-1);
    } while(layout[rx][ry].blocks);
    
    rid = rn.getrand(1,31337);
    goblin = new Actor();
    goblin->setup({rx,ry},rid,'G');
    goblins.push_back(goblin);
}

void AI::take_turn(field& layout)
{
    for (auto gbln : goblins)
    {
        dmap_move(layout, gbln);
    }
}

void AI::render(int adjx, int adjy)
{
    int px,py,ax,ay;
    for (auto gbln : goblins)
    {
        ax = gbln->getPos().x;
        ay = gbln->getPos().y;
        std::tie(px,py) = player_to_cam(ax, ay, adjx, adjy);
        gbln->render(px, py);
    }
}

void AI::dmap_move(field& layout, Actor* gbln)
{
    pnrg rn(rd());
    std::vector<int> lvls;
    bool tiebreak = false;
    Point gPos = gbln->getPos();
    int bestVal = 666;
    Point bestDir;
    Point chk;
    for (auto i = 0; i < 4; i++)//4 for manhattan neighbors, 8 for diaganol movement
    {
        chk = {gPos.x + cd[i].x, gPos.y+cd[i].y};
        chk.level = layout[chk.x][chk.y].level;
        if (gbln->can_walk(layout, chk))
        {
            if (chk.level < bestVal)
            {
                bestVal = layout[chk.x][chk.y].level;
                bestDir = cd[i];
                lvls.push_back(bestVal);
            }
        }
    }
    if (lvls.size() > 1)
    {
        for (auto i = 0; i < lvls.size(); i++)
        {
            if (lvls[i] != lvls[0])
            {
                tiebreak = false;
                break;
            } else {
                tiebreak = true;
            }
        }
    }
    if (tiebreak == false)
    {
      gbln->move(layout, bestDir.x, bestDir.y);
    } else {
        do {
            bestDir = cd[rn.getrand(0,7)];
            chk = {gPos.x+bestDir.x, gPos.y+bestDir.y};
        }while (gbln->can_walk(layout, chk) == false);
        std::cout<<"tiebreaker!\n";
        gbln->move(layout, bestDir.x, bestDir.y);
    }
}