
/* electronia robot ARTURO.
10 SEPTIEMBRE 2014
SGTO. VAZQUEZ GARCIA


Este skecth se usa para cargar en la electroica instalada dentro del robot arturo para su control:

Objetivos.
- (CUMPLIDO) recepción de ordenes desde el mando universal.
- (CUMPLIDO) control de dos motores con los datos recibidos del joystick L
- (CUMPLIDO) parado de motores en caso de perder la conexión
- (CUMPLIDO) control de dos servos (pan tilt) para cámara del joystick R mando.
- CUMPLIDO) envio de datos al mando.
- (no cumplido) captura y calculo de la orientación por brujula del vehiculo
- (no cumplido) encendido y apagado remoto de luz frontal del vehiculo.

10sep14
se divide el programa en varios archivos por claridad.
implementada transmisión datos desde robot.

03sep14
se implementa max485.

02sep14
se cambia algoritmo de control de motores.

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
servo vertical             

*/

//-------------------------------DECLARACIÓN DE PINES COMO CONSTANTES

# define PinMIF 11
# define PinMIR 3
# define PinMDF 6
# define PinMDR 5
# define PinServoH 8
# define PinServoV 7
# define max485en 2

//-------------------------------DECLARACIÓN DE CONTANTES

# define zm 50

//librerias

#include <Servo.h> //libreria de servo

#include <EasyTransfer.h> //libreria Easy Transfer que permite comunicaciones mas seguras
EasyTransfer ETin;  //objeto tipo easy tranfer para RECIBIR datos y se le llama ETin
EasyTransfer ETout; //objeto tipo easy tranfer para RECIBIR datos y se le llama ETout

struct RECEIVE_DATA_STRUCTURE{
  //Creamos tantos datos como tengamos que RECIBIR.
  //tiene que ser EXACTAMENTE IGUAL que la estructura SEND_DATA_STRUCTURE del mando.
  int LY;
  int LX;
  int RY;
  
  int RX;
};

struct SEND_DATA_STRUCTURE{
  //Creamos tantos datos como tengamos que EMITIR
  //tiene que ser EXACTAMENTE IGUAL que la estructura RECEIVE_DATA_STRUCTURE del mando.
  int prueba;
  
};

RECEIVE_DATA_STRUCTURE datosrecibirrobot; //nombre del la estrutura que recibe los datos
SEND_DATA_STRUCTURE datosenviarrobot;     // nombre de la estructura que envia datos


//declaramos pin

/*int PinMIF=11;
int PinMIR=3;
int PinMDF=6;
int PinMDR=5;
int PinServoH=8;
int PinServoV=9;
*/


Servo servoh;  // Crea un Objeto servo  horizontal
Servo servov; //servo vertical

//variables que podemos modificar para mejorar o cambiar el comportamiento del vehiculo.
//int zm=50; //zona muerta de los joysticks
long tiempoDesc= 250; //tiempo máximo que estamos sin recibir ningún datos antes de desconectar los motores.

//variables de control. NO MODIFICA NUNCA.
long previousMillis = 0; //almacenamos ultimo tiempo donde no hemos recibido conexión
unsigned long currentMillis;
//int max485en=2;




void setup(){
  Serial.begin(9600);
  //inicia la libreria de cominucacion de tados, con los detalles de que estrctura usa y el puerto seria que puede ser Serial, Serial1, Serial2, etc. 
  ETin.begin(details(datosrecibirrobot), &Serial);
  ETout.begin(details(datosenviarrobot), &Serial);
  
  //declaramos los pines de los motores como salida
  pinMode(PinMIF, OUTPUT);
  pinMode(PinMIR, OUTPUT);
  pinMode(PinMDF, OUTPUT);
  pinMode(PinMDR, OUTPUT);
  
  
  pinMode(max485en, OUTPUT);//declaramos el pin de control de max485 como salida
  digitalWrite(max485en,LOW); //iniciamos el max485 como receptor.
  
  servoh.attach(PinServoH);  // Selecionamos el pin 2 como el pin de control para els ervo  
  servov.attach(PinServoV);
  servoh.write(90);
  servov.write(90);
  
  
}


void loop(){
  //recibimos datos robot   
  recibirdatos();
}
