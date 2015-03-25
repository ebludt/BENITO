

espesor_pieza=10;
ancho_pieza=10;
longitud_tensor=70;
longitud_brazo=53;
longitud_brazo_suspension=50;
finalanterior=1;
//longitud_brazo_suspension=longitud_brazo_suspension-10;
var_transit=longitud_tensor;
//longitud_tensor=var_transit-10;

longitud_brazo_diagonal=sqrt(pow(longitud_brazo,2)+pow(longitud_brazo_suspension,2));
//longitud_brazo_diagonal=35;

echo (longitud_brazo_diagonal);

suspension();
//brazo_diagonal();
module suspension(){
	difference(){
		union(){
			//brazo principal HORIZONTAL
			brazo_diagonal();
			
			if (finalanterior==0){
			translate([longitud_brazo_diagonal/2,0,0])
			rotate([0,0,40])
			brazotensor();			
			}
			else{
				
				translate([longitud_brazo_diagonal/2,0,0])
				rotate([0,0,-50])
				brazotensor();
			}
		
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
			
		cube([longitud_brazo_suspension-10,ancho_pieza-2 ,espesor_pieza],center=true);
		
		translate([longitud_brazo_diagonal/2,0,0])
		cylinder(r=8.2/2, h=espesor_pieza*3,$fn=20, center=true);
		*/
		if (finalanterior==0){
			translate([0,-ancho_pieza/2-20,-10])
			
				cube([50,20,50]);
						
			}
			else{
				translate([0,+ancho_pieza/2,-10])
			
				cube([50,100,50]);
			}
		
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

		cylinder(r=4.4/2, h=20, center=true);

		
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
			translate([-longitud_brazo_diagonal/2,0,0])
			cylinder(r=20/2, h=espesor_pieza, center=true);
			/*
			//redondeo alojamiento muelle
			translate([longitud_brazo_diagonal/2,0,0])
			cylinder(r=20/2, h=espesor_pieza, center=true);
			*/
		}
		translate([longitud_brazo_diagonal/2,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([-longitud_brazo_diagonal/2,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([longitud_brazo_diagonal/4,0,0])
		cylinder(r=4.2/2, h=20, center=true);
		translate([-longitud_brazo_diagonal/4,0,0])
		cylinder(r=4.2/2, h=20, center=true);

		cylinder(r=4.4/2, h=20, center=true);

		//ALOJAMIENTO TUERCA
		/*bulbo
		translate([-longitud_brazo_diagonal/2,0,-espesor_pieza/2])
		cylinder(r=15.5/2, h=espesor_pieza*2-2,$fn=6);
		*/
		translate([-longitud_brazo_diagonal/2,0,-espesor_pieza/2+4])
		cylinder(r=15.5/2, h=espesor_pieza*2-2,$fn=6);
		//EJE TUERCA
		
		translate([-longitud_brazo_diagonal/2,0,0])
		cylinder(r=8.2/2, h=espesor_pieza*3,$fn=20, center=true);
	}

}


//brazotensor();