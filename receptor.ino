#include <SPI.h>
#include "RF24.h"

RF24 myRadio (7, 8);
struct package 
{
  float T;
  float P;
  float A;
  float H;
  float Ax;
  float Ay;
  float Az;
  float D;
 
};

byte addresses[][6] = {"0"}; 

typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(100);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop()  
{

  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print(data.T);
    Serial.print(' ');
    Serial.print(data.P);
    Serial.print(' ');
    Serial.print(data.A);
    Serial.print(' ');
    Serial.print(data.H);
    Serial.print(' ');
    Serial.print(data.Ax);
    Serial.print(' ');
    Serial.print(data.Ay);
    Serial.print(' ');
    Serial.print(data.Az);
    Serial.print(' ');
    Serial.println(data.D);
  }

}
