#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_GFX.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_SSD1306.h> //INCLUSÃO DE BIBLIOTECA
#include <Servo.h> //INCLUSÃO DE BIBLIOTECA

Adafruit_SSD1306 display = Adafruit_SSD1306(); //OBJETO DO TIPO Adafruit_SSD1306

const int PIN_SENSOR = 10;
const int PIN_RODA_DIR = 8;
const int PIN_RODA_ESQ = 9;
const int PIN_POT = A0;
const bool DEBUG = false;
const int DEFINICAO = 6;
int PIN_INICIO;
int PIN_FINAL;
int POSICAO = 0;
int sensor1 = 0; //definindo valor inicial para o sensor
int pico1 = 0; //definindo valor inicial para pico1
int pico2 = 0; //definindo valor inicial para pico2
int valor = 10;


Servo roda1;
Servo roda2;


void setup() {
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  pinMode(PIN_POT, INPUT); //ativa o potenciometro na porta A0
  pinMode(PIN_SENSOR, INPUT); //ativa o sensor na porta 10
  roda1.attach(PIN_RODA_DIR); //ativa roda direita
  roda2.attach(PIN_RODA_ESQ); //ativa roda esquerda
  parar();
  Serial.begin(9600); //ativa o serial monitor
  Serial.println("valores"); //imprime mensagem inicial no serial monitor
  delay(1000);
}



void loop() {


  MONITOR();

  sensor1 = (digitalRead(PIN_SENSOR)); //atribuindo o valor atual do sensor a variavel

  if (sensor1 == 1) {
    pico1 = pico1 + 1;

  }
  if (sensor1 == 0 && pico1 > 0) {
    pico2 = pico2 + 1;
    pico1 = 0;
    POSICAO = POSICAO + 1;
    Serial.print("valor cm: ");
    Serial.println(pico2);
  } else if (pico2 >= linha()) {
    parar();
  } else {
    andar();
  }

}

int linha() {
  int valor = (analogRead(PIN_POT));
  valor = map(valor, 0, 1023, 0, 100);
  return valor;

}

void parar() {
  roda1.write(87);
  roda2.write(90);
}

void andar() {
  roda1.write(97);
  roda2.write(79);
}

void MONITOR() {

  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.setCursor(10, 8); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Numero"); //ESCREVE O TEXTO NO DISPLAY
  display.setCursor(10, 18); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("linhas :"); //ESCREVE O TEXTO NO DISPLAY
  display.setTextSize(2); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.setCursor(80, 13); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print(linha()); //ESCREVE O TEXTO NO DISPLAY
  display.display(); //EFETIVA A ESCRITA NO DISPLAY
  delay(50); //INTERVALO DE 1,5 SEGUNDOS
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY

}
