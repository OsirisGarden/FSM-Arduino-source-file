#include <DHT.h>
#define DHTPIN 2

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// constants won't change. Used here to set a pin number:
const int ledPinRelay1 =  13;// the number of the LED pin
const int ledPinRelay2 = 12;

// Variables will change:
int ledState = HIGH; 
// ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
    float val = analogRead(A0);
    Serial.println(val);
    if(val < 500) {
      digitalWrite(ledPinRelay1, HIGH);
    }
    else {
      digitalWrite(ledPinRelay1, LOW);
    }
    delay(5000);
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    Serial.println(t);
    Serial.println(h);
    if(t > 19) {
      digitalWrite(ledPinRelay2, LOW);
    }
    else {
      digitalWrite(ledPinRelay2, HIGH);
    }
    Serial.flush();    
}
