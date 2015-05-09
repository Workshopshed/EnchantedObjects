
difference() {
cube([33,10,7]);
//Debugging Socket	
translate([6,-1,-1])
	cube([9,7,10]);
//Champhered Corners	
translate([0,6,-1])
	rotate([0,0,45])
	cube([15,10,10]);
translate([25,13,-1])
	rotate([0,0,-45])
	cube([18,10,10]);
//Mounting Holes
translate([3,3,5])
	cylinder(d=3.2,h=12,center=true,$fn=15);
translate([30,3,5])
	cylinder(d=3.2,h=12,center=true,$fn=15);
//Light holes
for(i = [0:1:6]) 
	translate([16+(i*1.25),2,-1])
	cube([0.5,1,12]);
}
