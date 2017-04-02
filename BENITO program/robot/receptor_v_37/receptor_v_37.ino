
/* electronia robot ARTURO.
10 SEPTIEMBRE 2014
SGTO. VAZQUEZ GARCIA


Este skecth se usa para cargar en la electroica instalada dentro del robot arturo para su control:

Objetivos.
- (CUMPLIDO) recepciÃ³n de ordenes desde el mando universal.
- (CUMPLIDO) control de dos motores con los datos recibidos del joystick L
- (CUMPLIDO) parado de motores en caso de perder la conexiÃ³n
- (CUMPLIDO) control de dos servos (pan tilt) para cÃ¡mara del joystick R mando.
- CUMPLIDO) envio de datos al mando.
- (no cumplido) captura y calculo de la orientaciÃ³n por brujula del vehiculo
- (no cumplido) encendido y apagado remoto de luz frontal del vehiculo.

02abr17 37
-tres años.....
-cambiamos código para nano
-Metemos monstermoto

15-07-21 v.030
-Se clarifica el cÃ³digo.
-AÃ±adido mas sensibilidad al MPU6050.


03JUL15
-El proyecto se da por muerto.
-Se aÃ±ade sensor mpu6050 con inclinometro.


05may15 v.026
-cambiadas los vectores de envio a estructuras

15abr15 v.025
-suavizado cÃ³digo de mezcla de motores. motores cuadrÃ¡ticos en el eje x

08MAR15 v.021
-suavizado cÃ³digco de mezcla de motores.

06mar15 V.020
-Codigo NRF24L01 mas eficiente

05ENE15 V.016
-ClarificaciÃ³n de la funciones con parametros de entrada.

17DIC14 V.015
-Acerelacion progresiva

16dic14 v_0.14
-aÃ±adido control de velocidad desde el mando

12dic14
-aÃ±adimos a MIRF un byte de control de deconexion.

21NOV14
-Modificamos el algoritmo de mezcla de los ejes para el giro tipo tanke

14nov14
- pasamos el control microsecundo para controlar esc(ANULADO)

22OCT14
IMPLEMENTAMOS LIBRERIA MIRF

10sep14
se divide el programa en varios archivos por claridad.
implementada transmisiÃ³n datos desde robot.

03sep14
se implementa max485.

02sep14
se cambia algoritmo de control de motores.

01SEP14
Se elmina la suavidad de los servos.
Se remapea los datos.

14 AGOSTO. V0.3
ModificaciÃ³n para que los servos sean mas suaves

03 AGOSTO 2014 V 0.2
Se asignan y declaran pines pwm para el control de los motores.
Se decodifica el control de los motores.
se controlan dos servos pan tilt para cÃ¡mara.


02 AGOSTO 2014 V 0.1

Primera versiÃ³n. Se usan la librerÃ­a Easy tranfer para recibir datos desde otro arduino
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

/*#################################################################################################################################
  ##                          PARAMETROS CONFIGURACION                                                                           ##
  #################################################################################################################################
*/

/*CONTROL MOTORES.
sistema que se utiliza para el el control de motores.
1 ESC.
2 IBT 2.
3 MOTOR SHIELD.
4 PUENTE DE RELE
*/
//# define control_motores_ESC
//# define control_motores_IBT2
# define control_motores_MonsterMoto

/*CONTROL RC.
Sistema de control RC. a 29/09/15 solo MIRF y RF24 para NRF24L01 y serial
*/
//# define control_rc_MIRF //NRF24L01 con librerÃ­a MIRF. Mas obsoleta y menos funcional
//# define control_rc_SERIAL //Control por serial y max485
//# define control_RF24 //NRF24L01 con librerÃ­a RF24. MÃ¡s modernea y funcional.
# define control_rc_UART  //control via serial por softserial


/*ELECTRÃ“NICA DE CONTROL.
DefiniciÃ³n de la placa electrÃ³nica que controla el robot
*/
//# define placa_control_ramps //arduino mega con ramps. Mas moderna
//# define placa_control_mega //arduino mega. Actualmente en uso
# define placa_control_nano

