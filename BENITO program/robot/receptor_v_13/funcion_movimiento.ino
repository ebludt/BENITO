//se colocan todas las funciones que afectan al movimiento del vehiculo





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
              analogWrite(PinMIF,20);
              analogWrite(PinMIR,20);
              analogWrite(PinMDF,20);
              analogWrite(PinMDR,20); 
              delay(10);
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
void movimiento(){
     /*long vely;
     float dirx;
     long vel;
     long dir;
     float mia=0;
     float mit=0;
     float mda=0;
     float mdt=0;
     int izd=0;
     int der=0;
     int motorizd=Servomid;
     int motordch=Servomid;
	 
     vel= map(datosrecibirrobot.LY, 255,0 , -255, 255);
     dir= map(datosrecibirrobot.LX, 0, 255, -255, 255);
     vely=sqrt(sq(vel)+sq(dir));
     if (vely>255){
       vely=255;
     }
     dirx=abs(float(vel)/float(vely));
  
     
     
     if (vel> zm){ //si presionamos le joystick adelante
         if (dir>(zm/2)){//si giramos a la derecha.
             izd=int(vely);
             der=int(vely*dirx);
             
         }
         else if(dir<(-zm/2)) { //a la izquierda
             izd=int(vely*dirx);
             der=int(vely);
             
         }
         else { //tutiavante
           izd=int(vely);
           der=int(vely);
         }
     }
     else if (vel<-zm){ //si va para atras
         
         if (dir>zm/2){//patras y a la derecha)
            izd=(-1)*(int(vely));
            der=(-1)*(int(vely*dirx));
         }
         else if (dir<zm/2){
           izd=(-1)*(int(vely*dirx));
           der=(-1)*(int(vely));
         }
         
         else { //tutireverso
           izd=(-1)*(int(vely));
           der=(-1)*(int(vely));
         }
     }
     
     else {//mi palante ni patras en pivote
     
         if (dir>zm){ //si para la derecha
             izd=vely/1;
             der=-vely/1;
         }
         else if (dir<-zm){
             
             izd=-vely/1;
             der=vely/1;
         
         }
         
     }
     
     if ((vel <zm) && (vel > -zm) && (dir<zm) && (dir>-zm)){
       } 
     
     if(izd>0){
       mia=izd;
       mia= map(mia, zm,255 , 0, 255);
       mia=((mia*mia*mia)/65025);
       motorizd=(map(mia,0,255,Servomid,Servomax));
       }
     else if (izd<-0){
       mit=abs(izd);
       mit= map(mit, zm,255 , 0, 255);
       mit=((mit*mit*mit)/65025);
       motorizd=(map(mit,0,255,Servomid,Servomin));
       }
       
     if(der>0){
       mda=der;
       mda= map(mda, zm,255 , 0, 255);
       mda=(mda*mda*mda/65025);
       motordch=(map(mda,0,255,Servomid,Servomax));
       }
     else if (der<0){
       mdt=abs(der);
       mdt= map(mdt, zm,255 , 0, 255);
       mdt=(mdt*mdt*mdt/65025);
       motordch=(map(mdt,0,255,Servomid,Servomin));
       }  
       */
       
       //declaramos variables
       float eje_lx, eje_ly;
       
       int giromotorizd=100;
       int giromotordch=100;
       float motor_izd;
       float motor_dch;
       int motorizd;
       int motordch;
       
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
              if (DepuradoSerial==1){
                Serial.print(" izd ");
                 Serial.print(motor_izd);
                 Serial.print(" giro ");
                 Serial.print(giromotorizd);
                 Serial.print(" dch ");
                 Serial.print(motor_dch);
                 Serial.print(" giro ");
                 Serial.print(giromotordch);
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
