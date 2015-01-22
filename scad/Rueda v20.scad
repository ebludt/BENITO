//RUEDA con radios 
//parametros rueda

//medidas del aro externo de la rueda.
diametro=86; //diametro externo de la rueda. influye en la velocidad.
grosor=6;	// grosor del aro externo de la rueda

//medidas de los radios
//grosor_radios=8; //grosor o altura de los radios

//medidas del hub central
grosor_hub=12; //grosor o altura del hub central. minimo grosor_tuerca+1
diam_hub=31;	//diametro del hub
diametro_tuerca=16.8; //diametro mayor, entre picos, de la tuerca
grosor_tuerca=6; //grosor o altura de la tuerca
diam_eje=5;  //eje central por el que pasa el tornillo de izquierdas
diam_eje_motor=9.6; //diametro del eje motor
diam_eje_mandril=12; //diametro del eje del mandril


//medidas de las cadenas
dientes=8; //numero de dientes de la rueda
paso=30; //distacia entre las tuercas o dientes de la cadena

//medidas de los agujeros del hub
tornillohub=2;
pasohub=diametro_tuerca+5.8;
metrica_hub=3;

//exterior (1) interior (2) suplementos(3)
pos_rueda=2;



angulodientes=360/dientes;
distanciadientes=paso*dientes/3.141592;

angulohub=360/tornillohub;
distanciahub=pasohub*tornillohub/3.141592;

module rueda(gros=grosor, diam=diametro, diam_axis=diam_eje,diam_tuerca=diametro_tuerca)
{
	difference(){
		union(){
			difference(){
			//rueda
				
				//parte exterior y radios
				cylinder (r=diam/2, h=gros, $fn=100);
				//translate([0,0,grosor_radios])
				//cylinder (r=(diam-20)/2, h=100, $fn=100);
				//vaciado de radios
				if (pos_rueda!=3){
					for (i=[0:4]) 
					{
					translate([(25)*cos(72*i),(25)*sin(72*i),-1])
					cylinder(r=(38)/4, h=100, $fn=20);
		
					}//fin for
				}
						
			}// fin diference
			//cilindro del hub	
			//si es rueda externa hub alto
			if (pos_rueda==1){
					cylinder (r=diam_hub/2, h=grosor_hub+grosor, $fn=20);
			}
			//si es rueda interna hub bajo
			if (pos_rueda==2){
					cylinder (r=diam_hub/2, h=grosor, $fn=20);
			}
		}// fin union
			if (pos_rueda==1){
				//taladro
				cylinder(r=diam_axis/2, h=80, $fn=30, center=true);
				//tuerca
				translate ([0,0,grosor])
				cylinder(r=diam_tuerca/2, h=grosor+grosor_hub+2, $fn=6);
				//agujero resto hub
				translate ([0,0,grosor+grosor_tuerca])
				cylinder(r=(diam_tuerca+1)/2, h=grosor+grosor_hub+2, $fn=20);
			}
			if (pos_rueda==2){
				//cylinder(r=diam_eje_mandril/2, h=80, $fn=30, center=true);
				//translate ([0,0,grosor-2])
				cylinder(r=(diam_tuerca)/2, h=grosor*5, $fn=20, center=true);
			}
	}//fin diference
}



difference()
//union()
{
	//rueda en si
	rueda();
	//taladros
	for (i=[0:dientes-1]) 
	{
		translate([distanciadientes/2*cos(angulodientes*i),distanciadientes/2*sin(angulodientes*i),0])
		cylinder(r=4.5/2, h=100, $fn=20);
		//translate ([8*cos(angulodientes*i),8*sin(angulodientes*i),grosor])
		//rotate([0,0,angulodientes*i])
		//cube([4,distanciadientes/2,10]);
	}
	//agujeros de union de hub
	for (i=[0:tornillohub-1]) 
	{
		translate([pasohub/2*cos(angulohub*i+39),pasohub/2*sin(angulohub*i+39),0])
		cylinder(r=metrica_hub/2, h=100, $fn=20,center=true);
		//translate ([8*cos(angulodientes*i),8*sin(angulodientes*i),grosor])
		//rotate([0,0,angulodientes*i])
		//cube([4,distanciadientes/2,10]);
	}
	if (pos_rueda==3){
		cylinder(r=(diametro-20)/2, h=20, $fn=50,center=true);	
	}

}

echo("diametro de la rueda   ",diametro);
echo("diametro de los dientes    ",distanciadientes);
echo("separacion entre dientes y borde   ",(diametro-distanciadientes)/2);
echo("Velocidad teorica a 550rpm ", (diametro*3.141592*550/1000000*60));
echo("diametro del hub    ",distanciahub);

	