#include "Arduino.h"



//función que envia y recibe datos con el robot

void enviardatos(){
  
  long ultimoMillis = 0; //almacenamos ultimo tiempo donde no hemos recibido conexión
  unsigned long actualMillis;
  boolean recibido=false;
  
 /* 
  Serial.print (Vals[0]);
  Serial.print ("    ");
  Serial.print (Vals[1]);
  Serial.print ("    ");
  Serial.print (Vals[2]);
  Serial.print ("    ");
  Serial.print (Vals[3]);
  //Serial.print ("    ");
  //Serial.print (analogRead(JoyPinLY)); 
  //Serial.print ("    ");
  //Serial.print (analogRead(JoyPinLX));
 
 Serial.println (" -- ");
*/
 
 
  switch (control_rc){
  
    ////////////////////////////////////////////////////////////                 NRF24L01////////////////////////////////////////
    case 1:
    //control nrfl2401
  
    Mirf.setTADDR((byte *)"recep");
    Mirf.send((byte *) &Vals);
    while(Mirf.isSending()){
      //
      //Wait.
      //Serial.println ("enviando");
    }
    digitalWrite(PinLed, LOW);
    delay(20);
    
    ///////////////////////////RECEPCION
    
    if(Mirf.dataReady()){
                Mirf.getData((byte *) &Vals);
                //Serial.println("recibiendo");    
             }
      
    
    
    if (Vals[4]==150){
      digitalWrite(PinLed, HIGH);
       
    }
    else{
      
      contador=contador+1;
      
    }
    millis_ahora=millis();
    if (millis_ahora - millis_antes > intervalo_muestra)
    {
        millis_antes=millis_ahora; 
        Serial.print(Vals[0]);
        Serial.print("   "); 
        Serial.print(Vals[5]);
        Serial.print("   "); 
        Serial.println(contador);
      digitalWrite(PinLed, HIGH);
     }
    //digitalWrite(PinLed, HIGH);

    
    //Serial.println("="); 
    //Serial.println ("nrfl");
    break;
  case 2:
    //control mediante serial
    
    datosenviar.LY=Vals[0];
    datosenviar.LX=Vals[1];
    datosenviar.RY=Vals[2];
    datosenviar.RX=Vals[3];
    datosenviar.Control=Vals[4];
    datosenviar.Vel=Vals[5];
    digitalWrite(max485en,HIGH); //activa el max845 en modo de transmisión
    ETout.sendData(); //envia datos
    delay(50); //pausa para que los datos se envien
    digitalWrite(max485en,LOW); //coloca el max485 en modo recepción

    //pasamos a recepción.
    ultimoMillis=millis();
    do
    {
      //digitalWrite(PinLed,LOW);
      if(ETin.receiveData()){
        recibido=true;
        if (datosrecibir.prueba >10){
          digitalWrite(PinLed,HIGH);
        }
        else{
          digitalWrite(PinLed,LOW);
        }
        // digitalWrite(PinLed,LOW);
      }
      delay(10);
      actualMillis=millis();
      if (actualMillis-ultimoMillis> 50){
        recibido=true;
      }

    } 
    while (recibido==false);
    //Serial.println ("serial");
    break;
  default: 
    // if nothing else matches, do the default
    // default is optional
    //Serial.println ("otro");
    break;
  }




}



