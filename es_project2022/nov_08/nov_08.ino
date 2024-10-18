#include <ESP8266WiFi.h>

#include <FirebaseArduino.h>

#define FIREBASE_HOST “monitoring-system-*****-default-rtdb.firebaseio.com”

#define FIREBASE_AUTH “82uVGyZY**********************************4esgZP”

#define WIFI_SSID “JioFi3_4DA470”

#define WIFI_PASSWORD “03tact21nh”

int moistureSensor = A0;

#include <DHT.h>

#define DHTPIN 14

#define DHTTYPE DHT11

DHT dht (DHTPIN,DHTTYPE);

void setup() {
Serial.begin(9600);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print(“connecting”);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(“.”);
delay(1000);
}

dht.begin();
Serial.println(“”);
Serial.print(“connected: “);
Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
delay(1000);

pinMode(moistureSensor,INPUT);
// connect to wifi.

}

void loop()
{
float hum=dht.readHumidity();
float tem=dht.readTemperature();

int moi = analogRead(moistureSensor);

Firebase.setInt(“data1”,moi);
Serial.println(moi);
delay(1000);

Firebase.setFloat(“data2”,hum);
Serial.println(hum);
delay(1000);

Firebase.setFloat(“data3”,tem);
Serial.println(tem);
delay(1000);

}
