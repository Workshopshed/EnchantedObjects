module housing(radius,height,curve_radius) {
	detail = 70;
	doughnut = radius-curve_radius;
	cylinder_height = height - curve_radius;
	difference() {
		union() {
		rotate_extrude(convexity = 30, $fn = detail)
			translate([doughnut, 0, 0])
				circle(curve_radius, $fn=detail);
		//Peg
		fit = -0.25;
		pegh = 1;
		pegr = 3+fit;
		translate([0, 0, cylinder_height + (pegh/2)])
			cylinder(h = pegh+1, r=pegr, $fn=detail, center = true);
		//Outer Cylinder
		translate([0, 0, cylinder_height/2])
			cylinder(h = cylinder_height, r=radius, $fn=detail, center = true);
		//Inner filler
		translate([0, 0, -curve_radius/2])
			cylinder(h = curve_radius, r=doughnut, $fn=detail, center = true);
		}
	magnetr = 3;
	magneth = 1;
	//Hole for magnet
	translate([0, 0, (magneth/2)-(curve_radius)-0.5])
			cylinder(h = magneth+0.5, r=magnetr, $fn=detail, center = true);
		
	}
}

housing(7,5,2);

