
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

05ENE15 V.016
-Clarificación de la funciones con parametros de entrada.

17DIC14 V.015 
-Acerelacion progresiva

16dic14 v_0.14
-añadido control de velocidad desde el mando 

12dic14
-añadimos a MIRF un byte de control de deconexion.

21NOV14
-Modificamos el algoritmo de mezcla de los ejes para el giro tipo tanke

14nov14
- pasamos el control microsecundo para controlar esc(ANULADO)

22OCT14
IMPLEMENTAMOS LIBRERIA MIRF

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

//--------------------------------CONFIGURACION----------------------------------


/*CONTROL MOTORES.
sistema que se utiliza para el el control de motores.
1 ESC.
2 IBT 2.
3 MOTOR SHIELD.
4 PUENTE DE RELE
*/
# define control_motores 2


/*CONTROL RC.
Sistema de control RC sin cables.
1 nrfl2401
2 Puerto serial

*/

# define control_rc 1
//-------------------------------DECLARACIÓN DE PINES COMO CONSTANTES

//para nano
//# define Pincsnmirf 9
//# define Pincemirf 10

///para mega
# define Pincsnmirf 53
# define Pincemirf 49

# define max485en 2

//descomentar si se usan ibt-2
# define PinMIF 4
# define PinMIR 5
# define PinMDF 6
# define PinMDR 7

//descomentar si se usa esc
# define PinServoMI 8
# define PinServoMD 9

//servos que controla la camara
# define PinServoH 10
# define PinServoV 11



//-------------------------------DECLARACIÓN DE CONTANTES

# define zm 10
# define Servomin 0
# define Servomax 180
# define Servomid 90
# define tiempoDesc 250

//-------------------------------codigo de control.

#define Codigo_control 142


//-------------------------------MODO DEBUG

int DepuradoSerial=14;



//librerias

#include <Servo.h> //libreria de servo
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>


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
  int Control;
  int Vel;
};

struct SEND_DATA_STRUCTURE{
  //Creamos tantos datos como tengamos que EMITIR
  //tiene que ser EXACTAMENTE IGUAL que la estructura RECEIVE_DATA_STRUCTURE del mando.
  int prueba;
  
};

RECEIVE_DATA_STRUCTURE datosrecibirrobot; //nombre del la estrutura que recibe los datos
SEND_DATA_STRUCTURE datosenviarrobot;     // nombre de la estructura que envia datos


Servo servoh;  // Crea un Objeto servo  horizontal
Servo servov; //servo vertical

//Control motores esc
Servo servomi;
Servo servomd;



//variables de control. NO MODIFICA NUNCA.
long previousMillis = 0; //almacenamos ultimo tiempo donde no hemos recibido conexión
unsigned long currentMillis;
int motor_izd_ini=0;
int motor_dch_ini=0;
int motor_izd_obj=0;
int motor_dch_obj=0;
int aceleracion=5;




void setup(){
  
    
    Mirf.spi = &MirfHardwareSpi;
    Mirf.csnPin = Pincsnmirf;
    Mirf.cePin = Pincemirf;
    Mirf.init(); 
    Mirf.setRADDR((byte *)"recep");
    Mirf.payload = 6;
    Mirf.config();
  Serial.begin(9600);
  //inicia la libreria de cominucacion de tados, con los detalles de que estrctura usa y el puerto seria que puede ser Serial, Serial1, Serial2, etc. 
  ETin.begin(details(datosrecibirrobot), &Serial);
  ETout.begin(details(datosenviarrobot), &Serial);
  
  switch (control_motores) {
            case 1:
              //control mediante esc
              //declaramos servos. 
                servomi.attach(PinServoMI);
              servomd.attach(PinServoMD);
              servomi.write(90);
              servomd.write(90);
            break;
            case 2:
              //control mediante IBT 2
              //declaramos los pines de los motores como salida en IBT-2.
               pinMode(PinMIF, OUTPUT);
               pinMode(PinMIR, OUTPUT);
               pinMode(PinMDF, OUTPUT);
               pinMode(PinMDR, OUTPUT);
             break;
            default: 
            // if nothing else matches, do the default
          // default is optional
            break;
        }
  
  
  
  
  
  
  
  pinMode(max485en, OUTPUT);//declaramos el pin de control de max485 como salida
  digitalWrite(max485en,LOW); //iniciamos el max485 como receptor.
  
  servoh.attach(PinServoH);  // Selecionamos el pin 2 como el pin de control para els ervo  
  servov.attach(PinServoV);
  servoh.write(90);
  servov.write(90);
  
  Serial.println ("Control de robot Benito v_15. 17DIC14");
  Serial.println ("programado por SGT VAZQUEZ");
  Serial.println ("comezando......");
  delay(2000);
  
}


void loop(){
  //recibimos datos robot   
  recibirdatos();
}
