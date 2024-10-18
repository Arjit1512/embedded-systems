#include <ESP8266WiFi.h>
//#include <FirebaseArduino.h> 
#include <FirebaseESP8266.h>
FirebaseJson json;

FirebaseData firebaseData;
#define FIREBASE_HOST "team-6-a79db-default-rtdb.firebaseio.com"

#define FIREBASE_AUTH "N3yGpgwEgNnPaTk9jiZ4ylkuUN0BAU7i1fk3h3ha"

#define WIFI_SSID "IIITS_Students"

#define WIFI_PASSWORD "iiit5@2k18"
//#define soil A0
#define pumpMotor D7

#define moistureSensor A0
//int moistureSensor = D7;

//int moi = digitalRead(moistureSensor);
#include <DHT.h>

#define DHTPIN 14

#define DHTTYPE DHT11

DHT dht (DHTPIN,DHTTYPE);
float soilLevel, soilR;
char *pump_status="ON";

#define sensorPin A0
//#define sensorPin1 A1

volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
//unsigned long currentTime;
//unsigned long cloopTime;
void flow () // Interrupt function
{
   flow_frequency++;
}

void setup() {
Serial.begin(9600);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(1000);

pinMode(pumpMotor,OUTPUT);
//pinMode(waterPump, OUTPUT);
//  digitalWrite(waterPump, LOW);

//pinMode(moi, OUTPUT);
  //digitalWrite(moi, LOW);
 pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
  // currentTime = millis();
  // cloopTime = currentTime;

  
  delay(1000);

}

dht.begin();
Serial.println("");
Serial.print("connected: ");
Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
delay(1000);

pinMode(moistureSensor,INPUT); //BE CAREFUL
// connect to wifi.

}

void loop()
{
  float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(moistureSensor)/1023.00) * 100.00 ) );



  int moi= moisture_percentage;
//int moi = analogRead(moistureSensor);
float hum=dht.readHumidity();
float tem=dht.readTemperature();

//int sensorValue = analogRead(sensorPin);

  //  Serial.println("Water level in 1st tank :");
  //  Serial.println(sensorValue);
  
/*int sensorValue1 = analogRead(sensorPin1);

    Serial.println("Water level in 2nd tank :");
    Serial.println(sensorValue1);
  
*/


      cloopTime = currentTime; // Updates cloopTime
     Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      Serial.print(l_hour, DEC); // Print litres/hour
      Serial.println(" L/hour");
   delay(1000);


Firebase.setInt(firebaseData,"data1",moi);
Serial.println("Moisture = ");
Serial.println(moi);
Serial.print("%");
Serial.println(" ");
delay(1000);

Firebase.setFloat(firebaseData,"data2",hum);
Serial.println("Humidity = ");
Serial.println(hum);
Serial.print("%");
Serial.println(" ");
delay(1000);

Firebase.setFloat(firebaseData,"data3",tem);
Serial.println("Temperature = ");
Serial.println(tem);
Serial.print("c"); 
Serial.println(" ");
delay(1000);

Firebase.setFloat(firebaseData,"data4",moisture_percentage);
Serial.println("Moisture Percentage = ");
Serial.println(moisture_percentage);
Serial.print("%"); 
Serial.println(" ");
delay(1000);


Firebase.setFloat(firebaseData,"data5",l_hour);
Serial.println("Flow rate value = ");
Serial.println(l_hour);
Serial.print("L/hr"); 
Serial.println(" ");
delay(1000);






//Firebase.setFloat(firebaseData,"data5",pump_status);


 
//Serial.print("Soil Moisture(in Percentage) = ");
  //Serial.print(moisture_percentage);
  //Serial.println("%");


  //delay(1000);

   if (moisture_percentage < 10) {
    digitalWrite(pumpMotor, HIGH);
    Serial.println("SOIL IS DRY");
    Serial.println("PUMP MOTOR IS ON");
    //pump_status="ON";
    

  }
  else if (moisture_percentage >10 && moisture_percentage <50 ) {
    digitalWrite(pumpMotor, LOW);
    Serial.println("SOIL IS WET");
    Serial.println("PUMP MOTOR IS OFF");
    //pump_status="OFF";
  }
  else if (moisture_percentage > 50 ) {
    digitalWrite(pumpMotor, LOW);
    Serial.println("SOIL IS FULLY WATERED");
    Serial.println("PUMP MOTOR IS OFF");
    //pump_status="OFF";
  }





//sendSensor();
}
