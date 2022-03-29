// Bengala Ultrasonica 


#include <I2Cdev.h>
#include <MediaMovel.h> //Biblioteca para uso de mdia mvel
#include <Ultrassonico.h>
#include <MPU6050.h>
#include "Wire.h" //Biblioteca para comunicao I2C
#include <math.h> //Inclui biblioteca para uso da funo atan()
#include <Wtv020sd16p.h> //Inclui biblioteca MP3

#define   RAD(grau)                   ((grau*3.1415926)/180) //Converte de radianos para graus
#define   GRAU(rad)                   ((rad*180)/3.1415926) //Converte de graus para radiano
//Converte algum valor de tenso entre 0 e 5V, para a faixa entre 0 e 255
#define   TENSAO(tensao)              ((255*tensao)/5.0) 
#define   pino_buzzer                 2
#define   pino_vibracall              3
#define   DISTANCIA_MINIMA            40 //Define distncia mnima de deteco
#define   ANGULO_LIMITE_SUPERIOR      30 //Valor em graus

//Carto
int resetPin = 10;  //Pino Reset
int clockPin = 9;  //Pino clock
int dataPin = 11;   //Pino data (DI)
int busyPin = 12;   //Pino busy

//Boto
int bottonPin = 4; // Pino Liga/Desliga
int estadoboton;
int ativado=HIGH;

Ultrassonico ultra(8, 7); //Echo e trigger
MM mms_1(20), mms_2(30); //Instncia dois objetos do tipo MM, com 15 e 50 amostras, respectivamente
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin); //Instncia quatro ojetos a classe da biblioteca MP3

MPU6050 accelgyro; //Instancia objeto accelgyro, do tipo MPU6050

//Variveis auxiliares
int16_t ax, ay, az, gx, gy, gz;
float anguloEixoX, ALTURA_PESSOA=170.0, DISTANCIA_DETECCAO=200.0;
uint16_t distanciaHorizontal, leituraUltra;
bool flag; //Indicador de inclinao
char buf;//Variavel que armazena os caracteres recebidos do MP3

float ANGULO_DETECCAO(float valor){ //Funo para clculo do ngulo de deteco
  return (GRAU(atan(valor)));
}

void setup(){
    Wire.begin(); //Inicializa comunicao I2C
    Serial.begin(9600); //Inicializa serial
    accelgyro.initialize(); //Inicializa objeto accelgyro
    pinMode(pino_buzzer, OUTPUT);
    pinMode(pino_vibracall, OUTPUT);
    pinMode(bottonPin, INPUT_PULLUP);
    //Inicializa o modulo WTV020
    wtv020sd16p.reset();
    //Informacoes iniciais 
    menu_inicial();
    //Testa conexo, em caso de sucesso, dar um simples bip
    if(accelgyro.testConnection()){
      tone(pino_buzzer, 2500);
      delay(500);
      noTone(pino_buzzer);
    }
    //Em caso de falha na conexo, dar dois bips
    else{
      tone(pino_buzzer, 3500);   
      delay(150);  
      noTone(pino_buzzer);
      delay(500);
      tone(pino_buzzer, 3500);
      delay(150);  
      noTone(pino_buzzer);
    }
}

void loop(){
  estadoboton=digitalRead(bottonPin);
  if (estadoboton==LOW){
    ativado=!ativado;
    delay(20);
  }
  if (ativado==LOW){
aqui:    
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //Obtm valores do acelermetro e giroscpio 
        
    if(ax<-16400) ax=-16400; //Limita valores de "ax"
    if(ax>=0){ //Se dispositivo inclinado para cima ou reto
      flag=0; //Indicador de inclinao para cima ou reta
      //Converte valores de "ax" na faixa de 0  16400, para valores entre 0 e 90
      anguloEixoX=float((90*(mms_1.calculaMMS(ax)))/16400);
      if(anguloEixoX>ANGULO_LIMITE_SUPERIOR){ //Verifica limite de ngulo para cima
        noTone(pino_buzzer); //Desliga tone 
        analogWrite(pino_vibracall, 0); //Desliga vibracall 
        goto aqui; //Salta para a label "aqui"
      }
    }
    else{ //Se dispositivo inclinado para baixo
      flag=1; //Indicador de inclinao para baixo
      //Converte valores de "ax" na faixa de 0  -16400, para valores entre 0 e 90
      anguloEixoX=float((90*(mms_1.calculaMMS(ax)))/(-16400));
    }

    //Verifica se a pessoa est com inclinao para o cho    
    if((anguloEixoX>ANGULO_DETECCAO(ALTURA_PESSOA/DISTANCIA_DETECCAO)) && (flag==1)){
      tone(pino_buzzer, 2500); //Detecta cho - Liga tone  
      analogWrite(pino_vibracall, 0); //Desliga vibracall
    }
    else{
      noTone(pino_buzzer); //Desliga tone  
         
      leituraUltra=mms_2.calculaMMS(ultra.centimetrosUltra()); //Ler ultrassnico
      distanciaHorizontal=leituraUltra*(cos(RAD(anguloEixoX))); //Calcula distncia horizontal 

      //CHAMADA MP3
      if ((distanciaHorizontal>2000) && (distanciaHorizontal<3000)) {
        wtv020sd16p.playVoice(0);
      //Reproduz o arquivo 1
      wtv020sd16p.asyncPlayVoice(1); //Voc esta a mais de 2 metros de um obstculo!
      delay(3000); 
      wtv020sd16p.stopVoice();
      delay(2000);
      menu_inicial();
      }
      if ((distanciaHorizontal>1000)&& (distanciaHorizontal<2000)){
        wtv020sd16p.playVoice(0);
      //Reproduz o arquivo 2
      wtv020sd16p.asyncPlayVoice(2); //Ateno obstaculo a menos de 2 metros!
      delay(3000); 
      wtv020sd16p.stopVoice();
      delay(2000);
      menu_inicial();
      }
      
      if ((distanciaHorizontal>200)&& (distanciaHorizontal<1000)){
        wtv020sd16p.playVoice(0);
      //Reproduz o arquivo 2
      wtv020sd16p.asyncPlayVoice(3); //Cuidado obstaculo a menos de 1 metro!
      delay(3000); 
      wtv020sd16p.stopVoice();
      delay(2000);
      menu_inicial();
      }
      
         
      //Limita valores de distanciaHorizontal
      if(distanciaHorizontal<DISTANCIA_MINIMA) distanciaHorizontal=DISTANCIA_MINIMA;
      if(distanciaHorizontal>DISTANCIA_DETECCAO){
        analogWrite(pino_vibracall, 0); //Desliga vibracall      
      }
      //Varia a tenso no vibracall de 2.0V  4.0V, conforme a distncia detectada, de 
      //DISTANCIA_MINIMA  DISTANCIA_DETECCAO                                                             
      else analogWrite(pino_vibracall, map(distanciaHorizontal, DISTANCIA_DETECCAO, DISTANCIA_MINIMA, TENSAO(1.5), TENSAO(4.0))); 
    }  
    Serial.print(anguloEixoX);
    Serial.print(',');
    Serial.print(ANGULO_DETECCAO(ALTURA_PESSOA/DISTANCIA_DETECCAO));
    Serial.print(',');
    Serial.println(distanciaHorizontal);
    //delay(1);
  }
}
//Mostra menu de opcoes
void menu_inicial()
{
  Serial.println("\nDigite : ");
  Serial.println("1 - Reproduz o arquivo 0001.ad4");
  Serial.println("2 - Reproduz o arquivo 0002.ad4");
  Serial.println("3 - Reproduz o arquivo 0003.ad4");
  Serial.println();
}
