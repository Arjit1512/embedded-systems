#include <ESP8266WiFi.h>
//#include <FirebaseArduino.h> 
#include <FirebaseESP8266.h>
FirebaseJson json;

FirebaseData firebaseData;
#define FIREBASE_HOST "team-6-a79db-default-rtdb.firebaseio.com"

#define FIREBASE_AUTH "N3yGpgwEgNnPaTk9jiZ4ylkuUN0BAU7i1fk3h3ha"

#define WIFI_SSID "IIITS_Student"

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

int sensorFLOWPin = D2;
volatile long pulse;
void setup() {
pinMode(sensorFLOWPin, INPUT);  
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
 
  
  delay(100);

  
 


}

dht.begin();
Serial.println("");
Serial.print("connected: ");
Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
delay(1000);

pinMode(moistureSensor,INPUT); //BE CAREFUL
// connect to wifi.
 attachInterrupt(digitalPinToInterrupt(sensorFLOWPin), increase, RISING);

}

void loop()
{
  float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(moistureSensor)/1023.00) * 100.00 ) );



  int moi= moisture_percentage;
//int moi = analogRead(moistureSensor);
float hum=dht.readHumidity();
float tem=dht.readTemperature();
float volume;

volume = 2.663 * pulse / 1000 * 30;
pulse=0;


//unsigned long lastTime;


//int sensorValue = analogRead(sensorPin);

  //  Serial.println("Water level in 1st tank :");
  //  Serial.println(sensorValue);
  
/*int sensorValue1 = analogRead(sensorPin1);

    Serial.println("Water level in 2nd tank :");
    Serial.println(sensorValue1);
  
*/



Serial.println("Moisture = ");
Serial.println(moi);
Serial.print("%");
Serial.println(" ");
delay(1000);


Serial.println("Humidity = ");
Serial.println(hum);
Serial.print("%");
Serial.println(" ");
delay(1000);


Serial.println("Temperature = ");
Serial.println(tem);
Serial.print("c"); 
Serial.println(" ");
delay(1000);


Serial.println("Moisture Percentage = ");
Serial.println(moisture_percentage);
Serial.print("%"); 
Serial.println(" ");
delay(1000);



  Serial.println("Flow rate =");
  Serial.print(volume);
  Serial.println(" L/m");
  delay(1000);
  

if(moisture_percentage<10){
Firebase.setInt(firebaseData,"data1",moi);
Firebase.setFloat(firebaseData,"data2",hum);
Firebase.setFloat(firebaseData,"data3",tem);
Firebase.setFloat(firebaseData,"data4",moisture_percentage);
Firebase.setFloat(firebaseData,"data6",volume);
String y="ON";
Firebase.setString(firebaseData,"data5",y);

}else{
  Firebase.setInt(firebaseData,"data1",moi);
Firebase.setFloat(firebaseData,"data2",hum);
Firebase.setFloat(firebaseData,"data3",tem);
Firebase.setFloat(firebaseData,"data4",moisture_percentage);
Firebase.setFloat(firebaseData,"data6",volume);
String n="OFF";
Firebase.setString(firebaseData,"data5",n);

}

//Firebase.setFloat(firebaseData,"data5",pump_status);
//Firebase.setFloat(firebaseData,"data6",volume);

 
//Serial.print("Soil Moisture(in Percentage) = ");
  //Serial.print(moisture_percentage);
  //Serial.println("%");


  delay(1000);

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
ICACHE_RAM_ATTR void increase() {
  pulse++;
}
/*
void sendSensor()
{
  int moi = analogRead(moistureSensor);
 // readSoil();
  if(moi>=80)//soilLevel
  {    
   analogWrite(moi, LOW);
    Serial.println("moisture level =");
    Serial.println(moi);
    //Serial.println(soilLevel);
    //vLcd.print(0,0,"Water Pump OFF");
    Serial.println("Pump motor status :ON");
   // pump.off();
  }
  
 if(moi<20)//soilLevel
  {    
    analogWrite(moi, HIGH);
//    vLcd.print(0,0, "Water Pump ON ");
Serial.println("moisture level =");
    Serial.println(moi);
    //Serial.println(soilLevel);
   Serial.println("Pump motor status :OFF");
//    pump.on();
  }
}
void readSoil()
{
  soilR=analogRead(soil);  
  Serial.println(soilR);
  soilLevel=map(soilR, 0, 1024, 200,0); // adjust soil level here
  Serial.println(soilLevel);
//  Blynk.virtualWrite(V0, soilLevel);
  delay(1000);
}
*/
