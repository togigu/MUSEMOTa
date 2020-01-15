float *Sensor(float result[4]){
  
  #define SEALEVELPRESSURE_PA (101325)
  float Temp;
  float Pres;
  float HumR;
  float Alt;
  Adafruit_BME280 bme; // I2C -> Lee sobre el protocolo I2C
  
  while(!Serial);    // time to get serial running
    unsigned status;
   // default settings
   // (you can also pass in a Wire library object like &Wire2)
   status = bme.begin();  
   if (!status) {
        digitalWrite(LED_BUILTIN, HIGH);   // Define an error
        while (1);
    }
  Wire.beginTransmission(Sen_ADDR);
  Wire.endTransmission(false);
  Temp = bme.readTemperature();
  Pres = bme.readPressure();
  Alt = bme.readAltitude(SEALEVELPRESSURE_PA/100.);
  HumR = bme.readHumidity();
  Wire.endTransmission(true);

  //Serial.print("Temperatura = ");
  //Serial.print(Temp);
  //Serial.println(" ºC"); 
  //Serial.print("Presión = ");
  //Serial.print(Pres);
  //Serial.println(" Pa");
  //Serial.print("Altura aproximada = ");
  //Serial.print(Alt);
  //Serial.println(" m");
  //Serial.print("Humedad relativa = ");
  //Serial.print(HumR);
  //Serial.println(" %");
  //Serial.println();
  result[1] = Temp;
  result[2] = Pres;
  result[3] = Alt;
  result[4] = HumR;
  
  return result;

}
