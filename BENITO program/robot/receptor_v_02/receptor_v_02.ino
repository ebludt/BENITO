
/* electronia robot ARTURO.
02 AGOSTO 2014
SGTO. VAZQUEZ GARCIA


Este skecth se usa para cargar en la electroica instalada dentro del robot arturo para su control:

Objetivos.
- (CUMPLIDO) recepción de ordenes desde el mando universal.
- (no cumplido) control de dos motores con los datos recibidos del joystick L
- (no cumplido) control de dos servos (pan tilt) para cámara del joystick R mando.
- (no cumplido) envio de datos al mando.
- (no cumplido) captura y calculo de la orientación por brujula del vehiculo
- (no cumplido) encendido y apagado remoto de luz frontal del vehiculo.

03 AGOSTO 2014 V 0.2
Se asignan y declaran pines pwm para el control de los motores.
Se decodifica el control de los motores.
se controlan dos servos pan tilt para cámara.


02 AGOSTO 2014 V 0.1

Primera versión. Se usan la librería Easy tranfer para recibir datos desde otro arduino
via cable. Su valor se da a dos led.

------------------------
Pines usados.

Motor izquierdo adelante   PWM 11
Motor izquierdo atras      pwm 10

motor derecho adelante      pwm 6
motor derecho atras         pwm 5

servos horizontal          8
servo vertical             9

*/

//declaramos pin

int PinMIF=11;
int PinMIR=10;
int PinMDF=6;
int PinMDR=5;
int PinServoH=8;
int PinServoV=9;


#include <EasyTransfer.h> //se inclute la libreria Easy Transfer que permite comunicaciones mas seguras
EasyTransfer ETin;  //creamos un objeto tipo esay tranfer y se le llama ET 

struct RECEIVE_DATA_STRUCTURE{
  //Creamos tantos datos como tengamos que RECIBIR.
  //tiene que ser EXACTAMENTE IGUAL que la estructura SEND_DATA_STRUCTURE del mando.
  int LY;
  int LX;
  int RY;
  int RX;
};


RECEIVE_DATA_STRUCTURE datosrecibirrobot; //give a name to the group of data

void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ETin.begin(details(datosrecibirrobot), &Serial);
  
  pinMode(PinMIF, OUTPUT);
  pinMode(PinMIR, OUTPUT);
  pinMode(PinMDF, OUTPUT);
  pinMode(PinMDR, OUTPUT);
  
}

// funcion que detiene todos los motores
void stop(){
  //analogWrite(PinMIF,0);
  //analogWrite(PinMIR,0);
  //analogWrite(PinMDF,0);
  //analogWrite(PinMDR,0); 
  
}
void loop(){
  
  stop(); //detenemos todos los motores por si se pierde la conexión
  
  //check and see if a data packet has come in. 
  if(ETin.receiveData()){
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out. 
   analogWrite(PinMIF,datosrecibirrobot.LY );
   analogWrite(PinMIR,datosrecibirrobot.LX );
   analogWrite(PinMDF,datosrecibirrobot.RY );
   analogWrite(PinMDR,datosrecibirrobot.RX );
  }
  
  //you should make this delay shorter then your transmit delay or else messages could be lost
  delay(50);
}
