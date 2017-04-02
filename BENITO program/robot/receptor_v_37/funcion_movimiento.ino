
////////////////////////////////////////////////////////////////////////////
/// esta pestaÃ±a almacena todas las funciones de movimiento del robot./////
//////////////////////////////////////////////////////////////////////////



/*#################################################################################################################################
  ##                          FUNCION ALTO                                                                                       ##
  #################################################################################################################################
*/
void alto(){
  
  
            #ifdef control_motores_ESC
              //control mediante esc
              servomi.write(Servomid);
              servomd.write(Servomid);
            #endif

            
            #ifdef control_motores_IBT2
            
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
            #endif
            
            
            #ifdef control_motores_MonsterMoto
                parar();
            #endif
  
}





/*#################################################################################################################################
  ##                          FUNCION DE MOVIMIENTO                                                                              ##
  #################################################################################################################################
*/
void movimiento( float eje_ly, float eje_lx, int velocidad){
     
       //declaramos variables
       //float eje_lx, eje_ly;
       
       int giromotorizd=100;
       int giromotordch=100;
       
       //float motor_izd;
      // float motor_dch;
       
       int motorizd;
       int motordch;
       
       //limite mÃ¡ximo y minimo para el mapeo del eje x y su suavizado en los giros
       int maxmezcla=200;
       int minmezcla=-200;
       
       
       int estado_motores=0;
       //Serial.println(datosrecibirrobot.LX);
       
       //ponemos los motores a 0 por si hay perdidas o error en comunicacion
           #ifdef control_motores_ESC
              //control mediante esc
              motorizd=Servomid;
              motordch=Servomid;
           #endif
            #ifdef control_motores_IBT2
              //control mediante IBT 2
              motorizd=0;
              motordch=0;
             #endif
             #ifdef control_motores_MonsterMoto
              //control mediante IBT 2
              motorizd=0;
              motordch=0;
             #endif
       
       
       //almacenar los datos 
       eje_ly= map(datosrecibirrobot.LY, 255,0 , -255, 255);
       //eje_lx= map(datosrecibirrobot.LX, 0, 255, minmezcla, maxmezcla);
      eje_lx= map(datosrecibirrobot.LX, 255,0 , -255, 255);
       
      
      //suavizado cuadrÃ¡ticp del eje X para giros mas suaves.
      //eje_lx= (abs(eje_lx)*eje_lx)/ maxmezcla;
      
      
       //comprobacion de zona muerta
       int zm_corregida;
       zm_corregida=zm*2;
       if (abs(eje_ly)<zm_corregida) eje_ly=0;                 
       if (abs(eje_lx)<zm_corregida && abs(eje_ly)<zm_corregida)  eje_lx=0; 
         
        //=====================================================================================
        /*   
       //mezclado de eje para usar en modo carro de combate giramos ejes de coordenadas 45 grados
       motor_izd= (eje_lx*(0.70716))+(eje_ly*(0.70716));
       motor_dch= ((-eje_lx)*(0.70716))+(eje_ly*(0.70716));
       //limitamos el valor a -180 180
       motor_izd=constrain(motor_izd,-180,180);
       motor_dch=constrain(motor_dch,-180,180);
       
       
       //mapeamos para que pasa a -225 255
       motor_izd=map(motor_izd,-180,180,-255,255);
       motor_dch=map(motor_dch,-180,180,-255,255);
       
       /* 
       //eliminiado en v.021 para mayor sensibilidad en el giro
       //aplicamos una funciÃ³n cubica para que el acelerado sea mas suave
       motor_izd=(motor_izd*motor_izd*motor_izd/65025);
       motor_dch=(motor_dch*motor_dch*motor_dch/65025);
       */
       
       //aplicamos una funciÃ³n cubica para que el acelerado sea mas suave
       //motor_izd=(motor_izd*motor_izd/255);
       //motor_dch=(motor_dch*motor_dch/255);
       
       
       //==================================================================================

    //int analogTmp = 0; //temporary variable to store 
    int throttle, direction = 0; //throttle (Y axis) and direction (X axis) 
    
    int leftMotor,leftMotorScaled = 0; //left Motor helper variables
    float leftMotorScale = 0;
    
    int rightMotor,rightMotorScaled = 0; //right Motor helper variables
    float rightMotorScale = 0;
    
    float maxMotorScale = 0; //holds the mixed output scaling factor
    
    //int deadZone = 10; //jostick dead zone     
  
  throttle = (512-eje_ly)/2;

  direction = -(512-eje_lx)/2;

  //mix throttle and direction
  leftMotor = throttle+direction;
  rightMotor = throttle-direction;

    //Serial.print("Joy Y:"); Serial.print(analogRead(joysticYA));
 // Serial.print(", Joy x:"); Serial.print(analogRead(joysticXA));


  //print the initial mix results
  //Serial.print(",  LIN:"); Serial.print( leftMotor, DEC);
  //Serial.print(", RIN:"); Serial.print( rightMotor, DEC);

  //calculate the scale of the results in comparision base 8 bit PWM resolution
  leftMotorScale =  leftMotor/255.0;
  leftMotorScale = abs(leftMotorScale);
  rightMotorScale =  rightMotor/255.0;
  rightMotorScale = abs(rightMotorScale);

  //Serial.print("| LSCALE:"); Serial.print( leftMotorScale,2);
  //Serial.print(", RSCALE:"); Serial.print( rightMotorScale,2);

  //choose the max scale value if it is above 1
  maxMotorScale = max(leftMotorScale,rightMotorScale);
  maxMotorScale = max(1,maxMotorScale);

  //and apply it to the mixed values
  leftMotorScaled = constrain(leftMotor/maxMotorScale,-255,255);
  rightMotorScaled = constrain(rightMotor/maxMotorScale,-255,255);

  //Serial.print("| LOUT:"); Serial.print( leftMotorScaled);
  //Serial.print(", ROUT:"); Serial.print( rightMotorScaled);

  //Serial.print(" |");
  motor_izd=leftMotorScaled;
  motor_dch=rightMotorScaled;
       
       //aplicamos la reducion de velocidad
       /*if (velocidad<250){
           motor_izd=motor_izd/velocidad*10;
           motor_dch=motor_dch/velocidad*10;
       }
       */
       motor_izd=motor_izd/velocidad*10;
       motor_dch=motor_dch/velocidad*10;
       
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


       motor_izd = constrain(motor_izd, -255, 255);
       motor_dch = constrain(motor_dch, -255, 255);
       // Mostrar en puerto serie
       
       
       //FORMA DE CONTROL DE MOTORES.
            #ifdef control_motores_ESC
              //control mediante esc
              motor_izd=map(motor_izd,-255,255,0,180);
              motor_dch=map(motor_dch,-255,255,0,180);
              servomi.write(motor_izd);
              servomd.write(motor_dch);
              
              //Puerto serial
              
            #endif

            
            #ifdef control_motores_IBT2
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
              
            #endif


            #ifdef control_motores_MonsterMoto
                if (motor_izd>0){
                  motorGo(0, CCW, motor_izd);
                }
                else if(motor_izd<0){
                  motorGo(0, CW, abs(motor_izd));
               }
                    

               if (motor_dch>0){
                  motorGo(1, CCW, motor_dch);
                }
                else if(motor_dch<0){
                  motorGo(1, CW, abs(motor_dch));
               }

               if (motor_izd==0) motorOff(0);
               if (motor_dch==0) motorOff(1);
            #endif
            
       /*
       if (DepuradoSerial==1){
           Serial.print("eje ly  ");
           Serial.print(eje_ly); // mandamos el dato al monitor serie
           Serial.print("  eje lx ");
           Serial.print(eje_lx); // mandamos el dato al monitor serie
           Serial.println("  :-)");
         
       }    
       
       
                Serial.print("  motor izd  ");
                 Serial.print(motor_izd);
                 Serial.print(" motor dch ");
                 Serial.print(motor_dch);
      
      */ 
      
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//
//                                    FUNCIONES PROPIOS DE LOS MODULOS DE MOTORES
//
//------------------------------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------------------------------
//                                    MonsterMoto
//------------------------------------------------------------------------------------------------------------------------------------------

#ifdef control_motores_MonsterMoto
                       void motorOff(int motor) {
                                            // Initialize braked
                                            for (int i=0; i<2; i++)
                                            {
                                              digitalWrite(inApin[i], LOW);
                                              digitalWrite(inBpin[i], LOW);
                                            }
                                            analogWrite(pwmpin[motor], 0);
                       }
                                  
                                  /* motorGo() will set a motor going in a specific direction
                                   the motor will continue going in that direction, at that speed
                                   until told to do otherwise.
                                   
                                   motor: this should be either 0 or 1, will selet which of the two
                                   motors to be controlled
                                   
                                   direct: Should be between 0 and 3, with the following result
                                   0: Brake to VCC
                                   1: Clockwise
                                   2: CounterClockwise
                                   3: Brake to GND
                                   
                                   pwm: should be a value between ? and 1023, higher the number, the faster
                                   it'll go
                                   */
                       void motorGo(int motor, int direct, int pwm){
                                    if (motor <= 1)
                                    {
                                      if (direct <=4)
                                      {
                                        // Set inA[motor]
                                        if (direct <=1)
                                          digitalWrite(inApin[motor], HIGH);
                                        else
                                          digitalWrite(inApin[motor], LOW);
                                  
                                        // Set inB[motor]
                                        if ((direct==0)||(direct==2))
                                          digitalWrite(inBpin[motor], HIGH);
                                        else
                                          digitalWrite(inBpin[motor], LOW);
                                  
                                        analogWrite(pwmpin[motor], pwm);
                                      }
                                    }
                       }
                    
                      void parar(){
                        motorOff(0);
                        motorOff(1);
                        Serial.println("parado");
                    
                      }
#endif 

