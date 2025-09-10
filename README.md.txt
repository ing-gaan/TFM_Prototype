# Diseño y desarrollo del prototipo del videojuego Prolifera
### Máster Universitario en Diseño y Desarrollo de Videojuegos
&nbsp;
&nbsp;
***
#### ⚠️ AVISO IMPORTANTE ⚠️

¡Gracias por jugar! Ten en cuenta que estás probando una versión en desarrollo del juego. Esto significa que:

- 🔧 **Faltan muchas funciones y contenido por implementar.**
- ⚖️ **El juego aún no está balanceado. Algunos aspectos pueden parecer demasiado fáciles, difíciles o injustos.**
- 🐞 **Pueden aparecer errores (bugs) que afecten la jugabilidad, el rendimiento o la experiencia general.**
- 🎮 **La experiencia final puede cambiar significativamente en futuras versiones.**
***

&nbsp;
## Controles del juego
El juego está diseñado para PC, por lo que los controles se basarán principalmente en el ratón y el teclado:

- **Movimiento**: Se podrá mover al organismo, en dos dimensiones, usando las teclas:
  - `W` y flecha arriba para movimiento hacia arriba.
  - `S` y flecha abajo para movimiento hacia abajo.
  - `A` y flecha izquierda para movimiento hacia la izquierda.
  - `D` y flecha derecha para movimiento hacia la derecha.
  - Si el jugador mueve el ratón de izquierda a derecha mientras mantiene presionado el botón derecho, el organismo rotará hasta que su frente quede apuntando a la posición en pantalla del cursor del ratón.

- **Selección**: El jugador hará clic sobre una célula para seleccionarla. Una vez seleccionada, aparecerá un panel con información y botones de opciones disponibles para esa célula.

### Acciones Celulares

- **Dividir**: Si una célula es seleccionada y tiene la opción de dividir habilitada, el jugador hará clic en este botón. Además, si hay espacio y cumple los requisitos de energía y límite de Hayflick, la célula se dividirá, y una nueva célula del mismo tipo aparecerá en el espacio adyacente elegido por el jugador.
- **Transformar/Diferenciar**: Si una célula totipotente es seleccionada y se elige la opción de transformar, se mostrará un menú con los tipos celulares disponibles. Luego, el jugador elegirá un tipo; entonces, la célula seleccionada se convertirá al tipo elegido.

### Navegación de Cámara

- Si el jugador mueve el ratón de izquierda a derecha mientras mantiene presionado el botón izquierdo, la cámara se desplazará de izquierda a derecha según el caso.
- Si la cámara se encuentra desplazada cuando el jugador pulse alguna tecla para mover al organismo, la cámara enfocará inmediatamente al organismo.
- Con el botón de scroll del ratón se hará **zoom in/out**.

## Referencias usadas en este prototipo

- **Sonido: Underwater [Loop] AMB.wav** - [Link](https://freesound.org/people/DCSFX/sounds/366159/)
- **Sonido: relaxation music #2.mp3** - [Link](https://freesound.org/people/ZHR%C3%98/sounds/520674/)
- **Sonido: waves underwater lake 140730_0319.flac** - [Link](https://freesound.org/people/klankbeeld/sounds/243825/)
- **Sonido: Dark Chillout (loop)** - [Link](https://freesound.org/people/SondreDrakensson/sounds/625384/)
- **Sonido: Cartoon drip or bubble pop, wet popping sound. Version 2** - [Link](https://www.zapsplat.com/music/cartoon-drip-or-bubble-pop-wet-popping-sound-version-2/)
- **Sonido: water splash** - [Link](https://pixabay.com/sound-effects/water-splash-88415/)
- **Low Poly Underwater World:** - [link](https://www.fab.com/listings/c97ca6e8-e5bd-4114-b2a6-513d38314d5e)