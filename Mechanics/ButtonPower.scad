module logo(radius,height) {
	union() {
		del = 1;
		band = 0.6;
		scale = (radius/4);
		//Arc
		difference() {
				cylinder(h=height,r=3*scale,center=true,$fn=50);
				cylinder(h=height+del,r=(3-band)*scale,center=true,$fn=50);
				translate([0,3*scale,0])
					cube(size = [2*scale,2*scale,height+del], center = true);
			}
		//Bar 
		translate([0,scale,-height/2])
			hull() {
				cylinder(h=height,r=band,centre=true,$fn=50);
				translate([0,2*scale,0])
					cylinder(h=height,r=band,centre=true,$fn=50);
			}
	}
}

module button_power() {
	union() {
		//Cap
		difference () {
			cylinder(h=5,r1=5.2,r2=5,center=true,$fn=50);
			translate([1.8,2.3,2.5])
				logo(6,1);
		}
		//Shank
		translate([0,0,-5])
			cylinder(h=6,r=3,center=true,$fn=50);
		translate([1,2.7,-7.5])
			sphere(0.5,$fn=50);
	}
}

//rotate([0,180,0])
	logo(6,1);
	//button_power();