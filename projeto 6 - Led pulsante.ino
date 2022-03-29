// projeto de led Pulsante ..


 int ledPin = 11;
 float sinVal;
 int ledVal;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for (int x=0; x<180; x++) {         
    // converter graus em radianos e so depois obter o valo do seno
    sinVal = (sin(x*(3,1416/180)));
    ledVal = (sinVal*255);
    analogWrite(ledPin, ledVal);
    delay(250);
  }
}
