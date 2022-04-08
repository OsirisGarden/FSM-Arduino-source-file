//#include <DHT.h>
#define DHTPIN 2

#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);
//CONSTANTES PINES
const int ledPinRelay1 =  13;// the number of the LED pin
const int ledPinRelay2 = 12;
const int ledPinRelay3 = 8;//Acciona rele de la bomba

//CONSTANTES HUMEDAD
const int humedadMax = 180; //Mientras más humedad menor es la señal analógica
const int humedadMin = 750;

//CONSTANTES LUZ

//CONSTANTES TEMPERATURA


void setup() {
  // set the digital pin as output:
  Serial.begin(9600);
  //pinMode(ledPin, OUTPUT);
}

void loop() {

    
    //////////////LECTURA VALORES RASPI/////////////
    //Aqui se lee y procesa la informacion pasada por el puerto serial desde raspi a arduino
    //Probablemente haya que cambiar las const a variables
    
    //////////////GESTION TEMPERATURA///////////////
    float hum_tierra = analogRead(A1);
    if (hum_tierra > humedadMin){
      //Encendemos el rele que acciona la bomba
      digitalWrite(ledPinRelay3, HIGH);
    }else{
      //Apagamos el rele, hay humedad suficiente
      digitalWrite(ledPinRelay3, LOW);
    }
    
    //////////////GESTION LUZ///////////////////////

    
    //////////////GESTION TEMPERATURA///////////////

    
    //////////////ESCRITURA VALORES PARA RASPI//////
    float val = analogRead(A0);
    //Serial.println(val);
    if(val < 500) {
      digitalWrite(ledPinRelay1, HIGH);
    }
    else {
      digitalWrite(ledPinRelay1, LOW);
    }
    //delay(5000);
    //float t = dht.readTemperature();
    //float h = dht.readHumidity();
    //Serial.println(t);
    //Serial.println(h);
    int t=0;
    if(t > 19) {
      digitalWrite(ledPinRelay2, LOW);
    }
    else {
      digitalWrite(ledPinRelay2, HIGH);
    }
    Serial.flush();    
    
}
