


void camServo(){
      //int servoinicial;
      
      if  (datosrecibirrobot.RX< (128-zm) || datosrecibirrobot.RX> (128+zm)){    
           servoh.write((servoh.read())-(map(datosrecibirrobot.RX, 255, 0, -8, 10))); 
            
      }
      if  (datosrecibirrobot.RY< (128-zm) || datosrecibirrobot.RY> (128+zm)){               
            servov.write((servov.read())-(map(datosrecibirrobot.RY, 255, 0, -8, 10)));
      }
            
      
     
}
