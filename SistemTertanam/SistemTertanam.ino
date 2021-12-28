//Penyiram tanaman otomatis
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <DHT.h>
DHT dht(2, DHT11); //Pin, Jenis DHT

const int sensorSoil = A0; //inisialisasi pin sensor
const int pompa = 6;       //inisialisasi pin pompa 

void setup() {
lcd.init();
lcd.backlight();
dht.begin();
Serial.begin (9600);          //memanggil serial monitor
pinMode(sensorSoil, INPUT);   //menetapkan pin A0 sebagai input
pinMode(pompa, OUTPUT);       //menetapkan pin 6 sebagai output
}

void loop() {
int dataAnalog = analogRead (sensorSoil);  //membaca nilai dari pin sensor
float kelembaban = dht.readHumidity();
float suhu = dht.readTemperature();
//print hasil ke serial monitorlcd.clear();
lcd.setCursor(0,0);
lcd.print("Suhu Udr: ");
lcd.print(suhu);
lcd.print("C    ");
lcd.setCursor(0,1);
lcd.print("Klmb Tnh: ");
lcd.print(dataAnalog);
lcd.print("%    ");
delay (3000);
lcd.clear();

//jika nilai A0 kurang dari 500, print kata serta nyalakan led hijau dan matikan led kuning, merah dan juga relay
if (dataAnalog < 500) {
  lcd.setCursor(0,0);
  lcd.print("Media Basah     ");
  lcd.setCursor(0,1);
  lcd.print("Pompa OFF       ");
  digitalWrite (pompa, HIGH);
  
  }

 //tetapi, jika nilai A0 kurang dari 900, print kata serta nyalakan led kuning dan relay kemudian matikan led hijau dan juga merah
 else if (dataAnalog  < 800) {
  lcd.setCursor(0,0);
  lcd.print("Kelembaban Cukup");
  lcd.setCursor(0,1);
  lcd.print("Pompa ON 8 Detik");
  digitalWrite (pompa, LOW);
  delay(8000);
  lcd.setCursor(0,1);
  lcd.print("Pompa OFF       ");
  digitalWrite (pompa, HIGH);
  }

 //selain dari itu, hanya nyalakan led merah dan juga relay
 else { 
  lcd.setCursor(0,0);
  lcd.print("Media Kurang Air");
  lcd.setCursor(0,1);
  lcd.print("Pompa ON 15 Detik");
  digitalWrite (pompa, LOW);
  delay(15000);
  lcd.setCursor(0,1);
  lcd.print("Pompa OFF       ");
  digitalWrite (pompa, HIGH);
  }

 delay (120000);
}
