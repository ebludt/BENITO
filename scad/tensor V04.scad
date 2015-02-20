ancho_pared=7;

module tensor(){
	difference(){

		cube([20,40,10],center=true);
		
		translate([0,0,-4])
		cylinder(r=15.5/2,h=100, $fn=6);

		cylinder(r=8.5/2,h=100, center=true, $fn=20);


		translate([20,0,0]) rotate([0,0,0])
		cube([20,40,40],center=true);

		translate([0,14,0]) rotate([0,90,0])
		cylinder(r=4.2/2,h=100,center=true , $fn=15);

		translate([0,-14,0]) rotate([0,90,0])
		cylinder(r=4.2/2,h=100,center=true , $fn=15);

		translate([-6,-14,0.75]) rotate([0,0,0])
		cube([4,7.30,10],center=true);

		translate([-6,14,0.75]) rotate([0,0,0])
		cube([4,7.30,10],center=true);
	}
}
module placa(){
	difference(){	
		cube([ancho_pared+20+20,40,5],center=true);
		
		translate([ancho_pared+20/2,14,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([0,14,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([ancho_pared+20/2,-14,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([0,-14,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);
		
		translate([-ancho_pared-20/2,14,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([-ancho_pared-20/2,-14,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);
	

	}
}

module cubre_tensor(){
	difference(){
		
		//CUERPO CENTRAL
		union(){
			cube([60,50,14],center=true);
			
			
			//pestañas de montaje
			translate([2.5,60/2,5]) rotate([0,0,0])
			cube([65,10,4],center=true);

			translate([2.5,-60/2,5]) rotate([0,0,0])
			cube([65,10,4],center=true);

			
			
			//suplemento
			translate([60/2,0,0]) rotate([0,0,0])
			cube([10,50,14],center=true);
			
		}
		//VACIADO CUERPO CENTRAL
		translate([0,0,3]) rotate([0,0,0])
		//cube([50,42,16],center=true);
		cylinder(r=15.5/2,h=14, $fn=6, center=true);
		
		//AGUJERO TENSOR
		translate([0,14,2]) rotate([0,90,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		
		//AGUJERO TENSOR
		translate([0,-14,2]) rotate([0,90,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);
	
		//AGUJERO INFERIOR EJE

		//cube ([40,10,100], center=true);
		
		cylinder(r=9/2,h=100, $fn=20, center=true);		

		//alojmaiento tuerca

		translate([55/2,14,0.75]) rotate([0,0,0])
		cube([4,7.30,14],center=true);
		
		translate([55/2,-14,0.75]) rotate([0,0,0])
		cube([4,7.30,14],center=true);

		

		translate([-45/2,14,0.75]) rotate([0,0,0])
		cube([4,7.30,14],center=true);
		
		translate([-45/2,-14,0.75]) rotate([0,0,0])
		cube([4,7.30,14],center=true);
		
		//agujero montaje
		translate([55/2,60/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);
		
		translate([-45/2,60/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([55/2,-60/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([-45/2,-60/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);
		
		translate([-45/2,-60/2,0]) rotate([0,0,0])
		cylinder(r=4.6/2,h=100,center=true , $fn=15);

		translate([2.5,60/2,5]) rotate([0,0,0])
			cube([50,4.60,100],center=true);

		translate([2.5,-60/2,5]) rotate([0,0,0])
			cube([50,4.60,100],center=true);
		

		//agujeros para aligerar
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
	}
}

module tensor_liso(){
	difference(){

		cube([20,40,10],center=true);
		
		translate([0,0,-4])
		//cylinder(r=15.5/2,h=100, $fn=6);

		cylinder(r=8.5/2,h=100, center=true, $fn=20);


		translate([20,0,0]) rotate([0,0,0])
		cube([20,40,40],center=true);

		translate([0,14,0]) rotate([0,90,0])
		cylinder(r=4.2/2,h=100,center=true , $fn=15);

		translate([0,-14,0]) rotate([0,90,0])
		cylinder(r=4.2/2,h=100,center=true , $fn=15);

		translate([-6,-14,0.75]) rotate([0,0,0])
		cube([4,7.30,10],center=true);

		translate([-6,14,0.75]) rotate([0,0,0])
		cube([4,7.30,10],center=true);
	}
}


//translate([50,0,2]) rotate([0,0,0])
//tensor();

//translate([0,70,2.5]) rotate([0,0,0])
//placa();

translate([0,0,0]) rotate([0,0,0])
cubre_tensor();

//translate([-50,0,2]) rotate([0,0,0])
//tensor_liso();
