//Bibliotecas
#include <LiquidCrystal_I2C.h>  // chip PCF8574 (ahorra cables)
#include <Servo.h>              // Librería para controlar servos

//Variables
int apagado = 1;
int contador = 0;           // Puntaje (guarda cuántas veces el jugador acertó)
int ultimoConteo = -1;      // Para saber si el puntaje cambió 
int ultimoTiempo = -1;      // Para actualizar sólo si cambia el tiempo
int tiempoFinal = 0;        // Para verificar si terminó la ronda
int ledActivo = -1;
unsigned long tiempo = 0;  // Marca de tiempo para los ciclos. Usado como millis()
unsigned long tiempoPrendido = 0;  // Tiempo que un LED lleva encendido

const int leds[] = { 12, 10, 3 };               // Pines de salida para LEDs
const int botones[] = { 11, 9, 2 };             // Pines de entrada para botones
bool ledsActivos[3] = { false, false, false };  // Estado de cada LED

const int botonMenu = 4;               // Botón para empezar el juego
LiquidCrystal_I2C lcd_1(0x27, 16, 2);  // Dirección del LCD [PCF8574]
bool inicio = false;                   // Marca si el juego ya comenzó
bool pantallaInicioMostrada = false;   // Evita mostrar el menú muchas veces

unsigned long tiempoEnPantalla = 0;    // Momento en que se mostró el menú
unsigned long tiempoDeJuego = 0;       // Tiempo transcurrido desde que empezó el juego

// Variables del topo (servo + sensor ultrasónico)
Servo topo1;                       // Le pongo nombre al servo
const int trig1 = 5;               // Transmisor
const int echo1 = 6;               // Receptor
const int servo1Pin = 7;           // Pin del servo
bool topoActivo = false;
unsigned long inicioTopo = 0;
const unsigned long duracionTopo = 3000; //3 segundos
bool esperandoTopo = false;
unsigned long proximoTopo = 0;  // Cuándo debe aparecer el siguiente topo

bool juegoTerminado = false;

//--------------------------------------------Propias funciones--------------------------------------------
void Menu() {
//Muestra el texto de inicio en la pantalla LCD. Se llama una sola vez antes de jugar.
  lcd_1.setCursor(0, 0);
  lcd_1.print("Atrapa al topo");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Presione el boton");
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
}  //__Fin de la función__

//**Manejar el tiempo de la ronda [EN SEGUNDOS] y Pantalla LCD**
// Muestra y controla la cuenta regresiva de cada ronda
void Tiempo_ronda(int ronda, int duracion_ronda, int tiempo_pausa, int tiempo_inicio_ronda) {
  //'tiempo_inicio_ronda' es desde que tiempo de ejecución la ronda se inició
  int tiempo_transcurrido = ((tiempoDeJuego / 1000) - tiempo_inicio_ronda); // Convierte millis() a segundos.
  static bool limpio = true, pausa = false; //Guarda si ya mostró el mensaje "FIN DE LA RONDA".


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

    if (!pausa) {
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

void ControlarTopo(unsigned long inicioRonda, unsigned long finRonda, int frecuenciaMin, int frecuenciaMax) {
  unsigned long ahora = millis();

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

      if (distancia > 0 && distancia < 15) {
        contador += 2;
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



//--------------------------------------------Fin de las propias funciones || SETUP--------------------------------------------


void setup() {
  Serial.begin(9600);                   // Para mostrar datos por el monitor serial
 
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botones[i], INPUT_PULLUP);  //Genera una resistencia interna en el PIN. Ahora, cuando el botón no esté presionado dará HIGH y si se presiona el botón dará LOW
  }
  
  pinMode(botonMenu, INPUT_PULLUP);
  pinMode(trig1, OUTPUT);    //trig es salida. transmite el sonido.
  pinMode(echo1, INPUT);     //echo es entrada. recibe el rebote.
  
  topo1.attach(servo1Pin);   // Asocio el servo al pin en el que está conectado 
  topo1.write(0);            // Su reposo es 0°.
  
  tiempo = millis();
  tiempoPrendido = millis();
  randomSeed(analogRead(A0));  //Inicia el generador de números aleatorios con un valor "ruidoso" del pin A0.
  
  lcd_1.init();       //Inicializar el LCD
  lcd_1.backlight();  //Prender la pantalla
  Menu();
}

bool juegoTerminado = false; //Indica si el juego ya terminó (para no seguir ejecutando cosas).

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

  // Rondas del juego con LEDs y servo  
    if (tiempoDeJuego < 7000) {
      Tiempo_ronda(1, 6, 3, 0);
      Velocidad_reaccion(1000, 3000, 1, 1);
    } else if (tiempoDeJuego >= 8000 && tiempoDeJuego < 12000) {  // Ronda 2: activa entre 8s-12s desde el inicio del juego.
      Tiempo_ronda(2, 4, 3, 7); //2: número de ronda. 4: duración de la ronda en segundos. 3: pausa luego de la ronda. 7: momento de inicio (en segundos
      Velocidad_reaccion(1000, 2000, 1, 2);
      ControlarTopo(8000, 12000, 2000, 4000); // El topo podrá aparecer entre 2 y 4 segundos de intervalo aleatorio dentro de esos 4 segundos totales.
    } else if (tiempoDeJuego >= 13000 && tiempoDeJuego < 17000) {
      Tiempo_ronda(3, 5, 3, 12);
      Velocidad_reaccion(1000, 1500, 1, 3);
      ControlarTopo(13000, 17000, 1000, 2500);
    }

    // Verificar aciertos por botones LED
    for (int i = 0; i < 3; i++) {
      int estado = digitalRead(botones[i]);

      if (estado == LOW && apagado == 1 && ledsActivos[i]) {
        Serial.println(estado);
        contador++;                   //Sumas un punto
        apagado = 0;                  //Para evitar multiple lectura 
        tiempoPrendido = millis();
        digitalWrite(leds[i], LOW);   //Apaga el LED
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

    //Final del juego
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
