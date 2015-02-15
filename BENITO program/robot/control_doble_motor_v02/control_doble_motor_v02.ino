 /* Control doble de motor.
 
27 OCTUBRE 2014
SGTO. VAZQUEZ GARCIA
Un arduino lee dos señales tipo servo de un receptor RC y controla dos motores mediante IBT2

-OBJETIVOS
 - [si]control de dos motores mediante la lectura de dos señales rc
 - [NO] Suavidad y frenado en los motores.

pines
Pin MIF 11
Pin MIR 3
Pin MDF 6
Pin MDF 5
Pin MIC 10
Pin MDC 8

Pulso 0 =573
pulso 90= 1536 y 1543
pulso 180= 2506 y 2513
27OCTUBRE 2014
Primera pruebas

*/

# define PinMIF 11
# define PinMIR 3
# define PinMDF 6
# define PinMDR 5
# define PinMIC 9
# define PinMDC 8
# define Velocidad 5


unsigned long pulsoMIC=90; // variable en la que almacenaremos la lectura
unsigned long pulsoMDC=90; // variable en la que almacenaremos la lectura
int zm=10;

int depurar=1;

void setup()
{
pinMode(PinMIC, INPUT); // configuramo el pin como entrada
pinMode(PinMDC, INPUT); // configuramo el pin como entrada
//declaramos los pines de los motores como salida
  pinMode(PinMIF, OUTPUT);
  pinMode(PinMIR, OUTPUT);
  pinMode(PinMDF, OUTPUT);
  pinMode(PinMDR, OUTPUT);
Serial.begin(9600); // habilitamos puerto serie
}

void motores(){
  
  int mia=0;
  int mir=0;
  int mda=0;
  int mdr=0;
  
  
  if(pulsoMIC>1558){ //93 en servo
      
       mia= map(pulsoMIC, 1540,2509 , 0, 255);
       }
  else if (pulsoMIC<1529){
       mir= map(pulsoMIC, 1527,573 , 0, 255);
       }
  
  if(pulsoMDC>1558){
      
       mda= map(pulsoMDC, 1540,2509 , 0, 255);
       }
  else if (pulsoMDC<1529){
       mdr= map(pulsoMDC, 1527,573 , 0, 255);
       }
  mia = constrain(mia, 0,255);
  mir = constrain(mir, 0,255);
  mda = constrain(mda, 0,255);   
  mdr = constrain(mdr, 0,255);
  
       analogWrite(PinMIF,(mia/Velocidad));
       analogWrite(PinMIR,(mir/Velocidad));
       analogWrite(PinMDF,(mda/Velocidad));
       analogWrite(PinMDR,(mdr/Velocidad));
       
      if (depurar==1){
          Serial.print(" pulso MIC ");
          Serial.print(pulsoMIC); // mandamos el dato al monitor serie
          Serial.print("  pulso MDC ");
          Serial.print(pulsoMDC);
          Serial.print("  mia ");
          Serial.print(mia/Velocidad); // mandamos el dato al monitor serie
          Serial.print("  mir ");
          Serial.print(mir/Velocidad);
          Serial.print("  mda ");
          Serial.print(mda/Velocidad);
          Serial.print("  mdr ");
          Serial.print(mdr/Velocidad);
          Serial.println("  ");
      }
}


void loop()
{
pulsoMIC = pulseIn(PinMIC, HIGH, 21000); // leemos el pulso
pulsoMDC = pulseIn(PinMDC, HIGH, 21000); // leemos el pulso


if (pulsoMIC==0){
  pulsoMIC=1536;
  }
if (pulsoMDC==0){
  pulsoMDC=1536;
  }  


motores();

/*Serial.print(" pulso MIC ");
Serial.print(pulsoMIC); // mandamos el dato al monitor serie
Serial.print("  pulso MDC ");
Serial.println(pulsoMDC);
*/
delay(50); // pausa para no volver loco al monitor serie
}
