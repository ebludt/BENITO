
////////////////////////////////////////////////////////////////////////////
/// esta pestaña almacena todas las funciones de transmision de datos./////
//////////////////////////////////////////////////////////////////////////





//--------------------------------------función de comprobación de ultima recepción---------------
void checkConect(){
  currentMillis = millis(); //almacenamos el momento actual
  //contador=contador+1;
  //Serial.println(contador); 
  if(currentMillis - previousMillis > tiempoDesc){ //comprobamos si desde la ultima vez que recibimos datos hasta ahora ha pasado mas del intervalo de seguridad
    alto(); //si ha pasado mas del intervalo de seguridad paramos el vehiculo.
    Serial.print("TX bad ");
    previousMillis=millis();
          
          
    #ifdef control_rc_MIRF
             //control nrfl2401
             //intentamos rearmar el mirf
              ArmarMIRF();
              
              
              Serial.println("rearmar");
              delay(50);
    #endif
   }
}


//--------------------------------------función armar mirf---------------

void ArmarMIRF(){
  #ifdef control_rc_MIRF
      Mirf.spi = &MirfHardwareSpi;
      Mirf.csnPin = Pincsnmirf;
      Mirf.cePin = Pincemirf;
      Mirf.init(); 
      Mirf.setRADDR((byte*) Direccion_receptor);
      Mirf.channel = 90;
      Mirf.payload = 7;//sizeof(datosenviarrobot);
      Mirf.config();
      Mirf.configRegister(RF_SETUP,0x06); 
  #endif
  

}



