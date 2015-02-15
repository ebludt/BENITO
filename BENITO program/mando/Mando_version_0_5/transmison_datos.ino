#include "Arduino.h"


//función que envia y recibe datos con el robot

void enviardatos(){
    
     digitalWrite(max485en,HIGH); //activa el max845 en modo de transmisión
     ET.sendData(); //envia datos
     delay(50); //pausa para que los datos se envien
     digitalWrite(max485en,LOW); //coloca el max485 en modo recepción
     }
