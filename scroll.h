
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

//Returns coordinates for the camera's upper left corner
auto set_camera(int playerx, int playery) -> std::tuple<int,int>
{
	const int map_width = 300;
    const int map_height = 300;
    const int scr_width =  100;
    const int scr_height = 40;
    int x = playerx - scr_width / 2; //Keep the player in the middle
	int y = playery - scr_height / 2; //of the screen
 
	
	if (x < 0) { x = 0; }
	if (y < 0) { y = 0; }
	if (x > map_width - scr_width - 1) { x = map_width - scr_width - 1; }
	if (y > map_height - scr_height - 1) { y = map_height - scr_height - 1; }
 
 
	return std::make_tuple(x,y);
}
 
auto player_to_cam(int playerx, int playery, int camerax, int cameray) -> std::tuple<int,int>
{
    const int map_width = 300;
    const int map_height = 300;
    const int scr_width =  100;
    const int scr_height = 40;
   
    playerx = playerx - camerax;
    playery = playery - cameray;
 
	if (playerx < 0 || playery < 0 || playerx >= scr_width || playery >= scr_height)
    { 
		return std::make_tuple(0, 0);  //if it's outside the view, return nothing
    }
	return std::make_tuple(playerx, playery);
} 

auto main_render(field& layout, Point player_pos, std::vector<Point> fov) -> std::tuple<int, int> 
{
    const int map_width = 300;
    const int map_height = 300;
    const int scr_width =  100;
    const int scr_height = 40;
    int x, y;
    int px, py;
    int camerax, cameray;
    int mapx, mapy;
    double mix;
   // std::string lvl="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::tie(camerax,cameray) = set_camera(player_pos.x, player_pos.y);
    terminal_print(1,1,"1/1 Camera.\n");
    for (x = 0; x < scr_width; x++)
    {
        for (y = 0; y < scr_height; y++)
        {
            mapx = camerax + x;
            mapy = cameray + y;
            terminal_color(layout[mapx][mapy].color * .55);
            terminal_printf(x,y,"%c", layout[mapx][mapy].symbol);
         /*  
           If you want to see the dijkstra map visualized, uncomment this section
            if (layout[mapx][mapy].level < lvl.size()-1)
            {
                terminal_printf(x,y,"%c", lvl.at(layout[mapx][mapy].level));
            }*/
        }
    }
    int mx, my, cx, cy;
    for (auto p : fov)
    {
        std::tie(cx,cy) = player_to_cam(p.x,p.y,camerax,cameray);
        mx = p.x - camerax;
        my = p.y - cameray;
        terminal_color(layout[p.x][p.y].color);
        terminal_printf(cx,cy,"%c", layout[p.x][p.y].symbol);
    }
    return std::make_tuple(camerax,cameray);
}
