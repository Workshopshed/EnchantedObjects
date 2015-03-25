//Hull test

module beam(thickness) {
	
		difference() {
		union() {
			hull(){
			translate([30,0,0])
				cylinder(d=18,h=thickness,center=true);
			translate([30,20,0])
				cylinder(d=10,h=thickness,center=true);	
			};
			hull(){
			cylinder(d=10,h=thickness,center=true);
			translate([30,0,0])
				cylinder(d=18,h=thickness,center=true);
			translate([60,0,0])
				cylinder(d=10,h=thickness,center=true);
				
			};
			
		}
		//Holes
		cylinder(d=3,h=thickness*1.2,center=true,$fn=20);
		translate([30,0,0])
			cylinder(d=3,h=thickness*1.2,center=true,$fn=20);
		translate([60,0,0])
			cylinder(d=3,h=thickness*1.2,center=true,$fn=20);
		translate([30,20,0])
			cylinder(d=3,h=thickness*1.2,center=true);
	}
}

beam(10);