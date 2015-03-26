/* Mando control robot ARTURO.
 02ene15 SEPTIEMBRE 2014
 SGTO. VAZQUEZ GARCIA
 
 
 Este skecth se usa para crear un mando universal de control para el robot ARTURO de exploración.
 En esta version se usará:
 
 objetivos:
 - (CUMPLIDO) Recojer los datos que envia un mando PS2X que controla el operador.
 - (CUMPLIDO) Emisión de datos via cable al robot.
 - (CUMPLIDO) Recepción de datos via cable desde el robot.
 - (no cumplido) max 485 para comunicaciona gran distancia.
 - (no cumplido) pantalla donde se puedan visualizar datos enviados desde el robot.
 
 Extras.
 - (CUMPLIDO) comunicación inhalanbrica
 
 27mar15 v.0.16
 -Boton derecho alterna entre velocidad máxima y cabeceo del servo
 
 14mar15 v.0.15
 -Clarificar y adelgazar código.
 -Mirf más estable. 
 -Recepción de datos desde robot
 -Led comprobación conexion.
 
 05ENE14 V.0.11
 -Se unifica el código para usar arduino nano, mega o mini
 
 02ENE14 v0.10
 
 -joystick analogicos
 
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

#define control_rc_MIRF
//#define control_rc_SERIAL

/* ---------------------------tipo de joystick----------------
 (1) ps2 game pad
 (2) dos joystick analogicos
 */

#define control_joystick 2
//-----------------------------------------contantes de definición de pines-------------------

// #define placa_control_mega
#define placa_control_nano
// define placa_control_promini

#ifdef placa_control_mega

  #define max485en 2 //pin que activa la transmision del max485, high para enviar low para recivir
  #define ps2_clock 5
  #define ps2_command 4
  #define ps2_attention 3
  #define ps2_data 2
  #define PinLed 13 
  # define Pincsnmirf 53
  # define Pincemirf 49
#endif

#ifdef placa_control_nano

  #define max485en 2 //pin que activa la transmision del max485, high para enviar low para recivir
  #define ps2_clock 3
  #define ps2_command 4
  #define ps2_attention 5
  #define ps2_data 6
  #define PinLed 7
  # define Pincsnmirf 9
  # define Pincemirf 10
#endif

#ifdef placa_control_promini
  #define max485en 7 //pin que activa la transmision del max485, high para enviar low para recivir
  #define ps2_clock 5
  #define ps2_command 4
  #define ps2_attention 3
  #define ps2_data 2
  #define PinLed 6
  # define Pincsnmirf 9
  # define Pincemirf 10
#endif



  #define JoyPinLY 1
  #define JoyPinLX 0
  #define JoyPinRY 3
  #define JoyPinRX 2
  #define JoyPinLB 6
  #define JoyPinRB 7

//---------------------------------------------------constantes de trabajo
#define Codigo_control 142
#define velocidad 25







//---------------------------------Mando ps2 configuración--------------------------------------------------------
#include <PS2X_lib.h>  //se incluye la libreria ps2x que controla en mando ps2
PS2X ps2x; // creamos un objeto tipo mando ps2 y le llamamo ps2x
int error_ps2=0;
//-------------------librerias MIRF

#ifdef control_rc_MIRF
    #include <SPI.h>
    #include <Mirf.h>
    #include <nRF24L01.h>
    #include <MirfHardwareSpiDriver.h>

#endif
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
byte Vals[6]={
  128,128,128,128,Codigo_control,velocidad};

long contador=0;
unsigned long millis_ahora;
unsigned long millis_antes=millis();
long intervalo_muestra=1000;
int pulsadoLB=0;
int pulsadoRB=0;

//--------------------------------------constantes---------------------------------------

//int max485en=2; //pin que activa la transmision del max485, high para enviar low para recivir


