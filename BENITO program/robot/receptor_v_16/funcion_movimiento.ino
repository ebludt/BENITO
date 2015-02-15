////////////////////////////////////////////////////////////////////////////
/// esta pestaña almacena todas las funciones de movimiento del robot./////
//////////////////////////////////////////////////////////////////////////




//================================================= funcion que detiene todos los motores
void alto(){
  
  switch (control_motores) {
            case 1:
              //control mediante esc
              servomi.write(Servomid);
              servomd.write(Servomid);
            break;
            case 2:
              //control mediante IBT 2
              /*analogWrite(PinMIF,20);
              analogWrite(PinMIR,20);
              analogWrite(PinMDF,20);
              analogWrite(PinMDR,20); 
             
              delay(10);
              */
              analogWrite(PinMIF,0);
              analogWrite(PinMIR,0);
              analogWrite(PinMDF,0);
              analogWrite(PinMDR,0); 
             break;
            default: 
            // if nothing else matches, do the default
          // default is optional
            break;
        }
  
}






//========================================Funcion que controla el movimiento
void movimiento( float eje_ly, float eje_lx, int velocidad){
     
       //declaramos variables
       //float eje_lx, eje_ly;
       
       int giromotorizd=100;
       int giromotordch=100;
       float motor_izd;
       float motor_dch;
       int motorizd;
       int motordch;
       
       //ponemos los motores a 0 por si hay perdidas o error en comunicacion
       switch (control_motores) {
            case 1:
              //control mediante esc
              motorizd=Servomid;
              motordch=Servomid;
            break;
            case 2:
              //control mediante IBT 2
              motorizd=0;
              motordch=0;
             break;
            default: 
            // if nothing else matches, do the default
          // default is optional
            break;
        }
       
       
       //almacenar los datos 
       eje_ly= map(datosrecibirrobot.LY, 255,0 , -255, 255);
       eje_lx= map(datosrecibirrobot.LX, 0, 255, -255, 255);
      
       //comprobacion de zona muerta
       if (abs(eje_ly)<zm) eje_ly=0;                 
       if (abs(eje_lx)<zm) eje_lx=0;   
       
       //mezclado de eje para usar en modo carro de combate giramos ejes de coordenadas 45 grados
       motor_izd= (eje_lx*(0.70716))+(eje_ly*(0.70716));
       motor_dch= ((-eje_lx)*(0.70716))+(eje_ly*(0.70716));
       //limitamos el valor a -180 180
       motor_izd=constrain(motor_izd,-180,180);
       motor_dch=constrain(motor_dch,-180,180);
       //mapeamos para que pasa a -225 255
       motor_izd=map(motor_izd,-180,180,-255,255);
       motor_dch=map(motor_dch,-180,180,-255,255);
       
       //aplicamos una función cubica para que el acelerado sea mas suave
       motor_izd=(motor_izd*motor_izd*motor_izd/65025);
       motor_dch=(motor_dch*motor_dch*motor_dch/65025);
       
       //aplicamos la reducion de velocidad
       motor_izd=motor_izd/velocidad;
       motor_dch=motor_dch/velocidad;
       
       //aceleracion progresiva
       motor_izd_obj=motor_izd;
       motor_dch_obj=motor_dch;
       //motor izd
       if (abs(motor_izd_obj)>abs(motor_izd_ini)){
         if (motor_izd_obj>0){
           motor_izd=motor_izd_ini+aceleracion;
           motor_izd_ini=motor_izd;
         }
         else{
           motor_izd=motor_izd_ini-aceleracion;
           motor_izd_ini=motor_izd;
         }
       }
       else{
        motor_izd_ini=motor_izd; 
       }
       //motor dch
       if (abs(motor_dch_obj)>abs(motor_dch_ini)){
         if (motor_dch_obj>0){
           motor_dch=motor_dch_ini+aceleracion;
           motor_dch_ini=motor_dch;
         }
         else{
           motor_dch=motor_dch_ini-aceleracion;
           motor_dch_ini=motor_dch;
         }
       }
       else{
        motor_dch_ini=motor_dch; 
       }
       
       //FORMA DE CONTROL DE MOTORES.
       // Mostrar en puerto serie
       if (DepuradoSerial==1){
           Serial.print("eje ly  ");
           Serial.print(eje_ly); // mandamos el dato al monitor serie
           Serial.print("  eje lx ");
           Serial.print(eje_lx); // mandamos el dato al monitor serie
         
       }
       
       
       switch (control_motores) {
            case 1:
              //control mediante esc
              motor_izd=map(motor_izd,-255,255,0,180);
              motor_dch=map(motor_dch,-255,255,0,180);
              servomi.write(motor_izd);
              servomd.write(motor_dch);
              
              //Puerto serial
              if (DepuradoSerial==1){
                Serial.print("  motor izd  ");
                 Serial.print(motor_izd);
                 Serial.print(" motor dch ");
                 Serial.print(motor_dch);
              }
            break;
            case 2:
              //control mediante IBT 2 o similar
              
              //comprobamos is el motor izquierdo tiene que mover adelante o atras.
              if (motor_izd>0){
                analogWrite(PinMIF,motor_izd);
                analogWrite(PinMIR,0); 
                giromotorizd=1;
              }
              else if(motor_izd<0){
                analogWrite(PinMIF,0);
                analogWrite(PinMIR,abs(motor_izd)); 
                giromotorizd=0;
             }
             else{
                analogWrite(PinMIF,0);
                analogWrite(PinMIR,0);
                 //Serial.print(" motor izd desconectado ");
             }
             //comprobamos is el motor derecho tiene que mover adelante o atras.
              if (motor_dch>0){
                analogWrite(PinMDF,motor_dch);
                analogWrite(PinMDR,0); 
                giromotordch=1;
              }
              else if(motor_dch<0){
                analogWrite(PinMDF,0);
                analogWrite(PinMDR,abs(motor_dch));
               giromotordch=0; 
             } 
             else{
                analogWrite(PinMDF,0);
                analogWrite(PinMDR,0);
                //Serial.print(" motor dch desconectado ");
             }
              if (DepuradoSerial==14){
                Serial.print(" izd ");
                 Serial.print(motor_izd);
                 //Serial.print(" giro ");
                 //Serial.print(giromotorizd);
                 Serial.print(" dch ");
                 Serial.println(motor_dch);
                 //Serial.print(" giro ");
                 //Serial.print(giromotordch);
              }
            break;
            default: 
            // if nothing else matches, do the default
          // default is optional
            break;
        }
       
       
       
       
       /*analogWrite(PinMIF,(mia));
       analogWrite(PinMIR,(mit));
       analogWrite(PinMDF,(mda));
       analogWrite(PinMDR,(mdt));
       */
       
       ///pruebaenvio
      // datosenviarrobot.prueba= mia;
        
       
           
       
       if (DepuradoSerial==1){
         Serial.println("  :-)");
       }
       
}
