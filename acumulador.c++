// C++ code
//
void setup()
{
  Serial.begin(9600);
  pinMode(13,INPUT);
  Serial.print("Se inicio");

}
  int acc =0;
void loop()
{
   int boton= digitalRead(13);
  if(boton){
  Serial.println(boton);
  Serial.println("tocaste el boton");
  acc++;
  Serial.println(acc);

  }else{
  Serial.println("no tocaste el boton");

  }
}
