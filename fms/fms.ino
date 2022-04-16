#include <DHT.h>
#define DHTPIN 2

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
CONSTANTES PINES
const int releLuz =  13;// Número del pin
const int releCalor = 12;
const int releAgua = 8;//Acciona rele de la bomba

//CONSTANTES HUMEDAD
const int humedadMax = 180; //Mientras más humedad menor es la señal analógica
const int humedadMin = 750;

//CONSTANTES LUZ
const int luzMin = 500;

//CONSTANTES TEMPERATURA
const int minCalor = 19;

void setup() {
  Serial.begin(9600);
}

void loop() {
    //////////////LECTURA VALORES RASPI/////////////
    //Aqui se lee y procesa la informacion pasada por el puerto serial desde raspi a arduino
    //Probablemente haya que cambiar las const a variables
    
    //////////////GESTION HUMEDAD TIERRA///////////////
    float hum_tierra = analogRead(A1);
    if (hum_tierra > humedadMin){
      //Encendemos el rele que acciona la bomba
      digitalWrite(releAgua, HIGH);
    }
    else{
      //Apagamos el rele, hay humedad suficiente
      digitalWrite(releAgua, LOW);
    }
    
    //////////////GESTION LUZ///////////////////////
    float luz_int = analogRead(A0);
    if(luz_int < luzMin) {
      digitalWrite(releLuz, HIGH);
    }
    else {
      digitalWrite(releLuz, LOW);
    }
    //////////////GESTION TEMPERATURA Y HUMEDAD AIRE///////////////
    // HAY QUE HACER THREADING YA QUE ESTE SENSOR PILLA CADA 5 SECS
    float temp = dht.readTemperature();
    float hum_aire = dht.readHumidity();
    if(t > minCalor) {
      digitalWrite(releCalor, LOW);
    }
    else {
      digitalWrite(releCalor, HIGH);
    }
    //////////////LECTURA VALORES PARA RASPI//////
    //HACER EN THREADING
    String cmd = "";
    if(Serial.available()) {
      delay(10);
      while(Serial.available() > 0){
        cmd += (char)Serial.read();
      }
      Serial.flush();
    }
    if(cmd != "") {
      Serial.print("Comando recibido, procesaremos solicitud");
    }
    delay(500);
    
}
