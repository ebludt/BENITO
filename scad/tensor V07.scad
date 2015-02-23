ancho_pared=7;


module cubre_tensor(){
	difference(){
		
		//CUERPO CENTRAL
		union(){
			cube([55,55,14],center=true);
			
			
			//pestañas de montaje
			/*translate([2.5,60/2,5]) rotate([0,0,0])
			cube([65,10,4],center=true);

			translate([2.5,-60/2,5]) rotate([0,0,0])
			cube([65,10,4],center=true);
			
			
			
			//suplemento
			translate([60/2,0,0]) rotate([0,0,0])
			cube([10,50,14],center=true);
			*/
			
		}
		//VACIADO tuerca
		translate([10,0,3]) rotate([0,0,0])
		//cube([50,42,16],center=true);
		cylinder(r=15.5/2,h=14, $fn=6, center=true);
		

		translate([-20,0,]) rotate([0,0,0])
		cube([16,25,16],center=true);


		//AGUJERO INFERIOR EJE
		translate([10,0,3]) rotate([0,0,0])
		cylinder(r=9/2,h=100, $fn=20, center=true);
		
		//AGUJERO TENSOR
		translate([0,10,2]) rotate([0,90,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		
		//AGUJERO TENSOR
		translate([0,-10,2]) rotate([0,90,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);
	
				

		//alojmaiento tuerca

		translate([40/2,10,0.75]) rotate([0,0,0])
		cube([4,7.30,14],center=true);
		
		translate([40/2,-10,0.75]) rotate([0,0,0])
		cube([4,7.30,14],center=true);

		

		translate([-10/2,10,0.75]) rotate([0,0,0])
		cube([4,7.30,14],center=true);
		
		translate([-10/2,-10,0.75]) rotate([0,0,0])
		cube([4,7.30,14],center=true);
		
		//agujero montaje
		translate([40/2,40/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);
		
		translate([-40/2,40/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([40/2,-40/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([-40/2,-40/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);
		
		translate([-25/2,-40/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([0,40/2,5]) rotate([0,0,0])
			cube([40,4.60,100],center=true);

		translate([0,-40/2,5]) rotate([0,0,0])
			cube([40,4.60,100],center=true);
		

		/*//agujeros para aligerar
		translate([15,15,0]) rotate([0,0,0])
		cylinder(r=15/2,h=100,center=true , $fn=15);
		translate([-11,15,0]) rotate([0,0,0])
		cylinder(r=15/2,h=100,center=true , $fn=15);
		translate([15,-15,0]) rotate([0,0,0])
		cylinder(r=15/2,h=100,center=true , $fn=15);
		translate([-11,-15,0]) rotate([0,0,0])
		cylinder(r=15/2,h=100,center=true , $fn=15);

		translate([-19,0,0]) rotate([0,0,0])
		cylinder(r=14/2,h=100,center=true , $fn=15);
		translate([23,0,0]) rotate([0,0,0])
		cylinder(r=14/2,h=100,center=true , $fn=15);
		*/
	}
}


translate([0,0,0]) rotate([0,0,0])
cubre_tensor();


