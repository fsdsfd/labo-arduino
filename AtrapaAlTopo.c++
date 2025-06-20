
//Bibliotecas
#include <Wire.h>
#include <Adafruit_GFX.h>      // Librería de Adafruit
#include <Adafruit_SSD1306.h>  // Librería para pantallas OLED
#include <Servo.h>             // Librería para controlar servos

//Variables
// Definiciones de la pantalla OLED
#define SCREEN_WIDTH 128
// Ancho de la pantalla OLED
#define SCREEN_HEIGHT 32
// Alto de la pantalla OLED
#define OLED_RESET -1
// Reset de la pantalla OLED

//IMAGEN DE MENU
const unsigned char topo_bitmapponele2[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4f, 0x80, 0x00, 0x00,
  0x00, 0x01, 0xff, 0x3f, 0xf3, 0xff, 0x1f, 0xe0, 0xff, 0x00, 0x00, 0x00, 0x71, 0xc0, 0x00, 0x00,
  0x00, 0x01, 0xff, 0xbf, 0xfb, 0xff, 0x3f, 0xf9, 0xff, 0xc0, 0x00, 0x04, 0x7e, 0x40, 0x00, 0x00,
  0x00, 0x01, 0xc3, 0xb8, 0x3b, 0x80, 0x78, 0x3b, 0xc1, 0xc0, 0x00, 0x8c, 0xc7, 0xc0, 0x00, 0x00,
  0x00, 0x01, 0xc3, 0xb8, 0x3b, 0x80, 0x78, 0x33, 0xc1, 0x80, 0x00, 0xcc, 0xc7, 0xc0, 0x00, 0x00,
  0x00, 0x01, 0xc3, 0xb8, 0x7b, 0xfe, 0x3f, 0x81, 0xfc, 0x00, 0x00, 0xc8, 0x81, 0xf0, 0x00, 0x00,
  0x00, 0x01, 0xff, 0xbf, 0xf3, 0xfe, 0x1f, 0xe0, 0xff, 0x00, 0x00, 0x69, 0x83, 0x3e, 0x00, 0x00,
  0x00, 0x01, 0xff, 0x3f, 0xc3, 0x80, 0x00, 0x38, 0x01, 0xc0, 0x00, 0x31, 0xf3, 0x87, 0x80, 0x00,
  0x00, 0x01, 0xfe, 0x3f, 0xc3, 0x80, 0x30, 0x39, 0x81, 0xc0, 0x03, 0xc3, 0xff, 0xf0, 0xc0, 0x00,
  0x00, 0x01, 0xc0, 0x39, 0xf3, 0x80, 0x78, 0x3b, 0xc1, 0xc0, 0x07, 0x1a, 0x3e, 0x3e, 0xc0, 0x00,
  0x00, 0x01, 0xc0, 0x38, 0xfb, 0xff, 0x3f, 0xf1, 0xff, 0x80, 0x00, 0x33, 0xc3, 0x07, 0xc0, 0x00,
  0x00, 0x01, 0xc0, 0x38, 0x3b, 0xff, 0x1f, 0xe0, 0xff, 0x00, 0x00, 0x60, 0xff, 0x03, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x4f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x66, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x1f, 0xf0, 0x70, 0x3f, 0xf1, 0xff, 0x00, 0x00, 0xce, 0xe6, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xff, 0xdf, 0xf0, 0xf8, 0x3f, 0xf9, 0xff, 0x00, 0x00, 0xc4, 0x46, 0x00, 0x00, 0x00,
  0x00, 0x03, 0xc1, 0xc3, 0x81, 0xde, 0x38, 0x38, 0x38, 0x00, 0x00, 0xc1, 0x06, 0x00, 0x00, 0x00,
  0x00, 0x03, 0xc1, 0x83, 0x83, 0x8e, 0x38, 0x38, 0x38, 0x00, 0x00, 0xc3, 0x86, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xfc, 0x03, 0x87, 0x07, 0x38, 0x78, 0x38, 0x00, 0x00, 0xdb, 0xb6, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x03, 0x87, 0x07, 0x3f, 0xf0, 0x38, 0x00, 0x00, 0xcf, 0xe6, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xc3, 0x87, 0xff, 0x3f, 0xc0, 0x38, 0x00, 0x00, 0xc2, 0xc6, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x81, 0xc3, 0x87, 0xff, 0x3f, 0xc0, 0x38, 0x00, 0x00, 0xc3, 0x86, 0x00, 0x00, 0x00,
  0x00, 0x03, 0xc1, 0xc3, 0x87, 0x07, 0x39, 0xf0, 0x38, 0x00, 0x00, 0xc0, 0x06, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xff, 0x83, 0x87, 0x07, 0x38, 0xf8, 0x38, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x03, 0x87, 0x07, 0x38, 0x38, 0x38, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int apagado = 1;
int contador = 0;                  // Puntaje (guarda cuántas veces el jugador acertó)
int ultimoConteo = -1;             // Para saber si el puntaje cambió
int ultimoTiempo = -1;             // Para actualizar sólo si cambia el tiempo
int tiempoFinal = 0;               // Para verificar si terminó la ronda
int ledActivo = -1;                // Para indicar qué LED está activo
unsigned long tiempo = 0;          // Marca de tiempo para los ciclos. Usado como millis()
unsigned long tiempoPrendido = 0;  // Tiempo que un LED lleva encendido

const int leds[] = { 12, 10, 3 };               // Pines de salida para LEDs
const int botones[] = { 11, 9, 2 };             // Pines de entrada para botones
bool ledsActivos[3] = { false, false, false };  // Estado de cada LED

const int botonMenu = 4;  // Botón para empezar el juego

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Pantalla OLED, es para usar el I2C

bool inicio = false;                  // Marca si el juego ya comenzó
bool pantallaInicioMostrada = false;  // Evita mostrar el menú muchas veces

unsigned long tiempoEnPantalla = 0;  // Momento en que se mostró el menú
unsigned long tiempoDeJuego = 0;     // Tiempo transcurrido desde que empezó el juego

// Variables del topo (servo + sensor ultrasónico)
Servo topo1;                              // Le pongo nombre al servo
const int trig1 = 5;                      // Transmisor
const int echo1 = 6;                      // Receptor
const int servo1Pin = 7;                  // Pin del servo1
bool topoActivo = false;                  // Para indicar si el topo se activó
unsigned long inicioTopo = 0;             // Tiempo en que apareció el topo
const unsigned long duracionTopo = 3000;  // Duración MAX del topo visible: 3 segundos
bool esperandoTopo = false;               // Indica si se está esperando a mostrar al topo1
unsigned long proximoTopo = 0;            // Cuándo debe aparecer el siguiente topo1
Servo topo2;
const int trig2 = A0;
const int echo2 = A1;
const int servo2Pin = 8;
bool juegoTerminado = false;  //Indica si el juego terminó
bool topo2Activo = false;
unsigned long inicioTopo2 = 0;
const unsigned long duracionTopo2 = 3000;
bool esperandoTopo2 = false;
unsigned long proximoTopo2 = 0;

//--------------------------------------------Propias funciones--------------------------------------------
void Menu() {
  // OLED 128x32
  display.clearDisplay();
  display.drawBitmap(0, 0, topo_bitmapponele2, 128, 32, WHITE);
  display.display();  //Para que no se actualize INNECESARIAMENTE*
}


void Velocidad_reaccion(int tiempo_espera, int tiempo_reaccion, int minLEDs, int maxLEDs) {
  //Manejar la velocidad con la que la persona tendrá que reaccionar y prendido/apagado de LEDS**
  static bool yaEncendidos = false;  //Inicializar variable una sola vez y su valor no se resetea

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
}  //Fin de la función

//Manejar el tiempo de la ronda [EN SEGUNDOS] y Pantalla LCD
// Muestra y controla la cuenta regresiva de cada ronda
void Tiempo_ronda(int ronda, int duracion_ronda, int tiempo_inicio_ronda) {
  //'tiempo_inicio_ronda' es desde que tiempo de ejecución la ronda se inició
  int tiempo_transcurrido = ((tiempoDeJuego / 1000) - tiempo_inicio_ronda);  // Convierte millis() a segundos.
  static bool limpio = true, pausa = false;                                  //Guarda si ya mostró el mensaje "FIN DE LA RONDA".

  if (tiempo_transcurrido != ultimoTiempo) {
    //DISPLAY OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Ronda:"));
    display.print(ronda);
    display.setCursor(74, 0);
    display.print(F("Tiempo:"));
    display.println(duracion_ronda - tiempo_transcurrido);
    //display.println("Contador");  // Título
    display.setCursor(0, 16);
    display.print("Puntos:");  // Mostrar puntaje inicial
    display.print(contador);
    display.display();

    ultimoTiempo = tiempo_transcurrido;
  }

  if (duracion_ronda - tiempo_transcurrido == tiempoFinal) {
    for (int i = 0; i < 3; i++) {

      digitalWrite(leds[i], LOW);
      ledsActivos[i] = false;
    }


    if (!pausa) {
      display.clearDisplay();
      display.setCursor(20, 0);
      display.println(F("FIN DE LA RONDA"));
      display.setCursor(20, 20);
      display.println(F("SIGUIENTE RONDA"));
      display.display();
      display.clearDisplay();
      limpio = false;
      pausa = true;
    }

  } else {
    if (limpio == false) {
      display.clearDisplay();


      ultimoTiempo = tiempo_transcurrido;

      limpio = true;
      pausa = false;
    }
  }
}  //Fin de la función

void ControlarTopo(unsigned long inicioRonda, unsigned long finRonda, int frecuenciaMin, int frecuenciaMax) {
  unsigned long ahora = tiempoDeJuego;

  if (ahora >= inicioRonda && ahora < finRonda) {
    if (!topoActivo && !esperandoTopo) {
      unsigned long intervalo = random(frecuenciaMin, frecuenciaMax);
      proximoTopo = ahora + intervalo;
      esperandoTopo = true;
    }

    if (!topoActivo && esperandoTopo && ahora >= proximoTopo) {
      topo1.write(90);  // Sube el topo
      inicioTopo = ahora;
      topoActivo = true;
      esperandoTopo = false;
    }

    if (topoActivo) {
      digitalWrite(trig1, LOW);
      delayMicroseconds(2);
      digitalWrite(trig1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig1, LOW);

      long duracion = pulseIn(echo1, HIGH, 15000);
      int distancia = duracion / 58;

      if (distancia > 0 && distancia < 7) {
        contador += 2;   // DOBLE puntaje si el sensor detecta el topo
        topo1.write(0);  // Baja el topo
        topoActivo = false;
      } else if (ahora - inicioTopo >= duracionTopo) {
        topo1.write(0);  // Baja el topo igual si se terminó el tiempo
        topoActivo = false;
      }
    }
  } else {
    topo1.write(0);
    topoActivo = false;
    esperandoTopo = false;
  }
}
void ControlarTopo2(unsigned long inicioRonda, unsigned long finRonda, int frecuenciaMin, int frecuenciaMax) {
  unsigned long ahora = tiempoDeJuego;

  if (ahora >= inicioRonda && ahora < finRonda) {
    if (!topo2Activo && !esperandoTopo2) {
      unsigned long intervalo = random(frecuenciaMin, frecuenciaMax);
      proximoTopo2 = ahora + intervalo;
      esperandoTopo2 = true;
    }

    if (!topo2Activo && esperandoTopo2 && ahora >= proximoTopo2) {
      topo2.write(90);
      inicioTopo2 = ahora;
      topo2Activo = true;
      esperandoTopo2 = false;
    }

    if (topo2Activo) {
      digitalWrite(trig2, LOW);
      delayMicroseconds(2);
      digitalWrite(trig2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig2, LOW);

      long duracion = pulseIn(echo2, HIGH, 15000);
      int distancia = duracion / 58;

      if (distancia > 0 && distancia < 15) {
        contador += 2;
        topo2.write(0);
        topo2Activo = false;
      } else if (ahora - inicioTopo2 >= duracionTopo2) {
        topo2.write(0);
        topo2Activo = false;
      }
    }
  } else {
    topo2.write(0);
    topo2Activo = false;
    esperandoTopo2 = false;
  }
}

//--------------------------------------------Fin de las propias funciones || SETUP--------------------------------------------

void setup() {         // Función que se ejecuta 1 sola vez al inciar el juego
  Serial.begin(9600);  // Para mostrar datos por el monitor serial. a 9600 BAUDIOS.
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  topo2.attach(servo2Pin);
  topo2.write(0);
  for (int i = 0; i < 3; i++) {         //Bucle para configurar los LEDS y botones
    pinMode(leds[i], OUTPUT);           //LEDS son salida
    pinMode(botones[i], INPUT_PULLUP);  //Genera una resistencia interna en el PIN. Ahora, cuando el botón no esté presionado dará HIGH y si se presiona el botón dará LOW

  }  //FinFor

  pinMode(botonMenu, INPUT_PULLUP);  //Botón de "inicio de juego" con resistencia PULL-UP
  pinMode(trig1, OUTPUT);            //trig es salida. transmite el sonido.
  pinMode(echo1, INPUT);             //echo es entrada. recibe el rebote.

  topo1.attach(servo1Pin);  // Asocio el servo al pin en el que está conectado
  topo1.write(0);           // Su reposo es 0°.

  tiempo = millis();
  tiempoPrendido = millis();
  randomSeed(analogRead(A2));  //Inicia el generador de números aleatorios con un valor "ruidoso" del pin A2.

  Wire.begin();                               // Iniciar la comunicación I2C OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);  // Iniciar la pantalla OLED 0X3D es para el OLED 128x64
  display.clearDisplay();                     //Limpia cualquier texto previo
  display.display();                          //Aplica los cambios de pantalla
  display.setTextSize(1);
  Menu();
}  //FinVOID

void loop() {                                   //Función principal que se repite continuamente mientras el Arduino esta prendido
  int botonActivo = digitalRead(botonMenu);     //Lee el botón de inicio
  tiempoDeJuego = millis() - tiempoEnPantalla;  //Tiempo total del juego desde que se mostró el menú
  // Mostrar menú solo una vez antes de que inicie el juego
  if (!inicio && !pantallaInicioMostrada) {  //Si el juego no inicio Y el menú aún no se mostró...
    Menu();                                  //Muestra "Atrapa al topo" y "Presione el botón"
    pantallaInicioMostrada = true;           //Evita que el menú se muestre más de una vez

    while (botonActivo) {                    //Espera  que se presione el boton para iniciar juego
      tiempoEnPantalla = millis();           //Actualiza el momento en que el menú fue mostrado
      botonActivo = digitalRead(botonMenu);  //Vuelve a leer el boton para salir del bucle si se presiona
    }                                        //FinWhile
  }                                          //FinIf

  // Esperar botón para iniciar el juego
  if (!inicio && botonActivo == LOW) {  //Cuando se presiona el botón, inicia el juego
    inicio = true;                      //Marca quye el juego comenzó
    tiempo = millis();                  // Resetear el tiempo de juego
    display.setTextColor(SSD1306_WHITE);
  }  //Fin del IF que inicia el juego

  // Solo ejecutar el juego si ya empezó
  if (inicio && !juegoTerminado) {   //Si el juego está en curso Y no terminó...
    if (contador != ultimoConteo) {  //Si el puntaje cambió...

      ultimoConteo = contador;  //Guarda el nuevo puntaje
    }                           //Fin IF actualizacion de puntaje

    // Rondas del juego con LEDs y servo

    // PRIMERA RONDA sólo LEDS
    if (tiempoDeJuego < 8000) {
      Tiempo_ronda(1, 7, 0);
      Velocidad_reaccion(1000, 3000, 1, 1);
      // SEGUNDA RONDA LEDS + Topo (uno a la vez)(agregar)
    } else if (tiempoDeJuego >= 9000 && tiempoDeJuego < 17000) {
      Tiempo_ronda(2, 7, 9);
      Velocidad_reaccion(1000, 2000, 1, 2);

      if (random(1, 3) == 1) {
        ControlarTopo(8000, 15000, 2000, 4000);  // solo uno de los dos
      } else {
        ControlarTopo2(8000, 15000, 2000, 4000);
      }

      // RONDA 3
    } else if (tiempoDeJuego >= 18000 && tiempoDeJuego < 25000) {
      Tiempo_ronda(3, 7, 18);
      Velocidad_reaccion(1000, 1500, 1, 3);

      ControlarTopo(16000, 23000, 1000, 2500);
      ControlarTopo2(16000, 23000, 1000, 2500);
    }



    // Verificar aciertos por botones LED
    for (int i = 0; i < 3; i++) {            //Recorre todos los botones para verificar si se acertó
      int estado = digitalRead(botones[i]);  //Lee el estado del botón i

      if (estado == LOW && apagado == 1 && ledsActivos[i]) {  //Si el botón fue presionado Y el led correspondiente está activo...
        Serial.println(estado);
        contador++;                                               //Sumas un punto
        apagado = 0;                                              //Para evitar multiple lectura del botón presionado
        tiempoPrendido = millis();                                //Actualiza el tiempo para control de rebote
        digitalWrite(leds[i], LOW);                               //Apaga el LED
      } else {                                                    //Si no se presionó el boton bien, analiza el rebote
        if (millis() - tiempoPrendido >= 20 && estado == HIGH) {  //Si se terminó el tiempo para presionar, permite sumar puntos de nuevo
          apagado = 1;                                            //Habilita de nuevo el botón
        } else {                                                  //Si no terminó el tiempo pero el botón esta presionado...
          if (estado == LOW) {                                    //Si sigue presionado, actualiza el tiempo de rebote
            tiempoPrendido = millis();                            //Actualiza el tiempo para reiniciar el control de rebote
          }                                                       //Fin del If
        }                                                         //Fin Else rebote
      }                                                           //Fin Else principal
    }                                                             //Fin Verificar botones

    //Final del juego
    if (tiempoDeJuego >= 25000 && !juegoTerminado) {
      display.clearDisplay();  //Limpia la pantalla OLED
      display.setCursor(25, 0);
      display.println("FIN DEL JUEGO");
      display.setCursor(15, 16);
      display.print("Puntaje total:");
      display.println(contador);
      display.display();  //Actualiza la pantalla OLED con el contenido nuevo


      juegoTerminado = true;  //Para marcar que se terminó el juego y no se repita la sección
    }                         //Fin bloque final del juego
  }                           //Fin bloque preincipal del juego

  //Reinicio las variables y del juego
  if (juegoTerminado && botonActivo == LOW) {
    contador = 0;
    ultimoConteo = -1;
    ultimoTiempo = -1;
    tiempoFinal = 0;
    ledActivo = -1;
    tiempo = millis();
    tiempoPrendido = millis();
    tiempoEnPantalla = millis();
    pantallaInicioMostrada = false;
    inicio = false;
    juegoTerminado = false;
    topoActivo = false;
    topo2Activo = false;
    esperandoTopo = false;
    esperandoTopo2 = false;
    topo1.write(0);
    topo2.write(0);

    for (int i = 0; i < 3; i++) {  //apago los leds
      digitalWrite(leds[i], LOW);
      ledsActivos[i] = false;
    }
    Menu();                                  //muestro elk menu de nuevo
    while (digitalRead(botonMenu) == LOW) {  // al tocar el boton vuelve al menu, y espera a que el jugador presione nuevamente
      delay(10);
    }
  }
}