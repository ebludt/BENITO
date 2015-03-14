#include "Arduino.h"

//funcion que obliga al operador a mover los joystick a su posición máxima antes de empezar a emitir

void armar_conexion(){
  
  millis_ahora = millis(); 
  int comprobar_max=0;
  int comprobar_min=0; 
   
  Serial.println("Iniciando armado");
  Serial.println("Mueve el joystick hasta el maximo");
  
  
  switch (control_joystick){
  case 1:
    ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed     
    
    
    break;
  case 2:
    while(comprobar_min < 1){
      while(comprobar_max < 1){
        if (analogRead(JoyPinLY)<50){
          Serial.println("Mueve el joystick hasta el mínimo");
          comprobar_max=256;
        }
      }
      if (analogRead(JoyPinLY)>1000){
          Serial.println("Conexion armada");
          comprobar_min=256;
      }
        
    }
    break;
  
  }
  
  
delay(1000);  

  
  
}
