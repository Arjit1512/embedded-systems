#include <ESP8266WiFi.h>
#include <FirebaseArduino.h> 

#define FIREBASE_HOST "group-6-be9ed-default-rtdb.firebaseio.com"

#define FIREBASE_AUTH "IKsrq53aJl38of41IxCIXqzPwyxz1CkwiKwJmX5j"

#define WIFI_SSID "Hello"

#define WIFI_PASSWORD "12345678"

int moistureSensor = A0;

#include <DHT.h>

#define DHTPIN 14

#define DHTTYPE DHT11

DHT dht (DHTPIN,DHTTYPE);

void setup() {
Serial.begin(115200);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(1000);
}

dht.begin();
Serial.println("");
Serial.print("connected: ");
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

Firebase.setInt("data1",moi);
//Serial.println("Moisture = ");
Serial.println(moi);
delay(1000);

Firebase.setFloat("data2",hum);
//Serial.println("Humidity = ");
Serial.println(hum);
delay(1000);

Firebase.setFloat("data3",tem);
//Serial.println("Temperature = ");
Serial.println(tem);
delay(1000);

}
