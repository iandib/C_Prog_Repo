# TETRIS

Trabajo Práctico Final de la materia **Programación I**, correspondiente al segundo cuatrimestre de la carrera **Ingeniería Electrónica** en el Instituto Tecnológico de Buenos Aires (ITBA).

Este proyecto implementa el juego Tetris, adaptado para ejecutarse tanto en PC (Windows y Linux) como en Raspberry Pi con una matriz de 16x10 LEDs. Se desarrolló respetando las reglas originales del juego, incorporando funcionalidades adicionales y utilizando una estructura modular organizada en Back-End y Front-End.

---

## 📂 **Estructura del Proyecto**

- **Back_End/** 
   Contiene todos los archivos encargados de la lógica del juego y algunas definiciones comunes.  

- th2_display_sound.c y th2_display_sound.h 
   Estos archivos gestionan el **Front-End** del juego. Incluyen la visualización de las piezas en la pantalla/matriz LED y la coordinación de sonidos a través de un segundo thread.
   > Estos archivos se encuentran en la carpeta principal del proyecto.

---

## 🎮 **Características del Juego**

El programa cumple con todos los requisitos fundamentales del juego Tetris:
- Generación de piezas aleatorias.
- Movimientos de las piezas: lateral, vertical (hacia abajo) y rotación.
- Eliminación de líneas completas y otorgamiento de puntaje.
- Progresión de niveles según el puntaje acumulado.
- Fin del juego al llegar a la altura máxima.

**Funciones Adicionales**
- Sonidos y animaciones originales del juego.
- Cambio de color de las piezas según el nivel actual.
- Posibilidad de guardar la partida y retomarla posteriormente, incluso tras regresar al menú.
- Detección de récords: al finalizar la partida, el programa muestra si el puntaje obtenido es el nuevo máximo registrado.

---

## 🛠️ **Compilación del Proyecto**

El proyecto incluye un Makefile con una bandera dinámica que permite compilar el programa tanto para PC como para Raspberry Pi cambiando únicamente el target de compilación.

### 📌 **Dependencias**

   1. En PC (Linux/Windows) se utiliza la biblioteca **Allegro** para gráficos, fuentes, imágenes y audio:
      ```bash
      -lallegro
      -lallegro_primitives
      -lallegro_image
      -lallegro_font
      -lallegro_ttf
      -lallegro_audio
      -lallegro_acodec
      ```

   2. Raspberry Pi utiliza dos bibliotecas para manejar el display, los controles y el audio. 
   - **Joydisp Library** detecta y maneja el joystick:
      ```bash
      ../libs/joydisp/joydrv.o  
      ../libs/joydisp/disdrv.o
      ```  
   - **SDL2 Audio Library** gestiona el sonido:  
      ```bash
      ../libs/audio/SDL2/libAudioSDL2.o
      ``` 

### 🔧 **Cómo Compilar**

1. Navegar al directorio raíz del proyecto
   ```bash
   cd /path/to/Tetris
   ```

2. Compilar para PC
   Utiliza el target `tetris_pc`. La plataforma (Linux o Windows) se detecta automáticamente:
   ```bash
   make tetris_pc
   ```

   Esto genera un ejecutable llamado `tetris_pc`.

3. Compilar para Raspberry Pi
   Utiliza el target `tetris_rpi`:
   ```bash
   make tetris_rpi
   ```

   Esto genera un ejecutable llamado `tetris_rpi`, optimizado para la Raspberry Pi.

---

## 🚀 **Ejecución del Programa**

1. En PC (Linux/Windows) ejecutar el archivo compilado:
   ```bash
   ./tetris_pc
   ```

2. En Raspberry Pi ejecutar el archivo compilado con permisos de acceso a hardware:
   ```bash
   sudo ./tetris_rpi
   ```

---

## 🖥️ **Modo de Uso**

1. Inicio del juego:
   Al iniciar, el programa muestra un menú principal. Si no hay una partida cargada, se inicia una nueva.

2. Controles en PC:
   - Movimiento lateral: Flechas izquierda/derecha.
   - Movimiento vertical: Flecha abajo.
   - Rotar pieza: Flecha arriba.
   - Pausa: Tecla `ESC`.

3. Controles en Raspberry Pi:
   - ???

---

## 📜 **Notas Finales**

- El programa está diseñado para ser portable y ejecutarse en diferentes plataformas sin cambios adicionales en el código fuente.  
- Gracias a la estructura modular del proyecto y el uso de threads, se logra una separación eficiente entre la lógica del juego y la visualización/sonidos, permitiendo sincronización sin interferencias.  
- Se implementaron buenas prácticas de programación, con manejo adecuado de memoria y concurrencia mediante semaforización.

---

## ✒️ **Autores**

- Juan Ignacio Caorsi
- Ian Antonio Dib
- Tomás Luchelli
- Rita Moschini
