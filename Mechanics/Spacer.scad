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

translate([-1.5,1.7,0])	
	cube([3,6,0.3]);
translate([-1.5,12.5,0])	
	cube([3,5.5,0.3]);
translate([0,0,5.5])	
	spacer(5.2,11,3.7);
translate([0,10,8])	
	spacer(5.2,16,3.7);
translate([0,20,3])	
	spacer(5.2,6,3.7);