//Collar sujeta ejes
//parametros rueda


diametro_varilla=9; //diametro interior del eje o varilla         ///////axis diameter
diametro_exterior=15;	// grosor del aro externo de la rueda     ////////external diameter
grosor_collar=12; //altura del collar             /////////height
metrica_freno=3; //metrica tornillo freno         ///////screw size

module collar(){
	difference(){
		
				cylinder (r=diametro_exterior/2, h=grosor_collar, $fn=20);
				cylinder (r=diametro_varilla/2, h=100, $fn=100, center=true);
				translate([0,diametro_exterior/2,grosor_collar/2])
				rotate([90,0,0])
				cylinder (r=metrica_freno/2, h=diametro_exterior, $fn=20, center=true);
				
			
	}//fin diference
}




	//rueda en si
	collar();
	
	
		

	