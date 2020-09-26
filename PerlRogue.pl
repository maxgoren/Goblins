#!/usr/bin/perl
use List::Util qw/min max/;
$maxw = 80;            #map width
$maxh = 40;            #map height
$numRooms = 15;
@rooms = [];
$playerx = $maxw / 2;  #player position
$playery = $maxy / 2;  #starting right in the middle of the $map
$blocking = ' ';       #cant cross tile
$clear = '.';          #can cross tile
for ($y = 0; $y < $maxh; $y++) {        #Initialize our map layout
  for ($x = 0; $x < $maxw; $x++) {      #to contain all blocking tiles.
  $map[$y][$x] = $blocking;
  }
}
srand($time ^ $$ ^ unpack "%32L*", `ps wwax | gzip`); #well thats certainly one way
                                                      #to seed rand();
&make_rooms;
$map[$playerx][$playery] = "@";       #place our player on the map;
foreach (@rooms) {
  print $_[$_];
}

while (chomp($in = <>) ne "quit") {
 $oldpx = $playerx; $oldpy = $playery;
 if ($in eq "u") { $playery--; &move_player; }         #doesn't matter the language,
 if ($in eq "d") { $playery++; &move_player; }       #this looks awfully familiar :-p
 if ($in eq "l") { $playerx--; &move_player; }
 if ($in eq "r") { $playerx++; &move_player; }
 &render;
}
sub move_player {
  $map[$oldpy][$oldpx] = $map[$playery][$playerx];
  $map[$playery][$playerx] = "@";
}

sub render {
 for ($y = 0; $y < $maxh; $y++) {
   for ($x = 0; $x < $maxw; $x++) {
    print $map[$y][$x];
   }
   print "\n";
 }
}



sub make_rooms {

  for ($i = 0; $i < $numRooms; $i++) 
  {
   OMG:
    $rw = int(rand() * 10) + 4;              #room width
    $rh = int(rand() * 10) + 6;		     #room height
    $x1 = int(rand() * $maxw - rw - 1) + 1;  #upper left X
    $y1 = int(rand() * $maxh - rh - 1) + 1;  #upper left Y
    $x2 = $x1 + $rw;			     #lower right X
    $y2 = $y1 + $rh;			     #lower right Y
    print "Trying for Room $i: $x1:$y1/$x2:$y2...\n";
    if ($i == 0)
    {
      $rooms[$i] = ([$x1, $y1, $x2, $y2]); #first room made doesnt need to check for collision
    } else {
     foreach $yo (@rooms) 
     {
      $t = 0;							#Make sure the room we made doesnt
       if ($x1 <= $rooms[$t][2] && $x2 >= $rooms[$t][0] &&	#coolide with the previously made Rooms
           $y1 <= $rooms[$t][3] && $y2 >= $rooms[$t][1]) 
       {
                print "Collision.\n";
       	        goto OMG; #start over
       }
       $t++;
      }

      #if the room did not overlap, its good, and we keep it
      $rooms[$i] = ([$x1, $y1, $x2, $y2]);
      print "Success!\n";
      # places the room on the map
      for ($x = $x1; $x < $x2; $x++) { 
        for ($y = $y1; $y < $y2; $y++) { 
            $map[$y][$x] = $clear; 
        } 
      }

      #gets the coordinates for roughly the middle of the room
      $newx = int(($x1 + $x2) / 2);
      $newy = int(($y1 + $y2) / 2);
      if ($i == 0) 
      {
         $playerx = $newx; #place the player in the first room made 
         $playery = $newy;
      } else {
         $prevx = int(($rooms[$i - 1][0] + $rooms[$i - 1][2]) / 2);
         $prevy = int(($rooms[$i - 1][1] + $rooms[$i - 1][3]) / 2);
         if ( int((rand() * 2) + 1) == 1) #flip a coin to go verticle then horizontal, or horizontal than verticale.
         { 
 	     &vtun($prevy,$newy,$newx); 
	     &htun($prevx,$newx,$prevy); 
         } else { 
             &htun($prevx,$newx,$newy); 
             &vtun($prevy,$newy,$prevx); 
         }
      } 
     }
   }
}


#tunnel verticle
sub vtun {
 my ($a1, $a2, $b) = @_; 
  for ($t = min($a1, $a2); $t < max($a1, $a2); $t++) {
   $map[$t][$b] = $clear;
  }
}

#tunnel horizontal
sub htun {
 my ($a1, $a2, $b) = @_;
 for ($q = min($a1, $a2); $q < max($a1,$a2); $q++) {
   $map[$b][$q] = $clear;
 }
}
