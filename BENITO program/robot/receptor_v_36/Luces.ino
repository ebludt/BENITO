

void controlLucesFrontal(byte valor){
  #ifdef LucesFrontales 
      analogWrite(PinLucesFrontal1,valor);
      Serial.print("LUCES "); Serial.println(valor);
  #endif
}

