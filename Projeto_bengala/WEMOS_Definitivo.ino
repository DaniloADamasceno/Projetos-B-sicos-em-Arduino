//                                           PROJETO BENGALA MULTISSENSORIAL
//                                    ESP32 + HC-SR04 + MOTOR DE VIBRAÇÃO + BUZZER
//                                      Desenvolvedor: Danilo Almeida Damasceno
//-----------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------- INCLUDES DO SISTEMA -------------------------------------------------
#include <VibrationMotor.h>                   // Biblioteca do Motor de Vibração


//  -----------------------------------------     CONSTANTES E VARIÁVEIS DO SISTEMA   -----------------------------------------
const int trigPin = D7;                       // ESP32 WEMOS GPIO D7 conectado ao TRIG (Trigger) do sensor ultrassônico (saída)
const int echoPin = D6;                       // ESP32 WEMOS GPIO D6 conectado ao ECHO (Echo) do Sensor Ultrassônico (Entrada)
const int buzzerPin = D5;                     // ESP32 WEMOS GPIO D5 conectado ao BUZZER
const int motorPin = D2;                      // ESP32 WEMOS GPIO D2 Conectado ao Motor de Vibração 1027
const int motorPinSegundo = D3;               // ESP32 WEMOS GPIO D3 Conectado ao Motor de Vibração 1027 (Segundo Motor)

long duracao;                                 // Variável que armazena a duração do pulso enviado pelo sensor ultrassônico
int distancia;                                // Variável que armazena a distância recebida através do sensor ultrassônico
int distanciaSalva = distancia;               // Variável que salva a distância 
int maximaDistancia = 90;                     // Distância Maxima em centimetros (cm)
int minimaDistancia = 30;                     // Distância Maxima em centimetros (cm)

//  ------------------------------------------      INSTÂNCIAS DO MOTOR DE VIBRAÇÂO 1027  -------------------------------------
VibrationMotor myVibrationMotor(motorPin);                    // Motor de Vibração 1027
VibrationMotor myVibrationMotorSegundo(motorPinSegundo);      // Segundo Motor de Vibração 1027


//  ------------------------------------------      SETUP DO SISTEMA  ---------------------------------------------------------
void setup() {
iniciarPinosDoSistema();                      // Método de inicialização dos pinos do sistema
iniciarSistemaSonoro();                       // Método de inicialização do Buzzer em caso de sucesso
Serial.begin(9600);                           // Inicializa a Porta Serial

Serial.print("...Sistema Incializado com sucesso...");
Serial.println("");                           // Quebra de Linha
Serial.println("");                           // Quebra de Linha
mensagemInicialDoSistema();
}

//  ------------------------------------------------     LOOP DO SISTEMA   ----------------------------------------------------
void loop() {
  digitalWrite(trigPin, LOW);                 // Desligar o Trigger  
  delayMicroseconds(2);                       // Aguardar 2 microssegundos
  digitalWrite(trigPin, HIGH);                // Ligar o Trigger
  delayMicroseconds(10);                      // Aguardar 10 microssegundos 
  digitalWrite(trigPin, LOW);                 // Desligar o Trigger

    duracao = pulseIn(echoPin, HIGH);         // Mede a duração do pulso enviado pelo Trigger
    distancia = duracao*0.034/2;              // Calcula a distância usando a velocidade do som (aproximadamente 343 m/s) 

  Serial.print("Distancia (cm): "); // Imprime o valor da distância no monitor serial em centimetros **OBS.: valor sera retornado a nível de testes 
  Serial.println(distancia);


  if (distancia > maximaDistancia) {          // Se a distancia for maior que a distância máxima (Não Fazer Nada)
    digitalWrite(motorPin, LOW);              // Vibracall Desligado
    digitalWrite(buzzerPin, LOW);             // Buzzer Desligado

  } else if (distancia >= minimaDistancia && distancia <= maximaDistancia) { // Se a distância for Maior que a Distância minima(30cm) e menor que a Distancia Maxima (90cm)
    myVibrationMotor.pulse(2);                // Motor de Vibração Vibra 2 Vezes
    myVibrationMotorSegundo.pulse(2);         // Segundo motor de vibração vibra 2 vezes

  } else {
    myVibrationMotor.pulse(4);                // Motor de Vibração Vibra 4 Vezes
    myVibrationMotorSegundo.pilse(4)          // Segundo motor de vibração vibra 2 vezes
    tone(buzzerPin,2500);                     // Buzzer Toca uma vez
          delay(500);
          noTone(buzzerPin);
          delay(500);
  }
    delay(1500);                              // Delay de 1.5 segundos até a próxima varedura 
}

//  -----------------------------------------     MÉTODO DE MENSAGEM DE INIIALIZAÇÃO DO SISTEMA  ------------------------------
void mensagemInicialDoSistema(){
    Serial.println("          PROJETO BENGALA MULTISSENSORIAL");
    Serial.println("    ESP32 + HC-SR04 + MOTOR DE VIBRAÇÃO + BUZZER");
    Serial.println("      Desenvolvedor: Danilo Almeida Damasceno");
    Serial.println("");                               // Quebra de Linha
    Serial.println("");                               // Quebra de Linha
}


//  -----------------------------------------     MÉTODO DE INIIALIZAÇÃO DOS PINOS DO SISTEMA  -------------------------------
void iniciarPinosDoSistema(){
    pinMode(trigPin, OUTPUT);               // Pino TRIG Output do Sensor ultrassônico
    pinMode(echoPin, INPUT);                // Pino ECHO Input do Sensor ultrassônico
    pinMode(buzzerPin, OUTPUT);             // Pino Buzzer
    pinMode(motorPin, OUTPUT);              // Pino Motor de Vibração
    pinMode(motorPinSegundo, OUTPUT);       // Pino Segundo Motor de Vibração 
}

//  ------------------------------------      Função Inicial do Sistema     -------------------------------------------------
 void iniciarSistemaSonoro() {              // Em Caso de Sucesso, dar 2 bips Simples
          tone(buzzerPin,2500);
          delay(500);
          noTone(buzzerPin);
          delay(500);
          tone(buzzerPin,2500);
          delay(500);
          noTone(buzzerPin);
        }
