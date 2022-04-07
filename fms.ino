
// constants won't change. Used here to set a pin number:
const int ledPin =  13;// the number of the LED pin

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
      digitalWrite(ledPin, HIGH);
    }
    else {
      digitalWrite(ledPin, LOW);
    }
    Serial.flush();





    
}
