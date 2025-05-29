// C++ code
//
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd_1(0);
void setup()
{

  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.print("Puntos");
  pinMode(13,INPUT);
  Serial.print("Se inicio");

}
  int acc =0;
  unsigned long seg = 0;
void loop()
{
  seg= millis();
	
   int boton= digitalRead(13);
  if(boton){
  acc++;
  Serial.println(acc);

  }else{
  }
  if(seg >= 200){
   lcd_1.setCursor(0, 1);
  lcd_1.print(acc);
  lcd_1.setBacklight(1);
  lcd_1.setBacklight(0); 
  }
  

}
