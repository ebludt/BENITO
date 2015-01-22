use <write.scad>
DrillMotorMount();

altura_aro=10; //height body mount ring

altura_soporte=25; //height mounting tab

version="V 2.0";

module DrillMotorMount()
{
	difference()
	{
		union()
		{
			difference()
			{
				union()
				{
					// body mount ring
					// cuerpo del aro de montaje
					translate([0,13,altura_aro/2])
						cube([40,26,altura_aro],center=true);
					translate([0,0,altura_aro/2])
						cylinder(r=40/2,h=altura_aro, center=true);

					// mounting tab
					// pestaña de anclaje
					translate([0,24,altura_soporte/2])
						cube([76,5,altura_soporte],center=true);
					//refuerzos
					translate([20.5,10,5/2]) rotate([0,0,-33])
						cube([16,40,5],center=true);
					translate([-20.5,10,5/2]) rotate([0,0,33])
						cube([16,40,5],center=true);
					

				}
			

				// body mount cutout
				// agujero de montaje del motor
				translate([0,0,15])
					cylinder(r=30.5/2,h=40, center=true, $fn=100);

				// mounting holes on tabs
				//tornillos de montaje en pestaña
				translate([31,20,15]) rotate([90,0,0])
					cylinder(r=4.3/2,h=20, center=true);
				translate([-31,20,15]) rotate([90,0,0])
					cylinder(r=4.3/2,h=20, center=true);

				// cut off excess
				// bisel de la pestaña 
				translate([0,24+5,24/2])
					cube([70,5.1,26],center=true);

				translate([38,24,altura_soporte]) rotate([0,36,0])
					cube([30,5.2,10],center=true);
				translate([-38,24,altura_soporte]) rotate([0,-36,0])
					cube([30,5.2,10],center=true);
				
				translate([76/2,0,-5]) 
						cube([5,50,20]);
				translate([-86/2,0,-5]) 
						cube([5,50,20]);
				//CORTE HORIZONTAL
				//translate([-35,21,0]) rotate([-45,0,0])
					//cube([70,5.2,40]);
			}

			// keyed body mount
			// encaje de motor
			translate([0,24.5/2+5/2,10/2])
				cube([20,5,10],center=true);
			translate([0,-24.5/2-5/2,10/2])
				cube([20,5,10],center=true);
		}

		// keyed body mount
		// cilindro superior del encaje del motor
		translate([-3,-24.5/2,16])
			cylinder(r=4/2,h=40, center=true, $fn=30);
		//version
		translate([0, 22, altura_aro+5]) 
		rotate([90,0,0])
   	write(version,t=5, h=5,center=true);
	}
}
