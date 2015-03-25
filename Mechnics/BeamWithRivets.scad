//Hull test
clearance=0.6;

module beam(length,width,height,hole) {
	difference() {
		//Body
		hull(){
		cylinder(d=width,h=height,center=true);
		translate([length/2,0,0])
			cylinder(d=width*1.8,h=height,center=true);
		translate([length,0,0])
			cylinder(d=width,h=height,center=true);	
		};
		//Holes
		cylinder(d=hole+clearance/2,h=height*1.5,center=true,$fn=20);
		translate([length,0,0])
			cylinder(d=hole+clearance/2,h=height*1.5,center=true,$fn=20);
		translate([length/2,0,0])
			cylinder(d=hole+clearance/2,h=height*1.5,center=true,$fn=20);
	}
}

module rivet(length,diameter) {
//Length excludes that of clips, it's the lenght of the part that passes through
		head = 2.5;
		hdiameter = diameter + 1;
		difference() {
			union() {
				cylinder(d=diameter,h=length+clearance,$fn=20);
				translate([0,0,length-head+clearance])
					cylinder(r2=(diameter/2),r1=(hdiameter/2),h=head,$fn=20);	
				}
			translate([-diameter,-diameter/4,length-head-2])
				cube([diameter*2,diameter/2,head*3]);
			
				translate([diameter/2-clearance,-diameter,length-head+clearance-0.1])
					cube([diameter/2,diameter*2,head*3]);
			
				translate([-diameter+clearance,-diameter,length-head+clearance-0.1])
					cube([diameter/2,diameter*2,head*3]);
		}
		
}

module beam2(length,width,height) {
		//Body
		union() {
			hull(){
			cylinder(d=width,h=height,center=true);
			translate([length/2,0,0])
				cylinder(d=width*1.8,h=height,center=true);
			translate([length,0,0])
				cylinder(d=width,h=height,center=true);	
			};
			rivet(5,3);
			translate([length,0,0])
				rivet(5,3);
		}
}

beam(60,10,2,3);
translate([0,20,0])
		beam2(60,8,2);