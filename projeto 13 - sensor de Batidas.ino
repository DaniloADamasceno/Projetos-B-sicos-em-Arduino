// Projeto 13
// Sensor de Batida Piezzo ( Buzzer )


int ledPin = 9;                            // led no pino 9
int piezoPin = 5;                          // Buzzer no pino analigico 5
int thresholthreshold  = 120;              // o valor do sensor a ser atingido antes da ativação
int sensorValue = 0;                       // uma Variavel para armazenar o valor lido do sensor 
float ledValue = 0;                        // o Brilho do Led


void setup() {
  pinMode(ledPin,OUTPUT);        // Define o Led como Saida

  // Piscar o LED duas vezes , para demonstrar que o programa iniciou.
  digitalWrite(ledPin, HIGH); delay(150); digitalWrite(ledPin, LOW); delay(150);
  digitalWrite(ledPin, HIGH); delay(150); digitalWrite(ledPin, LOW); delay(150);

}

void loop() {
  sensorValue = analogRead (piezoPin);             // Escreve o valor do Brilho do LeD
  if (sensorValue >= thresholthreshold) {         // Se uma batida for detectada , defina o brilho maximo do Led
    ledValue = 255;
  }
  analogWrite(ledPin, int(ledValue) );      // Escreva o valor do brilh do led
  ledValue = ledValue - 0,05;              // Apaga o led Lentamete (ledvalue <= 0) e Certificara que o valor não descera ate 0 (Zero).
 

}
