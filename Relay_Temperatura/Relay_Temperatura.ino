/* -------------Termometro cervejeiro -----------------
  Mostra as temperaturas MAX e MIN no display e no serial   
                 GUILHERME CHAGAS
                 18/11/2018
 ------------------------------------------------------*/
//Define bibliotecas usadas
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>



// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 5
 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);
float tempC = 0; 

//Portas relacionadas ao Rele
//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 8;
 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
 
 
void setup()
{
 
  
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
      
  
    // Mostra dados no serial monitor
    Serial.print("Temp C: ");
    Serial.print(tempC);
    Serial.println();
    
    //se temperatura < 24 desliga relé
    if (tempC < 24.0)
    {
      digitalWrite(porta_rele1, HIGH);  //Desliga rele 1
    }
    //se temperatura >=24 liga relé
    if (tempC >= 24.0)
    {
      digitalWrite(porta_rele1, LOW);  //Liga rele 1
    }
  
   delay(vdelay);  

}
