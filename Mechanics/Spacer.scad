//Hexagon from http://svn.clifford.at/openscad/trunk/libraries/shapes.scad
// size is the XY plane size, height in Z
module hexagon(size, height) {
  boxWidth = size/1.75;
  for (r = [-60, 0, 60]) rotate([0,0,r]) cube([boxWidth, size, height], true);
}

module spacer(size, height,hole) {
	difference() {
		hexagon(size,height);
		translate([0,0,-height/2-1])	
			cylinder(d=hole,height+2,centre=true,$fn=32);	
	}
}

spacer(5.2,11,3.7);