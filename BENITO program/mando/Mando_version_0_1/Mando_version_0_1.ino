/* Mando control robot ARTURO.
02 AGOSTO 2014
SGTO. VAZQUEZ GARCIA


Este skecth se usa para crear un mando universal de control para el robot ARTURO de exploración.
En esta version se usará:

(no implementado) Un gamepad de la play station 2 con interfaz de introcución de datos.
(no implementado) Comunicación serial por cable.


02 AGOSTO 2014 V 0.1

Conexión de mando de la PS 2 y prueba de captura de datos.


esquema pines para mi mando



*/

#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // creamos un objeto tipo mando ps2 y le llamamo ps2x


void setup(){
   
   Serial.begin(57600);
    
    ps2x.config_gamepad(11,10,9,8,true,true);   //setup pins and settings:  GamePad(clock(lila), command(naranja), attention(rojo), data (verde), Pressures?, Rumble?) check for error
    Serial.println("Beginning ... "); // "Beginning ..." on sender, or "Listening ..." on sever (Receiver)
  }
  
  void loop(){ 
    
   
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed
        
    byte Vals[4];                        //creación de array de 4 posiciones para los dos joystick del mando  
    Vals[0]=ps2x.Analog(PSS_LY),DEC;     //almecenamos los valores de los ejes en cada byte del array
    Vals[1]=ps2x.Analog(PSS_LX),DEC;
    Vals[2]=ps2x.Analog(PSS_RY),DEC;
    Vals[3]=ps2x.Analog(PSS_RX),DEC;
    
    //imprimimos el valor del array en pantalla para ver que capturamos correctamente los ejes
    Serial.print("   ");
    Serial.print(Vals[0]);
    Serial.print("   ");
    Serial.print(Vals[1]);
    Serial.print("   ");
    Serial.print(Vals[2]);
    Serial.print("   ");
    Serial.println(Vals[3]);
    
    delay(1000);
    
}
