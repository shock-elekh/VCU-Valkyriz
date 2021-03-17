

int HighCurrentsensorPin = 20;    // select the input pin for the potentiometer
int LowCurrentsensorPin = 21;    // select the input pin for the potentiometer
int TeensyGNDPin = 22;    // select the input pin for the potentiometer
int PowerFromMACPin = 23;    // select the input pin for the potentiometer

float HighCurrentsensorValue = 0;  // variable to store the value coming from the sensor
float LowCurrentsensorValue = 0;  // variable to store the value coming from the sensor
float PowerFromMACValue = 0;  // variable to store the value coming from the sensor
float TeensyGNDValue = 0;  // variable to store the value coming from the sensor
float PowerFromMACTrueValue = 3.3;    // select the input pin for the potentiometer


void setup() {Serial.begin(9600);
 
}

void loop() {
  // read the value from the sensor:
  HighCurrentsensorValue = analogRead(HighCurrentsensorPin);    
    // read the value from the sensor:
  LowCurrentsensorValue = analogRead(LowCurrentsensorPin);
    // read the value from the sensor:
  TeensyGNDValue = analogRead(HighCurrentsensorPin);    
    // read the value from the sensor:
  PowerFromMACValue = analogRead(LowCurrentsensorPin);
  Serial.print("5V power from the MAC : ");
  Serial.println(PowerFromMACValue*PowerFromMACTrueValue/1023);
  Serial.print("GND of the teensy 3.5 : ");
  Serial.println(TeensyGNDValue*PowerFromMACTrueValue/1023);
  Serial.print("high current voltage value : ");
  Serial.println(HighCurrentsensorValue*PowerFromMACTrueValue/1023*1.5);
  Serial.print("low current voltage value : ");
  Serial.println(LowCurrentsensorValue*PowerFromMACTrueValue/1023*1.5);
  Serial.print("high current sensor value : ");
  Serial.println(((HighCurrentsensorValue*PowerFromMACTrueValue/1023*1.5)-2.5)/0.0057);
  Serial.print("low current sensor value : ");
  Serial.println(((LowCurrentsensorValue*PowerFromMACTrueValue/1023*1.5)-2.5)/0.0667);
  delay(5000);
  
}
