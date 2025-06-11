//Bibliotecas
#include <LiquidCrystal_I2C.h>  //PCF8574


//Variables
int apagado = 1;
int contador = 0;
int ultimoConteo = -1;
int ultimoTiempo = -1;
int tiempoFinal = 0;
int ledActivo = -1;
unsigned long tiempo = 0;
unsigned long tiempoPrendido = 0;
const int leds[] = { 12, 10, 3 };               // Pines de salida para LEDs
const int botones[] = { 11, 9, 2 };             // Pines de entrada para botones
bool ledsActivos[3] = { false, false, false };  // LEDs encendidos actualmente
const int botonMenu = 4;
LiquidCrystal_I2C lcd_1(0x27, 16, 2);  //Dirección del LCD [PCF8574]
bool inicio = false;
bool pantallaInicioMostrada = false;
unsigned long tiempoEnPantalla = 0, tiempoDeJuego = 0;

//--------------------------------------------Propias funciones--------------------------------------------
void Menu() {
  lcd_1.setCursor(0, 0);
  lcd_1.print("Atrapa al topo");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Presione el boton");
}
//**Manejar la velocidad con la que la persona tendrá que reaccionar y prendido/apagado de LEDS**
void Velocidad_reaccion(int tiempo_espera, int tiempo_reaccion, int minLEDs, int maxLEDs) {
  //Inicializar variable una sola vez y su valor no se resetea
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
}  //__Fin de la función__

//**Manejar el tiempo de la ronda [EN SEGUNDOS] y Pantalla LCD**
void Tiempo_ronda(int ronda, int duracion_ronda, int tiempo_pausa, int tiempo_inicio_ronda) {
  //'tiempo_inicio_ronda' es desde que tiempo de ejecución la ronda se inició
  int tiempo_transcurrido = ((tiempoDeJuego / 1000) - tiempo_inicio_ronda);
  static bool limpio = true, pausa = false;


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

    if (pausa == false) {
      lcd_1.clear();
      lcd_1.print("FIN DE LA RONDA");
      limpio = false;
      pausa = true;
    }
  } else {
    if (tiempoDeJuego - tiempo_inicio_ronda > duracion_ronda + tiempo_pausa && limpio == false) {
      lcd_1.clear();
      lcd_1.setCursor(0, 0);
      lcd_1.print("Contador");
      lcd_1.setCursor(9, 0);
      lcd_1.print("Ronda");
      lcd_1.setCursor(3, 1);
      lcd_1.print(contador);


      lcd_1.setCursor(14, 0);
      lcd_1.print(ronda);
      lcd_1.setCursor(11, 1);
      lcd_1.print(duracion_ronda - tiempo_transcurrido);
      ultimoTiempo = tiempo_transcurrido;

      limpio = true;
      pausa = false;
    }
  }


}  //__Fin de la función__


//--------------------------------------------Fin de las propias funciones--------------------------------------------


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botones[i], INPUT_PULLUP);  //Genera una resistencia interna en el PIN. Ahora, cuando el botón no esté presionado dará HIGH y si se presiona el botón dará LOW
  }
  pinMode(botonMenu, INPUT_PULLUP);
  tiempo = millis();
  tiempoPrendido = millis();
  randomSeed(analogRead(A0));
  lcd_1.init();       //Inicializar el LCD
  lcd_1.backlight();  //Prender la pantalla

  Menu();
}

bool juegoTerminado = false;

void loop() {
  int botonActivo = digitalRead(botonMenu);
  tiempoDeJuego = millis() - tiempoEnPantalla;

  // Mostrar menú solo una vez antes de que inicie el juego
  if (!inicio && !pantallaInicioMostrada) {
    Menu();  // Muestra "Atrapa al topo" y "Presione el botón"
    pantallaInicioMostrada = true;

    while (botonActivo) {
      tiempoEnPantalla = millis();
      botonActivo = digitalRead(botonMenu);
    }
  }

  // Esperar botón para iniciar el juego
  if (!inicio && botonActivo == LOW) {
    inicio = true;
    tiempo = millis();  // Resetear el tiempo de juego
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Contador");
    lcd_1.setCursor(9, 0);
    lcd_1.print("Ronda");
    lcd_1.setCursor(3, 1);
    lcd_1.print(contador);
  }

  // Solo ejecutar el juego si ya empezó
  if (inicio && !juegoTerminado) {
    if (contador != ultimoConteo) {
      lcd_1.setCursor(3, 1);
      lcd_1.print(contador);
      ultimoConteo = contador;
    }

    if (tiempoDeJuego < 7000) {
      Tiempo_ronda(1, 6, 3, 0);
      Velocidad_reaccion(1000, 3000, 1, 1);
    } else if (tiempoDeJuego >= 8000 && tiempoDeJuego < 12000) {
      Tiempo_ronda(2, 4, 3, 7);
      Velocidad_reaccion(1000, 2000, 1, 2);
    } else if (tiempoDeJuego >= 13000 && tiempoDeJuego < 17000) {
      Tiempo_ronda(3, 5, 3, 12);
      Velocidad_reaccion(1000, 1500, 1, 3);
    }

    for (int i = 0; i < 3; i++) {
      int estado = digitalRead(botones[i]);

      if (estado == LOW && apagado == 1 && ledsActivos[i]) {
        Serial.println(estado);
        contador++;
        apagado = 0;
        tiempoPrendido = millis();
        digitalWrite(leds[i], LOW);
      } else {
        if (millis() - tiempoPrendido >= 20 && estado == HIGH) {
          apagado = 1;
        } else {
          if (estado == LOW) {
            tiempoPrendido = millis();
          }
        }
      }
    }

    if (tiempoDeJuego >= 17000 && !juegoTerminado) {
      lcd_1.clear();
      lcd_1.setCursor(0, 0);
      lcd_1.print("FIN");
      lcd_1.setCursor(9, 0);
      lcd_1.print("Puntaje");
      lcd_1.setCursor(12, 1);
      lcd_1.print(contador);
      juegoTerminado = true;
    }
  }
}  // Cierre del loop