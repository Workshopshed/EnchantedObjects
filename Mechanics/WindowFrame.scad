
module framepart(l,h) {
	difference(){
		cube([l,h,h]);
		translate([-h,h,-h])
			rotate([15,0,0])
				cube([l+2*h,2*h,3*h]);
	}
}

module bar(l,h) {
	difference(){
		cube([l,h,h]);
		translate([-h/2,h+h/4,-h])
			rotate([15,0,0])
				cube([l+2,2*h,3*h]);
		translate([l+h/2,-h/4,-h])
			rotate([15,0,180])
				cube([l+2,2*h,3*h]);		
	}
}

module frame(l,h){
	union() {
	framepart(l,h);
	translate([0,l,0])
		rotate([0,0,-90])
			framepart(l,h);
	translate([l,0,0])
		rotate([0,0,90])
			framepart(l,h);
	translate([l,l,0])
		rotate([0,0,180])
			framepart(l,h);
	translate([0,l/2-h/2,0])	
		bar(l,h);
	translate([l/2+h/2,0,0])
		rotate([0,0,90])	
			bar(l,h);		
	}
}

frame(15,2);

