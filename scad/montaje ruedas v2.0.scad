//estructura reforzada

use <write.scad>
DrillMotorMount();

altura_aro=12; //height body mount ring

altura_soporte=25; //height mounting tab
diam_tuerca=15.8;
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
					translate([0,15,altura_aro/2])
						cube([40,18,altura_aro],center=true);
					translate([0,7,altura_aro/2])
						cylinder(r=40/2,h=altura_aro, center=true);


					// mounting tab
					// pestaña de anclaje
					translate([0,24,altura_soporte/2])
						cube([76,5,altura_soporte],center=true);
					//refuerzos eje x
					translate([20.5,13,altura_aro/2]) rotate([0,0,-41])
						cube([16,40,altura_aro],center=true);
					translate([-20.5,13,altura_aro/2]) rotate([0,0,41])
						cube([16,40,altura_aro],center=true);

				}
			

				// body mount cutout
				// agujero de montaje del motor
				translate([0,0,altura_aro-8]) rotate([0,0,90])
				
					cylinder(r=diam_tuerca/2,h=10,  $fn=6);
					cylinder(r=8.4/2,h=100, center=true, $fn=20);

				// mounting holes on tabs
				//tornillos de montaje en pestaña
				translate([31,20,altura_soporte-10]) rotate([90,0,0])
					cylinder(r=4.2/2,h=20, center=true);
				translate([-31,20,altura_soporte-10]) rotate([90,0,0])
					cylinder(r=4.2/2,h=20, center=true);

				// cut off excess
				// bisel de la pestaña 
				

				// cut off excess
				// bisel de la pestaña 
				translate([-80/2,26.5,-5])
					cube([80,20,40]);

				translate([38,24,altura_soporte]) rotate([0,36,0])
					cube([30,5.2,10],center=true);
				translate([-38,24,altura_soporte]) rotate([0,-36,0])
					cube([30,5.2,10],center=true);
				
				translate([76/2,0,-5]) 
						cube([5,50,20]);
				translate([-86/2,0,-5]) 
						cube([5,50,20]);

				translate([0, 22, altura_aro+5]) 
				rotate([90,0,0])
   			write(version,t=1.1, h=7,center=true);
				
			}

			
		}

	}
}
