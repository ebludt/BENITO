

module cuerpo(){
	difference(){
	translate([0,0,0])
	cube([55,55,3],center=true);

	//agujero central
	translate([0,0,0])
	cylinder(r=48/2,h=20, center=true);
	
	//cuatro agujeros
	translate([45/2,45/2,0])
	cylinder(r=3/2,h=20, $fn=10, center=true);
	translate([-45/2,45/2,0])
	cylinder(r=3/2,h=20, $fn=10, center=true);
	translate([45/2,-45/2,0])
	cylinder(r=3/2,h=20, $fn=10, center=true);
	translate([-45/2,-45/2,0])
	cylinder(r=3/2,h=20, $fn=10, center=true);
	}
}



module soporte	(){

	difference(){
	union(){
	translate([55/2,55/2-10,0])
	cube([3,10,34+3]);
	translate([55/2,55/2-10,0])
	cube([10,10,3]);
		
	translate([55/2,-55/2,0])
	cube([3,10,34+3]);
	translate([55/2,-55/2,0])
	cube([10,10,3]);

	translate([-55/2-3,55/2-10,0])
	cube([3,10,34+3]);
	translate([-55/2-10,55/2-10,0])
	cube([10,10,3]);

	translate([-55/2-3,-55/2,0])
	cube([3,10,34+3]);
	translate([-55/2-10,-55/2,0])
	cube([10,10,3]);
	}

	
	translate([55/2+6,55/2-5,0])
	cylinder(r=3/2,h=20, $fn=10, center=true);

	translate([55/2+6,-55/2+5,0])
	cylinder(r=3/2,h=20, $fn=10, center=true);
	
	translate([-55/2-6,55/2-5,0])
	cylinder(r=3/2,h=20, $fn=10, center=true);

	translate([-55/2-6,-55/2+5,0])
	cylinder(r=3/2,h=20, $fn=10, center=true);
	
	}
}

module total()
	{
	soporte();
	translate([0,0,34+1.5])
	cuerpo();
}


module corte(){
		difference(){		

			translate([0,0,55/2])
			rotate([90,0,0])
			total();

			translate([-100,-100,10])
			cube([200,200,100]);
		}
}

corte();

//total();
