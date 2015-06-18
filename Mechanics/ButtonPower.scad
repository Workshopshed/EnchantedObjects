module logo(radius,height) {
	union() {
		del = 1;
		scale = (radius/5);
		band = scale / 2.5;
		angle = 27;
		//Arc
		difference() {
				cylinder(h=height,r=3*scale,center=true,$fn=50);
				cylinder(h=height+del,r=(3*scale)-2*band,center=true,$fn=50);
				translate([0,2.2*scale,0])
					cube(size = [2*scale,2*scale,height+del], center = true);
			}
		//Bar 
		translate([0,scale,-height/2])
			hull() {
				cylinder(h=height,r=band,centre=true,$fn=50);
				translate([0,2.2*scale,0])
					cylinder(h=height,r=band,centre=true,$fn=50);
			}
		translate([sin(-angle)*((3*scale)-band),cos(-angle)*((3*scale)-band),0])
			cylinder(h=height,r=band,center=true,$fn=50);
	    translate([sin(angle)*((3*scale)-band),cos(angle)*((3*scale)-band),0])
			cylinder(h=height,r=band,center=true,$fn=50);
					
	}
}

module button_power() {
	union() {
		//Cap
		difference () {
			cylinder(h=2.5,r1=5.2,r2=5,center=true,$fn=50);
			translate([0,0,1.5])
				logo(6.4,1);
		}
		//Shank
		translate([0,0,-3])
			cylinder(h=5.5,r=3.3,center=true,$fn=50);
		translate([1,3,-5.0])
			sphere(0.5,$fn=50);
	}
}

rotate([0,180,0])
	button_power();
