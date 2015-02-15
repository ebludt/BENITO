//se colocan todas las funciones que afectan al movimiento del vehiculo





// funcion que detiene todos los motores
void alto(){
  /*
  analogWrite(PinMIF,0);
  analogWrite(PinMIR,0);
  analogWrite(PinMDF,0);
  analogWrite(PinMDR,0); 
  */
  servomi.write(90);
  servomd.write(90);
}

//Funcion que controla el movimiento
void movimiento(){
     long vely;
     float dirx;
     long vel;
     long dir;
     float mia=0;
     float mit=0;
     float mda=0;
     float mdt=0;
     int izd=0;
     int der=0;
     int motorizd=90;
     int motordch=90;
	 
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
     
     if(izd>0){
       mia=izd;
       mia= map(mia, zm,255 , 0, 255);
       mia=((mia*mia*mia)/65025);
       motorizd=(map(mia,0,255,90,180));
       }
     else if (izd<-0){
       mit=abs(izd);
       mit= map(mit, zm,255 , 0, 255);
       mit=((mit*mit*mit)/65025);
       motorizd=(map(mit,0,255,90,0));
       }
       
     if(der>0){
       mda=der;
       mda= map(mda, zm,255 , 0, 255);
       mda=(mda*mda*mda/65025);
       motordch=(map(mda,0,255,90,180));
       }
     else if (der<0){
       mdt=abs(der);
       mdt= map(mdt, zm,255 , 0, 255);
       mdt=(mdt*mdt*mdt/65025);
       motordch=(map(mdt,0,255,90,0));
       }  
       
       
       servomi.write(motorizd);
       servomd.write(motordch);
       /*analogWrite(PinMIF,(mia));
       analogWrite(PinMIR,(mit));
       analogWrite(PinMDF,(mda));
       analogWrite(PinMDR,(mdt));
       */
       
       ///pruebaenvio
       datosenviarrobot.prueba= mia;
       //Serial.print("dir ");
       //Serial.print(dir); // mandamos el dato al monitor serie
       /*rial.print("  mia ");
       Serial.print(mia); // mandamos el dato al monitor serie
       Serial.print("  mir ");
       Serial.print(mit);
       Serial.print("  mda ");
       Serial.print(mda);
       Serial.print("  mdr ");
       Serial.print(mdt);
       */
}
