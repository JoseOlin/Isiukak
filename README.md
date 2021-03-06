# Sistema de Conducción Isiukak

Código, piezas 3D, diagramas y esquemáticos y  para replicar el **sistema Isiukak para conducción con Joystick**.

![](assets/imgs/Diagrama_General_Isiukak.png)

La carpeta **Programas** contiene dos carpetas. 
- **Arduino_PlatformIO** contiene el código en lenguaje Arduino para el microcontrolador del módulo de control. 
- **MonitorSerial_Qt** es un programa en C++/Qt para monitorear los valores del sistema en tiempo real.

![](assets/imgs/interfaz-monitor-serial.png)
Más detalles en el [archivo README.md de la carpeta Programas](Programas/README.md)

La carpeta **Componentes_3DParts_Schematics** contiene el diagrama general del sistema y los esquemáticos de cada subsistema, así como las piezas 3D necesarias y fotografías de las piezas construidas.

Si requieres más información acerca de los componentes del sistema puedes visitar la [página del proyecto Isiukak en Olin Robotics](https://www.olinrobotics.com/proyecto_isiukak)

# Estructura general del sistema

Los subsistemas del Isiukak son:

- Módulo de control

- Joystick

- Actuación de pedales, volante y palanca

Que se muestran a continuación.

![Esquema_General.png](./assets/imgs/Diagrama_General_Isiukak.png)

El **módulo de control** es la parte central, donde se realiza el procesamiento del sistema. Lee la  posición del *joystick* para controlar los pedales y el volante. 

El **eje vertical del joystick, controla el freno y el acelerador**, mientras que el **eje horizontal asiste en el movimiento del volante**. La palanca de cambios se  controla con dos botones ubicados en el mismo joystick.

Dos actuadores lineales controlan el freno y el acelerador, un tercer motor asiste en el movimiento del volante y otro actuador lineal asiste en el movimiento de la palanca.

Actualmente se tiene una prueba de concepto del sistema implementada en un Arduino UNO. La siguiente etapa portar el código a un microcontrolador de grado automotriz.


# Acerca del Software
Utilizamos [PlatformIO](https://platformio.org/) para la compilación del código en Arduino, con [Qt Creator](https://www.qt.io/product/development-tools) como editor.
 
El software se comparte con la mejor intención de que como comunidad desarrollemos tecnología de asistencia que nos permita una vida más autónoma, pero sin garantías. **Úsalo bajo tu propia responsabilidad**.

 Esperamos que te diviertas tanto como nosotros desarrollándolo. Que la Autonomía te acompañe.


## Versionado Semántico
Estamos en proceso de adoptar [versionado semántico (SemVer)](https://semver.org/) para la nomenclatura de las versiones liberadas.

Dada un número de versión MAYOR.MENOR.PATCH, se incrementa:
1. MAYOR cuando se hace un **cambio incompatible a la API**.
2. MENOR cuando se agrega funcionalidad compatible con versiones anteriores.
3. PATCH cuando se arreglan bugs compatibles con versiones anteriores.

Una versión MAYOR **0 indica que se está en las primeras etapas de desarrollo**, la API es inestable y puede tener muchos cambios.