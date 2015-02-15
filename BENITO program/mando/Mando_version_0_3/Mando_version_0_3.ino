/* Mando control robot ARTURO.
1 SEPTIEMBRE 2014
SGTO. VAZQUEZ GARCIA


Este skecth se usa para crear un mando universal de control para el robot ARTURO de exploración.
En esta version se usará:

objetivos:
- (CUMPLIDO) Recojer los datos que envia un mando PS2X que controla el operador.
- (CUMPLIDO) Emisión de datos via cable al robot.
- (no cumplido) Recepción de datos via cable desde el robot.
- (no cumplido) max 485 para comunicaciona gran distancia.
- (no cumplido) pantalla donde se puedan visualizar datos enviados desde el robot.

Extras.
- comunicación inhalanbrica



01SEPTIEMBRE 2014
- Se hacen pruebas de mix de mandos, se descartan

02 AGOSTO 2014 V 0.2

Tranferimos los dato usando la libreria Easy tranfer
Se elimina el array VALS para la recogida de datos.
02 AGOSTO 2014 V 0.1

Conexión de mando de la PS 2 y prueba de captura de datos.


esquema pines para mi mando



*/

#include <PS2X_lib.h>  //se incluye la libreria ps2x que controla en mando ps2
PS2X ps2x; // creamos un objeto tipo mando ps2 y le llamamo ps2x

#include <EasyTransfer.h> //se inclute la libreria Easy Transfer que permite comunicaciones mas seguras
EasyTransfer ET;  //creamos un objeto tipo esay tranfer y se le llama ET

struct SEND_DATA_STRUCTURE{
  //Creamos tantos datos como tengamos que enviar.
  //tiene que ser EXACTAMENTE IGUAL que la del receptor.
  int LY;
  int LX;
  int RY;
  int RX;
};


SEND_DATA_STRUCTURE datosenviar; //give a name to the group of data

void setup(){
   
   Serial.begin(57600);
    
    ps2x.config_gamepad(11,10,9,8,true,true);   //setup pins and settings:  GamePad(clock(lila), command(naranja), attention(rojo), data (verde), Pressures?, Rumble?) check for error
    //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
    ET.begin(details(datosenviar), &Serial);
    
    Serial.println("Beginning ... "); // "Beginning ..." on sender, or "Listening ..." on sever (Receiver)
  }
  
  void loop(){ 
    
   
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed
        
     int LY;                         
    //datosenviar.
    LY=ps2x.Analog(PSS_LY),DEC;     //almecenamos los valores de los ejes en la variable que le corresponde.
    datosenviar.LY=ps2x.Analog(PSS_LY),DEC;
    datosenviar.LX=ps2x.Analog(PSS_LX),DEC;
    datosenviar.RY=ps2x.Analog(PSS_RY),DEC;
    datosenviar.RX=ps2x.Analog(PSS_RX),DEC;
    
    //imprimimos el valor del array en pantalla para ver que capturamos correctamente los ejes
    /*Serial.print("   ");
    Serial.print(LY);
    Serial.print("   ");
    Serial.print(datosenviar.LY);
    Serial.print("   ");
    Serial.print(datosenviar.LX);
    Serial.print("   ");
    Serial.print(datosenviar.RY);
    Serial.print("   ");
    Serial.println(datosenviar.RX);
    */
    ET.sendData();
    
    delay(50);
    
}
