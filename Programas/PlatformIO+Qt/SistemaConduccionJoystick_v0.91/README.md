
# Sistema Conducción Joystick

El archivo principal es **ControlActuadoresJoystick_Retro.cpp**


# Referencia de pines

## Pines analógicos:

**A0: INPUT Analógica**. Joystick eje Y. Incremento acelera, decremento frena.
**A1: INPUT Analógica**. Josytick eje X. (Volante).
**A2: INPUT Analógica**. Pot actuador 1. (Freno).
**A3: INPUT Analógica**. Pot actuador 2. (Accel).

**A4: I2C SDA**

**A5: I2C SCL**


## Pines digitales:
**15: I2C SDA**: Comunicación con el extensor PCF.
**14: I2C SCL**: Comunicación con el extensor PCF.
13: SPI SCK   -> 5 encoder. **Pendiente de implementación**
12: SPI MISO  -> 3 encoder. **Pendiente de implementación**
11: SPI MOSI  <- 7 encoder. **Pendiente de implementación**
10: SPI CS    -> 2 encoder. **Pendiente de implementación**

9: Pin Paro de emergencia manual. **Pendiente de implementación**
**8: OUTPUT**. Tx Software serial. Hacia los Drivers de los motores.
**7: INPUT.** Rx Software Serial. Desde los Drivers de los motores.

6: INPUT. Para definir si el auto está encendido o no (Cuando el auto se apague se guarda la posición del volante). **Pendiente de implementación**
**5: OUTPUT** pinPalanca_Bajar. Pin para controlar el puebte H de la palanca.
**4: OUTPUT.** pinPalanca_Bajar. Pin para controlar el puente H de la palanca.



**3: OUTPUT**. **5V Virtual**. Para Validación de potenciómetros conectados.
**2: OUTPUT**. **GND Virtual**. Para Validación de potenciómetros conectados

**1: **Serial Tx
**0: **Serial Rx



### Extensor PCF 
(Nota: Asegurarse que el PCF tome voltaje de +5V no de las salidas digitales que se usan para verificar el comportamiento de los potenciómetros.)

**Entradas:**
    **P0: INPUT** Botón de fijar posición del freno (en caso de que se requiera frenar y acelerar al mismo tiempo).
    **P1: INPUT** Switch de mapeo completo de acelerador (para el modo carretera, también usarla para hacer el volante menos sensible en carretera).
        **Pendiente de implementar la sensibilidad del joystick **.
    **P2: INPUT** Botón Subir palanca de cambios.
    **P3: INPUT** Botón Bajar palanca de cambios.

**Salidas:** Códigos de Error e información en los LED del controller
    1 (P4): LED de información. (Disponible).
    2 (P5): LED de seguridad. Actuadores desconectados.
    3 (P6): LED de seguridad. Joystick desconectado o posible falso.
    4 (P7): LED de seguridad. Encoder desconectado. ** Pendiente de implementación **.


###  Joystick
```
        ^
        |
        |
  <----------->
        |
        |
        v
```
#### LEDs
L1  L2  L3  L4    // Este orden corresponde con la documentación.





# Calibración de los valores de umbral de los actuadores

Una vez calibrados los motores actualizar las siguientes variables:

actFreno_valorExtendido
actFreno_valorRetraido
actFreno_valorParoEmergencia

actAcel_valorExtendido
actAcel_valorRetraido



# Release Notes

## 0.9.1

En esta versión el actuador del freno puede tener retroalimentación con una resistencia variable (por ejemplo con los actuadores de Pololu o Servocity) o con un encoder (por ejemplo el actuador de GoBilda)


# Tareas futuras
**TODO**: Implementar lectura de status de los drivers DC para detectar sobretemperatura, etc. P2
**TODO**: Cambiar el orden de los pines para dejar el 2 para Serial y que sea compatible con ST NUCLEO.

## Standards
### NASA
### MISRA C
Motor Industry Software Reliability Association C Standard

### AUTOSAR