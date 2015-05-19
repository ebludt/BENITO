ancho_pared=5;

servo_montaje();

translate([0,70,0]) rotate([00,0,0])
servo_placa();
module servo_montaje(){
	difference(){
		
		//CUERPO CENTRAL
		union(){
			cube([60,60,2], center=true);
			
		/*
			translate([15,14,2.5]) rotate([90,0,0])
			cylinder(r=20/2,h=2, $fn=20, center=true);
			translate([15,-14,2.5]) rotate([90,0,0])
			cylinder(r=20/2,h=2, $fn=20, center=true);
			translate([-15,14,2.5]) rotate([90,0,0])
			cylinder(r=20/2,h=2, $fn=20, center=true);
			translate([-15,-14,2.5]) rotate([90,0,0])
			cylinder(r=20/2,h=2, $fn=20, center=true);
			*/

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
		translate([0,0,0]) rotate([0,0,0])
		cube([42,22,40],center=true);
		
		translate([0,0,-11]) rotate([0,0,0])
		cube([80,80,20],center=true);
			
		//VACIADO CENTRAL
		
		
		//AGUJEROS DE MONTAJE
		translate([-23.75,-5,0]) rotate([0,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);

		translate([-23.75,5,0]) rotate([0,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);

		translate([23.75,-5,0]) rotate([0,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);

		translate([23.75,5,0]) rotate([0,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);


		//bujeros damper
		translate([20,20,0]) rotate([0,0,0])
		cylinder(r=8/2,h=100, $fn=20, center=true);
		
		translate([-20,20,0]) rotate([0,0,0])
		cylinder(r=8/2,h=100, $fn=20, center=true);

		translate([20,-20,0]) rotate([0,0,0])
		cylinder(r=8/2,h=100, $fn=20, center=true);		

		translate([-20,-20,0]) rotate([0,0,0])
		cylinder(r=8/2,h=100, $fn=20, center=true);
		
		//
		}

		
		
}
module servo_placa(){
	difference(){
		
		//CUERPO CENTRAL
		union(){
			cube([70,70,2], center=true);
			

			
			

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
		translate([0,0,0]) rotate([0,0,0])
		cube([60,33.5,40],center=true);
		
		
			
		
		
		//AGUJEROS DE MONTAJE
		translate([-30,-30,0]) rotate([0,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);

		translate([-30,30,0]) rotate([0,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);

		translate([30,30,0]) rotate([0,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);

		translate([30,-30,0]) rotate([0,0,0])
		cylinder(r=3.5/2,h=100, $fn=20, center=true);


		//bujeros damper
		translate([20,20,0]) rotate([0,0,0])
		cylinder(r=8/2,h=100, $fn=20, center=true);
		
		translate([-20,20,0]) rotate([0,0,0])
		cylinder(r=8/2,h=100, $fn=20, center=true);

		translate([20,-20,0]) rotate([0,0,0])
		cylinder(r=8/2,h=100, $fn=20, center=true);		

		translate([-20,-20,0]) rotate([0,0,0])
		cylinder(r=8/2,h=100, $fn=20, center=true);
		
		//
		}

		
		
}

