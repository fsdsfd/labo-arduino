

//Bibliotecas
#include <Adafruit_LiquidCrystal.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C.h>
//Variables
int apagado = 1;
int contador = 0;
int ultimoConteo = -1;
int ultimoTiempo = -1;
int tiempoFinal = 0;
unsigned long tiempo = 0;
unsigned long tiempoPrendido = 0;

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

//--------------------------------------------Propias funciones--------------------------------------------

void limpiezatot(){
  lcd_1.setCursor(0, 0);  //lcd_1.setCursor(columna , fila)
  lcd_1.print("                            ");
  lcd_1.setCursor(0, 1);  //lcd_1.setCursor(columna , fila)
  lcd_1.print("                     ");
}
void limpiezainf(){
  lcd_1.setCursor(0, 1);  //lcd_1.setCursor(columna , fila)
  lcd_1.print("                     ");
}
//Función en donde se puede manejar la velocidad con la que la persona tendrá que reaccionar
void Velocidad_reaccion(int pin, int tiempo_espera, int tiempo_reaccion) {
  //Tiempo en el que no dará voltaje el pin
  if (millis() <= tiempo + tiempo_espera) {
    digitalWrite(pin, LOW);
    Serial.println("0 V");

  } else {
    //Tiempo en donde dará voltaje por 'x' seg (espera-reaccion = tiempo de reacción del jugador)
    if (millis() <= tiempo + tiempo_reaccion) {
      digitalWrite(pin, HIGH);
      Serial.println("5 V");

    } else {
      //Actualización del tiempo para repetir el ciclo
      tiempo = millis();
    }

  }  //Cierre de todo el condicional

}  //Fin de la función


//Función para manejar el tiempo de la ronda [EN SEGUNDOS]
void Tiempo_ronda(int ronda, int duracion_ronda, int tiempo_inicio_ronda) {
  //'tiempo_inicio_ronda' es desde que tiempo de ejecución la ronda se inició
  int tiempo_transcurrido = (millis() / 1000 - tiempo_inicio_ronda);

  //Evito que el LCD se resetee por actualizarse constantemente
  if (tiempo_transcurrido != ultimoTiempo) {
    lcd_1.setCursor(14, 0);
    lcd_1.print(ronda);
    lcd_1.setCursor(11, 1);
    lcd_1.print(duracion_ronda - tiempo_transcurrido);
    ultimoTiempo = tiempo_transcurrido;
  }
  if(duracion_ronda - tiempo_transcurrido == tiempoFinal){
        lcd_1.setCursor(0, 0);
    lcd_1.print("FIN DE RONDA     ");
	limpiezainf();
      limpiezatot();

    if(duracion_ronda - tiempo_transcurrido <=tiempoFinal - 1000){
    lcd_1.setCursor(14, 0);
    lcd_1.print(ronda);
    lcd_1.setCursor(11, 1);
    lcd_1.print(duracion_ronda - tiempo_transcurrido);	

      limpiezatot();
	  //lcd_1.backlight();
    }
  }
      lcd_1.setCursor(0, 0);  //lcd_1.setCursor(columna , fila)

  lcd_1.print("Contador");
  lcd_1.setCursor(9, 0);  //lcd_1.setCursor(columna , fila)
  lcd_1.print("Ronda");
       lcd_1.setCursor(3, 1);
    lcd_1.print(contador);
}  //Fin de la función


//--------------------------------------------Fin de las propias funciones--------------------------------------------


void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);  //(OUTPUT = Entrega voltaje)
  pinMode(11, INPUT);   //(INPUT = Recibe voltaje)

  tiempo = millis();
  tiempoPrendido = millis();

  lcd_1.begin(16, 2);
  //lcd_1.init();
  //lcd_1.backlight();
  lcd_1.print("Contador");
  lcd_1.setCursor(9, 0);  //lcd_1.setCursor(columna , fila)
  lcd_1.print("Ronda");
}


void loop() {
  //Evitar reseteo del LCD [BUG corregido]
  if (contador != ultimoConteo) {
    lcd_1.setCursor(3, 1);
    lcd_1.print(contador);
    ultimoConteo = contador;
  }

  //Tiempo de la ronda y varial la velocidad de reacción
  if (millis() < 7000) {
    Tiempo_ronda(1, 6, 0);
    //Llamada a la función creada
    Velocidad_reaccion(12, 1000, 3000);  //Dos segundos de reacción
  } else {
    if (millis() >= 8000 && millis() < 12000) {
      Tiempo_ronda(2, 4, 7);
      Velocidad_reaccion(12, 1000, 2000);  //Un segundo de reacción
    } else {
      if (millis() >= 13000 && millis() < 18000) {
        Tiempo_ronda(3, 5, 12);
        Velocidad_reaccion(12, 1000, 1500);  //0,5 segundos de reacción
      }
    }
  }

  //Si el pin está recibiendo voltaje, dará 1 (prendido) sino, dará 0 (apagado)
  int estado = digitalRead(11);



  //Validación del conteo de puntos
  if (estado == HIGH && apagado == 1) {
    contador++;
    apagado = 0;
    tiempoPrendido = millis();
  } else {
    //Tiempo de espera [BUG corregido]
    if (millis() - tiempoPrendido >= 20 && estado == LOW) {
      apagado = 1;
    } else {
      /*Valido que se tenga que soltar el botón, sino lo que hará
        será actualizar el tiempoPrendido y nunca la diferencia dará
        mayor a 20*/
      if (estado == HIGH) {
        tiempoPrendido = millis();
      }
    }
  }  // Fin de todo el condicional
  if(millis()>=17000){
      lcd_1.setCursor(0 , 0);
    lcd_1.print("FIN     ");
	  lcd_1.setCursor(9 , 0);
    lcd_1.print("Puntaje");
     lcd_1.setCursor(1 , 2);
    lcd_1.print("       ");

    lcd_1.setCursor(8 , 2);
    lcd_1.print(contador);
    lcd_1.setCursor(13 , 2);
    lcd_1.print("              ");

  }
}  //Cierre del loop
