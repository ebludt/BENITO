
module brazo(){
	hull(){
	
	cylinder(r = 11/2, h = 3, $fn = 50);
	translate([20, 0, 0])
    cylinder(r = 6/2, h = 3,  $fn = 50);
	translate([-20, 0, 0])
    cylinder(r = 6/2, h = 3,  $fn = 50);

	}

	cylinder(r = 9/2, h = 10,  $fn = 50);
}

module agujeros(){

	translate([7.5, 0, 0])
   cylinder(r = 1.5/2, h = 10,  $fn = 50);
	translate([-7.5, 0, 0])
   cylinder(r = 1.5/2, h = 10,  $fn = 50);
	translate([10, 0, 0])
   cylinder(r = 1.5/2, h = 10,  $fn = 50);
	translate([-10, 0, 0])
   cylinder(r = 1.5/2, h = 10,  $fn = 50);


}

module horn(){
	brazo();
	agujeros();

}

difference(){
//import_stl("pan_tilt.stl", convexity = 5);

translate([0, 0,5.5])
rotate([180,0,0])
horn();
}