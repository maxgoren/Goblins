

What is this?
----------------
This is a basic Environment that i use when explainin Roguelike Development concepts
on my website http://www.maxcodes.info

Whats here?
--------------
The code file's here represent the minimum requirements for a "functioning rogulike world"
i did this so all of the "boiler plate" is taken care of when im discussing a certain topic.
For example if you're reading the article on basic shooting mechanics
(http://www.maxcodes.info/cgi-bin/meshugana.pl?p=proj&f=shooting) all you have to do
is include bullets.h and bullets.cpp that are created in the follow along or downloaded
from my github, and you can plug it right in, in this way you can focus on the concepts being
presented without being distracted by all the other world building stuff.
Or, if you just want a good jumping off point for creating a game of your own, this is a decent
"template world" to start with. Seeing as i release all my code under the MIT license you're
free to use it however you like.


actor.h    - This is a basic class for creating both player characters and NPC's
actor.cpp     It has the functionality necessary to move the character around on the map
             and have it displayed, etc.
             Functions are: 
             .move() - move the character on the map
             .render() - display the character in the terminal
             .canMove() used by .move() to check if a tile is a walkable or blocking, or already occupied 
             by someone else.
             .getPos() returns the characters Positions.

ai.h
ai.cpp     -This is a VERY basic AI that can control a single or multiple NPC's which navigate the map
            via dijkstra_maps
            Functions are:
            take_turn() - called by the engine to initiate the NPC's turn. currently it simply has the NPC
            navigate the map towards the player, but can be expanded to handle a range of possible NPC
            interactions
cave.h
cave.cpp   -this creates the maps for the world, it uses the four/five rule of cellular automata to create
            good looking caves of any size(it will be rather slow to make on maps > 500 tiles);
            Relevent functions:
            .config() set the size of the map
            .automaton() creates and returns the map as a 2d vector of points(discussed more below)

dijkstra_map.h   - Dijkstra maps are awesome, read about them at the following to see what their all about:
dijkstra_map.cpp   http://www.roguebasin.com/index.php?title=The_Incredible_Power_of_Dijkstra_Maps
                   http://www.roguebasin.com/index.php?title=Dijkstra_Maps_Visualized
                    Also included here is a regular breadth first search single source single point path finder.
                    Functions are:
                    .config() set up size of the map et,
                    .dijk_map() creates the dijkstra map assigning values ot each tile
                    .bfs_Path() returns a step by step path between locations in a stack, you just pop the stack
                    and move to the position it puts out.
engine.cpp
engine.h        - this is the game engine class, its not meant to be a fully fleshed out game engine
                  but it presents the concept in an easy to understand use fashion, and while not its not
                  super robust it IS adequate for a Roguelike.
                .config() to set up, this function calls the map generator and passes the map to the engine,
                    it also initializes the player, the AI, the dijkstra_map etc etc. if you are adding
                    a feature to the engine, this the place to set it up.
                .main_loop() as you can tell by the name, this is the main game loop which controls game following
                    passing control to the player and the NPC's for turns. it also calls the following
                    functions:
                .handle_input() - this is the function which captures keystrokes for playing the game, or assigning
                    keystrokes to new features etc.
                .handle_ai() - this updates the dijkstra_map between turns, as well handin control over to the AI
                    for the NPC's to do their turns.
                .handle_renders() - most things from the map to the characters have their own render functions
                    this corganizes and calls them in an organized manner, it also interacts with the functions in
                    scroll.h to handle maps that have dimensions larger than the window (scrolling maps).
                   


  layout_types.h - this is where the datastructures that make up the map are defined.
                    Point() - being gridbased, almost EVERYTHING comes down to interactions with
                             a point, from movement to item placement, level generation, EVERYTHING.
                    field - this just a stypedef around std::vector<std::vector<Point>> to make life
                            a little easier. if you thing of an actual map, this is the canvas its drawn on.
                    color_t - bear lib terminal uses an unsigned integer for representing color 
                           via ARGB as this: 0xAARRGGBB. if your familiar with HTML color codes
                           for example, green would be 0xFF00FF00;
                    new_field() is a funcion which returns a field populated with all of its Point's
                           property set to default values.
main.cpp - this is the driver program with int main() for doing basic bearlib housekeeping before setup
              and then initializing the engine and calling the main loop.
master.h - if you've ever dealt with the hell that is circular dependencies before, this helps keep all of
          the headers organized for easier use.
prng.h - just your everyday Mersenne Twister psuedo random number generator
scroll.h - these are the functions that make using a scrolling map easy to implement.


BearLibTerminal.h           --the required header and library for bearlibterminal(macosX version)
libBearLibTerminal.dylib    BearLibTerminal is NOT my creation, i'm just a fan of its use.
                            For more information about BearLibTerminal check out
                            http://foo.wyrd.name/en:bearlibterminal