/*SENSORES
Sensores diponibles.
*/
//# define mpu6050_sensor //mpu6050 acelerÃ³metro para muestra de inclinaciÃ³n. Falta pulir
//# define DMP6_mpu6050 //mpu650 con interrupciones.

/*LUCES
Numero de luces
*/
//#define LucesFrontales

//int DepuradoSerial=3; //0 SOLO DATOS TX, 1 DATOS TX Y DATOS RECIBIDOS, 2 DATOS TX, MOTOR Y SERVO, 3 DATOS TX Y DATOS ENVIADOS

//# define SaltoFrecuenciaNRF24L01 //experimental
/*
#ifdef SaltoFrecuenciaNRF24L01
       #define RadioCanal1 30
       #define RadioCanal2 10
       #define RadioCanal3 20
       int contadorsaltocanales=1;
       int saltocanalactual=1;
#endif
*/
/*#################################################################################################################################
  ##                          DECLARACION DE PINES                                                                               ##
  #################################################################################################################################
*/


//para nano
//# define Pincsnmirf 9
//# define Pincemirf 10

//////////////////////////////////////////////////////arduino MEGA
#ifdef placa_control_mega
///para mega
#ifdef control_RF24 //si hay RF24
# define Pincsnmirf 53
# define Pincemirf 49
#endif
#ifdef control_rc_MIRF //si hay RF24
# define Pincsnmirf 53
# define Pincemirf 49
#endif

# define PinLed 13

# define max485en 3

#ifdef control_motores_IBT2
# define PinMIF 4
# define PinMIR 5
# define PinMDF 6
# define PinMDR 7
#endif


#ifdef control_motores_ESC
# define PinServoMI 8
# define PinServoMD 9
#endif

#ifdef LucesFrontales
# define PinLucesFrontal1 10
# define PinLucesFrontal2 9
# define PinLucesFrontal3 8
#endif
#define PinSetUART 23

//servos que controla la camara
# define PinServoH 10
# define PinServoV 11
#endif
//////////////////////////////////////////////////////arduino mega +ramps

#ifdef placa_control_ramps
///para mega
#ifdef control_RF24 //si hay RF24
# define Pincsnmirf 53
# define Pincemirf 49
#endif

#ifdef control_rc_MIRF //si hay RF24
# define Pincsnmirf 53
# define Pincemirf 49
#endif
#ifdef control_rc_UART
#define PinSetUART 23
#endif

#ifdef control_rc_SERIAL
# define max485en 58
#endif

#ifdef control_motores_IBT2
# define PinMIF 11
# define PinMIR 6
# define PinMDF 5
# define PinMDR 4
#endif

#ifdef control_motores_ESC
# define PinServoMI 11
# define PinServoMD 6
#endif

#ifdef LucesFrontales
    # define PinLucesFrontal1 10
    # define PinLucesFrontal2 9
    # define PinLucesFrontal3 8
#endif
//servos que controla la camara
# define PinServoH 25
# define PinServoV 27


# define PinLed 13


#endif


//////////////////////////////////////////////////////arduino nano

#ifdef placa_control_nano
///para mega
#ifdef control_RF24 //si hay RF24
    # define Pincsnmirf 10
    # define Pincemirf 9
#endif

#ifdef control_rc_MIRF //si hay RF24
    # define Pincsnmirf 10
    # define Pincemirf 9
#endif
#ifdef control_rc_UART
    #define PinSoftSerialRX 12
    #define PinSoftSerialTX 11
#define PinSetUART 10
#endif

#ifdef control_rc_SERIAL
# define max485en 10
#endif

#ifdef control_motores_IBT2
    # define PinMIF 3
    # define PinMIR 6
    # define PinMDF 5
    # define PinMDR 4
#endif

#ifdef control_motores_ESC
# define PinServoMI 11
# define PinServoMD 6
#endif

//servos que controla la camara
# define PinServoH 2
# define PinServoV 3

