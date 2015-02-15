/* Mando control robot ARTURO.
02ene15 SEPTIEMBRE 2014
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

02ENE14 V0.7
-Unificamos con MIRF para nrl 2401

11 SEP14
-dividimos el programa en varias tabs
-implementado recepción datos desde robot

02 SEPTIEMBRE 2014

-se añade la función de enviar datos.
-se añada max 485


01SEPTIEMBRE 2014
- Se hacen pruebas de mix de mandos, se descartan

02 AGOSTO 2014 V 0.2

Tranferimos los dato usando la libreria Easy tranfer
Se elimina el array VALS para la recogida de datos.
02 AGOSTO 2014 V 0.1

Conexión de mando de la PS 2 y prueba de captura de datos.


esquema pines para mi mando



*/

/*-----------------------------------------modo de envío-------------------------------------
  (1) NRF2401L 
  (2) SERIAL
   
*/

#define control_rc 1

//-----------------------------------------contantes de definición de pines-------------------


#define max485en 7 //pin que activa la transmision del max485, high para enviar low para recivir
#define ps2_clock 5
#define ps2_command 4
#define ps2_attention 3
#define ps2_data 2
#define PinLed 6 
//para nano
# define Pincsnmirf 9
# define Pincemirf 10

///para mega
//# define Pincsnmirf 53
//# define Pincemirf 48

//---------------------------------------------------constantes de trabajo
#define Codigo_control 142
#define velocidad 3







//---------------------------------Mando ps2 configuración--------------------------------------------------------
#include <PS2X_lib.h>  //se incluye la libreria ps2x que controla en mando ps2
PS2X ps2x; // creamos un objeto tipo mando ps2 y le llamamo ps2x

//-------------------librerias MIRF

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

//----------------------------------Librería de comunicaciones configuración--------------------------------------
#include <EasyTransfer.h> //se inclute la libreria Easy Transfer que permite comunicaciones mas seguras
EasyTransfer ETout;  //creamos un objeto tipo esay tranfer y se le llama ET
EasyTransfer ETin;

struct SEND_DATA_STRUCTURE{
  //Creamos tantos datos como tengamos que enviar.
  //tiene que ser EXACTAMENTE IGUAL que la del receptor.
  int LY;
  int LX;
  int RY;
  int RX;
  int Control;
  int Vel;
};
struct RECEIVE_DATA_STRUCTURE{
  
  int prueba;

};

SEND_DATA_STRUCTURE datosenviar; //give a name to the group of data
RECEIVE_DATA_STRUCTURE datosrecibir;


//-------------variables
byte Vals[6]={128,128,128,128,Codigo_control,velocidad};



//--------------------------------------constantes---------------------------------------

//int max485en=2; //pin que activa la transmision del max485, high para enviar low para recivir


//-------------------------------------setup--------------------------------------------
void setup(){
   
   Serial.begin(9600);
    
    ps2x.config_gamepad(ps2_clock,ps2_command, ps2_attention, ps2_data,true,true);   //setup pins and settings:  GamePad(clock(azul), command(naranja), attention(amarillo), data (marron), Pressures?, Rumble?) check for error
    //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
    ETout.begin(details(datosenviar), &Serial);
    ETin.begin(details(datosrecibir), &Serial);
    //configuracion de mirf
    Mirf.spi = &MirfHardwareSpi;
    Mirf.csnPin = Pincsnmirf;
    Mirf.cePin = Pincemirf;
    Mirf.init(); 
    Mirf.init(); 
    Mirf.setRADDR((byte *)"emiso");
    Mirf.payload = 6;
    Mirf.config();
    
    //pin de que establece la comunicación semiduplex en el max485. si high envia, si low recibe
    pinMode(max485en, OUTPUT);
    pinMode(PinLed, OUTPUT);
    digitalWrite(PinLed,HIGH);
    
    Serial.println("Empezando la emisión"); // "Beginning ..." on sender, or "Listening ..." on sever (Receiver)
    Serial.print("modo de RC   ");
    Serial.println(control_rc);
  }
  
 //-------------------------------------------------función enviar-------------------------------
 /*
 void enviardatos(){
     digitalWrite(max485en,HIGH);
     ET.sendData();
     delay(50);
     digitalWrite(max485en,LOW); 
     }
 */
 
 
  void loop(){ 
    
   
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed
    
    
    
    Vals[0]=ps2x.Analog(PSS_LY),DEC;
    Vals[1]=ps2x.Analog(PSS_LX),DEC;
    Vals[2]=ps2x.Analog(PSS_RY),DEC;
    Vals[3]=ps2x.Analog(PSS_RX),DEC;
    Vals[4]=142;
    if(ps2x.Button(PSB_R1)){
      Vals[5]=1;
    }
    if(ps2x.Button(PSB_R2)){
      Vals[5]=1;
    }       
    enviardatos();
    
    //delay(50);
    
}
