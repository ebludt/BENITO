
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
  
  //digitalWrite(max485en,LOW);
  if(ETin.receiveData()){
    //this is how you access the variables. [name of the group].[variable name]
    //since we have data, we will blink it out. 
   /*analogWrite(PinMIF,datosrecibirrobot.LY );
   analogWrite(PinMIR,datosrecibirrobot.LX );
   analogWrite(PinMDF,datosrecibirrobot.RY );
   analogWrite(PinMDR,datosrecibirrobot.RX );
   */
     movimiento(); //llamamos a la funcion que mueve el robot  
     camServo();
     previousMillis=millis(); //almacenamos en la ultima vez que hemos recibido un dato
     delay(50);
     digitalWrite(max485en,HIGH);
     ETout.sendData();
     delay(10);
     digitalWrite(max485en,LOW);
     
     
  }
  else{
      checkConect();
  }
     
  
  //you should make this delay shorter then your transmit delay or else messages could be lost
  
  
  
}
