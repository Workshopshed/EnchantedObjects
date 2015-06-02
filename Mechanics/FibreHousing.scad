
difference() {
cube([33,10,7]);
//Debugging Socket	
translate([6,-1,-1])
	cube([9,7,10]);
//Champhered Corners	
translate([0,6,-1])
	rotate([0,0,45])
	cube([15,10,10]);
translate([26,13,-1])
	rotate([0,0,-45])
	cube([18,10,10]);
translate([31.5,-13.5,-1])
	rotate([0,0,45])
	cube([18,10,10]);
translate([-12,0.5,-1])
	rotate([0,0,-45])
	cube([18,9.5,10]);	
//Mounting Holes
translate([3,3,5])
	cylinder(d=3.2,h=12,center=true,$fn=25);
translate([30,3,5])
	cylinder(d=3.2,h=12,center=true,$fn=25);
//Light holes
s = 11.0/7.0;
for(i = [0:1:6]) 
	translate([17+(i*s),2,-1])
	cube([0.5,1,12]);
}
