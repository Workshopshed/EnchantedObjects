
module housing(thickness)
{
	difference() {
	cube([33,10,thickness]);
		translate([20.5,6,-1])
			cube([18,10,thickness+2]);
	//Debugging Socket	
	translate([6,-1,-1])
		cube([9,7,thickness+2]);
	//Champhered Corners	
	translate([0,5,-1])
		rotate([0,0,45])
		cube([10,6,thickness+2]);
	translate([27,10,-1])
		rotate([0,0,-45])
		cube([10,5,thickness+2]);
	translate([30.5,-7.5,-1])
		rotate([0,0,45])
		cube([10,5,thickness+2]);
	translate([-12,0.5,-1])
		rotate([0,0,-45])
		cube([15,9.5,thickness+2]);
	translate([24,9.5,-1])
		rotate([0,0,135])
		cube([10,5,thickness+2]);

	//Mounting Holes
	translate([3,3,thickness/2])
		cylinder(d=3.2,h=thickness+2,center=true,$fn=25);
	translate([30,3,thickness/2])
		cylinder(d=3.2,h=thickness+2,center=true,$fn=25);
	//Light holes
	s = 11.0/7.0;
	for(i = [0:1:6]) 
		rotate([-12,0,0])
		translate([17+(i*s),2,-1])
		cube([0.5,1,thickness+3]);
	}
}

housing(6);