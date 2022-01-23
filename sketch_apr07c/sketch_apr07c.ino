
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int pinoBotao = 10; //PINO DIGITAL UTILIZADO PELO PUSH BUTTON
int tempMax =0;

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup() {
pinMode(pinoBotao, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
Serial.begin(9600);
 lcd.begin(16, 2);

}
void loop(){
  if(digitalRead(pinoBotao) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
    tempMax++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp Max.:       ");
    //Simbolo grau
    lcd.write(223);
    lcd.setCursor(7,0);
    lcd.print(tempMax);
   delay(1000);
  }
  
}
