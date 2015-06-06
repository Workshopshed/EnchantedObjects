module panel(w,l,height){
	difference() {
	cube([w,l,height]);
	translate([-1,10,-3])
		cube([w+2,l-20,height]);				
	//Light holes
	for(i = [0:1:3]) {	
		translate([w/2,70 + i*4,height/2])
			cylinder(d=2.5,h=height+2,center=true,$fn=25);		
	}
    //Switch
	translate([w/2,16,height/2])
		cylinder(d=7,h=height+2,center=true,$fn=25);
	translate([w/2,27,height/2])
		cylinder(d=7,h=height+2,center=true,$fn=25);
	
	
	//Mounting holes
	translate([w/2,5,height/2])
		rotate([0,90,0])
			cylinder(d=3.2,h=w+2,center=true,$fn=25);
	translate([w/2,l-5,height/2])
		rotate([0,90,0])
			cylinder(d=3.2,h=w+2,center=true,$fn=25);		
	}
}

rotate([0,180,0])
	panel(12,99,6);