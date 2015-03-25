

espesor_pieza=5;
ancho_pieza=10;
longitud_tensor=50;
longitud_brazo=53;
longitud_brazo_suspension=50;


longitud_brazo_diagonal=sqrt(pow(longitud_brazo,2)+pow(longitud_brazo_suspension,2));

suspension();
//brazo_diagonal();
module suspension(){
	difference(){
		union(){
			//brazo principal HORIZONTAL
			brazo_diagonal();
			
			
			translate([longitud_brazo_diagonal/2,,0])
			rotate([0,0,45])
			brazotensor();			
			
			//placa apoyo
			//translate([(-longitud_brazo+ancho_pieza*2.5)/2,-ancho_pieza*1.5,-2.5])
			//cube([20,20,5], center=true);
		}
		/*
		translate([(-longitud_brazo)/2,,0,])
			cube([20,longitud_brazo_suspension-ancho_pieza,40], center=true);
		translate([(longitud_brazo)/2,-longitud_brazo_suspension +(ancho_pieza/4),0])
			cube([20,longitud_brazo_suspension/2+ancho_pieza,40], center=true);
		
		translate([longitud_brazo_diagonal/2,0,3])
			rotate([0,0,45])
		cube([longitud_brazo_suspension-10,ancho_pieza-2 ,espesor_pieza],center=true);
		*/
		translate([longitud_brazo_diagonal/2,0,0])
		cylinder(r=8.2/2, h=espesor_pieza*3,$fn=20, center=true);
	}
}

module brazotensor(){
	difference(){
		union(){
			cube([longitud_tensor,ancho_pieza+2 ,espesor_pieza],center=true);
			translate([longitud_tensor/2,0,0])
			cylinder(r=ancho_pieza/2+1, h=espesor_pieza, center=true);
			translate([-longitud_tensor/2,0,0])
			cylinder(r=ancho_pieza/2+1, h=espesor_pieza, center=true);
		}
		translate([longitud_tensor/2,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([-longitud_tensor/2,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([longitud_tensor/4,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([-longitud_tensor/4,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		cylinder(r=4.2/2, h=20, center=true);

		
	}


}



module brazo_diagonal(){
	difference(){
		union(){
			
			cube([longitud_brazo_diagonal,ancho_pieza ,espesor_pieza],center=true);
			translate([longitud_brazo_diagonal/2,0,0])
			cylinder(r=ancho_pieza/2, h=espesor_pieza, center=true);
			translate([-longitud_brazo_diagonal/2,0,0])
			cylinder(r=ancho_pieza/2, h=espesor_pieza, center=true);

			//redondeo alojamiento tuerca
			translate([-longitud_brazo_diagonal/2,0,espesor_pieza/2])
			cylinder(r=20/2, h=espesor_pieza*2, center=true);
			
			//redondeo alojamiento tuerca
			translate([longitud_brazo_diagonal/2,0,0])
			cylinder(r=20/2, h=espesor_pieza, center=true);
			
		}
		translate([longitud_brazo_diagonal/2,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([-longitud_brazo_diagonal/2,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([longitud_brazo_diagonal/4,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([-longitud_brazo_diagonal/4,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		cylinder(r=4.2/2, h=20, center=true);

		//ALOJAMIENTO TUERCA

		translate([-longitud_brazo_diagonal/2,0,-espesor_pieza/2])
		cylinder(r=15.5/2, h=espesor_pieza*2-2,$fn=6);
		
		//EJE TUERCA
		
		translate([-longitud_brazo_diagonal/2,0,0])
		cylinder(r=8.2/2, h=espesor_pieza*3,$fn=20, center=true);
	}

}


//brazotensor();