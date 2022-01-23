/* -------------Termometro cervejeiro -----------------
  Mostra as temperaturas MAX e MIN no display e no serial   
                 GUILHERME CHAGAS
                 18/11/2018
 ------------------------------------------------------*/
//Define bibliotecas usadas

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float seno;
int frequencia, x;

const int BotaoUp = 10; //Botão que aumenta
const int BotaoDown = 11;// Botão que diminui


 
// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 5
 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);
 
// Armazena temperaturas minima e maxima
float tempMin = 6;
float tempMax = 9;
float tempC =0;

//Portas relacionadas ao Rele

//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 8;


  
 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
 
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
 
void setup()
{
 
  pinMode(BotaoUp, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  pinMode(BotaoDown, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //define o pino D2 como saída para o Buzzer
  pinMode(2,OUTPUT);
  //Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT); 
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
     
     int vdelay=1000;
    // Le a informacao do sensor
    sensors.requestTemperatures();
    tempC = sensors.getTempC(sensor1);
    // Atualiza temperaturas minima e maxima
  /*  if (tempC < tempMin)
    {
      tempMin = tempC;
    }
    if (tempC > tempMax)
    {
      tempMax = tempC;
    }*/
  
  
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
    lcd.setCursor(7,0);
    lcd.print(tempC);
    lcd.setCursor(12,0);
    lcd.print("C");
    lcd.setCursor(1,1);
    lcd.print("L: ");
    lcd.setCursor(3,1);
    lcd.print(tempMin,1);
    lcd.setCursor(8,1);
    lcd.print("H: ");
    lcd.setCursor(11,1);
    lcd.print(tempMax,1);
    //se temperatura <=14 desliga relé
    if (tempC <= tempMin)
    {
       digitalWrite(porta_rele1, HIGH);  //Desliga rele 1
    }
    //se temperatura >=tempMax liga relé
    if (tempC >= tempMax)
    {
       digitalWrite(porta_rele1, LOW);  //Liga rele 1
   
    }
  if(digitalRead(BotaoUp) == LOW){ //Se pressionado o botão branco
    tempMax++;
    tempMin++;
    delay(10);
  
  }
  if(digitalRead(BotaoDown) == LOW){ //Se pressionado o botão branco
    tempMax--;
    tempMin--;
    delay(10);
  }
   delay(vdelay);    
 }
