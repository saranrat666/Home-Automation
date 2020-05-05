#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
char auth[] = "CRtkHojRrhS9WbwIABBsotu1vir_-O29";
char ssid[] = "Anarchy";
char pass[] = "111111111";
BlynkTimer timer;
#define LED D6                  // LED on chip ESP8266
#define DHTPIN  D2              // pin of sensor connected to
#define DHTTYPE DHT11           // DHT22 if useDHT22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  //  Blynk.begin(auth, ssid, pass);
  //  Blynk.begin(auth, ssid, pass, "prakitblog.com", 8181);
  Blynk.begin(auth, ssid, pass,);
  dht.begin();
  timer.setInterval(2500, Sensor);
}
void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // run BlynkTimer
}
void Sensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    digitalWrite(LED, LOW);
    delay(1500);
    return;
  }
  Serial.print("Humidity is: "); Serial.println(h, 1);
  Serial.print("Temperature is: "); Serial.println(t, 1);
  digitalWrite(LED, HIGH);
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
}
