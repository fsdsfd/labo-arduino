// C++ code
//
#include <Adafruit_LiquidCrystal.h>


//Variables
int apagado = 1;
int contador = 0;
int ultimoConteo = -1;
unsigned long tiempo = 0;
unsigned long tiempoPrendido = 0;
Adafruit_LiquidCrystal lcd_1(0x20);

//Función para no repetir código
void Velocidad_reaccion(int pin, int tiempo_espera, int tiempo_reaccion){
  //Tiempo en el no dará voltaje el pin
  if (millis() <= tiempo+tiempo_espera){
  	digitalWrite(pin,LOW);
    Serial.println("0 V");
    
  } else {
	//Tiempo en donde dará voltaje por 'x'seg (espera-reaccion = tiempo de reaccion del jugador)
    if (millis() <= tiempo+tiempo_reaccion){
    	digitalWrite(pin,HIGH);
     	Serial.println("5 V");
      
    } else {
      //Actualización del tiempo para repetir el ciclo
      tiempo = millis() ;
      
  	}
    
  } //Fin de todo el condicional
  
} // Cierre de la función

void setup()
{
  Serial.begin(9600);
  pinMode(12,OUTPUT); //(OUTPUT = Entrega voltaje)
  pinMode(11,INPUT); //(INPUT = Recibe voltaje)
  
  tiempo = millis();
  tiempoPrendido = millis();
  
  lcd_1.begin(16, 2);
  lcd_1.print("Contador");
}



void loop()
{
  
  //Evitar reseteo del LSD [BUG corregido]
  if (contador != ultimoConteo){
    lcd_1.setCursor(0, 1);
    lcd_1.print(contador);
    ultimoConteo = contador;
  
  }
  //Si el pin está recibiendo voltaje, dará 1 (prendido) sino, dará 0 (apagado)
  int estado = digitalRead(11);
  
  
  //Variar el tiempo de reaccion en función del tiempo de juego
  if (millis() < 6000){
    //LLamadas a la función creada
    Velocidad_reaccion(12,1000,3000); //Dos segundos de reacción
  }
  
  if (millis() >= 6000 && millis() < 10000){
  	Velocidad_reaccion(12,1000,2000); //Un segundo de reaccion
  }
  
  if (millis() >= 10000 && millis() < 15000){
  	Velocidad_reaccion(12,1000,1500); //0,5 segundos de reaccion
  }
  
  
  //Validación del conteo de puntos
  if (estado == HIGH && apagado == 1){
  	contador++;
    apagado = 0;
    tiempoPrendido = millis();
  } else {
    //Tiempo de espera [BUG corregido]
    if(millis()-tiempoPrendido >= 20 && estado == LOW) {
      apagado = 1;
      
    } else {
      	/*Valido que se tenga que soltar el botón, sino lo que hará
        será actualizar 'tiempoPrendido' y nunca la diferencia dará
        mayor a 20*/
      	if (estado == HIGH) {
          tiempoPrendido = millis();
          
      }
      
    }
    
  } // Fin de todo el condicional
  
} //Cierre del loop