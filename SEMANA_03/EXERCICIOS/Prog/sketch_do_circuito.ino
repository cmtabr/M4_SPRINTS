// https://wokwi.com/projects/347157786473267794
#define LED1 1 
#define LED2 2
#define LED3 42
#define LED4 41

#define LDR 3

#define BZZ 38

#define BTN1 5
#define BTN2 6

// Variáveis utilizadas
int lux = 0; // Valor lido pelo sensor
int ativaBtn1 = 1; 
int ativaBtn2 = 1; 
int binLeds = 0; // Armazena conversão do sensor para uma escala de 0 a 15
int notas[30];
int adiciona = 0;

void acende(int value);
void countTo(int value);
void led();
void guardaValor();
void tocaAi();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Bem-vindo ao seu aparelho de som!");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(LDR, INPUT);

  pinMode(BZZ, OUTPUT);

  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);  
}


void loop() {

  led();

  guardaValor();

  tocaAi();

  delay(50);

}

void led(){
  int lux = analogRead(3);

  if (binLeds != map(lux, 32, 4063, 0, 15)) {
    // converter o valor lido pelo sensor em úm número de 0 a 15
    binLeds = map(lux, 32, 4063, 0, 15);
    Serial.println(binLeds);
    countTo(binLeds);
  }
}

void acende(int value){
  digitalWrite(LED1, value & 0b0001); // ligar o led 12
  digitalWrite(LED2, value & 0b0010); // ligar o led 13
  digitalWrite(LED3, value & 0b0100); // ligar o led 14
  digitalWrite(LED4, value & 0b1000); // ligar o led 27

}


void countTo (int value) {
  for(int i = 0; i <= value; i++) {
    // Serial.println(i, DEC); // imprimir o valor lido
    acende(i);
    notaMusical(i);
    delay(250);
    noTone(BZZ);
  }
}


void guardaValor() {
  int estadoAtual = digitalRead(BTN1);
  Serial.println(estadoAtual);
  if (estadoAtual != ativaBtn1) {
    if (estadoAtual == 0) {
      ativaBtn1 = 0;
      notas[adiciona] = binLeds;
      adiciona++;
    } else {
      ativaBtn1 = 1;
    }
  }
}

void notaMusical(int value){
  int notas = 0;

  switch(value) {
  case 0:
    notas = 50;
    break;
  case 1:
    notas = 100;
    break;
  case 2:
    notas = 150;
    break;
  case 3:
    notas = 200;
    break;
  case 4:
    notas = 250;
    break;
  case 5:
    notas = 300;
    break;
  case 6:
    notas = 350;
    break;
  case 7:
    notas = 400;
    break;
  case 8:
    notas = 450;
    break;
  case 9:
    notas = 500;
    break;
  case 10:
    notas = 550;
    break;
  case 11:
    notas = 600;
    break;
  case 12:
    notas = 650;
    break;
  case 13:
    notas = 700;
    break;
  case 14:
    notas = 750;
    break;
  case 15:
    notas = 800;
    break;
  }
  tone(BZZ, notas);
}


void tocaAi(){
  int estadoAtual2 = digitalRead(BTN2); //variável auxiliar para saber o estado do botão
  Serial.println(estadoAtual2);
  if (estadoAtual2 != ativaBtn2) { //se o estado atual diverge do estado estabelecido
                                   // o valor é reajustado e inicia o a leitura das notas no buzzer
    if (estadoAtual2 == 0) {
      ativaBtn2 = 0;
      for (int i = 0; i < adiciona; i++) {
        notaMusical(notas[i]);
        delay(250);
        noTone(BZZ);
      }
    } else {
      ativaBtn2 = 1;
    }
  }
}
