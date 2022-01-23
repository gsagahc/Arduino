/* -------------Termometro cervejeiro -----------------
  Mostra as temperaturas MAX e MIN no display e no serial   
                 GUILHERME CHAGAS
                 18/11/2018
 ------------------------------------------------------*/
//Define bibliotecas usadas
#include <Pitches.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float seno;
int frequencia, x;


// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

 
// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 3
 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);
 
// Armazena temperaturas minima e maxima
float tempMin = 999;
float tempMax = 0;
float tempC =0;




  
 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
 
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
 
void setup()
{
 
  
  //define o pino D11 como saída para o Buzzer
  pinMode(11,OUTPUT);

  Serial.begin(9600);
  
  sensors.begin();
  // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();
  lcd.begin(16, 2);

   
}
//Mostrar o endereço do sensor no serial monitor  
void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
 
void loop()
{
    int vdelay=0;
    vdelay=1000;
    // Le a informacao do sensor
    sensors.requestTemperatures();
    tempC = sensors.getTempC(sensor1);
    // Atualiza temperaturas minima e maxima
    if (tempC < tempMin)
    {
      tempMin = tempC;
    }
    if (tempC > tempMax)
    {
      tempMax = tempC;
    }
    // Mostra dados no serial monitor
    Serial.print("Temp C: ");
    Serial.print(tempC);
    Serial.print(" Min : ");
    Serial.print(tempMin);
    Serial.print(" Max : ");
    Serial.println(tempMax);
   
  // Mostra dados no LCD  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp.:       ");
    //Simbolo grau
    lcd.write(223);
    lcd.print("C");
    lcd.setCursor(7,0);
    lcd.print(tempC);
    lcd.setCursor(0,1);
    lcd.print("L: ");
    lcd.setCursor(3,1);
    lcd.print(tempMin,1);
    lcd.setCursor(8,1);
    lcd.print("H: ");
    lcd.setCursor(11,1);
    lcd.print(tempMax,1);
    //se temperatura <=14 desliga relé
    if (tempC <= 65)
    {
       som();
    }
    //se temperatura >=18 liga relé
    if (tempC >= 67)
    {
       som();      
    }
   
  delay(vdelay);
}

void som(){
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(11, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(11);
    
  }
}
