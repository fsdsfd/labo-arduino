//Bibliotecas
#include <LiquidCrystal_I2C.h>  // PCF8574


//Variables
int apagado = 1;
int contador = 0;
int ultimoConteo = -1;
int ultimoTiempo = -1;
int tiempoFinal = 0;
unsigned long tiempo = 0;
unsigned long tiempoPrendido = 0;
const int leds[] = {12, 10, 8};     // Pines de salida para LEDs
const int botones[] = {11, 9, 7};   // Pines de entrada para botones
int ledActivo = -1; 
bool ledsActivos[3] = {false, false, false}; // LEDs encendidos actualmente

LiquidCrystal_I2C lcd_1(0x27, 16, 2);  //Dirección del LCD [PCF8574]

//--------------------------------------------Propias funciones--------------------------------------------

void limpiezatot() {
  lcd_1.setCursor(0, 0);  //lcd_1.setCursor(columna , fila)
  lcd_1.print("                            ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("                     ");
}


void limpiezainf() {
  lcd_1.setCursor(0, 1);
  lcd_1.print("                     ");
}


//**Manejar la velocidad con la que la persona tendrá que reaccionar**
void Velocidad_reaccion(int tiempo_espera, int tiempo_reaccion, int minLEDs, int maxLEDs) {
  static bool yaEncendidos = false;

  if (millis() <= tiempo + tiempo_espera) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], LOW);
      ledsActivos[i] = false;
    }
    yaEncendidos = false;

  } else {
    if (millis() <= tiempo + tiempo_reaccion) {
      if (!yaEncendidos) {
        // Apagar todos antes de empezar
        for (int i = 0; i < 3; i++) {
          digitalWrite(leds[i], LOW);
          ledsActivos[i] = false;
        }

        // Elegir una cantidad aleatoria de LEDs a prender
        int cantidadLEDs = random(minLEDs, maxLEDs + 1);
        int encendidos = 0;

        while (encendidos < cantidadLEDs) {
          int elegido = random(0, 3);
          if (!ledsActivos[elegido]) {
            ledsActivos[elegido] = true;
            digitalWrite(leds[elegido], HIGH);
            encendidos++;
          }
        }

        yaEncendidos = true;
      }

    } else {
      // Fin del ciclo: apagar todos y reiniciar
      for (int i = 0; i < 3; i++) {
        digitalWrite(leds[i], LOW);
        ledsActivos[i] = false;
      }
      yaEncendidos = false;
      tiempo = millis();
    }
  }
}
//**Manejar el tiempo de la ronda [EN SEGUNDOS]**
void Tiempo_ronda(int ronda, int duracion_ronda, int tiempo_inicio_ronda) {
  //'tiempo_inicio_ronda' es desde que tiempo de ejecución la ronda se inició
  int tiempo_transcurrido = (millis() / 1000 - tiempo_inicio_ronda);

  if (tiempo_transcurrido != ultimoTiempo) {
    lcd_1.setCursor(14, 0);
    lcd_1.print(ronda);
    lcd_1.setCursor(11, 1);
    lcd_1.print(duracion_ronda - tiempo_transcurrido);
    ultimoTiempo = tiempo_transcurrido;
  }

  if (duracion_ronda - tiempo_transcurrido == tiempoFinal) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], LOW);
      ledsActivos[i] = false;
    }
    lcd_1.setCursor(0, 0);
    lcd_1.print("FIN DE RONDA     ");
    limpiezainf();
    limpiezatot();

    if (duracion_ronda - tiempo_transcurrido <= tiempoFinal - 1000) {
      lcd_1.setCursor(14, 0);
      lcd_1.print(ronda);
      lcd_1.setCursor(11, 1);
      lcd_1.print(duracion_ronda - tiempo_transcurrido);

      limpiezatot();
      //lcd_1.backlight();
    }
  }
  lcd_1.setCursor(0, 0);
  lcd_1.print("Contador");
  lcd_1.setCursor(9, 0);
  lcd_1.print("Ronda");
  lcd_1.setCursor(3, 1);
  lcd_1.print(contador);

}  //__Fin de la función__


//--------------------------------------------Fin de las propias funciones--------------------------------------------


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botones[i], INPUT);  // O INPUT_PULLUP si el botón va a GND
  }
  tiempo = millis();
  tiempoPrendido = millis();

  lcd_1.init();       //Inicializar el LCD
  lcd_1.backlight();  //Prender la pantalla
  lcd_1.print("Contador");
  lcd_1.setCursor(9, 0);  //lcd_1.setCursor(columna , fila)
  lcd_1.print("Ronda");
}


void loop() {
  //Imprimir contador en el LCD
  if (contador != ultimoConteo) {
    lcd_1.setCursor(3, 1);
    lcd_1.print(contador);
    ultimoConteo = contador;
  }
if (millis() < 7000) {
  Tiempo_ronda(1, 6, 0);
  Velocidad_reaccion(1000, 3000, 1, 1);  // Solo 1 LED se prende
} else if (millis() >= 8000 && millis() < 12000) {
  Tiempo_ronda(2, 4, 7);
  Velocidad_reaccion(1000, 2000, 1, 2);  // Se prenden 1 o 2
} else if (millis() >= 13000 && millis() < 18000) {
  Tiempo_ronda(3, 5, 12);
  Velocidad_reaccion(1000, 1500, 1, 3);  // Se prenden entre 1 y 3
}

  //Si el pin está recibiendo voltaje, dará 1 (prendido) sino, dará 0 (apagado)
for (int i = 0; i < 3; i++) {
  int estado = digitalRead(botones[i]);

  if (estado == HIGH && apagado == 1 && ledsActivos[i]) {
    contador++;
    apagado = 0;
    tiempoPrendido = millis();

        digitalWrite(leds[i], LOW);
  } else {
    if (millis() - tiempoPrendido >= 20 && estado == LOW) {
      apagado = 1;
    } else {
      if (estado == HIGH) {
        tiempoPrendido = millis();
      }
    }
  }
}


  //Pantalla final
  if (millis() >= 17000) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("FIN     ");
    lcd_1.setCursor(9, 0);
    lcd_1.print("Puntaje");
    lcd_1.setCursor(1, 2);
    lcd_1.print("       ");

    lcd_1.setCursor(13, 2);
    lcd_1.print(contador);
    lcd_1.setCursor(13, 2);
  }
}  //Cierre del loop
