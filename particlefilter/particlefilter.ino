#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;
float error_particles[100];
float weights[100];
bool firstime;

float mini;
float maxi;
void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  firstime = true;
}

void loop() {
  // read the sensor
  IMU.readSensor();
  // display the data
  Serial.print("AccelX: ");
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("  ");
  Serial.print("AccelY: ");  
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("  ");
  Serial.print("AccelZ: ");  
  Serial.println(IMU.getAccelZ_mss(),6);
  float accelero = IMU.getAccelX_mss();
  Serial.print("GyroX: ");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("  ");
  Serial.print("GyroY: ");  
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("  ");
  Serial.print("GyroZ: ");  
  Serial.println(IMU.getGyroZ_rads(),6);
  float gyro = IMU.getGyroX_rads();
  Serial.print("MagX: ");  
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("  ");  
  Serial.print("MagY: ");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("  ");
  Serial.print("MagZ: ");  
  Serial.println(IMU.getMagZ_uT(),6);
  float magnetometer = IMU.getMagX_uT();
  Serial.print("Temperature in C: ");
  Serial.println(IMU.getTemperature_C(),6);
  Serial.println();
  if(firstime)
  {
    create_particles(0,90, gyro);
    firstime = false; 
  }
  else
  {
    create_particles(mini, maxi, gyro);
  }
  assign_weights(gyro, magnetometer, accelero);
  float errorX = filter_bad_particles(magnetometer);
  Serial.print("Particle Filtered error:       ");
  Serial.println(errorX);
  delay(200);
} 
void create_particles(float _min, float _max, float gyro)
{
  for(int i = 0;i<100;i++)
  {
    error_particles[0] = random(_min, _max) * gyro; // multiply the random number with some operation that gives a relation with the error of the drone and the raw gyroscope readings.
  }
  
}
void assign_weights(float gyro, float magneto, float acc) // pass in current gyro, magnetometer and accelorometer readings
{
  float expected_error = gyro + magneto + acc; // change the formula so that it is similar as the one in the create particles method, but this one uses magnetometer in an additive sense.
  for(int i = 0;i<100;i++)
  {
    weights[i] = error_particles[i] / expected_error;
  }
}
float filter_bad_particles(float magneto)
{
  int smallest_weight_index = 0;
  int largest_weight_index = 0;
  for(int i = 0;i<99;i++)
  {
    if(weights[i] > 1.2){weights[i] = 0.5;}
    if(weights[i] > weights[largest_weight_index])                                         // this  for loop filters all particles that are +- 20% relative to expected error
    {
      largest_weight_index = i;
    }
    if(weights[i] < 0.8){weights[i] = 1000;}
    if(weights[i] < weights[smallest_weight_index])
    {
      smallest_weight_index = i;
    }
    
  }
  mini = error_particles[smallest_weight_index] + magneto; // use the same formula as above
  maxi = error_particles[largest_weight_index] + magneto; //use the same formula as above
  return (mini + maxi) / 2;
}
