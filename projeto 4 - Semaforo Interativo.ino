// Delcarando as variaveis do Semaforo 
int LedCarroVerde = 12;
int LedCarroAmarelo = 10;
int LedCarroVermelho = 8;
int LedPedestreVerde = 2;
int LedPedestreVermelho = 4;
int Botao = 6;
int crossTime = 5000;       // Tempo para que os pedestres atravessem
unsigned long changeTime;   // Tempo desde que o botão foi pressionado 



void setup() {
 pinMode(LedCarroVerde, OUTPUT);
 pinMode(LedCarroAmarelo, OUTPUT);
 pinMode(LedCarroVermelho, OUTPUT);
 pinMode(LedPedestreVerde, OUTPUT);
 pinMode(LedPedestreVermelho, OUTPUT);
 pinMode(Botao, INPUT);
 digitalWrite(LedCarroVerde, HIGH);
 digitalWrite(LedPedestreVermelho, HIGH);

}

void loop() {
  int state = digitalRead(Botao);      // Verifica se o botão do pedestre foi assionado nos ultimos 5 segundos 
  // se o botão tiver sido apertado realizar a tarefa a baixo 
  if(state == HIGH && (millis() - changeTime) > 5000) {
    // Chamar a função para alterar as luzes 
    changeLights();
  }
}
void changeLights(){
  // Apagar o o Vermelho dos carros e acender o amarelo
  digitalWrite(LedCarroVerde, LOW);
  digitalWrite(LedCarroAmarelo, HIGH);
  delay(2500);
  // Apagar o amarelo para os carros e acender o vermelho para os carros 
  digitalWrite(LedCarroAmarelo, LOW);
  digitalWrite(LedCarroVermelho, HIGH);
  delay(1500);

  //acender o semaforo de pedestres
  digitalWrite(LedPedestreVermelho, LOW);
  digitalWrite(LedPedestreVerde, HIGH);
  delay(crossTime);       // Esperar um intervalo de tempo pre definido de 5 segundos 


  // piscar o led verde de pedestres 
  for (int x=0; x<10; x++) {
    digitalWrite(LedPedestreVerde,HIGH);
    delay(250);
    digitalWrite(LedPedestreVermelho, LOW);
    delay(250);
  }

  // Acender o led vermelho dos pedestres
  digitalWrite(LedPedestreVermelho, HIGH);
  delay(500);

  digitalWrite(LedCarroAmarelo, HIGH);
  digitalWrite(LedCarroVermelho, LOW);
  delay(1000);
  digitalWrite(LedCarroAmarelo, LOW);
  
  // Registrar  o tempo da ultima alteração do semaforo
  changeTime = millis();
  //depois retornar para o loop principal do programa




}
