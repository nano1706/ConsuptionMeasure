#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
unsigned long measureTime=0;
unsigned long sendTime=0;

float busvoltage = 0;
float current_mA = 0;
float power_mW = 0;
double power_mWh = 0;


void setup() {
  Serial.begin(115200);

  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1);
  }
  
  ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  if(measureTime + 10 <= millis())
  {
    busvoltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();  
    power_mW = current_mA * busvoltage; 
    power_mWh += (power_mW*(millis()-measureTime))/3600000; //mw * ms * (1h->3600000ms)
    measureTime = millis();
  }
  if(sendTime + 500 <= millis())
  {
    Serial.print("Bus Voltage: "); Serial.print(busvoltage); Serial.println(" V");
    Serial.print("Current:     "); Serial.print(current_mA); Serial.println(" mA");
    Serial.print("Power:       "); Serial.print(power_mW); Serial.println(" mW"); 
    Serial.print("Consuption:  "); Serial.print(power_mWh); Serial.println(" mWh"); 
    Serial.println(); 

    sendTime = millis();
  }  
}