#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MPU6050_tockn.h>
#include "RF24.h"

#define BAUDRATE 115200
#define delayTime 100

MPU6050 mpu6050(Wire);

const int Ace_ADDR = 0x68;
const int Sen_ADDR = 0x76;
const int EchoPin = 5;
const int TriggerPin = 6;

const int channel = 115;



int distancia;
float sensor1[4];
float sensor2[6];

long timer = 0;

//----------------------CONFIGURACION DE LA RADIO---------------------------------
//Realizacion de la configuracion de la radio
RF24 myRadio(7, 8); //Definimos los conectores de la radio de digital
byte addresses[][6] = {"0"}; //Deifnimos la variable address para el posterior envio de datos
struct package // Definimos la estructura del paquete de envios de datos
{
  float T=0; //Temperatura
  float P=0; //Presion 
  float A=0; //Altura
  float H=0; //Humedad relativa
  float Ax=0; //Aceleracion en el eje x
  float Ay=0; //Aceleracion en el eje y
  float Az=0; //Aceleracion en el eje z
  float D=0; //Distancia del ultrasonidos
  //float Gx=0; //Se podria mandar los giros que mida los giros en caso necesario
  //float Gy=0;
  //float Gz=0;
};

typedef struct package Package; //Introducimos la estructura definida a nuestro packete de datos
Package data;

//--------------------------------------------------------------------------------
void setup() {
  Serial.begin(BAUDRATE);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Wire.begin();
  mpu6050.begin();
  //mpu6050.calcGyroOffsets(true);
  Wire.endTransmission(true);
  //---------------Apertura de la radio---------------
  myRadio.begin();  
  myRadio.setChannel(channel); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe(addresses[0]);
}

void loop() {
  
  Sensor(sensor1);
  Serial.print("La Temperatura es: ");
  Serial.println(sensor1[1]);
  Serial.print("La Presion es: ");
  Serial.println(sensor1[2]);
  Serial.print("La Altitud es: ");
  Serial.println(sensor1[3]);
  Serial.print("La Humedad Relativa es: ");
  Serial.println(sensor1[4]);
  
  //Acelerometro(sensor2);
  

  Acelerometro(sensor2);
  Serial.print("La Aceleracion X es: ");
  Serial.println(sensor2[1]);
  Serial.print("La Aceleracion Y es: ");
  Serial.println(sensor2[2]);
  Serial.print("La Aceleracion Z es: ");
  Serial.println(sensor2[3]);
  Serial.print("El giro X es: ");
  Serial.println(sensor2[4]);
  Serial.print("El giro Y es: ");
  Serial.println(sensor2[5]);
  Serial.print("El giro Z es: ");
  Serial.println(sensor2[6]);

  distancia=dist(TriggerPin, EchoPin);
  Serial.print("La Distancia es: ");
  Serial.println(distancia);  

  //Enviar(sensor1,sensor2,distancia);
  data.T=sensor1[1];
  data.P=sensor1[2];
  data.A=sensor1[3];
  data.H=sensor1[4];
  data.Ax=sensor2[1];
  data.Ay=sensor2[2];
  data.Az=sensor2[3];
  data.D=distancia;
  myRadio.write(&data, sizeof(data)); 
  
delay(delayTime);
}
