ancho_pared=5;

cuerpo_joystick();
translate([0,-58,0]) rotate([0,0,0])
Cuerpo_arduino();
module Cuerpo_arduino(){
	difference(){
		
		//CUERPO CENTRAL
		union(){
			cube([80,60,40],center=true);
			
			
			//pestañas de montaje
			
			
			/*
			translate([2.5,-60/2,5]) rotate([0,0,0])
			cube([65,10,4],center=true);
			
			
			
			//suplemento
			translate([60/2,0,0]) rotate([0,0,0])
			cube([10,50,14],center=true);
			translate([10,0,3]) rotate([0,0,0])
		//cube([50,42,16],center=true);
		cylinder(r=15.5/2,h=14, $fn=6, center=true)
			*/
			
		}
		
		//VACIADO CENTRAL
		translate([0,0,2.5]) rotate([0,0,0])
		cube([75,55,40],center=true);
		
		//TAPA USB
		translate([40,0,0]) rotate([0,0,0])
		cube([20,20,20],center=true);

		//AGUJERO ANTENA
		translate([-25,-30,0]) rotate([90,0,0])
		//cube([20,20,20],center=true);
		cylinder(r=20/2,h=14, $fn=20, center=true);
		
		//AGUJERO PASACABLES
		translate([0,21,0]) rotate([90,0,0])
		cylinder(r=20/2,h=20, $fn=20, center=true);
		//AGUJEROS DE MONTAJE
		translate([-25,0,0]) rotate([90,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);
		translate([25,0,0]) rotate([90,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);
		translate([0,-20,0]) rotate([0,90,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);
		translate([0,20,0]) rotate([0,90,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);
		
		//
		}

		translate([64/2,43/2,-13]) rotate([0,0,0])
			cylinder(r=2/2,h=4, $fn=20, center=true);
		translate([-64/2,43/2,-13]) rotate([0,0,0])
			cylinder(r=2/2,h=4, $fn=20, center=true);
		translate([64/2,-43/2,-13]) rotate([0,0,0])
			cylinder(r=2/2,h=4, $fn=20, center=true);
		translate([-64/2,-43/2,-13]) rotate([0,0,0])
			cylinder(r=2/2,h=4, $fn=20, center=true);
		
}


//cuerpo_joystick();
module cuerpo_joystick(){
		difference(){
				union(){
			//CUERPO CENTRAL
				cube([80,60,40],center=true);





			}
		//vaciado central
		translate([0,0,2.5]) rotate([0,0,0])
		cube([75,55,40],center=true);
		//
		translate([0,10,-15]) rotate([0,0,90])
		agujeros_joystick();


		//AGUJERO PASACABLES
		translate([0,-21,0]) rotate([90,0,0])
		cylinder(r=20/2,h=20, $fn=20, center=true);
		//AGUJEROS DE MONTAJE
		translate([-25,0,0]) rotate([90,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);
		translate([25,0,0]) rotate([90,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);
		translate([0,-20,0]) rotate([0,90,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);
		translate([0,20,0]) rotate([0,90,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);
		}
}



module agujeros_joystick(){
		translate([0,0,0]) rotate([0,0,0])
			cylinder(r=27.9/2,h=20, $fn=20, center=true);

		translate([-0.8,-23,0]) rotate([0,0,0])
			cylinder(r=4/2,h=20, $fn=20, center=true);

		translate([-0.8,24,0]) rotate([0,0,0])
			cylinder(r=4/2,h=20, $fn=20, center=true);

		
}

//import_stl("JoyStick_Top_Plate.stl", convexity = 5);