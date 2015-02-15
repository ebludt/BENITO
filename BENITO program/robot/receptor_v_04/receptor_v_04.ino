
/* electronia robot ARTURO.
1 SEPTIEMBRE 2014
SGTO. VAZQUEZ GARCIA


Este skecth se usa para cargar en la electroica instalada dentro del robot arturo para su control:

Objetivos.
- (CUMPLIDO) recepción de ordenes desde el mando universal.
- (CUMPLIDO) control de dos motores con los datos recibidos del joystick L
- (CUMPLIDO) parado de motores en caso de perder la conexión
- (CUMPLIDO) control de dos servos (pan tilt) para cámara del joystick R mando.
- (no cumplido) envio de datos al mando.
- (no cumplido) captura y calculo de la orientación por brujula del vehiculo
- (no cumplido) encendido y apagado remoto de luz frontal del vehiculo.

01SEP14
Se elmina la suavidad de los servos.
Se remapea los datos.

14 AGOSTO. V0.3
Modificación para que los servos sean mas suaves

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
Motor izquierdo atras      pwm 3

motor derecho adelante      pwm 6
motor derecho atras         pwm 5

servos horizontal          8
servo vertical             9

*/
//librerias

#include <Servo.h>


//declaramos pin

int PinMIF=11;
int PinMIR=10;
int PinMDF=6;
int PinMDR=5;
int PinServoH=8;
int PinServoV=9;
Servo servoh;  // Crea un Objeto servo  horizontal
Servo servov; //servo vertical

//variables que podemos modificar para mejorar o cambiar el comportamiento del vehiculo.
int zm=50; //zona muerta de los joysticks
long tiempoDesc= 250; //tiempo máximo que estamos sin recibir ningún datos antes de desconectar los motores.

//variables de control. NO MODIFICA NUNCA.
long previousMillis = 0; //almacenamos ultimo tiempo donde no hemos recibido conexión
unsigned long currentMillis;



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
  Serial.begin(57600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ETin.begin(details(datosrecibirrobot), &Serial);
  
  pinMode(PinMIF, OUTPUT);
  pinMode(PinMIR, OUTPUT);
  pinMode(PinMDF, OUTPUT);
  pinMode(PinMDR, OUTPUT);
  
  
  servoh.attach(PinServoH);  // Selecionamos el pin 2 como el pin de control para els ervo  
  servov.attach(PinServoV);
  servoh.write(90);
  servov.write(90);
  
  
}

// funcion que detiene todos los motores
void alto(){
  analogWrite(PinMIF,0);
  analogWrite(PinMIR,0);
  analogWrite(PinMDF,0);
  analogWrite(PinMDR,0); 
  
}

//Funcion que controla el movimiento
void movimiento(){
     long vely;
     float dirx;
     long vel;
     long dir;
     int mia=0;
     int mit=0;
     int mda=0;
     int mdt=0;
     int izd=0;
     int der=0;
	 
     vel= map(datosrecibirrobot.LY, 255,0 , -255, 255);
     dir= map(datosrecibirrobot.LX, 0, 255, -255, 255);
     vely=sqrt(sq(vel)+sq(dir));
     if (vely>255){
       vely=255;
     }
     dirx=abs(float(vel)/float(vely));
  
     
     
     if (vel> zm){ //si presionamos le joystick adelante
         if (dir>zm){//si giramos a la derecha.
             izd=int(vely);
             der=int(vely*dirx);
             
         }
         else if(dir<-zm) { //a la izquierda
             izd=int(vely*dirx);
             der=int(vely);
             
         }
         else { //tutiavante
           izd=int(vely);
           der=int(vely);
         }
     }
     else if (vel<-zm){ //si va para atras
         
         if (dir>zm){ //patras y a la derecha)
            izd=(-1)*(int(vely));
            der=(-1)*(int(vely*dirx));
         }
         else if (dir<-zm){
           izd=(-1)*(int(vely*dirx));
           der=(-1)*(int(vely));
         }
         
         else { //tutireverso
           izd=(-1)*(int(vely));
           der=(-1)*(int(vely));
         }
     }
     
     else {//mi palante ni patras en pivote
     
         if (dir>zm){ //si para la derecha
             izd=vely;
             der=-vely;
         }
         else if (dir<-zm){
             
             izd=vely;
             der=-vely;
         
         }
         
     }
     
     if(izd>0){
       mia=izd;
       mia= map(mia, zm,255 , 0, 255);
       }
     else if (izd<-0){
       mit=abs(izd);
       mit= map(mit, zm,255 , 0, 255);
       }
       
     if(der>0){
       mda=der;
       mda= map(mda, zm,255 , 0, 255);
       }
     else if (der<0){
       mdt=abs(der);
       mdt= map(mdt, zm,255 , 0, 255);
       }  
       
       
       
       analogWrite(PinMIF,(mia));
       analogWrite(PinMIR,(mit));
       analogWrite(PinMDF,(mda));
       analogWrite(PinMDR,(mdt));
       
}

//funcion que controla la conexión.
void checkConect(){
  currentMillis = millis(); //almacenamos el momento actual
  if(currentMillis - previousMillis > tiempoDesc){ //comprobamos si desde la ultima vez que recibimos datos hasta ahora ha pasado mas del intervalo de seguridad
  alto(); //si ha pasado mas del intervalo de seguridad paramos el vehiculo.
  }
}

//funcion que controla los servos
void camServo(){
      //int servoinicial;
      
      if  (datosrecibirrobot.RX< (128-zm) || datosrecibirrobot.RX> (128+zm)){    
           servoh.write((servoh.read())-(map(datosrecibirrobot.RX, 255, 0, -8, 10))); 
            
      }
      if  (datosrecibirrobot.RY< (128-zm) || datosrecibirrobot.RY> (128+zm)){               
            servov.write((servov.read())-(map(datosrecibirrobot.RY, 255, 0, -8, 10)));
      }
            
      
     
}


void loop(){
  
  //stop(); //detenemos todos los motores por si se pierde la conexión
  
  //check and see if a data packet has come in. 
  if(ETin.receiveData()){
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out. 
   /*analogWrite(PinMIF,datosrecibirrobot.LY );
   analogWrite(PinMIR,datosrecibirrobot.LX );
   analogWrite(PinMDF,datosrecibirrobot.RY );
   analogWrite(PinMDR,datosrecibirrobot.RX );
   */
     movimiento(); //llamamos a la funcion que mueve el robot  
     camServo();
     previousMillis=millis(); //almacenamos en la ultima vez que hemos recibido un dato
  }
  else{
      checkConect();
  }
     
  
  //you should make this delay shorter then your transmit delay or else messages could be lost
  delay(50);
}
