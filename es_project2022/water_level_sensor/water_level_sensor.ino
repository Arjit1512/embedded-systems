// Sensor pins pin D6 LED output, pin A0 analog Input
#define ledPin 2
#define sensorPin A5
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}
void loop() {
  int sensorValue = analogRead(sensorPin);

    Serial.println("Water level in the tank :");
    Serial.println(sensorValue);
   delay(1000);
  
  if (sensorValue > 570)  {
    int outputValue = map(sensorValue, 570, 800, 0, 255);
    Serial.println("Water level in the tank :");
    Serial.println(outputValue);
    //analogWrite(ledPin, outputValue); // generate PWM signal
    delay(2000);
  }
  }
