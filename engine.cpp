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
#include "engine.h"

gameEngine::gameEngine(int mw, int mh)
{
    //establish map rep
    this->mapW = mw;
    this->mapH = mh;
    this->layout = new_field(mw, mh);
    dmap = new dijkstra_map(mw, mh);
}

void gameEngine::config()
{
    cave.setup(mapW, mapH);
    layout = cave.automaton(layout);
    player = new Actor({50,20}, 666, '@');
    ai.config(layout, mapW, mapH);
}

void gameEngine::main_loop()
{
    bool player_turn = true; //this is a very basic way of controlling game state
    int key;
    while (true)
    {
        terminal_clear();
        if (terminal_has_input() && player_turn == true) //this allows for non blocking input
        {
            handle_input(); 
            player_turn = false;
            
        }
        if (player_turn == false) 
        {
            handle_ai();
            player_turn = true;
        }
        handle_render();
        terminal_refresh();
    }
}

void gameEngine::handle_ai()
{
    dmap->dijk_map(layout, player.pos);
    ai.take_turn(layout);
}

void gameEngine::handle_input()
{
    int key = terminal_read();
        switch(key)
        {
            case TK_UP:    player.move(layout, 0,-1); break;
            case TK_DOWN:  player.move(layout, 0, 1); break;
            case TK_LEFT:  player.move(layout,-1, 0); break;
            case TK_RIGHT: player.move(layout, 1, 0); break;
            case TK_Q: terminal_close();
                                exit(0);
                                break;
            default: break;
        }   
}

void gameEngine::handle_render()
{
    int px, py;
    int camerax, cameray;
    //render map, with scrolling:
    std::tie(camerax,cameray) = main_render(layout, player.getPos());
    //get translation coords for actor/item rendering
    int ax = player.pos.x;
    int ay = player.pos.y;
    std::tie(px,py) = player_to_cam(ax, ay, camerax, cameray);
    ai.render(camerax,cameray);
    player.render(px,py);
    terminal_color("red");
    terminal_printf(2,2,"%d / %d", px,py);
}
