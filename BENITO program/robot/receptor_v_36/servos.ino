
////////////////////////////////////////////////////////////////////////////
/// esta pestaÃ±a almacena todas las funciones de moviento de servos./////
//////////////////////////////////////////////////////////////////////////

//funcion que controla el movimientos de los servos
void camServo(int ServoX , int ServoY, int velocidad, int Comandoservo){
  
    
     
      if (Comandoservo==2){
           servoh.write(90);
           servov.write(90); 
      }
      /*
      if (velocidad==253){
        if  (ServoX< (128-zm) || ServoX> (128+zm)){    
           servoh.write((servoh.read())-(map(ServoX, 0, 255, -3, 3))); 
           if (DepuradoSerial==2) Serial.println((servoh.read())-(map(ServoX, 0, 255, -3, 3)));
           
        }
      
        if  (ServoY< (128-zm) || ServoY> (128+zm)){               
              servov.write((servov.read())-(map(ServoY, 255, 0, -3, 3)));
              if (DepuradoSerial==2)Serial.println(servov.read())-(map(ServoY, 0, 255, -3, 3));
              servoVViejo=servov.read();
        }
      }      
      */
      
      
      if  (ServoX< (128-zm) || ServoX> (128+zm)){    
           servoh.write((servoh.read())-(map(ServoX, 0, 255, -3, 3))); 
           //Serial.println((servoh.read())-(map(ServoX, 0, 255, -3, 3)));
           //if (DepuradoSerial==2) Serial.print((servoh.read())-(map(ServoX, 0, 255, -3, 3)));
           
        }
      
        if  (ServoY< (128-zm) || ServoY> (128+zm)){               
              servov.write((servov.read())-(map(ServoY, 255, 0, -3, 3)));
             // if (DepuradoSerial==2)Serial.print(servov.read())-(map(ServoY, 0, 255, -3, 3));
              servoVViejo=servov.read();
        }
      
      //compensaciÃ³n vertical de servo
      /*
      #ifdef mpu6050_sensor
      if (abs(AngleComp[0])>2){
          servov.write((servoVViejo)+(AngleComp[0]));
          //Serial.print("Servo compensado  ");Serial.println((servov.read())+(AngleComp[0]));
      }
      #endif
      
      #ifdef DMP6_mpu6050
      if (abs(AngleComp[0])>2){
          servov.write((servoVViejo)+(AngleComp[0]));
          Serial.print("Servo compensado  ");Serial.println((servov.read())+(AngleComp[0]));
      }
      #endif
      */
    
}

