#include <Arduino.h>

//Definir pines de salidas y entradas
#define LED1 19
#define LED2 18
#define LED3 5

#define Pot1 14
#define Referencia 23

//Definir variables globales
int opcion = 0, milV = 0, lim = 0, iLED = 0, itiempo = 0;
String instruccion, LED, tiempo;

void setup() {

  //Comenzar la comunicación serial
  Serial.begin(115200);

  //Configuración de pines
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(Pot1, INPUT);
  analogSetVRefPin(Referencia);
}

void loop() {

  Serial.println("1. LECTURA ADC \n2. Controlar LEDs\nIngrese el número de opción: ");

  while (Serial.available() == 0)
  {
    
  }

  if (Serial.available()) {

    opcion = Serial.read() - 48;

    if (opcion == 1) {
      milV = analogReadMilliVolts(Pot1);
      Serial.printf("Lectura de milivoltios en el potenciómetro: %f mV\n", milV);
    }

    else if (opcion == 2) {
      Serial.println("Ingrese el LED a encender y el tiempo separado por una coma");
      while (Serial.available() == 0) {
      // Esperar input
      }

      if (Serial.available()) {
        instruccion = Serial.readStringUntil('\n');
        lim = instruccion.indexOf(",");

        LED = instruccion.substring(0, lim);
        tiempo = instruccion.substring(lim + 1);

        iLED = LED.toInt();
        itiempo = tiempo.toInt();
        
        switch (iLED)
        {
        case 1:
          digitalWrite(LED1, HIGH);
          delay(itiempo);
          digitalWrite(LED1, LOW);
          break;
        case 2:
          digitalWrite(LED2, HIGH);
          delay(itiempo);
          digitalWrite(LED2, LOW);
          break;
        case 3:
          digitalWrite(LED3, HIGH);
          delay(itiempo);
          digitalWrite(LED3, LOW);
        default:
          Serial.println("Selección de LED inválida");
          break;
        }
      }
    } else {
      Serial.println("Opción de menú inválida");
    }
  }
}
