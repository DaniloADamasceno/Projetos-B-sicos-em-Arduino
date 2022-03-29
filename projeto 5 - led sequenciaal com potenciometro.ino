//projeto de iluminação com leds com potenciometro  


byte ledPin[] = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};    // criar um array para os pinos dos LEDs
int LedDelay;
int direction = 1;
int currentLED = 0;
unsigned long changeTime;
int potPin = 2;      // para selecionar o pino de entrado para o potenciometro 


void setup() {
  for (int x=0; x<10; x++){
    pinMode(ledPin[x], OUTPUT); 
    changeTime = millis();
  }
}

void loop() {
  LedDelay = analogRead (potPin);                //lê o valor do potenciometro
  if ((millis() - changeTime) > LedDelay) {    // verificar se ja ocorreu o LedDelay em milissim dede a ultima alteração
  changeLED();
  changeTime = millis();
    }
  }
  void changeLED (){                          // função para aoagar todos os leds
for (int x=0; x<0; x++){
digitalWrite(ledPin, LOW);
}
digitalWrite(ledPin[currentLED], HIGH);     // acend o led atua 
currentLED += direction;                   // incrementa de acordo com o valor de " direction"
if (currentLED == 9){direction = -1;}
if (currentLED == 0){direction = 1;}
}
