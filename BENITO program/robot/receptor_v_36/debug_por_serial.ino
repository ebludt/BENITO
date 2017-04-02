

void debugPorSerial(){

  byte debug_servo = 0;
  byte debug_mpu = 0;
  byte debug_rx = 1;
  byte debug_motores = 1;

  
 if (debug_servo==1){ 
  Serial.print(" servoh ");
  Serial.print(servoh.read());
  Serial.print(" servov ");
  Serial.print(servov.read());
 }
  
/*
 if (debug_mpu==1){
     if ((millis()-millis_antes_mostrar_mpu)>intervalo_muestra){
       Serial.println("-");
       Serial.print(" Angle X: "); Serial.print(Angle[0]);Serial.print(" Compensado "); Serial.print(AngleComp[0]); Serial.print(" Enviado  "); Serial.print(datosenviarrobot.AnguloX); Serial.println(" ");
       Serial.print(" Angle Y: "); Serial.print(Angle[1]);Serial.print(" Compensado "); Serial.print(AngleComp[1]); Serial.print(" Enviado  "); Serial.print(datosenviarrobot.AnguloY); Serial.println(" ");
       //Serial.println(float(millis_ahora_mpu*0.000001));
      // Serial.println(millis_ahora_mpu*0.000001,4);
       millis_antes_mostrar_mpu=millis();
       //Serial.println(DepuradoSerial);
     }
   }
   */
  if (debug_rx==1){
           Serial.print("  eje ly  ");
           Serial.print(datosrecibirrobot.LY); // mandamos el dato al monitor serie
           Serial.print("  eje lx ");
           Serial.print(datosrecibirrobot.LX); // mandamos el dato al monitor serie
           Serial.print(" velocidad  ");
           Serial.print(datosrecibirrobot.Vel); // mandamos el dato al monitor serie
            Serial.print("  eje Ry  ");
           Serial.print(datosrecibirrobot.RY); // mandamos el dato al monitor serie
           Serial.print("  eje Rx ");
           Serial.print(datosrecibirrobot.RX); // mandamos el dato al monitor serie
           Serial.print("  control ");
           Serial.print(datosrecibirrobot.ComandoControl); // mandamos el dato al monitor serie
       }    
       
       if (debug_motores==1){
                Serial.print("  motor izd  ");
                 Serial.print(motor_izd);
                 Serial.print(" motor dch ");
                 Serial.print(motor_dch);
      }

  Serial.println("-");
     




}  

