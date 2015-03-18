//RUEDA con radios 
//parametros rueda

//medidas del aro externo de la rueda.
diametro=50; //diametro externo de la rueda. influye en la velocidad.
grosor=4+6;	// grosor del aro externo de la rueda
altura_hub=7;
altura_bisel=2;

//medidas de los radios
//grosor_radios=8; //grosor o altura de los radios

//medidas del hub central
//diam_eje=4;  //eje central por el que pasa el tornillo de izquierdas


hub=true;
//medidas de los agujeros del hub
metrica_hub=3;

module rueda(gros=grosor, diam=diametro)
{	


	difference(){
		
				
				union(){
					cylinder (r=diam/2 ,h=gros/2-1, $fn=100);

					translate([0,0,grosor/2-1])
					cylinder (r1=diam/2, r2=(diam-2)/2,h=1, $fn=100);

					translate([0,0,grosor/2])
					cylinder (r2=diam/2, r1=(diam-2)/2,h=1, $fn=100);
					
					translate([0,0,grosor/2+1])
					cylinder (r=diam/2 ,h=gros/2-1, $fn=100);

					translate([0,0,grosor])
					cylinder (r1=diam/2,r2=20/2, h=altura_bisel, $fn=100);
					if (hub==true){
						translate([0,0,grosor])
						cylinder (r=20/2, h=altura_hub, $fn=100);
					}
					
				}
				
				
				
				if (hub==true){
					cylinder (r=14/2, h=100, $fn=20, center=true);
					translate([0,0,0])
					cylinder (r=22.5/2, h=7, $fn=60);
				}
				else{
					cylinder (r=18/2, h=100, $fn=20, center=true);
					translate([0,0,grosor+altura_bisel-7])
					cylinder (r=22.5/2, h=7, $fn=60);
				}

				

				//translate([8,0,0])
				//cylinder (r=3.5/2, h=100, $fn=20, center=true);
				//translate([-8,0,0])
				//cylinder (r=3.5/2, h=100, $fn=20, center=true);
			
	}//fin diference
}

				//translate([diametro/2-10,0,grosor])
				//cube ([10,10,10]);


	
	rueda();
	
	

	




	