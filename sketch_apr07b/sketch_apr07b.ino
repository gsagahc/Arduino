
//Define bibliotecas usadas
#include <Pitches.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
//Declaração das constantes

const int botao = 10; //constante botão refere-se ao pino digital 2.
 
//Variável que conterá os estados do botão (0 LOW, 1 HIGH).
int estadoBotao = 0;
int tempMax= 0;
 
//Método setup, executado uma vez ao ligar o Arduino.
void setup() {
 
  pinMode(botao,INPUT); //Definindo pino digital 2 como de entrada. 
  Serial.begin(9600);
}
 
//Método loop, executado enquanto o Arduino estiver ligado.
void loop() {  
  //Lendo o estado do pino 2, constante botao, e atribuindo 
  //o resultado a variável estadoBotao.
  estadoBotao = digitalRead(botao);          
   
  //Verificando o estado do botão para definir se acenderá ou
  //apagará o led.  
  if (estadoBotao == LOW) {
    tempMax++;
    Serial.print("Temp Max: ");
    Serial.print(tempMax);
  } else {
   // digitalWrite(led,LOW);  //Botão não pressionado, apaga o led.    
  }       
}
