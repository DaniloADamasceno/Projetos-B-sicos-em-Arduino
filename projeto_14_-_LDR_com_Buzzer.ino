// Sensor de Luz - Projeto 14


int piezoPin = 8;     // Definir o Buzzer para a porta 8
int LDR = 0;          // Definir o LDR no pino Analogico 0
int LDRValue = 0;     // Valor Lido pelo LDR
    
void setup() {
  // Nada A fazer nessa Aplicação
}

void loop() {
  LDRValue = analogRead(LDR);     // Le o valor do LDR
  tone(piezoPin, 1000);              // Toca um tom de 1000HZ no piezzo
  delay( 250);                       // delay 
  noTone (piezoPin);                 // Interrompe o tom 
  delay(LDRValue);                   // Espera a qautidade de milissegundos em LDRValue
  

}
