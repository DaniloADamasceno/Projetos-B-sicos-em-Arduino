// Alarme com sonorizador Piezo


float sinVal;
int toneVal;

void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  for (int x=0; x<180; x++) {
    sinVal = (sin(x*(3,1416/180)));      // Converter Graus e radianos e obter o valor do Seno
    toneVal = 2000+(int(sinVal*1000));    // Gerar uma frequencia a partir do valo do Seno
    tone(8, toneVal);
    delay(2);
  }

  

}
