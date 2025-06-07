//bibliotecas
#include <LiquidCrystal_I2C.h>

// Variables
int contador = 0;
int ultimoConteo = -1;
unsigned long tiempo = 0;
const int leds[] = {11, 10, 3};
const int botones[] = {12, 9, 2};  // Pin 12 botón inicio, 9 y 2 botones de juego
bool ledsActivos[3] = {false, false, false};
bool inicioJuego = false;

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

//--------------------------------------------Propias funciones--------------------------------------------

// Función para limpiar la línea inferior del LCD
void limpiezainf() {
  lcd_1.setCursor(0, 1);
  lcd_1.clear();
}

// Encender LEDs aleatorios según la ronda
void Velocidad_reaccion(int cantidadLEDs) {
  // Apagar todos
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
    ledsActivos[i] = false;
  }

  int encendidos = 0;
  Serial.print("Encendiendo ");
  Serial.print(cantidadLEDs);
  Serial.println(" LED(s):");

  while (encendidos < cantidadLEDs) {
    int elegido = random(0, 3);
    if (!ledsActivos[elegido]) {
      ledsActivos[elegido] = true;
      digitalWrite(leds[elegido], HIGH);
      Serial.print(" LED ");
      Serial.println(leds[elegido]);
      encendidos++;
    }
  }
}

// Mostrar contador y número de ronda
void Tiempo_ronda(int ronda, int segundos_restantes) {
  lcd_1.setCursor(0, 0);
  lcd_1.print("Contador");
  lcd_1.setCursor(9, 0);
  lcd_1.print("Ronda");
  lcd_1.setCursor(14, 0);
  lcd_1.print(ronda);

  lcd_1.setCursor(0, 1);
  lcd_1.print("Tiempo:");
  lcd_1.setCursor(8, 1);
  lcd_1.print("  ");
  lcd_1.setCursor(8, 1);
  lcd_1.print(segundos_restantes);

  Serial.print("Ronda ");
  Serial.print(ronda);
  Serial.print(" - Tiempo restante: ");
  Serial.println(segundos_restantes);
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(botones[i], INPUT);
  }

  lcd_1.init();
  lcd_1.backlight();
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Presione boton");
  lcd_1.setCursor(0, 1);
  lcd_1.print("para comenzar");

  Serial.println("Esperando para empezar");
}

void loop() {
  // Espera no bloqueante para iniciar juego con botón en pin 12
  if (!inicioJuego) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Presione boton");
    lcd_1.setCursor(0, 1);
    lcd_1.print("para comenzar");

    if (digitalRead(12) == LOW) { // botón presionado (considera INPUT sin pullup)
      delay(50); // debounce
      if (digitalRead(12) == LOW) { // confirmar que sigue presionado
        inicioJuego = true;
        tiempo = millis();
        lcd_1.clear();
        Serial.println("Juego iniciado.");
      }
    }
    return; // salimos para no ejecutar nada más hasta que inicie el juego
  }

  unsigned long tiempoActual = millis();
  int tiempoTotal = (tiempoActual - tiempo) / 1000;

  if (tiempoTotal < 7) {
    lcd_1.clear();
    Tiempo_ronda(1, 6 - tiempoTotal);
    if (tiempoActual % 1000 < 50) Velocidad_reaccion(1);
  } else if (tiempoTotal >= 8 && tiempoTotal < 12) {
    lcd_1.clear();
    Tiempo_ronda(2, 11 - tiempoTotal);
    if (tiempoActual % 1000 < 50) Velocidad_reaccion(random(1, 3));
  } else if (tiempoTotal >= 13 && tiempoTotal < 18) {
    lcd_1.clear();
    Tiempo_ronda(3, 17 - tiempoTotal);
    if (tiempoActual % 1000 < 50) Velocidad_reaccion(random(1, 4));
  }

  // Verificación de botones para juego (pines 9 y 2)
  for (int i = 1; i < 3; i++) { // botones[1] = 9, botones[2] = 2
    if (digitalRead(botones[i]) == HIGH && ledsActivos[i]) {
      contador++;
      digitalWrite(leds[i], LOW);
      ledsActivos[i] = false;
      Serial.print("Boton presionado correctamente en pin ");
      Serial.print(botones[i]);
      Serial.print(". Contador = ");
      Serial.println(contador);
      delay(200);  // antirrebote
    }
  }

  if (contador != ultimoConteo) {
    lcd_1.setCursor(3, 1);
    lcd_1.print("   ");
    lcd_1.setCursor(3, 1);
    lcd_1.print(contador);
    ultimoConteo = contador;
  }

  if (tiempoTotal >= 18) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(leds[i], LOW);
    }

    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("FIN DEL JUEGO");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Puntaje: ");
    lcd_1.print(contador);

    Serial.println("Juego terminado.");
    Serial.print("Puntaje final: ");
    Serial.println(contador);

    while (true);
  }
}
