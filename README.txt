# 🎮 Atrapa al Topo - Proyecto con Arduino

Este proyecto es una versión electrónica del clásico juego "Atrapa al Topo", desarrollado con Arduino UNO, servos, sensores ultrasónicos, una pantalla OLED y botones con LEDs. El objetivo es golpear al topo cuando aparece y sumar la mayor cantidad de puntos en el tiempo límite.


#🛠 Componentes Utilizados

- 1x Arduino UNO
- 1x Pantalla OLED 128x32 (I2C)
- 2x Servomotor SG90
- 2x Sensor ultrasónico HC-SR04
- 3x LEDs
- 3x Botones
- 3x Resistencias
- 1x Pulsador extra para iniciar el juego
- Protoboard

# 📋 Funcionalidades

- Menú de inicio con imagen y texto "PRESS START".
- 3 rondas de juego:
  1. Solo LEDs: el jugador debe presionar el botón correspondiente al LED encendido.
  2. LEDs + Topo aleatorio: se activa solo uno de los dos topos aleatoriamente.
  3. LEDs + Ambos topos: pueden activarse los dos topos al mismo tiempo.
- El topo aparece por un tiempo limitado y puede ser detectado por el sensor ultrasónico si el jugador lo "golpea".
- La puntuación se muestra en pantalla junto con el número de ronda y tiempo restante.
- Reinicio automático del juego tras finalizar, esperando nuevamente al botón de inicio.

#💡 Lógica del Juego

1. Pantalla de Inicio: Se muestra una imagen con la leyenda "PRESS START". El juego comienza cuando se presiona el botón de inicio.
2. LEDs: Se encienden al azar y el jugador debe presionar el botón correspondiente. Cada acierto suma 1 punto.
3. Topos:
   - Si el jugador golpea al topo (detectado por sensor ultrasónico), suma 2 puntos.
   - El topo se oculta luego de 3 segundos o tras ser golpeado.
4. Rondas: Cada ronda dura 7 segundos. Hay una pequeña pausa entre rondas con mensaje en pantalla.
5. Fin del Juego: Se muestra el puntaje final y se reinicia si se presiona el botón nuevamente.

# 🖼 Interfaz OLED

Se utiliza una pantalla OLED 128x32.
Se incluye un array bitmap con la imagen del topo en blanco y negro, mostrada al inicio del juego como parte del menú de espera. 
También hay texto informativo durante el juego. Las bibliotecas usadas son Adafruit_SSD1306 y Adafruit_GFX.

# 📂 Estructura del Código

- Variables globales: Configuración de pines, estados del juego, y tiempos de control.
- Funciones principales:
  - Menu(): Muestra la imagen de inicio.
  - Velocidad_reaccion(): Controla los LEDs según la ronda.
  - Tiempo_ronda(): Muestra y controla el cronómetro y estado de cada ronda.
  - ControlarTopo() y ControlarTopo2(): Manejan los servos y sensores ultrasónicos.
- *setup()*: Inicializa pantalla, servos, pines y muestra el menú.
- *loop()*: Controla la lógica del juego, las rondas, puntaje y reinicio.

# ✍ Autores

Desarrollado por Tomás Marcos, David Veron, Santiago Rautenberg y Carolina Benz.
