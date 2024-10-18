#define sensorPin A0
#define sensorPin2 A1

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue = analogRead(sensorPin);

    Serial.println("Water level in 1st tank :");
    Serial.println(sensorValue);
delay(2000);

int sensorValue2 = analogRead(sensorPin2);

    Serial.println("Water level in 2nd tank :");
    Serial.println(sensorValue2);
delay(2000);


}
