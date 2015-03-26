#include "Arduino.h"



//función que envia y recibe datos con el robot

void enviardatos(){
  
  
  long ultimoMillis = 0; //almacenamos ultimo tiempo donde no hemos recibido conexión
  unsigned long actualMillis;
                                     // Set up a variable to indicate if a response was received or not
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
 
 
  #ifdef control_rc_MIRF //////////////////////////////////////////MODO MIRF/////////////////////////////////////////////////////////////////////////////////////
  
  
    //////////////////////////////////////////////////////////////CONFIGURACION Y VARIABLES
   
    unsigned long started_waiting_at = millis();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;
    
    //Asignamos dirección del receptor
    Mirf.setTADDR((byte *)"recep");
    
    
    /////////////////////////////////////////////////////////////EMISION
    Mirf.send((byte *) &Vals);  
    while(Mirf.isSending()&& timeout==false){
      
        if(millis() - started_waiting_at > 10){
          timeout==true;
          Serial.println(F("timeout emision"));
          break;
                      
        }
        Serial.print ("+");
    }
    //apagamos el Led y damos un tiempo de espera
    timeout=false;
    digitalWrite(PinLed, LOW);
    delay(50);//50
    
    ///////////////////////////////////////////////////////////RECEPCION
    //Activamos modo de recepcion que y ponemos a cero la variable de control de tiempo
    Mirf.powerUpRx();                 
    started_waiting_at = millis();
    
    //esperamos hasta que recibamos o pasen mas de 50 milisegundos
    while ( ! Mirf.dataReady()&&timeout==false ){                 // While nothing is received
                    
                    if (millis() - started_waiting_at > 50 ){            // Si esperamos mas de 50 milisegundos la variable timeout se pasa a true y se rompe el bucle
                      timeout = true;
                      Serial.println(F("timeout recepcion"));
                      break;
                      
                    }      
    }
    
    //si no se recibe se muestra un mensaje    
    if ( timeout ){                                             // Describe the results
              Serial.println(F("Failed, response timed out."));
    }
    //si se recibe capturamos el datos y lo almacenamos en el vector de bytes Vals
    else{
               Mirf.getData((byte *) &Vals);
               Serial.print("-");
    }  
    
    //Si recibimos al valor de control encendemos el led
    if (Vals[4]==150) digitalWrite(PinLed, HIGH);
       
   
    //Si no recibimos al valor de control almentamos el valor del contador de perdidas.
    else{
       contador=contador+1; 
    }
    
    
    
    ////////////////////////////////////////////////////ENVIAR INFORMACION ESTADO
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
    
  #endif
  //////////////////////////////////////////MODO serial/////////////////////////////////////////////////////////////////////////////////////
  #ifdef control_rc_SERIAL
  
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
  #endif




}



