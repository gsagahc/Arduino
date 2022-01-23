// Programa de teste do modulo rele
// Autor : Arduino e Cia

//define a porta a ser utilizada para o acionamento do rele
int sinalparaorele = 8; 

void setup()
{
  //Define o pino como saida
  pinMode(sinalparaorele, OUTPUT); 
}

void loop()
{
  //Aciona o rele
  digitalWrite(sinalparaorele, HIGH); 
  delay(5000); //Aguarda 5 segundos
  //Desliga o rele
  digitalWrite(sinalparaorele, LOW); 
  delay(5000); //Aguarda 5 segundos e reinicia o processo
}
