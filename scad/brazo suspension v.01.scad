

espesor_pieza=10;
ancho_pieza=10;
longitud_tensor=70;


suspension();

module suspension(){
	difference(){
		union(){
			//brazo principal
			cube([10,50,10], center=true);
			//redondeo alojamiento tuerca
			translate([0,-25,0])
			cylinder(r=20/2, h=10, center=true);
			//redondeo fin brazon ppal
			translate([0,25,0])
			cylinder(r=10/2, h=10, center=true);
			//brazo tensor
			
			translate([-31,42,0])
			rotate([0,0,-30])
			brazotensor();			
			
			//placa apoyo
			translate([-10,20,-2.5])
			cube([20,20,5], center=true);
		}


		translate([0,-25,-5])
		cylinder(r=15.8/2, h=9,$fn=6);
		
		//translate([0,-25,-5])
		
		translate([0,-25,0])
		cylinder(r=8.2/2, h=20,$fn=20);


		translate([0,25,0])
		cylinder(r=4.2/2, h=20,$fn=20,center=true);

		translate([-70,25,0])
			cylinder(r=4.2/2, h=15, center=true);
	}
}

module brazotensor(){
	difference(){
		union(){
			cube([longitud_tensor,ancho_pieza ,espesor_pieza],center=true);
			translate([longitud_tensor/2,0,0])
			cylinder(r=ancho_pieza/2, h=espesor_pieza, center=true);
			translate([-longitud_tensor/2,0,0])
			cylinder(r=ancho_pieza/2, h=espesor_pieza, center=true);
		}
		translate([longitud_tensor/2,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([-longitud_tensor/2,0,0])
		cylinder(r=4.2/2, h=20, center=true);
	}

}

//brazotensor();