int sensorPin = D2;
volatile long pulse;
unsigned long lastTime;
float volume;
void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
}
void loop() {
  
  /*if (millis() - lastTime > 2000) {
    pulse = 0;
    lastTime = millis();
  }*/
    volume = 2.663 * pulse / 1000 * 30;
 // pulse=0;
  
  Serial.print(volume);
  Serial.println(" L/m");
  delay(1000);
}
ICACHE_RAM_ATTR void increase() {
  pulse++;
}
