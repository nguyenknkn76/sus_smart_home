#define BLYNK_TEMPLATE_ID "TMPL64VpAsmq1"
#define BLYNK_TEMPLATE_NAME "demo"
#define BLYNK_AUTH_TOKEN "5pXiL09pSgYnrPKqnxSn0eOTHbysho5N"

#define BLYNK_PRINT Serial
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_DEBUG
#define gaspin 5
// cam bien muc nuoc
#define sensorPower 4
#define sensorPin A0


// anh sang
#define DO_PIN D7

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 
SimpleTimer timer;

char auth[] = "5pXiL09pSgYnrPKqnxSn0eOTHbysho5N";
char ssid[] = "Eternity guilt";
char pass[] = "123456980";

float nd;
float da;
int gas;
int as;
int mn = 0;
WidgetLED led1(V1);

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    pinMode(gaspin, INPUT);
    pinMode(16, OUTPUT);
    pinMode(5, OUTPUT);
    timer.setInterval(2000, sendUptime);

    pinMode(sensorPower, OUTPUT);
    digitalWrite(sensorPower, LOW);

    pinMode(DO_PIN, INPUT);
}

void sendUptime()
{
    readTemperatureHumidity();
    readGas();
    readWaterLevel();
    readLight();

    Blynk.virtualWrite(V6, nd);
    Blynk.virtualWrite(V5, da);
    Blynk.virtualWrite(V1, gas);
    Blynk.virtualWrite(V2, mn);
    Blynk.virtualWrite(V7, as);
}

void loop()
{
    Blynk.run();
    timer.run();

    readGas();
    readWaterLevel();
    readLight();
}

void readTemperatureHumidity()
{
    da = dht.readHumidity();
    nd = dht.readTemperature(); 
    Serial.println("Do am va nhiet do");
    Serial.print("Do am hien tai = ");
    Serial.println(da);
    Serial.print("Nhiet do hien tai = ");
    Serial.println(nd); 
}

void readGas()
{
    gas = digitalRead(gaspin);
    Serial.print("gas = ");
    Serial.println(gas);
    if (gas == LOW) {
        digitalWrite(16, LOW);
        led1.off();
        Serial.println("gas: binh thuong");   
    } else {
        digitalWrite(16, HIGH);
        led1.on();
        Serial.println("gas: cao");
    }
}

void readWaterLevel()
{
    digitalWrite(sensorPower, HIGH);
    delay(10);
    mn = analogRead(sensorPin);
    digitalWrite(sensorPower, LOW);
    Serial.print("Muc nuoc: ");
    Serial.println(mn);
}

void readLight()
{
    as = digitalRead(DO_PIN);
    Serial.println(as);
    if (as == HIGH) {
        Serial.println("Khong co anh sang, BAT DEN");
    } else {
        Serial.println("Dang co anh sang , TAT DEN");
    }
}
