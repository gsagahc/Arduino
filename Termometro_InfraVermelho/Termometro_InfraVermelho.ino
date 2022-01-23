//Programa: Sensor de temperatura I2C MLX90614 e HC-SR04 Arduino
//Autor: Guilherme Chagas
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger 5
#define pino_echo 4
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//Define o endereco I2C do display e qtde de colunas e linhas

LiquidCrystal_I2C lcd(0x27,20,4);  // Configura do endereço do LCD 0x27 para  16 caracteres e  display de duas linhas
//Array que desenha o simbolo de grau
byte grau[8] = {B00110, B01001, B01001, B00110,
                B00000, B00000, B00000, B00000,};
double temp_amb;
double temp_obj;
void setup()
{
  Serial.begin(9600);
  Serial.println("Sensor de temperatura MLX90614");
  //Inicializa o display LCD I2C
  lcd.init();                      // inicializa o LCD
  lcd.init();

  lcd.backlight();
  //Atribui a "1" o valor do array "grau", que desenha o simbolo de grau
  lcd.createChar(1, grau);
  //Inicializa o MLX90614
  mlx.begin();
}
void loop()
{
 //Le as informacoes do sensor, em cm e pol
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
 
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  
  //Leitura da temperatura ambiente e do objeto
  //(para leitura dos valores em Fahrenheit, utilize
  //mlx.readAmbientTempF() e mlx.readObjectTempF() )
  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();
  //Mostra as informacoes no display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
  lcd.setCursor(11, 0);
  lcd.print(cmMsec);
  lcd.setCursor(0 , 1);
  lcd.print("Centimetros");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperaturas");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ambiente:");
  lcd.setCursor(10, 0);
  lcd.print(temp_amb);
  lcd.setCursor(15, 0);
  lcd.write(1);
  lcd.setCursor(0, 1);
  lcd.print("Objeto:");
  lcd.setCursor(10, 1);
  lcd.print(temp_obj);
  lcd.setCursor(15, 1);
  lcd.write(1);
  //Mostra as informacoes no Serial Monitor
  Serial.print("Ambiente = ");
  Serial.print(temp_amb);
  Serial.print("*CtObjeto = ");
  Serial.print(temp_obj); Serial.println("*C");
  //Aguarda 1 segundo ate nova leitura
  delay(1500);
}
