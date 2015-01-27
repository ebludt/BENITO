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
		
				
				//parte exterior y radios
				cylinder (r=diam/2, h=gros, $fn=100);

				cylinder (r=10.5/2, h=100, $fn=20, center=true);
				//translate([8,0,0])
				//cylinder (r=3.5/2, h=100, $fn=20, center=true);
				//translate([-8,0,0])
				//cylinder (r=3.5/2, h=100, $fn=20, center=true);
			
	}//fin diference
}




	//rueda en si
	rueda();
	
	translate([diametro +10,0,0])
	difference(){
		union(){
				rueda();
				cylinder (r=15/2, h=grosor*3, $fn=20);
		}
		cylinder (r=10.5/2, h=100, $fn=20, center=true);
	}
		

	