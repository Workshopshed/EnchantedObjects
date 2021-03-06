clearance=0.6;

module mainbeam(length,width,height,hole) {
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
				cylinder(d=diameter,h=length+clearance,$fn=40);
				translate([0,0,length-head+clearance])
					cylinder(r2=(diameter/2),r1=(hdiameter/2),h=head,$fn=40);	
				}
			translate([-diameter,-diameter/4,length-head-2])
				cube([diameter*2,diameter/2,head*3]);
			
				translate([diameter/2-clearance,-diameter,length-head+clearance-0.1])
					cube([diameter/2,diameter*2,head*3]);
			
				translate([-diameter+clearance,-diameter,length-head+clearance-0.1])
					cube([diameter/2,diameter*2,head*3]);
		}
		
}

module pin(length,diameter,hole) {
		difference() {
				cylinder(d=diameter,h=length,center=true,$fn=40);
				cylinder(d=hole,h=length*1.2,centre=true,$fn=40);
		}
}

module linkbeam(length,width,height,hole) {
		//Body
		difference() {
		union() {
			hull(){
			cylinder(d=width,h=height,center=true);
			translate([length/2,0,0])
				cylinder(d=width*1.5,h=height,center=true);
			translate([length,0,0])
				cylinder(d=width,h=height,center=true);	
			};
		}
		//Holes
		cylinder(d=hole+clearance/2,h=height*1.5,center=true,$fn=20);
		translate([length,0,0])
			cylinder(d=hole+clearance/2,h=height*1.5,center=true,$fn=20);
		}
}

module magnetcarrier(length,width,height,hole,screw) {
		//Magnet carrier
		magpos = length/2+7;
		//Body
		difference() {
		union() {
			hull(){
			cylinder(d=width,h=height,center=true);
			translate([magpos,0,0])
				cylinder(d=width*1.8,h=height,center=true);
			translate([length,0,0])
				cylinder(d=width,h=height,center=true);	
			};
			
			//translate([length/2,0,0])
			//	cylinder(d=11,height*1.5,centre=true);
			//Pins
			translate([0,0,height]){
				pin(height+clearance,hole,screw);
				translate([length,0,0])
					pin(height+clearance,hole,screw);
			}
		}
		//hole for magnet
		translate([magpos,0,-height])
			cylinder(d=6+clearance,h=height+2.5,centre=true);
	}
}

module plate(length,width,height,pin,pinpos,hole,screw) {

		//Body
		difference() {
		union() {
			hull(){
			cylinder(d=width,h=height,center=true);
			translate([length,0,0])
				cylinder(d=width,h=height,center=true);	
			};
			//Pins
			translate([pinpos,0,pin]){
				pin(height+clearance,hole,screw);
			}
		}
		//Holes
		translate([0,0,0.7])
			cylinder(d=screw+clearance/2,h=height*1.5,center=true,$fn=20);
		translate([length,0,0.7])
			cylinder(d=screw+clearance/2,h=height*1.5,center=true,$fn=20);
		}
}

module washer(diameter,height,hole)
{
	difference() {
		cylinder(d=diameter,h=height,center=true,$fn=40);
		translate([0,0,0.7])
			cylinder(d=hole+clearance,h=height*1.2,center=true,$fn=40);
	}
}

module main() {
	mainbeam(50,10,2.5,4);
	translate([0,20,0])
			linkbeam(25,8,2,4);
	translate([0,40,0])
			linkbeam(25,8,2,4);
	translate([0,60,0])
			magnetcarrier(30,8,2,4,2);
	translate([0,80,0])
			magnetcarrier(30,8,2,4,2);
	for (i=[1:2]){
	translate([0,85+(i*15),0.5])
			plate(25,8,2.5,2,10,4,2);
	}
	translate([0,85+(3*15),0.5])
		plate(30,12,2.5,2,12,4,2);


	//Washers thinner so need moving down to base
	for (i=[1:7]){
		translate([45,10+i*15,-0.5])
			washer(8,1.5,2);
	}
}

main();