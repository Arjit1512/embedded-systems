
const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
#define pumpMotor D4

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  pinMode(pumpMotor,OUTPUT);
}

void loop() {
  float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");


  delay(1000);

   if (moisture_percentage < 10) {
    digitalWrite(pumpMotor, HIGH);
    Serial.println("SOIL IS DRY");
    Serial.println("PUMP MOTOR IS ON");

  }
  else if (moisture_percentage >10 && moisture_percentage <50 ) {
    digitalWrite(pumpMotor, LOW);
    Serial.println("SOIL IS WET");
    Serial.println("PUMP MOTOR IS OFF");
  }
  else if (moisture_percentage > 50 ) {
    digitalWrite(pumpMotor, LOW);
    Serial.println("SOIL IS FULLY WATERED");
    Serial.println("PUMP MOTOR IS OFF");
  }

}
