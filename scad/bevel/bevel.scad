//RUEDA con radios 
//parametros rueda

	difference(){
	union(){
		import_stl("grande.stl");
		translate([0,0,18])
		import_stl("Gear_Bevelorigin.stl");			
	}
	translate([0,-7,22])cube([5.5,2.3,29],center = true);
	}




	