//RUEDA con radios 
//parametros rueda

//medidas del aro externo de la rueda.
diametro=50; //diametro externo de la rueda. influye en la velocidad.
grosor=6;	// grosor del aro externo de la rueda

//medidas de los radios
//grosor_radios=8; //grosor o altura de los radios

//medidas del hub central
//diam_eje=4;  //eje central por el que pasa el tornillo de izquierdas



//medidas de los agujeros del hub
metrica_hub=3;

module rueda(gros=grosor, diam=diametro)
{
	difference(){
		
				
				union(){
					cylinder (r=diam/2, h=gros, $fn=100);
					translate([0,0,grosor])
					cylinder (r=15/2, h=gros*2, $fn=100);
					translate([0,0,grosor*3])
					cylinder (r=diam/2, h=gros, $fn=100);
				}
				cylinder (r=10.5/2, h=100, $fn=20, center=true);
				//translate([8,0,0])
				//cylinder (r=3.5/2, h=100, $fn=20, center=true);
				//translate([-8,0,0])
				//cylinder (r=3.5/2, h=100, $fn=20, center=true);
			
	}//fin diference
}




	//rueda en si
	rueda();
	
	//taladros
	//translate([-8,0,0])
	//cylinder(r=metrica_hub/2, h=100, $fn=20,center=true);
	




	