use <write.scad>
DrillMotorMount();

altura_aro=10; //height body mount ring
grosor_pestanha=3;
altura_soporte=25; //height mounting tab
distancia_taladro_motor=36;

version="V 2.0";

module DrillMotorMount()
{
	difference()
	{
		union()
		{
			difference()
			{
				union(){
				translate([0,0,altura_aro/2])
				cylinder(r=50/2,h=altura_aro, center=true);
				
				translate([0,0,grosor_pestanha/2])
				cube([70,15,grosor_pestanha],center=true);
				
				translate([-35,-25,0])
				cube([70,25,grosor_pestanha]);
				}
				// body mount cutout
				// agujero de montaje del motor
				translate([0,0,15])
				cylinder(r=30.5/2,h=40, center=true, $fn=100);

				
			}
			// keyed body mount
			// encaje de motor
			translate([0,24.5/2+5/2,altura_aro/2])
				cube([20,5,altura_aro],center=true);
			translate([0,-24.5/2-5/2,altura_aro/2])
				cube([20,5,altura_aro],center=true);

		}

		// keyed body mount
		// cilindro superior del encaje del motor
		translate([-3,-24.5/2,16])
			cylinder(r=4/2,h=40, center=true, $fn=30);
		//taladros sujeccion a madera	
		translate([30,0,altura_aro/2])
		cylinder(r=4.5/2,h=25, center=true);
		translate([-30,0,altura_aro/2])
		cylinder(r=4.5/2,h=25, center=true);


		//taladros sujecion motor
		
		for (i=[0:8-1])
		{
			translate([distancia_taladro_motor/2*cos((360/8*i)+25),distancia_taladro_motor/2*sin((360/8*i)+25),0])
			cylinder(r=5/2, h=100, $fn=20,center=true);
			
		}
	}
}
