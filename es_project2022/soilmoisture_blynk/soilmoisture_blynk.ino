// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID           "TMPLsB3zpkOF"
#define BLYNK_DEVICE_NAME           "Soil Moisture Monitoring"
#define BLYNK_AUTH_TOKEN "kRBlEXvtgRB-IFeSZ2piBsdpTvgM_no_"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

#define soil A0
#define waterPump D7
WidgetLED pump(V1);

float soilLevel, soilR;
WidgetLCD vLcd(V2);
void sendSensor()
{
  readSoil();
  if(soilLevel>=80)
  {    
    digitalWrite(waterPump, LOW);
    vLcd.print(0,0,"Water Pump OFF");
    pump.off();
  }
  
 if(soilLevel<20)
  {    
    digitalWrite(waterPump, HIGH);
    vLcd.print(0,0, "Water Pump ON ");
    pump.on();
  }
}
void readSoil()
{
  soilR=analogRead(soil);  
  Serial.println(soilR);
  soilLevel=map(soilR, 0, 1024, 200,0); // adjust soil level here
  Serial.println(soilLevel);
  Blynk.virtualWrite(V0, soilLevel);
  delay(1000);
}

void setup()
{
  Serial.begin(115200);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, LOW);
  
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  sendSensor();
}
