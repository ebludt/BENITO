//RUEDA con radios 
//parametros rueda

use <write.scad>
version="V 2.8";

//medidas del aro externo de la rueda.
//diametro=86; //diametro externo de la rueda. influye en la velocidad.
grosor=6;	// grosor del aro externo de la rueda

//medidas de los radios
//grosor_radios=8; //grosor o altura de los radios

//medidas del hub central
grosor_hub=14; //grosor o altura del hub central. minimo grosor_tuerca+1
diam_hub=31;	//diametro del hub
diametro_tuerca=16.8; //diametro mayor, entre picos, de la tuerca
grosor_tuerca=6; //grosor o altura de la tuerca
diam_eje=5;  //eje central por el que pasa el tornillo de izquierdas
diam_eje_motor=9.6; //diametro del eje motor
diam_eje_mandril=12; //diametro del eje del mandril
casquillo=12.4;

//medidas de las cadenas
dientes=7; //numero de dientes de la rueda
paso=30; //distacia entre las tuercas o dientes de la cadena
Distancia_diente_borde=2.8; //2.8 para cadenas original

tornillo_diente=4.4;
//medidas de los agujeros del hub
tornillohub=2;
pasohub=diametro_tuerca+5.8;
metrica_hub=3;

/*exterior tractora (1) 
interior tractora (2) 
suplementos(3) 
tensora exterior(4) 
tensora interior (5)
experimental (6)
esterior total (7)
*/
pos_rueda=1;

/*(1)tornillos pasantes
	(2) aletas
*/
tipo_rueda=1;

//pasodientes=


angulodientes=360/dientes;
diametro=paso*dientes/3.141592;
distanciadientes=diametro-Distancia_diente_borde*2-tornillo_diente;
//diametro=distanciadientes+10; //diametro externo de la rueda. influye en la velocidad.
angulohub=360/tornillohub;
distanciahub=pasohub*tornillohub/3.141592;

module rueda(gros=grosor, diam=diametro, diam_axis=diam_eje,diam_tuerca=diametro_tuerca)
{
	difference(){
		union(){
			difference(){
			//rueda
				
				//parte exterior y radios
				if (pos_rueda==7){
				cylinder (r=diam/2+5, h=gros, $fn=100);
				}
				else {
				cylinder (r=diam/2, h=gros, $fn=100);
				//translate([0,0,grosor_radios])
				//cylinder (r=(diam-20)/2, h=100, $fn=100);
				//vaciado de radios
				}
				if (pos_rueda!=3){
					for (i=[0:dientes]) 
					{
					translate([((diam_hub/2+(diametro-diam_hub)/4)-1.5)*cos((360/dientes*i)+360/dientes/2),((diam_hub/2+(diametro-diam_hub)/4)-1.5)*sin((360/dientes*i)+360/dientes/2),-1])
					cylinder(r=(30)/4, h=100, $fn=20);
		
					}//fin for
				}
						
			}// fin diference
			//cilindro del hub	
			//si es rueda tractora externa hub alto
			if (pos_rueda==1){
					
					if (tipo_rueda==1){
					cylinder (r=diam_hub/2, h=grosor_hub+grosor, $fn=20);
					}
			}
			//si es rueda interna hub bajo
			if (pos_rueda==2){
					cylinder (r=diam_hub/2, h=grosor, $fn=20);
			}
			
			if (pos_rueda==4){
					cylinder (r=diam_hub/2, h=grosor_hub+grosor, $fn=20);
			}
			if (pos_rueda==5){
					cylinder (r=diam_hub/2, h=grosor, $fn=20);
			}

			//si es de paletas
			if (tipo_rueda==2)
			{
				for (i=[0:dientes-1]) 
				{
		
				//paletas
				translate([diametro/4*cos(angulodientes*i),diametro/4*sin(angulodientes*i),grosor*1.5])
				rotate([0,0,90+i*angulodientes])	
				cube([4,diametro/2,grosor],center=true);
				}
				cylinder (r=(diametro/2)-15, h=grosor*2, $fn=20);
				cylinder (r=(diametro/2), h=grosor, $fn=20);
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
			if (pos_rueda==4){
				//cylinder(r=diam_eje_mandril/2, h=80, $fn=30, center=true);
				//translate ([0,0,grosor-2])
				cylinder(r=casquillo/2, h=100, $fn=20, center=true);
			}
			if (pos_rueda==5){
				//cylinder(r=diam_eje_mandril/2, h=80, $fn=30, center=true);
				//translate ([0,0,grosor-2])
				cylinder(r=casquillo/2, h=100, $fn=20, center=true);
			}
	}//fin diference
}



difference()
//union()
{
	//rueda en si
	rueda();
	//taladros
	if (tipo_rueda==1) 
	{
		for (i=[0:dientes-1])
		{
			translate([distanciadientes/2*cos(angulodientes*i),distanciadientes/2*sin(angulodientes*i),0])
			cylinder(r=tornillo_diente/2, h=100, $fn=20,center=true);
			//translate([distanciadientes/2*cos(angulodientes*i),distanciadientes/2*sin(angulodientes*i),0])
			//cylinder(r=8/2, h=100, $fn=6,center=true);
			//translate ([8*cos(angulodientes*i),8*sin(angulodientes*i),grosor])
			//rotate([0,0,angulodientes*i])
			//cube([4,distanciadientes/2,10]);
		}
	}
	//agujeros de union de hub
	for (i=[0:tornillohub-1]) 
	{
		translate([pasohub/2*cos(angulohub*i),pasohub/2*sin(angulohub*i),0])
		cylinder(r=metrica_hub/2, h=100, $fn=20,center=true);
		//translate ([8*cos(angulodientes*i),8*sin(angulodientes*i),grosor])
		//rotate([0,0,angulodientes*i])
		//cube([4,distanciadientes/2,10]);
	}
	if (pos_rueda==3 || pos_rueda==7){
		cylinder(r=(diametro-20)/2, h=20, $fn=50,center=true);	
	}
	
	//cilindros aligeradores paletas
	if (tipo_rueda==2){
		for (i=[0:dientes-1])
		{
			/*translate([((diametro/4)+5)*cos((angulodientes*i)+20),((diametro/4)+5)*sin((angulodientes*i)+20),0])
			cylinder(r=15/2, h=100, $fn=20,center=true);
			*/
			/*for (i=[0:4]) 
					{
					translate([(25)*cos(72*i),(25)*sin(72*i),-1])
					cylinder(r=(15)/4, h=100, $fn=20);
		
					}//fin for
			*/
		}
			
	}
	/*translate([-25,0, grosor]) 
	rotate([0,0,0])
	write(version,t=3 , h=4,center=true);
*/
}
	

echo("diametro de la rueda   ",diametro);
echo("diametro de los dientes    ",distanciadientes);
echo("separacion entre dientes y borde   ",(diametro-distanciadientes-tornillo_diente)/2);
echo("Velocidad teorica a 550rpm ", (diametro*3.141592*550/1000000*60));
echo("cuerda usada ", (diametro*3.141592*100/360));
echo("diametro del hub    ",distanciahub);

	