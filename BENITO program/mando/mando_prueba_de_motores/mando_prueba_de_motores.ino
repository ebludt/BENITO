/* Mando control robot ARTURO.
1 SEPTIEMBRE 2014
probamos configuracion de motores



*/

#include <PS2X_lib.h>  //se incluye la libreria ps2x que controla en mando ps2
PS2X ps2x; // creamos un objeto tipo mando ps2 y le llamamo ps2x

  int LY;
  int LX;
  int RY;
  int RX;
  int zm=50;

void setup(){
   
   Serial.begin(57600);
    
    ps2x.config_gamepad(4,5,6,7,true,true);   //setup pins and settings:  GamePad(clock(lila), command(naranja), attention(rojo), data (verde), Pressures?, Rumble?) check for error
    //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
    
    Serial.println("Beginning ... "); // "Beginning ..." on sender, or "Listening ..." on sever (Receiver)
  }
  
 
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
	 
     vel= map(LY, 255,0 , -255, 255);
     dir= map(LX, 0, 255, -255, 255);
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
    
    Serial.print(" vel y  ");
    Serial.print(vely);
    Serial.print(" dirx   ");
    Serial.print(dirx);
    Serial.print(" izd ");
    Serial.print(mia);
    Serial.print(" der  ");
    Serial.print(mda);
    Serial.print(" izd reverso ");
    Serial.print(mit);
    Serial.print(" der reverso  ");
    Serial.println(mdt);
  
 }
 
 
 
 
 
  void loop(){ 
    
   
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed
        
                             
    //datosenviar.
    
    LY=ps2x.Analog(PSS_LY),DEC;
    LX=ps2x.Analog(PSS_LX),DEC;
    RY=ps2x.Analog(PSS_RY),DEC;
    RX=ps2x.Analog(PSS_RX),DEC;
    
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
    movimiento();
    
    delay(50);
    
}
