//Wood parts

//Servo model
//http://www.thingiverse.com/thing:697243
module woodparts() {
	translate([0,-55,0])
		cube([65,20,3]);

	translate([0,-30,0])
		cube([65,10,3]);

	translate([0,-15,0])
		cube([65,10,3]);

	cube([100,15,3]);

	translate([0,20,0])
		cube([100,15,3]);
		
	translate([0,40,0])
		cube([115,15,3]);	
		
	translate([0,60,0])
		cube([115,15,3]);
		
	//Servo plank
	translate([0,80,0])
		difference(){
		cube([40,30,3]);
		translate([-25,5,0]) {
			translate([30,10,-2])		
				cylinder(d=2,h=8,centre=true);
			translate([55,10,-2])		
				cylinder(d=2,h=8,centre=true);
			translate([40,10,-2])
				hull() {
					cylinder(d=12,h=8,centre=true);
					translate([8,0,0])	
					cylinder(d=4,h=8,centre=true);
					}
			}
		}
		
	//Back board
		
	translate([0,115,0])
		difference(){
		cube([100,97,3]);
		translate([12,50,-2])		
			cylinder(d=10,h=8,centre=true);
		translate([82,28,-2])
			hull() {
				cylinder(d=6,h=8,centre=true);
				translate([0,44,0])	
				cylinder(d=6,h=8,centre=true);
			}
		}
}
	
woodparts();