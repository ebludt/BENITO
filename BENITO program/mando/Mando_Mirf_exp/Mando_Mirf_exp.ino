//first included your library

/*
esquema pines para mi mando

2     DATA      VERDE
4     NARANJA   COMMAND
NC    AZUL      VIBRATION (7VOLTS)
GND   NEGRO     TIERRA
3,3V  AMARILLO  3,3 V
3     ROJO      ATTENTION
5     LILA      CLOCK
NC    BLANCO    CONO


NRF 2401L
13   CSK       MARRON
12   MISO      VERDE
11   MOSI      ROJO-BLANCO
10   CE        NARANJA
9    CSN       GRIS
NC   IRQ       AZUL
3,3            AMARILLO Y BLANCO
GND            MARRON Y MORADO

6   LED      VERDE-BLANCO


*/
#include <PS2X_lib.h>  //for v1.6
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

PS2X ps2x; // create PS2 Controller Class
int error = 0;
int led = 6;
int velocidad=3;
void setup(){
   Serial.begin(9600);
   pinMode(led, OUTPUT);
   digitalWrite(led, LOW);
    Mirf.spi = &MirfHardwareSpi;
    Mirf.cePin = 10;
    Mirf.csnPin = 9;
    Mirf.init(); 
    Mirf.setRADDR((byte *)"emiso");
    Mirf.payload = 6;
    Mirf.config();
    error=ps2x.config_gamepad(5,4,3,2,true,true);   //setup pins and settings:  GamePad(clock(lila), command(naranja), attention(rojo), data (verde), Pressures?, Rumble?) check for error
    Serial.println("Beginning ... "); // "Beginning ..." on sender, or "Listening ..." on sever (Receiver)
  }
  
  void loop(){ 
    
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed
      
    Mirf.setTADDR((byte *)"recep");
    byte Vals[6]={128,128,128,128,0,velocidad};
    
    /*almacenamos valores analogicos en el array
    ButtonReleased
    NewButtonState
    */
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
    /*Vals[6]=ps2x.Analog(PSAB_PAD_LEFT),DEC;
    Vals[7]=ps2x.Analog(PSAB_PAD_DOWN),DEC;
    
    if(ps2x.ButtonPressed(PSB_RED)) //circulo
          Vals[8]=1;
    if(ps2x.ButtonPressed(PSB_PINK)) //cuadrado
          Vals[9]=1;
    if(ps2x.ButtonPressed(PSB_BLUE)) //x
          Vals[10]=1;
    if(ps2x.ButtonPressed(PSB_GREEN)) //triangulo
          Vals[11]=1;
          
    if(ps2x.Button(PSB_L3))
          Vals[12]=1;
    if(ps2x.Button(PSB_R3))
          Vals[13]=1;
    if(ps2x.Button(PSB_L2))
          Vals[14]=1;
    if(ps2x.Button(PSB_R2))
          Vals[15]=1;
    if(ps2x.Button(PSB_L1))
          Vals[16]=1;
    if(ps2x.Button(PSB_R1))
          Vals[17]=1;      
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Vals[18]=1;
    if(ps2x.Button(PSB_SELECT))
          Vals[19]=1;
   */
    //enviamos los datos   
    
    
    Mirf.send((byte *) &Vals);
    while(Mirf.isSending()){
       //
       //Wait.
      }
    digitalWrite(led, LOW);  
    //imprimimos datos de ejes
    int cont;
    
    /*for (cont=0;cont<20;cont++){
      Serial.print (Vals[cont]);
      Serial.print (" -- ");
    }
    
      Serial.println();
      Serial.println();
    */
    delay(20);
    
    Serial.println (Vals[5]);
    
    if (Vals[0]!=128){
      digitalWrite(led, HIGH);
    }
}
