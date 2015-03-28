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

module beam2(length,width,height,hole) {
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

module beam3(length,width,height,hole,screw) {

		//Body
		union() {
			hull(){
			cylinder(d=width,h=height,center=true);
			translate([length/2,0,0])
				cylinder(d=width*1.8,h=height,center=true);
			translate([length,0,0])
				cylinder(d=width,h=height,center=true);	
			};
			//Magnet carrier
			translate([length/2,0,height])
				pin(height,10,6);
			//Pins
			translate([0,0,height]){
				pin(height+clearance,hole,screw);
				translate([length,0,0])
					pin(height+clearance,hole,screw);
			}
	}
}

module plate(length,width,height,hole,screw) {

		//Body
		difference() {
		union() {
			hull(){
			cylinder(d=width,h=height,center=true);
			translate([length,0,0])
				cylinder(d=width,h=height,center=true);	
			};
			//Pins
			translate([length/2,0,height]){
				pin(height+clearance,hole,screw);
			}
		}
		//Holes
		cylinder(d=screw+clearance/2,h=height*1.5,center=true,$fn=20);
		translate([length,0,0])
			cylinder(d=screw+clearance/2,h=height*1.5,center=true,$fn=20);
		}
}

module washer(diameter,height,hole)
{
	difference() {
		cylinder(d=diameter,h=height,center=true,$fn=40);
		cylinder(d=hole+clearance,h=height*1.2,center=true,$fn=40);
	}
}

/*
beam(50,10,2.5,4);
translate([0,20,0])
		beam2(25,8,2,4);
translate([0,40,0])
		beam2(25,8,2,4);
translate([0,60,0])
		beam3(30,8,2,4,2);
translate([0,80,0])
		beam3(30,8,2,4,2);
for (i=[1:3]){
translate([0,85+(i*15),0])
		plate(20,8,2,4,2);
}
for (i=[1:7]){
	translate([45,i*15,0])
		washer(8,1.5,2);
}
*/
//Test print
plate(20,8,2,4,2);
translate([0,20,0])
	beam2(25,8,2,4);
translate([10,40,0])
	washer(8,1.5,2);	



