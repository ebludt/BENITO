
ancho_pared=6;

module tensor(){
	difference(){

		cube([30,40,10],center=true);

		cylinder(r=15.8/2,h=100,center=true , $fn=6);
		translate([30,0,0]) rotate([0,0,0])
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
		cube([ancho_pared+20,40,5],center=true);
		
		translate([ancho_pared+5/2,14,0]) rotate([0,0,0])
		cylinder(r=4.2/2,h=100,center=true , $fn=15);

		translate([-ancho_pared-5/2,14,0]) rotate([0,0,0])
		cylinder(r=4.2/2,h=100,center=true , $fn=15);

		translate([ancho_pared+5/2,-14,0]) rotate([0,0,0])
		cylinder(r=4.2/2,h=100,center=true , $fn=15);

		translate([-ancho_pared-5/2,-14,0]) rotate([0,0,0])
		cylinder(r=4.2/2,h=100,center=true , $fn=15);	

	}
}

translate([30,0,5]) rotate([0,0,0])
tensor();

translate([0,0,2.5]) rotate([0,0,0])
placa();