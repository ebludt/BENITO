
////////////////////////////////////////////////////////////////////////////
/// esta pestaña almacena todas las funciones de transmision de datos./////
//////////////////////////////////////////////////////////////////////////





//--------------------------------------función de comprobación de ultima recepción---------------
void checkConect(){
  currentMillis = millis(); //almacenamos el momento actual
  if(currentMillis - previousMillis > tiempoDesc){ //comprobamos si desde la ultima vez que recibimos datos hasta ahora ha pasado mas del intervalo de seguridad
    alto(); //si ha pasado mas del intervalo de seguridad paramos el vehiculo.
    Serial.println("conexion perdida");
    switch (control_rc) {
            case 1:
             //control nrfl2401
             //intentamos rearmar el mirf
              Mirf.spi = &MirfHardwareSpi;
              Mirf.csnPin = Pincsnmirf;
              Mirf.cePin = Pincemirf;
              Mirf.init(); 
              Mirf.setRADDR((byte *)"recep");
              Mirf.payload = 6;
    
              Mirf.config();
              Serial.println("Intentando rearmar");
              delay(500);
             break;
             default: 
            // if nothing else matches, do the default
          // default is optional
              break;
    }
  }
}


//función de recepción de tados
void recibirdatos(){
     
     switch (control_rc) {
            case 1:
             //control nrfl2401
             byte data[6]; // or int data[32];
             data[0]=128;
             data[1]=128;
             if(Mirf.dataReady()){
                Mirf.getData((byte *) &data);    
             }
             datosrecibirrobot.LY=data[0];
             datosrecibirrobot.LX=data[1];
             datosrecibirrobot.RY=data[2];
             datosrecibirrobot.RX=data[3];
             //Serial.println(datosrecibirrobot.LY);
             //comprobamos que recibimos el byte de control y que hay conexion
             if (data[4]==142){
               previousMillis=millis();
             movimiento(); //llamamos a la funcion que mueve el robot  
             camServo();  
             }
             else{
                checkConect();
              }
             
             delay(50);
             //Serial.println("="); 
     
            break;
            case 2:
              //control mediante serial

              if(ETin.receiveData()){
                //this is how you access the variables. [name of the group].[variable name]
                //since we have data, we will blink it out. 
                 /*analogWrite(PinMIF,datosrecibirrobot.LY );
               analogWrite(PinMIR,datosrecibirrobot.LX );
               analogWrite(PinMDF,datosrecibirrobot.RY );
               analogWrite(PinMDR,datosrecibirrobot.RX );*/
             
                previousMillis=millis(); //almacenamos en la ultima vez que hemos recibido un dato
                movimiento(); //llamamos a la funcion que mueve el robot  
                camServo();
                delay(50);
                digitalWrite(max485en,HIGH);
                ETout.sendData();
                delay(10);
                digitalWrite(max485en,LOW);    
              }
              else{
                checkConect();
              } 
             break;
            default: 
            // if nothing else matches, do the default
          // default is optional
            break;
        }
        
        
     
  
  
  
  
}
