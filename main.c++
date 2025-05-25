// C++ code
//
int ledcito=13;
void setup()
{
  Serial.begin(8600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, OUTPUT);
  Serial.print("INICIÉ EL PUERTO SERIE");

}

void loop()
{
	  
  	int lecturaAnalogica= analogRead(A0);
    if (lecturaAnalogica){
    Serial.println(lecturaAnalogica);
  }
      Serial.println(lecturaAnalogica);

}