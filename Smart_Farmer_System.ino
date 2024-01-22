
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2GHTTxTgV"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "GUfOD_IR8oeRVauV7AmJF1Ad9Fta3OXJ"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Staff";
char pass[] = "Ejust-Staff-2023";

const int ldrPin = 34;  
const int controlPin = 35;  
const int irSensorPin = 15;  

unsigned long previousMillis = 0;
const long interval = 500;  // Interval in milliseconds (1 second)

void setup()
{
    Serial.begin(115200);

    pinMode(5, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(21, OUTPUT);
    
    pinMode(controlPin, OUTPUT);
    pinMode(irSensorPin, INPUT);
    
    digitalWrite(controlPin, HIGH); 
    digitalWrite(26, HIGH);
    
    digitalWrite(2, LOW);
    digitalWrite(12, LOW);
    digitalWrite(18, LOW);
    digitalWrite(27, LOW);
    digitalWrite(32, LOW);
 
  // Debug console
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();

    int irSensorValue = digitalRead(irSensorPin);

    if (irSensorValue == LOW) {
      Blynk.virtualWrite(V1,"Fire detected");
    } else {
      Blynk.virtualWrite(V1,"Nothing detected");
    }
    
 unsigned long currentMillis = millis();

  // Check if the specified interval has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the current time

    int ldrValue = analogRead(ldrPin);

    Blynk.virtualWrite(V0,ldrValue);

  }
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  ledcAttachPin(5, 0); // Attach pin 5 to channel 0
  ledcSetup(0, 1000, 8); // 1000 Hz PWM, 8-bit resolution
  ledcWrite(0, pinValue);
}
BLYNK_WRITE(V4)
{
  int pinValue = param.asInt();
  ledcAttachPin(19, 1); // Attach pin 19 to channel 1
  ledcSetup(1, 1000, 8); // 1000 Hz PWM, 8-bit resolution
  // Set PWM value
  ledcWrite(1, pinValue);

}

BLYNK_WRITE(V5)
{
  int pinValue = param.asInt();
  ledcAttachPin(21, 2); // Attach pin 21 to channel 2
  ledcSetup(2, 1000, 8); // 1000 Hz PWM, 8-bit resolution
  // Set PWM value
  ledcWrite(2, pinValue);
}
