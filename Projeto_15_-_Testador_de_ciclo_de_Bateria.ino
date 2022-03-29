/*
Um testador de ciclo de vida da bateria usando um LCD como saída  
*/

// inclui o código da biblioteca:
#include  <LiquidCrystal.h>

// inicializa a biblioteca com os números dos pinos da interface
LiquidCrystal  lcd ( 12 ,  11 ,  5 ,  4 ,  3 ,  2 );
const  int  botãoPino  =  9 ; 
int  sensorPin  =  A0 ;     // seleciona o pino de entrada para a bateria
int  sensorValue  =  0 ;   // variável para armazenar o valor vindo do sensor
const  int  relé =  10 ;
int  estado do botão  =  0 ;
float  mah  =  0,0 ;
início de tempo  longo   ;

void  configuração ()  {
  // configura o número de colunas e linhas do LCD:
  lcd . início ( 16 ,  2 );
  // Imprime uma mensagem no LCD.
  lcd . print ( "Batt life tester" );
  pinMode ( relé ,  SAÍDA );
pinMode ( buttonPin ,  INPUT );
}

void  loop ()  {
  // coloca o cursor na coluna 0, linha 1
  // (nota: a linha 1 é a segunda linha, pois a contagem começa com 0):
  digitalWrite ( relé ,  0  );  //desliga o relé de LED
 
  while  ( estado do botão  ==  LOW  )  {
  sensorValue  =  analogRead ( sensorPin );  // lê a bateria
  
  buttonState  =  digitalRead ( buttonPin );

  lcd . setCursor ( 0 ,  1 );
  lcd . print (( sensorValue * 4.98 ) / 1023 );
  lcd . print ( "Volts" );
  atraso ( 500 );
  }  //fim do loop pronto
  digitalWrite(relay, 1 ); //set the LED-relay on
  lcd.setCursor(0, 0);
  lcd.print("Testing              ");
  lcd.setCursor(0, 1);
  lcd.print("                         ");
  mah = 0.0;
  timestart = millis( );
  while ( ((sensorValue*4.98)/1023) > 3.00 ) {
     lcd.setCursor(0, 1);    
     lcd.print((sensorValue*4.98)/1023);
     lcd.print(" V ");
     sensorValue = analogRead(sensorPin); // read the battery
     mah = mah + (((sensorValue*4.98)/1023)/4 )/7.2;
     lcd.print(mah);
     lcd.print(" mAh ");
     delay ( 500 ) ;
     lcd.setCursor(8,0);
     lcd.print((millis( )- timestart)/1000); // time since test staarted
  }  // fim do consumo de bateria
    digitalWrite ( relé ,  0  );  //desliga o relé de LED

  // resultados finais
 
   lcd . setCursor ( 0 ,  0 );
   lcd . imprimir ( mah );
   lcd . print ( "mAH" );
   lcd . print (( milis (  ) -  timestart ) / 1000 );
   lcd . imprima ( "S" );
   buttonState  =  digitalRead ( buttonPin );
  
}

}
