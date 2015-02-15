
////////////////////////////////////////////////////////////////////////////
/// esta pestaña almacena todas las funciones de transmision de datos./////
//////////////////////////////////////////////////////////////////////////





//--------------------------------------función de comprobación de ultima recepción---------------
void checkConect(){
  currentMillis = millis(); //almacenamos el momento actual
  if(currentMillis - previousMillis > tiempoDesc){ //comprobamos si desde la ultima vez que recibimos datos hasta ahora ha pasado mas del intervalo de seguridad
  alto(); //si ha pasado mas del intervalo de seguridad paramos el vehiculo.
  }
}


//función de recepción de tados
void recibirdatos(){
     
    
     byte data[20]; // or int data[32];
     data[0]=128;
     data[1]=128;
     if(Mirf.dataReady()){
          
          Mirf.getData((byte *) &data);
         //Serial.println("recibo"); 
     }
     datosrecibirrobot.LY=data[0];
     datosrecibirrobot.LX=data[1];
     datosrecibirrobot.RY=data[2];
     datosrecibirrobot.RX=data[3];
     Serial.println("="); 
     Serial.println(datosrecibirrobot.LY);
     Serial.println(datosrecibirrobot.LX);
     movimiento(); //llamamos a la funcion que mueve el robot  
     camServo();
     delay(50);
  //you should make this delay shorter then your transmit delay or else messages could be lost
  
  
  
}