//--------------------------------------función de recepcion de datos---------------
void recibirdatos(){
     int emitiendo=1;
     unsigned long started_waiting_at=millis(); //controla el tiempo que empezó a escuchar para hacer un timeout
     int recibidoPaquete=0; //control de si se ha recibido correctamente algo
     //unsigned long started_waiting_at = micros();
     
     
      //============================================Control por MIRF==========================================
     #ifdef control_rc_MIRF
             //control nrfl2401
             
             unsigned long transmitiendoMillis;
             
             datosrecibirrobot.LY=128;
             datosrecibirrobot.LX=128;
             datosrecibirrobot.Control=0;
             datosenviarrobot.Control=0;
             
             Mirf.powerUpRx();
                          
             unsigned long started_waiting_at = millis();               // Set up a timeout period, get the current microseconds
             boolean timeout = false;                                  // Set up a variable to indicate if a response was received or not
                          
            //________________________________________________Recibir datos _________________________________
            while ( ! Mirf.dataReady()&&timeout==false ){                 // While nothing is received
                    if (millis() - started_waiting_at > 100 ){            // If waited longer than 100millis, indicate timeout and exit while loop
                      timeout = true;
                      break;  
                    }      
            }
            
             
            if ( timeout ){                                             // Si timeout en true es que se ha producido un fallo de recepción
              Serial.print(F("Fallo recepción. Timeout"));
              checkConect();
              
            }
            else{                                                      // en caso contrario recibimos perfectamente
               Mirf.getData((byte *) &datosrecibirrobot);   
            }
            
            //________________________________________________Enviar datos_________________________________
             //comprobamos que recibimos el byte de control y que hay conexion 
             if (datosrecibirrobot.Control==Codigo_control){
                 previousMillis=millis();
                 digitalWrite(PinLed,HIGH);
                 Serial.println(datosrecibirrobot.Control);
             
            
               
                 //________________________________________________PRUEBA EMISION_________________________________
                 transmitiendoMillis=millis();
                 datosenviarrobot.LY=random(1, 200);
                 datosenviarrobot.Control=CodigoControlRespuesta;
                 
                 //________________________________________________EMISION_________________________________
                 Mirf.setTADDR((byte *)Direccion_emisor);
                 Mirf.send((byte *) &datosenviarrobot);
                 
                 while(Mirf.isSending() && emitiendo>0){
                    // Serial.print("_"); 
                     if(millis() - transmitiendoMillis > 20){ 
                       emitiendo=0;
                       Serial.println("Fallo emisión. Timeout");
                     } 
                 }    
               
               
             //________________________________________________PROCESADO DE DATOS_________________________________  
             recibidoPaquete=1;
             }
             
             else{
                 Serial.println(datosrecibirrobot.Control);
                Serial.println("COD CONTROL INCORRECTO");
                
                 //________________________________________________PRUEBA EMISION_________________________________
                 transmitiendoMillis=millis();
                 datosenviarrobot.LY=random(1, 200);
                 datosenviarrobot.Control=CodigoControlRespuesta;
                 
                 //________________________________________________EMISION_________________________________
                 Mirf.setTADDR((byte *)Direccion_emisor);
                 Mirf.send((byte *) &datosenviarrobot);
                 
                 while(Mirf.isSending() && emitiendo>0){
                    // Serial.print("_"); 
                     if(millis() - transmitiendoMillis > 20){ 
                       emitiendo=0;
                       Serial.println("Fallo emisión. Timeout");
                     } 
                 }    
               
              }
             //antes 10
             delay(15);
             
     
     #endif
     
     
     //============================================Control por SERIAL==========================================
     #ifdef control_rc_SERIAL
            
              if(ETin.receiveData()){
                //this is how you access the variables. [name of the group].[variable name]
                //since we have data, we will blink it out. 
                 /*analogWrite(PinMIF,datosrecibirrobot.LY );
               analogWrite(PinMIR,datosrecibirrobot.LX );
               analogWrite(PinMDF,datosrecibirrobot.RY );
               analogWrite(PinMDR,datosrecibirrobot.RX );*/
             
                previousMillis=millis(); //almacenamos en la ultima vez que hemos recibido un dato
               recibidoPaquete=1;
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
     
    //============================================Control por RF24==========================================
    #ifdef control_RF24  
      #ifdef SaltoFrecuenciaNRF24L01
                Serial.print ("canal ");Serial.println(saltocanalactual);
     #endif
    
      if( radio.available()){ //IF 1                                                         
        digitalWrite(PinLed,HIGH);
        boolean timeout=false;      
        Serial.print("<");
        while (radio.available()){ //WHILE 1.1                                             // While there is data ready
          radio.read( &datosrecibirrobot, sizeof(datosrecibirrobot) ); 
        contador_datosconexion=contador_datosconexion+1;        // Get the payload
        } //WHILE 1.1

        if (timeout==false){ //IF 1.2
          
          //datosenviarrobot.LY=random(1, 250);                             
          radio.writeAckPayload(1,&datosenviarrobot, sizeof(datosenviarrobot));
          recibidoPaquete=1;
               
        
          /*Serial.print(F("Sent response "));
          Serial.print(datosrecibirrobot.LX);  
          Serial.print(" : ");
          Serial.println(datosrecibirrobot.Control);
          */
          previousMillis=millis();
          Serial.print(">");
          digitalWrite(PinLed,LOW);
          
          #ifdef SaltoFrecuenciaNRF24L01
             
             
             switch (contadorsaltocanales) {
                case 1:
                   contadorsaltocanales=2;
                   radio.setChannel(30);
                   radio.startListening();
                   saltocanalactual=1;
                break;
                case 2:
                  contadorsaltocanales=3;
                   radio.setChannel(10);
                   radio.startListening();
                   saltocanalactual=2;
                break;
                case 3:
                  contadorsaltocanales=1;
                  radio.setChannel(20);
                  radio.startListening();
                  saltocanalactual=3;
                break;
                default: 
                  // if nothing else matches, do the default
                  // default is optional
                break;
                delay(20);
              }
           Serial.print(saltocanalactual);
          #endif
              
        }// IF 1.2
        if (timeout==true){ //IF 1.3
         alto();
         Serial.println("Timeout"); 
        }//IF 1.3
      
     } //IF 1
     else{ //ELSE 1
        Serial.print("-");
        //Serial.print(millis());
        checkConect();
     } //ELSE 1
     
     delay(20);
      
    #endif
    
    //=====================================================================control por UART=============================================
    #ifdef control_rc_UART
       digitalWrite(PinLed,LOW);
       byte timeout=0;
       
       //Serial2.end();
       //Serial2.begin(9600);
       unsigned long millisControlRecepcion = millis();
       digitalWrite(PinLed,LOW);
       while((recibidoPaquete==0)&&(timeout==0)){
         if(ETin.receiveData()){    
            Serial.print("< ");      
            previousMillis=millis(); //almacenamos en la ultima vez que hemos recibido un dato
            recibidoPaquete=1;
            contador_datosconexion=contador_datosconexion+1; 
            digitalWrite(PinLed,HIGH);
            //delay(10);
            
         }
         else{
           checkConect();
           //Serial.print("/");
           
           if (millis()-millisControlRecepcion>130){
             timeout=1;
             if (timeout>0)Serial.print("T");
           }
           
         }
       }
       
       //++++++++++++++++++++++++++++++++++++++++experimento+++++++++++++++
       /*
       if(ETin.receiveData()){    
            Serial.print("< ");      
            previousMillis=millis(); //almacenamos en la ultima vez que hemos recibido un dato
            recibidoPaquete=1;
            //delay(10);
            
       }
       else checkConect();
       */
       //-------------------------------------fin
       
       
       
       ETout.sendData();
       Serial.print(">");
       #ifdef placa_control_nano 
            Serial.flush();        
       #endif 
       #ifdef placa_control_ramps     
            Serial2.flush(); 
       #endif
       #ifdef placa_control_ramps     
            Serial2.flush(); 
       #endif
       //delay(10);
       
            //lcd.setBacklight(0);  
          
    #endif
  //============================================Procesado de datos si se ha recibido paquete ==========================================
  
  
  if (millis()-millis_antes_datos_conexion>intervalo_muestra_datos_conexion){
    //digitalWrite(PinLed,HIGH);
    millis_antes_datos_conexion=millis();
    Serial.print("recibidos  ");
    Serial.print(contador_datosconexion);
    Serial.print(" paquetes ");
    Serial.print(millis()/1000);
    Serial.println(" seg");
    contador_datosconexion=0;
    
  }
  
  
  if (recibidoPaquete==1){
     movimiento(datosrecibirrobot.LY, datosrecibirrobot.LX, datosrecibirrobot.Vel); //llamamos a la funcion que mueve el robot  
     camServo(datosrecibirrobot.RX,datosrecibirrobot.RY,datosrecibirrobot.Vel,datosrecibirrobot.ComandoControl); 
     debugPorSerial();
     #ifdef LucesFrontales
             if (datosrecibirrobot.ComandoControl==2){
                if (lucesFrontal>200) lucesFrontal=0;
                else lucesFrontal=lucesFrontal+64;
                if (lucesFrontal>255) lucesFrontal=255;
                
                Serial.print(" LF "); Serial.print(lucesFrontal);
                controlLucesFrontal(lucesFrontal);
                
             }
     #endif
  }
  
  
}
