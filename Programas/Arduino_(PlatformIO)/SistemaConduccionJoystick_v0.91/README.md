# Sistema Conducción Joystick

El archivo principal es **ControlActuadoresJoystick_Retro.cpp**

## Joystick

```
        ^
        |
        |
  <----------->  JyHor
        |
        |
        JyVer
```

### LEDs

|       | L1         | L2        | L3            | L4         |
| ----- | ---------- | --------- | ------------- | ---------- |
| Blkng | JyNoCentro | PotsDscn  | ActFueraRango | ActsNoMov  |
| Stdy  | AcelDscn   | JyHorDscn | FrenoDscn     | JyVerDescn |

## Botones

FijarPosiciónFreno

SubirPalanca

BajarPalanca

ModoCarretera

# Referencia de pines

## Pines analógicos:

**A0: INPUT Analógica**. Joystick eje Y. Incremento acelera, decremento frena.
**A1: INPUT Analógica**. Josytick eje X. (Volante).
**A2: INPUT Analógica**. Pot actuador 1. (Freno).
**A3: INPUT Analógica**. Pot actuador 2. (Accel).
**A4: INPUT Digital.** Botón Fijar Posición Freno
**A5: INPUT Digital.** Botón Subir Palanca.

## Pines digitales:

**15: I2C SDA**:  Conectado a A4 ó A5.
**14: I2C SCL**:  Conectado a A4 ó A5.
13: Pendiente de implementación
12: Pendiente de implementación
**11: INPUT.** Switch Modo Carretera.
**10: INPUT.** Botón Bajar Palanca.

**9: INPUT_PULLUP. PinParoManualEmergencia.**
**8: OUTPUT**. Tx Software serial. Hacia los Drivers de los motores.
**7: INPUT.** Rx Software Serial. Desde los Drivers de los motores.

6: INPUT. Implementar GND Virtual en este pin para liberar el 2 para comunicación del ST.
**5: OUTPUT. pinPalanca_Bajar.** Pin para controlar el puebte H de la palanca.
**4: OUTPUT. pinPalanca_Bajar.** Pin para controlar el puente H de la palanca.

**3: OUTPUT**. **5V Virtual**. Para Validación de potenciómetros conectados.
**2: OUTPUT**. **GND Virtual**. Para Validación de potenciómetros conectados

**1:** Serial Tx
**0:** Serial Rx



# Calibración del Sitema

## Actuadores

Actualizar las siguientes variables:

actFreno_valorExtendido
actFreno_valorRetraido
actFreno_valorParoEmergencia

actAcel_valorExtendido
actAcel_valorRetraido

# Configurar QtCreator para compilar código de Arduino con PlatformIO

Para facilitar el desarrollo en lugar de usar el IDE de Arduino se utiliza QtCreator con PlatformIO para compilar y editar el código.

Requiere instalación de Qt Creator y PlatformIO

pip3 install -U platformio

La sección **Projects** de Qt Creator debe configurarse de la siguiente forma.

## Build Settings

Edit build configuration: Debug

**Build directory:** El directorio donde esté **platform.ini**

**Buils Steps.** Borrar todos los items

Build steps → Custom Process Step.

- Command: `platformio`
- **Arguments**: `-f -c qtcreator run`
- **Working directory**: %{buildDir}

**Clean Steps.** ``Borrar todos los items
Add clean step → Custom Process step

- **Command**: `platformio`
- **Arguments**: `-f -c qtcreator run --target clean`
- **Working directory**`: ``%{buildDir}`

## Deploy  Settings

Project → Run → Deploy configuration → Add Deploy Step → Custom Process Step
 • **Command:** platformio
 • **Arguments**: run --target upload
 • **Working directory**: %{buildDir}

# Release Notes

## 0.9.1

En esta versión el actuador del freno puede tener retroalimentación con una resistencia variable (por ejemplo con los actuadores de Pololu o Servocity) o con un encoder (por ejemplo el actuador de GoBilda)

# Tareas futuras

**TODO**: Implementar lectura de status de los drivers DC para detectar sobretemperatura, etc. P2
**TODO**: Cambiar el orden de los pines para dejar el 2 para Serial y que sea compatible con ST NUCLEO.

# Standards a Considerar

## MISRA C

Motor Industry Software Reliability Association C Standard

## AUTOSAR

## NASA (Código)
