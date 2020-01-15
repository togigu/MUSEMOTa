//------------------------ACELEROMETRO----------------------
//Funcion para la recogida de datos del acelerometro y demás. 

float *Acelerometro(float result[6]){
  
  mpu6050.update();
  
  result[1] = mpu6050.getAccX();
  result[2] = mpu6050.getAccY();
  result[3] = mpu6050.getAccZ();
  result[4] = mpu6050.getGyroX();
  result[5] = mpu6050.getGyroY();
  result[6] = mpu6050.getGyroZ();
  
  return result;

}
