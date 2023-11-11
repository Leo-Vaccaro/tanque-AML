#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <SoftwareSerial.h>

SoftwareSerial miBT(10, 11);  
MPU6050 sensor;

// Valores RAW (sin procesar) del acelerometro  en los ejes x,y,z
int ax, ay, az;
float accel_ang_x=0,accel_ang_y=0;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;

void angulito(void){
   sensor.getAcceleration(&ax, &ay, &az);
   accel_ang_x=atan(ax/sqrt(pow(ay,2) + pow(az,2)))*(180.0/3.14);
   accel_ang_y=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(180.0/3.14);
  //Mostrar los angulos separadas por un [tab]
  
}

void setup() {
  Serial.begin(38400);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor
  miBT.begin(38400);

  if (sensor.testConnection()) {
    Serial.println("Sensor iniciado correctamente");
  }
  else{
    Serial.println("Error al iniciar el sensor");
  }
  for (int RateCalibrationNumber=0;RateCalibrationNumber<2000;RateCalibrationNumber ++) {
    angulito();
    RateCalibrationRoll+=accel_ang_x;
    RateCalibrationPitch+=accel_ang_y;
    delay(1);
  }
  RateCalibrationRoll=RateCalibrationRoll/2000-90;
  RateCalibrationPitch/=2000;
  Serial.print(RateCalibrationRoll); 
  Serial.println("Listo");  // escribe Listo en el monitor
}

void loop() {
  angulito();
  accel_ang_x-=RateCalibrationRoll;
  accel_ang_y-=RateCalibrationPitch;
  Serial.print("Inclinacion en X: ");
  Serial.print(accel_ang_x); 
  Serial.print("  Inclinacion en Y:");
  Serial.println(accel_ang_y); 
  if((accel_ang_x<120&&accel_ang_x>85)&&(accel_ang_y<120&&accel_ang_y>-3)){
     Serial.println("Nada");
     miBT.write("0");
     Serial.println("0");
  }
  if((accel_ang_x<85&&accel_ang_x>68)&&(accel_ang_y<15&&accel_ang_y>-10)){
     Serial.println("Atras");
     miBT.write("2");
     Serial.println("2");
  }
  if((accel_ang_x<68&&accel_ang_x>0)&&(accel_ang_y<15&&accel_ang_y>-10)){
     Serial.println("Adelante");
     miBT.write("1");
     Serial.println("1");
  }
  if((accel_ang_y<-25&&accel_ang_y>-80)&&(accel_ang_x<65&&accel_ang_x>20)){
     Serial.println("Izquierda");
     miBT.write("4");
     Serial.println("4");
  }
  if((accel_ang_y<70&&accel_ang_y>25)&&(accel_ang_x<65&&accel_ang_x>20)){
     Serial.println("Derecha");
     miBT.write("3");
     Serial.println("3");
  }
  delay(30);
}
