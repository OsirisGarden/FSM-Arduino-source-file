
#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7,8,9,10,11,12);


//CONSTANTES Y VARIABLES MULTITASKING
float dhtContPrevio = 0;
float lcdContPrevio = 0;
float dhtContActual = 0;
float lcdContActual = 0;
float printContPrevio = 0;
float printContActual = 0;
const float dhtMax = 2000;
const float lcdMax= 750;
const float printMax = 1000;

//CONSTANTES PINES
const int releLuz =  5;// Número del pin
const int releCalor = 3;
const int releAgua = 4;//Acciona rele de la bomba
const int releVentilador = 2; // Acciona el relé de los ventiladores

//CONSTANTES HUMEDAD
int humedadMax = 44; //Mientras más humedad menor es la señal analógica

//CONSTANTES LUZ
int luzMin = 20;

//CONSTANTES TEMPERATURA
int minCalor = 20;
int maxCalor = 21;

// VALORES REGISTRADOS
float temp = 0;
float hum_tierra = 0;
float luz_int = 0;
float hum_per = 0;
float luz_per = 0;
void setup() {
  pinMode(releLuz, OUTPUT);
  pinMode(releCalor, OUTPUT);
  pinMode(releAgua, OUTPUT);
  pinMode(releVentilador, OUTPUT);
  analogWrite(6, 20);
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("L:");
  lcd.setCursor(8, 0);
  lcd.print("T: ");
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.setCursor(8, 1);
  lcd.print("R: ");
}

void loop() {
  // Contador para el sensor cada x tiempo
  dhtContActual = millis();
  // Leemos y pintamos en LCD la temp
  lcd.setCursor(3,0);
  luz_int = analogRead(A1) + analogRead(A2);
  luz_per = luz_int*100/2048;
  lcd.print(luz_per, 1);
  // Comprobamos el tiempo del sensor de temp, y además pintamos
  if(dhtContActual - dhtContPrevio > dhtMax) {
      temp = dht.readTemperature();
      dhtContPrevio = dhtContActual;
  }
  lcd.setCursor(11, 0);
  lcd.print(temp, 1);
  hum_tierra = analogRead(A4);
  lcd.setCursor(3, 1);
  // Leemos hhumedad y pintamos en LCD
  hum_per = 100 - hum_tierra*100/1024;
  lcd.print(hum_per, 1);
  lcd.setCursor(11, 1);
  // Comprobamos si hay riego y pintamos
  if(hum_per < humedadMax) {
    lcd.print("SI");
  }
  else {
    lcd.print("NO");
  }
  // Comprobamos si la luz está por debajo de mínimos, si es así la encendemos
  if(luz_per < luzMin) {
    digitalWrite(releLuz, LOW);
  }
  else {
    digitalWrite(releLuz, HIGH);
  }
  //TEMPERATURA
  if(temp < minCalor) {
    digitalWrite(releVentilador, HIGH);
    digitalWrite(releCalor, LOW);
  }
  else {
    digitalWrite(releCalor, HIGH);
  }
  if(temp > maxCalor) {
    digitalWrite(releVentilador, LOW);
    digitalWrite(releCalor, HIGH);
  }
  else {
    digitalWrite(releVentilador, HIGH);
  }
  //HUMEDAD
  if(hum_per < humedadMax) {
    digitalWrite(releAgua, LOW);
  }else{
    digitalWrite(releAgua, HIGH);
    
  }
  // LECTURA/ESCRITURA SERIAL
  String cmd = "";
    if(Serial.available()) {
      delay(10);
      while(Serial.available() > 0){
        cmd += (char)Serial.read();
      }
      Serial.flush();
    }
    if(cmd != "") {
      command(cmd);
    }

  
}

void command(String cmd){
  switch(cmd.charAt(0)) {
    case 'T': 
      Serial.println(temp);
      break;
    case 'L':
      Serial.println(luz_per);
      break;
    case 'H':
      Serial.println(hum_per);
      break;
    case 'S':
      switch(cmd.charAt(1)) {
        case 'T':
          maxCalor = cmd.substring(2).toInt();
          break;
        case 't':
          minCalor = cmd.substring(2).toInt();
          break;
        case 'l':
          luzMin = cmd.substring(2).toInt();
          break;
        case 'H':
          humedadMax = cmd.substring(2).toInt();
          break;
      }
  }
}
