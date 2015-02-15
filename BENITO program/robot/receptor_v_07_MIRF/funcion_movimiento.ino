//se colocan todas las funciones que afectan al movimiento del vehiculo





// funcion que detiene todos los motores
void alto(){
  analogWrite(PinMIF,0);
  analogWrite(PinMIR,0);
  analogWrite(PinMDF,0);
  analogWrite(PinMDR,0); 
  
}

//Funcion que controla el movimiento
void movimiento(){
     long vely;
     float dirx;
     long vel;
     long dir;
     int mia=0;
     int mit=0;
     int mda=0;
     int mdt=0;
     int izd=0;
     int der=0;
	 
     vel= map(datosrecibirrobot.LY, 255,0 , -255, 255);
     dir= map(datosrecibirrobot.LX, 0, 255, -255, 255);
     vely=sqrt(sq(vel)+sq(dir));
     if (vely>255){
       vely=255;
     }
     dirx=abs(float(vel)/float(vely));
  
     
     
     if (vel> zm){ //si presionamos le joystick adelante
         if (dir>zm){//si giramos a la derecha.
             izd=int(vely);
             der=int(vely*dirx);
             
         }
         else if(dir<-zm) { //a la izquierda
             izd=int(vely*dirx);
             der=int(vely);
             
         }
         else { //tutiavante
           izd=int(vely);
           der=int(vely);
         }
     }
     else if (vel<-zm){ //si va para atras
         
         if (dir>zm){ //patras y a la derecha)
            izd=(-1)*(int(vely));
            der=(-1)*(int(vely*dirx));
         }
         else if (dir<-zm){
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
             izd=vely;
             der=-vely;
         }
         else if (dir<-zm){
             
             izd=vely;
             der=-vely;
         
         }
         
     }
     
     if(izd>0){
       mia=izd;
       mia= map(mia, zm,255 , 0, 255);
       }
     else if (izd<-0){
       mit=abs(izd);
       mit= map(mit, zm,255 , 0, 255);
       }
       
     if(der>0){
       mda=der;
       mda= map(mda, zm,255 , 0, 255);
       }
     else if (der<0){
       mdt=abs(der);
       mdt= map(mdt, zm,255 , 0, 255);
       }  
       
       
       
       analogWrite(PinMIF,(mia));
       analogWrite(PinMIR,(mit));
       analogWrite(PinMDF,(mda));
       analogWrite(PinMDR,(mdt));
       
       ///pruebaenvio
       datosenviarrobot.prueba= mia;
       
       Serial.println(mia);
       Serial.println(mit);
       
}
