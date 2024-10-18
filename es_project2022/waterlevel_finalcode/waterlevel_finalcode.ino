const int analogInPin = A0;
int sensorValue = 0;

void setup() {
  // declare pin  to be an output:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  sensorValue = analogRead(analogInPin);
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");
  delay(1000);
}
