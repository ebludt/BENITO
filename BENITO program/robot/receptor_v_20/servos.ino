
////////////////////////////////////////////////////////////////////////////
/// esta pestaña almacena todas las funciones de moviento de servos./////
//////////////////////////////////////////////////////////////////////////

//funcion que controla el movimientos de los servos
void camServo(int ServoX , int ServoY){
     
      
      if  (ServoX< (128-zm) || ServoX> (128+zm)){    
           servoh.write((servoh.read())-(map(ServoX, 0, 255, -8, 10))); 
            
      }
      if  (ServoY< (128-zm) || ServoY> (128+zm)){               
            servov.write((servov.read())-(map(ServoY, 255, 0, -8, 10)));
      }
            
      
     
}