#ifdef control_motores_MonsterMoto
    #define BRAKEVCC 0
    #define CW   1
    #define CCW  2
    #define BRAKEGND 3
    #define CS_THRESHOLD 100
    
    /*  VNH2SP30 pin definitions
     xxx[0] controls '1' outputs
     xxx[1] controls '2' outputs */
    //int inApin[2] = {7, 4};  // INA: Clockwise input
    //int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
    
    int inApin[2] = {8, 9};  // INA: Clockwise input
    int inBpin[2] = {7, 4}; // INB: Counter-clockwise input
    
    int pwmpin[2] = {5, 6}; // PWM input
    int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
    int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

#endif

#define PinLed 13


#endif
/*#################################################################################################################################
  ##                          DECLARACION DE CONSTANTES        NO MODIFICAR                                                      ##
  #################################################################################################################################
*/

# define zm 30
# define Servomin 0
# define Servomax 180
# define Servomid 90
# define tiempoDesc 400
# define Direccion_receptor "recep"
# define Direccion_emisor "emiso"
//-------------------------------codigo de control.

#define Codigo_control 142
#define PayLoadMIRF 7
#define CodigoControlRespuesta 150
//-------------------------------MODO DEBUG



/*#################################################################################################################################
  ##                          DECLARACION DE VARIABLES        NO MODIFICAR                                                      ##
  #################################################################################################################################
*/


//--------------------------------------------------------------variables de control. NO MODIFICA NUNCA.
long previousMillis = 0; //almacenamos ultimo tiempo donde no hemos recibido conexiÃ³n
unsigned long currentMillis;
int motor_izd_ini = 0;
int motor_dch_ini = 0;
int motor_izd_obj = 0;
int motor_dch_obj = 0;
int aceleracion = 75;
int contador = 0;
int servoVViejo = 90;

int contador_datosconexion = 0;
unsigned long millis_ahora_datos_conexion;
unsigned long millis_antes_datos_conexion = millis();
long intervalo_muestra_datos_conexion = 1000;
int lucesFrontal = 0;

float motor_izd=0;
float motor_dch=0;

/*#################################################################################################################################
  ##                          LIBRERIAS                        NO MODIFICAR                                                      ##
  #################################################################################################################################
*/

//----------------------------------------------LIBRERIA DE SERVO-------------------------------------------------------------------
#include <Servo.h> //libreria de servo

Servo servoh;  // Crea un Objeto servo  horizontal
Servo servov; //servo vertical

//pines esc
Servo servomi;
Servo servomd;

//----------------------------------------------LIBRERIA DE CONTROL MIRF------------------------------------------------------------
#ifdef control_rc_MIRF

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#endif
//----------------------------------------------LIBRERIA MPU6050------------------------------------------------------------
#ifdef mpu6050_sensor
#include <Wire.h>

//Direccion I2C de la IMU
#define MPU 0x68

//Ratios de conversion
#define A_R 16384.0
#define G_R 131.0

//Conversion de radianes a grados 180/PI
#define RAD_A_DEG = 57.295779

//MPU-6050 da los valores en enteros de 16 bits
//Valores sin refinar
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

//Angulos
float Acc[2];
float Gy[2];
float Angle[2];
float AngleCalibration[2] = {0, 0};
float AngleComp[2];


//tiempos para mostrar datos

unsigned long millis_ahora;
unsigned long millis_antes = millis();
unsigned long millis_antes_mpu = micros();
unsigned long millis_ahora_mpu;
unsigned long millis_antes_mostrar_mpu = millis();
long intervalo_muestra = 1000;
#endif
//----------------------------------------------liberaia de mpu6050 con interrupcion---------------

#ifdef DMP6_mpu6050
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
MPU6050 mpu;
#define OUTPUT_READABLE_YAWPITCHROLL ////////////a ver si queda
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };



// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}


float Angle[2];
float AngleCalibration[2] = {0, 0};
float AngleComp[2];


//tiempos para mostrar datos