//-------------------------------------setup--------------------------------------------
void setup(){

  Serial.begin(9600);

  switch (control_joystick){
  case 1:
  //controlador ps2
  error_ps2=ps2x.config_gamepad(ps2_clock,ps2_command, ps2_attention, ps2_data,true,true);   //setup pins and settings:  GamePad(clock(azul), command(naranja), attention(amarillo), data (marron), Pressures?, Rumble?) check for error
  if(error_ps2 == 0)
    Serial.println("Gamepad ps2 encontrado y funcionando");
  else if(error_ps2 == 1)
    Serial.println("Gamepad ps2 no encontrado");

  else if(error_ps2 == 2)
    Serial.println("Gamepad ps2 encontrado pero sin comunicación");

  else if(error_ps2 == 3)
    Serial.println("Gamepad ps2 encontrado pero con lecturas analogicas incorrectas");
  if(error_ps2>0){
  Serial.println("Control no encontrado o erroneo. No se puede iniciar");
  while(error_ps2>0){
      //
      //Wait.
      //Serial.println ("enviando");
    }
  }
  //Serial.println(error_ps2);
  break;
  
  }



  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ETout.begin(details(datosenviar), &Serial);
  ETin.begin(details(datosrecibir), &Serial);
  
  
  
  
  #ifdef control_rc_MIRF 
      //configuracion de mirf
      Mirf.spi = &MirfHardwareSpi;
      Mirf.csnPin = Pincsnmirf;
      Mirf.cePin = Pincemirf;
      Mirf.init(); 
      Mirf.setRADDR((byte *)"emiso");
      Mirf.channel = 90;
      Mirf.payload = 6;
      Mirf.config();
      Mirf.configRegister(RF_SETUP,0x06); 
     
       byte rf_setup = 0;
       Mirf.readRegister( RF_SETUP, &rf_setup, sizeof(rf_setup) );
      Serial.print( "rf_setup = " );
      Serial.println( rf_setup, BIN );

      Serial.println( "Wireless initialized!" ); 
  #endif
  
  
  //pin de que establece la comunicación semiduplex en el max485. si high envia, si low recibe
  pinMode(max485en, OUTPUT);
  pinMode(PinLed, OUTPUT);
  digitalWrite(PinLed,HIGH);

  
  armar_conexion();
  
  
  Serial.println("Empezando la emisión"); // "Beginning ..." on sender, or "Listening ..." on sever (Receiver)
  
  Serial.print("  modo jostick   ");
  Serial.println(control_joystick);
  
  
}




void loop(){ 

  Vals[5]=velocidad;
  Vals[2]=128;
  
  switch (control_joystick){
  case 1:
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed     
    
    Vals[0]=ps2x.Analog(PSS_LY),DEC;
    Vals[1]=ps2x.Analog(PSS_LX),DEC;
    Vals[2]=ps2x.Analog(PSS_RY),DEC;
    Vals[3]=ps2x.Analog(PSS_RX),DEC;
    Vals[4]=142;
    if(ps2x.Button(PSB_R1)){
      Vals[5]=10;
    }
    if(ps2x.Button(PSB_R2)){
      Vals[5]=15;
    } 
    if(ps2x.Button(PSB_L1)){
      Vals[5]=10;
    }
    if(ps2x.Button(PSB_L2)){
      Vals[5]=15;
    } 
    break;
  case 2:
    Vals[0]=map(analogRead(JoyPinLY),0,1024,0,255);
    Vals[1]=map(analogRead(JoyPinLX),0,1024,0,255);
    //Vals[1]=map(Vals[1],0,255,255,0);
    
    Vals[3]=map(analogRead(JoyPinRX),0,1024,0,255);
    Vals[3]=map(Vals[3],0,255,255,0);
    Vals[4]=142;
    
    if (analogRead(JoyPinRB)>512){ //pulsado
        if (pulsadoRB==1) pulsadoRB=0;
        else pulsadoRB=1;
    }
    
    if (pulsadoRB==1) Vals[2]=map(analogRead(JoyPinRY),0,1024,0,255);
    else Vals[5]=map(analogRead(JoyPinRY),0,1024,10,30);
    
    break;    
  }
  enviardatos();

  //delay(50);

}

