module wifi(radius,height) {
	union() {
		del = 1;
		band = 0.45;
		scale = (radius/4);
		difference () {
			for ( i = [2 : 4] ) {
				difference() {
					cylinder(h=height,r=i*scale,center=true,$fn=50);
					cylinder(h=height+del,r=(i-band)*scale,center=true,$fn=50);
				}
			}
			translate([2.5*scale,0,0])
				cube(size = [5*scale,9*scale,height+del], center = true);
			rotate([0,0,20])
				translate([0,2.5*scale,0])
					cube(size = [9*scale,5*scale,height+del], center = true);
		}
		cylinder(h=height,r=band*(radius/4),center=true,$fn=50);
	}
}

module button_wifi() {
	union() {
		//Cap
		difference () {
			cylinder(h=3,r1=5.2,r2=5,center=true,$fn=50);
			translate([1.8,2.6,1.5])
				wifi(6.5,1);
		}
		//Shank
		translate([0,0,-3])
			cylinder(h=6,r=3.4,center=true,$fn=50);
		translate([1,3,-5.5])
			sphere(0.5,$fn=50);
	}
}

rotate([0,180,0])
	button_wifi();