unsigned long millis_ahora;
unsigned long millis_antes = millis();
unsigned long millis_antes_mpu = micros();
unsigned long millis_ahora_mpu;
unsigned long millis_antes_mostrar_mpu = millis();
long intervalo_muestra = 1000;

#endif
//----------------------------------------------LIBRERIA DE RF24------------------------------------------------------------
#ifdef control_RF24
#include <SPI.h>
#include "RF24.h"
#include "printf.h"
RF24 radio(Pincemirf, Pincsnmirf);
//RF24 radio(10,9);
#endif

#ifdef control_rc_SERIAL

#endif

/*#ifdef control_rc_RadioHead
        #include <SPI.h>
        #include <RH_NRF24.h>
        RH_NRF24 nrf24(Pincemirf,Pincemirf);

#endif
*/


//----------------------------------------------LIBRERIA EASY TRANSFER------------------------------------------------------------

#ifdef placa_control_nano
//#include <SoftwareSerial.h>
//SoftwareSerial rcUARTSerial(PinSoftSerialRX, PinSoftSerialTX); // RX, TX
//#include <SoftEasyTransfer.h>
//SoftEasyTransfer ETin;
//SoftEasyTransfer ETout;

#include <EasyTransfer.h> //libreria Easy Transfer que permite comunicaciones mas seguras
EasyTransfer ETin;  //objeto tipo easy tranfer para RECIBIR datos y se le llama ETin
EasyTransfer ETout; //objeto tipo easy tranfer para RECIBIR datos y se le llama ETout
#endif

#ifdef placa_control_mega
#include <EasyTransfer.h> //libreria Easy Transfer que permite comunicaciones mas seguras
EasyTransfer ETin;  //objeto tipo easy tranfer para RECIBIR datos y se le llama ETin
EasyTransfer ETout; //objeto tipo easy tranfer para RECIBIR datos y se le llama ETout
#endif

#ifdef placa_control_ramps
#include <EasyTransfer.h> //libreria Easy Transfer que permite comunicaciones mas seguras
EasyTransfer ETin;  //objeto tipo easy tranfer para RECIBIR datos y se le llama ETin
EasyTransfer ETout; //objeto tipo easy tranfer para RECIBIR datos y se le llama ETout
#endif
//----------------------------------------------ESTRUCTURA DE DATOS A ENVIAR--------------------------------------------------
struct RECEIVE_DATA_STRUCTURE {
  //Creamos tantos datos como tengamos que RECIBIR.
  //tiene que ser EXACTAMENTE IGUAL que la estructura SEND_DATA_STRUCTURE del mando.
  byte LY;
  byte LX;
  byte RY;
  byte RX;
  byte Control;
  byte Vel;
  byte ComandoControl;
  byte PayloadControl;
};

struct SEND_DATA_STRUCTURE {
  //Creamos tantos datos como tengamos que EMITIR
  //tiene que ser EXACTAMENTE IGUAL que la estructura RECEIVE_DATA_STRUCTURE del mando.
  byte AnguloX;
  byte AnguloY;
  byte RY;
  byte RX;
  byte Control;
  byte Vel;
  byte ComandoControl;
  byte PayloadControl;

};

RECEIVE_DATA_STRUCTURE datosrecibirrobot; //nombre del la estrutura que recibe los datos
SEND_DATA_STRUCTURE datosenviarrobot;     // nombre de la estructura que envia datos







/*#################################################################################################################################
  ##                          SETUP                       NO MODIFICAR                                                      ##
  #################################################################################################################################
*/


