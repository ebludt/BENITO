
////////////////////////////////////////////////////////////////////////////
/// esta pestaña almacena todas las funciones de transmision de datos./////
//////////////////////////////////////////////////////////////////////////





//--------------------------------------función de comprobación de ultima recepción---------------
void checkConect(){
  currentMillis = millis(); //almacenamos el momento actual
  contador=contador+1;
  Serial.println(contador); 
  if(currentMillis - previousMillis > tiempoDesc){ //comprobamos si desde la ultima vez que recibimos datos hasta ahora ha pasado mas del intervalo de seguridad
    alto(); //si ha pasado mas del intervalo de seguridad paramos el vehiculo.
    Serial.print("TX bad ");
          
          
    #ifdef control_rc_MIRF
             //control nrfl2401
             //intentamos rearmar el mirf
              Mirf.spi = &MirfHardwareSpi;
              Mirf.csnPin = Pincsnmirf;
              Mirf.cePin = Pincemirf;
              Mirf.init(); 
              Mirf.setRADDR((byte *)"recep");
              Mirf.payload = 6;
              Mirf.channel = 90;
              Mirf.config();
              Mirf.configRegister(RF_SETUP,0x06); 
              Serial.println("rearmar");
    #endif
   }
}


//---------------------------------------------------------función de recepción de datos
void recibirdatos(){
     int emitiendo=1;
     
     #ifdef control_rc_MIRF
             //control nrfl2401
             byte data[6]; // or int data[32];
             
             
             unsigned long transmitiendoMillis;
             
             data[0]=128;
             data[1]=128;
             Mirf.powerUpRx();
             /*
             if(Mirf.dataReady()){
                Mirf.getData((byte *) &data);  
                //Serial.println("+");  
             }
             datosrecibirrobot.LY=data[0];
             datosrecibirrobot.LX=data[1];
             datosrecibirrobot.RY=data[2];
             datosrecibirrobot.RX=data[3];
             datosrecibirrobot.Control=data[4];
             datosrecibirrobot.Vel=data[5];
             //velocidad=data[5];
             
             //Serial.println(datosrecibirrobot.LY);
             
             */
             
             unsigned long started_waiting_at = millis();               // Set up a timeout period, get the current microseconds
             boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
            while ( ! Mirf.dataReady()&&timeout==false ){                 // While nothing is received
                    //Serial.println(F("check"));
                    if (millis() - started_waiting_at > 200 ){            // If waited longer than 200ms, indicate timeout and exit while loop
                      timeout = true;
                      Serial.println(F("check if"));
                      break;
                      
                    }      
            }
        
            if ( timeout ){                                             // Describe the results
              Serial.println(F("Failed, response timed out."));
              checkConect();
              
            }
            else{
               Mirf.getData((byte *) &data);
               datosrecibirrobot.LY=data[0];
               datosrecibirrobot.LX=data[1];
               datosrecibirrobot.RY=data[2];
               datosrecibirrobot.RX=data[3];
               datosrecibirrobot.Control=data[4];
               datosrecibirrobot.Vel=data[5];
            }
             //comprobamos que recibimos el byte de control y que hay conexion
             if (data[4]==Codigo_control){
                 previousMillis=millis();
                 digitalWrite(PinLed,HIGH);
               
             
            
               
            //////////////prueba emision
                 transmitiendoMillis=millis();
                 data[0]=random(1, 200);
                 data[4]=150;
                 Mirf.setTADDR((byte *)Direccion_emisor);
                 Mirf.send((byte *) &data);
                 while(Mirf.isSending() && emitiendo>0){
                    // Serial.print("_"); 
                     if(millis() - transmitiendoMillis > 100) emitiendo=0;
                     //Serial.print("0"); 
                 }    
                Serial.println(millis() - transmitiendoMillis);
             ///////////////////////////////////////////////////
               
               
             movimiento(datosrecibirrobot.LY, datosrecibirrobot.LX, datosrecibirrobot.Vel); //llamamos a la funcion que mueve el robot  
             camServo(datosrecibirrobot.RX,datosrecibirrobot.RY);
             }
             
             else{
                //checkConect();
              }
             //antes 10
             delay(50);
             //Serial.println("="); 
     
     #endif
     
     #ifdef control_rc_SERIAL
            
              if(ETin.receiveData()){
                //this is how you access the variables. [name of the group].[variable name]
                //since we have data, we will blink it out. 
                 /*analogWrite(PinMIF,datosrecibirrobot.LY );
               analogWrite(PinMIR,datosrecibirrobot.LX );
               analogWrite(PinMDF,datosrecibirrobot.RY );
               analogWrite(PinMDR,datosrecibirrobot.RX );*/
             
                previousMillis=millis(); //almacenamos en la ultima vez que hemos recibido un dato
               movimiento(datosrecibirrobot.LY, datosrecibirrobot.LX, datosrecibirrobot.Vel); //llamamos a la funcion que mueve el robot  
                camServo(datosrecibirrobot.RX,datosrecibirrobot.RY);
                delay(50);
                digitalWrite(max485en,HIGH);
                ETout.sendData();
                delay(10);
                digitalWrite(max485en,LOW); 
                //lcd.setBacklight(0);  
              }
              else{
                checkConect();
              } 
             
     #endif
        
        
     
  
  
  
  
}
