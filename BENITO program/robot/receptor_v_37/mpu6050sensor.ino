/*#################################################################################################################################
  ##                          FUNCION MPU6050            NO MODIFICAR                                                            ##
  #################################################################################################################################
*/


#ifdef mpu6050_sensor
void read_mpu6050sensor(){
   //Leer los valores del Acelerometro de la IMU
   int AnguloXint=0; int AnguloYint=0;
   Wire.beginTransmission(MPU);
   Wire.write(0x3B); //Pedir el registro 0x3B - corresponde al AcX
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true); //A partir del 0x3B, se piden 6 registros
   AcX=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   AcY=Wire.read()<<8|Wire.read();
   AcZ=Wire.read()<<8|Wire.read();
 
    //Se calculan los angulos Y, X respectivamente.
   Acc[1] = atan(-1*(AcX/A_R)/sqrt(pow((AcY/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
   Acc[0] = atan((AcY/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
 
   //Leer los valores del Giroscopio
   Wire.beginTransmission(MPU);
   Wire.write(0x43);
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,4,true); //A diferencia del Acelerometro, solo se piden 4 registros
   GyX=Wire.read()<<8|Wire.read();
   GyY=Wire.read()<<8|Wire.read();
 
   //Calculo del angulo del Giroscopio
   Gy[0] = GyX/G_R;
   Gy[1] = GyY/G_R;
 
   //Aplicar el Filtro Complementario
   
   millis_ahora_mpu=micros()-millis_antes_mpu;
   Angle[0] = 0.93 *(Angle[0]+Gy[0]*float(millis_ahora_mpu*0.000001)) + 0.07*Acc[0];
   Angle[1] = 0.93 *(Angle[1]+Gy[1]*float(millis_ahora_mpu*0.000001)) + 0.07*Acc[1];
   millis_antes_mpu=micros();
   //Mostrar los valores por consola
   //Serial.print("Angle X: ");
    
    
    AngleComp[0]=Angle[0]-AngleCalibration[0];
    AngleComp[1]=Angle[1]-AngleCalibration[1];
    
    AnguloXint=int(AngleComp[0]);
    AnguloYint=int(AngleComp[1]);
    
    datosenviarrobot.AnguloX = map(AnguloXint,-90,90,0,180);
    datosenviarrobot.AnguloY = map(AnguloYint,-90,90,0,180);
   /*  
   if (DepuradoSerial>0){
     if ((millis()-millis_antes_mostrar_mpu)>intervalo_muestra){
       Serial.println("-");
       Serial.print("Angle X: "); Serial.print(Angle[0]);Serial.print(" Compensado "); Serial.print(AngleComp[0]); Serial.print(" Enviado  "); Serial.print(datosenviarrobot.AnguloX); Serial.println(" ");
       Serial.print("Angle Y: "); Serial.print(Angle[1]);Serial.print(" Compensado "); Serial.print(AngleComp[1]); Serial.print(" Enviado  "); Serial.print(datosenviarrobot.AnguloY); Serial.println(" ");
       //Serial.println(float(millis_ahora_mpu*0.000001));
       Serial.println(millis_ahora_mpu*0.000001,4);
       millis_antes_mostrar_mpu=millis();
       Serial.println(DepuradoSerial);
     }
   }
   */
    //delay(10); //Nuestra dt sera, pues, 0.010, que es el intervalo de tiempo en cada medida
   
}
#endif

////////////////////////////----------------------soncor mpu6050 con interrupciÃ³n
#ifdef DMP6_mpu6050
    void read_DMP6_mpu6050(){
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        // other program behavior stuff here
        // .
        // .
        // .
        // if you are really paranoid you can frequently test in between other
        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
        // .
        // .
        // .
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        //Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        

        

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            /*
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
            */
            Angle[0]=(ypr[2]*180/M_PI);
            Angle[1]=(ypr[1]*180/M_PI);
            
        #endif

    
    AngleComp[0]=Angle[0]-AngleCalibration[0];
    AngleComp[1]=Angle[1]-AngleCalibration[1];
    
    int AnguloXint=0; int AnguloYint=0;
    AnguloXint=int(AngleComp[0]);
    AnguloYint=int(AngleComp[1]);
    
    datosenviarrobot.AnguloX = map(AnguloXint,-90,90,0,180);
    datosenviarrobot.AnguloY = map(AnguloYint,-90,90,0,180);
     
   if (DepuradoSerial>0){
     if ((millis()-millis_antes_mostrar_mpu)>intervalo_muestra){
       Serial.println("-");
       Serial.print("Angle X: "); Serial.print(Angle[0]);Serial.print(" Compensado "); Serial.print(AngleComp[0]); Serial.print(" Enviado  "); Serial.print(datosenviarrobot.AnguloX); Serial.println(" ");
       Serial.print("Angle Y: "); Serial.print(Angle[1]);Serial.print(" Compensado "); Serial.print(AngleComp[1]); Serial.print(" Enviado  "); Serial.print(datosenviarrobot.AnguloY); Serial.println(" ");
       //Serial.println(float(millis_ahora_mpu*0.000001));
       Serial.println(millis_ahora_mpu*0.000001,4);
       millis_antes_mostrar_mpu=millis();
       Serial.println(DepuradoSerial);
     }
   }

        
    
        

    }
    }

#endif

