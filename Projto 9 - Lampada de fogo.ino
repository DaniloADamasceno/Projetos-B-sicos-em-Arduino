// Projeto 9 - Lampada de Fogo com Leds


int LedPin1 = 9;
int LedPin2 = 10;
int LedPin3 = 11;

void setup() {
  pinMode (LedPin1, OUTPUT);
  pinMode (LedPin2, OUTPUT);
  pinMode (LedPin3, OUTPUT);

}

void loop() {
  analogWrite(LedPin1, random(120)+136);
  analogWrite(LedPin2, random(120)+136);
  analogWrite(LedPin3, random(120)+136);
  delay (random(100));
 
}