void setup() {
  Serial.begin(9600);
  Serial.println ("Control de robot Benito v_33. 21JUL15");
  Serial.println ("programado por SGT VAZQUEZ");
  Serial.println ("comezando......");

  //--------------------------------------------control por mirf--------------------------------------
#ifdef control_rc_MIRF
  Serial.println ("Control por MIRF");
  //ArmarMIRF();


  Mirf.spi = &MirfHardwareSpi;
  Mirf.csnPin = Pincsnmirf;
  Mirf.cePin = Pincemirf;
  Mirf.init();
  Mirf.setRADDR((byte*) Direccion_receptor);
  Mirf.channel = 90;
  Mirf.payload = 7;//sizeof(datosrecibirrobot);
  Mirf.config();
  Mirf.configRegister(RF_SETUP, 0x06);



  byte rf_setup = 0;
  Mirf.readRegister( RF_SETUP, &rf_setup, sizeof(rf_setup) );
  Serial.print( "rf_setup = " );
  Serial.println( rf_setup, BIN );
#endif

  /*----------------------------------------------control por RadioHead
  #ifdef control_rc_RadioHead
        Serial.println ("Control por RadioHead");
        if (!nrf24.init())
            Serial.println("init failed");
        // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
        if (!nrf24.setChannel(90))
            Serial.println("setChannel failed");
        if (!nrf24.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower18dBm))
            Serial.println("setRF failed");

  #endif
  */
  //------------------------------------------control por RF24------------------------------

#ifdef control_RF24
  Serial.println ("Control por RF24");
  printf_begin();
  byte addresses[][6] = {"1Node", "2Node"};
  radio.begin();

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.enableAckPayload();                     // Allow optional ack payloads
  //radio.enableDynamicPayloads();


  radio.setChannel(30); //0-127
  radio.setPALevel(RF24_PA_HIGH); //Set Power Amplifier (PA) level to one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS); //RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setCRCLength(RF24_CRC_8);
  //radio.setRetries(2,15);


  radio.printDetails();
  radio.startListening();
  //Serial.println("RF 24");



#endif

  //----------------------------------------------EASY TRANSFER------------------------------------------------------------
  //inicia la libreria de cominucacion de tados, con los detalles de que estrctura usa y el puerto seria que puede ser Serial, Serial1, Serial2, etc.

#ifdef control_rc_UART
  Serial.print("Control por UART");
#ifdef placa_control_nano

  //rcUARTSerial.begin(9600);
  
  ETout.begin(details(datosenviarrobot), &Serial);
  ETin.begin(details(datosrecibirrobot), &Serial);
#endif
#ifdef placa_control_mega
  Serial2.begin(9600);
  ETin.begin(details(datosrecibirrobot), &Serial2);
  ETout.begin(details(datosenviarrobot), &Serial2);
#endif
  pinMode(PinSetUART, OUTPUT);
  digitalWrite(PinSetUART, HIGH);

#endif

#ifdef control_rc_serial

  pinMode(max485en, OUTPUT);//declaramos el pin de control de max485 como salida
  digitalWrite(max485en, LOW); //iniciamos el max485 como receptor.
  ETin.begin(details(datosrecibirrobot), &Serial);
  ETout.begin(details(datosenviarrobot), &Serial);
#endif

  //--------------------------control motores------------------------------
#ifdef control_motores_ESC
  Serial.println ("Motores por ESC");
  servomi.attach(PinServoMI);
  servomd.attach(PinServoMD);
  servomi.write(90);
  servomd.write(90);
#endif

#ifdef control_motores_IBT2
  //control mediante IBT 2
  //declaramos los pines de los motores como salida en IBT-2.
  Serial.println ("Motores por IBT2");
  pinMode(PinMIF, OUTPUT);
  pinMode(PinMIR, OUTPUT);
  pinMode(PinMDF, OUTPUT);
  pinMode(PinMDR, OUTPUT);
#endif

  //-------------------------------------------------------sensores mpu6050------------------------------------------
#ifdef mpu6050_sensor
  Serial.println ("Sensor inclinometro mpu6050");
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("Calibrando acelerÃ³metro");
  float media[2];
  int contadorCalibrarMpu = 0;
  millis_antes = millis();
  while (millis() - millis_antes < 10000) {
    read_mpu6050sensor();
    delay(10);
    media[0] += Angle[0];
    media[1] += Angle[1];
    contadorCalibrarMpu = contadorCalibrarMpu + 1;
  }
  millis_antes = millis();

  media[0] = media[0] / contadorCalibrarMpu;
  media[1] = media[1] / contadorCalibrarMpu;
  AngleCalibration[0] = media[0];
  AngleCalibration[1] = media[1];
  Serial.println(media[0]);
  Serial.println(media[1]);

  Serial.println("acelerÃ³metro calibrado");
  Serial.print("Angle X: "); Serial.print(Angle[0], 4); Serial.print(" - "); Serial.print("Angulo Calibrado X"); Serial.print( AngleCalibration[0]); Serial.println(" ");
  Serial.print("Angle Y: "); Serial.print(Angle[1], 4); Serial.print(" - "); Serial.print("Angulo Calibrado Y"); Serial.print( AngleCalibration[1]); Serial.println(" ");
  Serial.print("Contador "); Serial.println(contadorCalibrarMpu);
  delay(1000);
  Serial.println(DepuradoSerial);


#endif

  //-------------------------------------------------sensores mpu650 con interrupcion

#ifdef DMP6_mpu6050
  Serial.println ("Sensor inclinometro mpu6050 con intererupciÃ³n");
  Wire.begin();
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // wait for ready
  /*
  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
  */
  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(116);
  mpu.setYGyroOffset(21);
  mpu.setZGyroOffset(-13);
  //mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
  mpu.setZAccelOffset(1069);
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }

  Serial.println("Calibrando acelerÃ³metro");
  double media[2];
  unsigned contadorCalibrarMpu = 0;
  millis_antes = millis();
  while (millis() - millis_antes < 20000) {
    read_DMP6_mpu6050();
    delay(10);
    //se empieza a contar la media a partir del segundo 15
    if (millis() - millis_antes > 15000) {
      media[0] += Angle[0];
      media[1] += Angle[1];
      contadorCalibrarMpu = contadorCalibrarMpu + 1;
    }
  }
  millis_antes = millis();

  media[0] = media[0] / contadorCalibrarMpu;
  media[1] = media[1] / contadorCalibrarMpu;
  AngleCalibration[0] = media[0];
  AngleCalibration[1] = media[1];
  // Serial.println(media[0]);
  //Serial.println(media[1]);
  Serial.println("========================================================================================================================================");
  Serial.println("acelerÃ³metro calibrado");
  Serial.print("Angle X: "); Serial.print(Angle[0], 4); Serial.print(" - "); Serial.print("Angulo Calibrado X"); Serial.print( AngleCalibration[0]); Serial.println(" ");
  Serial.print("Angle Y: "); Serial.print(Angle[1], 4); Serial.print(" - "); Serial.print("Angulo Calibrado Y"); Serial.print( AngleCalibration[1]); Serial.println(" ");
  Serial.print("Contador "); Serial.println(contadorCalibrarMpu);
  Serial.println("========================================================================================================================================");
  delay(1000);
  //Serial.println(DepuradoSerial);
#endif
  //---------------------------------------------------------------------------------luces frontales----------------------------------
#ifdef LucesFrontales
  Serial.println ("Luces Frontales");
  pinMode(PinLucesFrontal1, OUTPUT);
  pinMode(PinLucesFrontal2, OUTPUT);
  pinMode(PinLucesFrontal3, OUTPUT);
  digitalWrite(PinLucesFrontal1, LOW);
  digitalWrite(PinLucesFrontal2, LOW);
  digitalWrite(PinLucesFrontal3, LOW);
#endif




  servoh.attach(PinServoH);  //
  servov.attach(PinServoV);
  servoh.write(90);
  servov.write(90);

  pinMode(PinLed, OUTPUT);
  digitalWrite(PinLed, HIGH);







}

/*#################################################################################################################################
  ##                          LOOP                       NO MODIFICAR                                                            ##
  #################################################################################################################################
*/

void loop() {
  //recibimos datos robot
#ifdef mpu6050_sensor
  read_mpu6050sensor();
#endif
#ifdef DMP6_mpu6050
  read_DMP6_mpu6050();
#endif
  recibirdatos();
  digitalWrite(PinLed, LOW);
}

