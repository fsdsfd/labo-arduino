// C++ code
//
#include <Adafruit_LiquidCrystal.h>


//Variables
int apagado = 1;
int contador = 0;
unsigned long tiempo = 0;
unsigned long tiempoPrendido = 0;
Adafruit_LiquidCrystal lcd_1(0x20);


void setup()
{
  Serial.begin(9600);
  pinMode(12,OUTPUT); //(OUTPUT = Entrega voltaje)
  pinMode(11,INPUT); // (INPUT = Recibe voltaje)
  
  tiempo = millis();
  tiempoPrendido = millis();
  
  lcd_1.begin(16, 2);
  lcd_1.print("Contador");
}



void loop()
{
  
  lcd_1.setCursor(0, 1);
  lcd_1.print(contador);

  //Si el pin está recibiendo voltaje, dará 1 (prendido); sino, dará 0 (apagado)
  int estado = digitalRead(11);
  
  
  //Tiempo en donde no dará voltaje el pin [Inicio de condicional]
  if (millis() <= tiempo+1000){
  	digitalWrite(12,LOW);
    Serial.println("0 V");
    
  } else {
	//Tiempo en donde dará voltaje por 1seg (2000-1000 = 1000)
    if (millis() <= tiempo+2000){
    	digitalWrite(12,HIGH);
      Serial.println("5 V");
      
    } else {
      //Actualización del tiempo para repetir el ciclo
      tiempo = millis() ;
      
  	}
    
  } //Fin de todo el condicional
  
  
  //Validación del conteo de puntos [Inicio de condicional]
  if (estado == HIGH && apagado == 1){
  	contador++;
    apagado = 0;
    tiempoPrendido = millis();
  } else {
    //Tiempo de espera 
    if(millis()-tiempoPrendido >= 20) {
      apagado = 1;
      
    } else {
      	/*Valido que se tenga que soltar el botón, sino lo que hará
        será actualizar el tiempoPrendido y nunca la diferencia dará
        mayor a 20*/
      	if (estado == HIGH) {
          tiempoPrendido = millis();
          
      }
    }
  } // Fin de todo el condicional
  
} //Cierre del loop